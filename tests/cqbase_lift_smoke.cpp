// Smoke harness: runs every lifted body once in a forked child, on a mapped stack, and records
// what happened. This is the first pass that is not a per-family fixture: it answers "does the
// body execute at all" for the whole module, one body per process, so a fault in one body cannot
// hide the rest.
//
// Zeroed arguments are deliberate. A body that dereferences its argument faults, and that is a
// true answer: it needs a real object before it can be exercised. What matters here is that a
// fault is isolated, attributed to an address, and distinguishable from a body that loops forever.
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <ucontext.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tests/lift_smoke_table.h"

namespace {

// The reference model addresses globals by their virtual address. Mapping the real sections means
// those reads and writes land on the bytes the DLL was built with instead of on a zero shadow.
struct Section { uintptr_t va; size_t size; size_t off; };
const Section kSections[] = {
    {0x141721000ULL, 0x10100eULL, 0x400ULL},      // .text
    {0x141823000ULL, 0x6067dULL, 0x101600ULL},    // .rdata
    {0x141884000ULL, 0x2e00ULL, 0x161e00ULL},     // .data
};
bool g_image_ready = false;

void map_image() {
    const char* dll = "/app/work/orig_extract/Source/Syndicate.dll";
    int fd = open(dll, O_RDONLY);
    if (fd < 0) return;
    bool all = true;
    for (const Section& s : kSections) {
        void* p = mmap(reinterpret_cast<void*>(s.va), s.size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_FIXED_NOREPLACE | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED) { all = false; break; }
        ssize_t got = pread(fd, p, s.size, static_cast<off_t>(s.off));
        if (got < 0) { all = false; break; }
    }
    close(fd);
    g_image_ready = all;
}

unsigned char* g_hits = nullptr;   // shared with the children, so a fork's marks are visible here
int g_fault_fd = -1;

void fault_handler(int sig, siginfo_t* info, void* ctx) {
    char buf[96];
    uintptr_t rip = 0;
    if (ctx) rip = static_cast<uintptr_t>(static_cast<ucontext_t*>(ctx)->uc_mcontext.gregs[REG_RIP]);
    int n = std::snprintf(buf, sizeof(buf), "%d:%llx:%llx", sig,
                          static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(info->si_addr)),
                          static_cast<unsigned long long>(rip));
    if (g_fault_fd >= 0 && n > 0) {
        ssize_t ignored = write(g_fault_fd, buf, static_cast<size_t>(n));
        (void)ignored;
    }
    _exit(2);
}

const char* signal_name(int sig) {
    switch (sig) {
        case SIGSEGV: return "segv";
        case SIGBUS:  return "bus";
        case SIGFPE:  return "fpe";
        case SIGILL:  return "ill";
        case SIGALRM: return "timeout";
        case SIGABRT: return "abort";
        default:      return "signal";
    }
}

}  // namespace

extern "C" void ml_hit(uintptr_t a) {
    // the table is sorted by address, so a binary search finds the body that just ran
    unsigned lo = 0, hi = kLiftBodyCount;
    while (lo < hi) {
        unsigned mid = (lo + hi) / 2;
        if (kLiftBodies[mid].addr < a) lo = mid + 1;
        else hi = mid;
    }
    if (lo < kLiftBodyCount && kLiftBodies[lo].addr == a) g_hits[lo] = 1;
}

extern "C" uint64_t* ml_image_slot(uintptr_t a) {
    if (!g_image_ready) return nullptr;
    for (const Section& s : kSections) {
        if (a >= s.va && a + 8 <= s.va + s.size && (a & 7) == 0) return reinterpret_cast<uint64_t*>(a);
    }
    return nullptr;
}

int main(int argc, char** argv) {
    unsigned first = 0, last = kLiftBodyCount;
    bool arena = (argc >= 4 && (std::strcmp(argv[3], "arena") == 0 || std::strcmp(argv[3], "pointers") == 0));
    bool self_pointers = (argc >= 4 && std::strcmp(argv[3], "pointers") == 0);
    bool roots_only = (argc >= 5 && std::strcmp(argv[4], "roots") == 0);
    if (argc >= 3) {
        first = static_cast<unsigned>(std::strtoul(argv[1], nullptr, 0));
        last = static_cast<unsigned>(std::strtoul(argv[2], nullptr, 0));
        if (last > kLiftBodyCount) last = kLiftBodyCount;
    }

    map_image();
    g_hits = static_cast<unsigned char*>(mmap(nullptr, kLiftBodyCount, PROT_READ | PROT_WRITE,
                                             MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    if (g_hits == MAP_FAILED) return 1;
    // wire every seam to the lifted body at that address, so an inner call lands on lifted code
    typedef uint64_t (*SeamFn)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
    unsigned bound = 0;
    for (unsigned i = 0; i < kLiftSeamCount; ++i) {
        if (!kLiftSeams[i].slot) continue;
        *reinterpret_cast<SeamFn*>(kLiftSeams[i].slot) = reinterpret_cast<SeamFn>(kLiftSeams[i].body);
        ++bound;
    }
    unsigned ran = 0, clean = 0, distinct = 0;
    unsigned by_signal[32] = {0};
    FILE* csv = std::fopen("tools/bulk/smoke_status.csv", "w");
    if (csv) std::fprintf(csv, "addr,status,accessed,ip\n");

    for (unsigned i = first; i < last; ++i) {
        const LiftBody& b = kLiftBodies[i];
        if (roots_only) {
            bool is_target = false;
            for (unsigned k = 0; k < kLiftSeamCount; ++k) {
                if (kLiftSeams[k].addr == b.addr) { is_target = true; break; }
            }
            if (is_target) continue;   // this body is reached from another, so start elsewhere
        }
        int fds[2] = {-1, -1};
        if (pipe(fds) != 0) return 1;
        pid_t pid = fork();
        if (pid == 0) {
            // child: report the faulting address through the pipe, then run the body
            close(fds[0]);
            g_fault_fd = fds[1];
            struct sigaction sa;
            std::memset(&sa, 0, sizeof(sa));
            sa.sa_sigaction = fault_handler;
            sa.sa_flags = SA_SIGINFO;
            sigaction(SIGSEGV, &sa, nullptr);
            sigaction(SIGBUS, &sa, nullptr);
            sigaction(SIGFPE, &sa, nullptr);
            sigaction(SIGILL, &sa, nullptr);
            alarm(1);
            static unsigned char scratch[1 << 20];
            std::memset(scratch, 0, sizeof(scratch));
            static unsigned char arenaMem[0x10000];
            std::memset(arenaMem, 0, sizeof(arenaMem));
            if (self_pointers) {
                // every word points back into the arena, so following a field lands in mapped memory;
                // a body that invents an address still faults, and that is the remaining signal
                uint64_t base = reinterpret_cast<uint64_t>(arenaMem);
                for (size_t off = 0; off + 8 <= sizeof(arenaMem); off += 8) {
                    uint64_t target = base + (off * 3) % (sizeof(arenaMem) - 0x100);
                    std::memcpy(arenaMem + off, &target, 8);
                }
            }
            volatile uint64_t sink;
            if (arena) {
                // a zeroed but mapped object per argument: a body that only walks its fields runs,
                // a body that invents an address does not
                sink = b.fn(reinterpret_cast<uint64_t>(arenaMem),
                            reinterpret_cast<uint64_t>(arenaMem) + 0x1000,
                            reinterpret_cast<uint64_t>(arenaMem) + 0x2000,
                            reinterpret_cast<uint64_t>(arenaMem) + 0x3000);
            } else {
                sink = b.fn(0, 0, 0, 0);
            }
            (void)sink;
            _exit(0);
        }
        close(fds[1]);
        char fault[64] = {0};
        ssize_t got = read(fds[0], fault, sizeof(fault) - 1);
        if (got < 0) got = 0;
        fault[got] = 0;
        close(fds[0]);
        int status = 0;
        waitpid(pid, &status, 0);
        ++ran;
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            ++clean;
            if (csv) std::fprintf(csv, "0x%llx,ok,,\n", static_cast<unsigned long long>(b.addr));
        } else {
            int sig = WIFSIGNALED(status) ? WTERMSIG(status) : 0;
            if (sig >= 0 && sig < 32) ++by_signal[sig];
            char* fa = nullptr;
            char* fr = nullptr;
            char ripbuf[32] = {0};
            if (fault[0]) {
                char* c1 = std::strchr(fault, ':');
                if (c1) {
                    fa = c1 + 1;
                    char* c2 = std::strchr(fa, ':');
                    if (c2) {
                        std::snprintf(ripbuf, sizeof(ripbuf), "%.*s", static_cast<int>(c2 - fa), fa);
                        fr = c2 + 1;
                    }
                }
            }
            if (csv) std::fprintf(csv, "0x%llx,%s,%s,%s\n", static_cast<unsigned long long>(b.addr),
                                 fault[0] ? signal_name(atoi(fault)) : (sig ? signal_name(sig) : "exit"),
                                 ripbuf, fr);
        }
    }
    if (csv) std::fclose(csv);

    for (unsigned i = 0; i < kLiftBodyCount; ++i) distinct += g_hits[i] ? 1 : 0;
    std::printf("bodies=%u seams_bound=%u clean=%u distinct_reached=%u\n", ran, bound, clean, distinct);
    for (int s = 0; s < 32; ++s) {
        if (by_signal[s]) std::printf("  %-8s %u\n", signal_name(s), by_signal[s]);
    }
    std::printf("SMOKE_DONE: %u ran, %u clean\n", ran, clean);
    return 0;
}
