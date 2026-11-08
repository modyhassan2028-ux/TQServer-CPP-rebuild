// Differential driver: run lifted bodies on a fixed, printable state so an independent emulator
// (unicorn, in tools/bulk/diff_test.py) can execute the original bytes from the same state and
// compare. Nothing here decides correctness; it only reports state in and state out.
//
// The stack lives in a static frame inside the body, so its address is printed rather than chosen:
// the emulator maps that same address and sets RSP to the same value.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include "tests/lift_smoke_table.h"

struct Sec { uintptr_t va; size_t size; size_t off; };
const Sec kSecs[] = {
    {0x141721000ULL, 0x10100eULL, 0x400ULL},
    {0x141823000ULL, 0x6067dULL, 0x101600ULL},
    {0x141884000ULL, 0x2e00ULL, 0x161e00ULL},
};
bool g_image = false;

void map_image() {
    int fd = open("/app/work/orig_extract/Source/Syndicate.dll", O_RDONLY);
    if (fd < 0) return;
    bool all = true;
    for (const Sec& s : kSecs) {
        void* p = mmap(reinterpret_cast<void*>(s.va), s.size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_FIXED_NOREPLACE | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED) { all = false; break; }
        if (pread(fd, p, s.size, static_cast<off_t>(s.off)) < 0) { all = false; break; }
    }
    close(fd);
    g_image = all;
}

extern "C" uint64_t* ml_image_slot(uintptr_t a) {
    if (!g_image) return nullptr;
    for (const Sec& s : kSecs) {
        if (a >= s.va && a + 8 <= s.va + s.size && (a & 7) == 0) return reinterpret_cast<uint64_t*>(a);
    }
    return nullptr;
}

uint64_t g_rsp = 0;
uintptr_t g_rsp_addr = 0;

extern "C" void ml_entry_rsp(uintptr_t a, uint64_t rsp) {
    (void)a;
    // the outermost body only: an inner body reached through a seam reports its own frame
    if (g_rsp_addr == 0) { g_rsp = rsp; g_rsp_addr = rsp; }
}

namespace {

// fixed buffers: a hex dump that cannot be resized is one less thing to go wrong in a process
// that has just executed arbitrary lifted code
struct Sink {
    char buf[0x3000];
    size_t n = 0;
    void hex(const void* p, size_t bytes) {
        const unsigned char* b = static_cast<const unsigned char*>(p);
        static const char* d = "0123456789abcdef";
        for (size_t i = 0; i < bytes && n + 2 < sizeof(buf); ++i) {
            buf[n++] = d[b[i] >> 4];
            buf[n++] = d[b[i] & 15];
        }
        buf[n] = 0;
    }
};

uint64_t g_init[16];
uint64_t g_scratch_addr = 0;
unsigned char g_scratch[0x2000];

}  // namespace

int main(int argc, char** argv) {
    map_image();
    // an inner call goes through g_fnLIFT_<addr>; point every seam at the lifted body
    typedef uint64_t (*SeamFn)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
    for (unsigned i = 0; i < kLiftSeamCount; ++i) {
        if (kLiftSeams[i].slot) {
            *reinterpret_cast<SeamFn*>(kLiftSeams[i].slot) =
                reinterpret_cast<SeamFn>(kLiftSeams[i].body);
        }
    }
    if (argc < 2) { std::fprintf(stderr, "usage: %s <addr> [seed]\n", argv[0]); return 2; }
    unsigned seed = argc > 2 ? static_cast<unsigned>(std::strtoul(argv[2], nullptr, 0)) : 1;
    std::vector<uint64_t> wanted;
    {
        uint64_t one = std::strtoull(argv[1], nullptr, 0);
        if (one) wanted.push_back(one);
    }

    // the image is mapped by the smoke harness's helper when available; here the emulator reads the
    // same bytes from the same addresses, so the model must see them too
    std::printf("{\"scratch\":%llu,\"stack\":%llu,\"seed\":%u}\n",
                static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(g_scratch)),
                static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(g_init)), seed);
    std::fflush(stdout);   // survives a crash inside the body that follows

    for (uint64_t a : wanted) {
        const LiftBody* body = nullptr;
        for (unsigned i = 0; i < kLiftBodyCount; ++i) {
            if (kLiftBodies[i].addr == a) { body = &kLiftBodies[i]; break; }
        }
        if (!body) continue;
        // deterministic input: every register gets a pattern, pointers land in the scratch area
        unsigned s = seed ^ static_cast<unsigned>(a);
        auto next = [&s]() { s = s * 1103515245u + 12345u; return static_cast<uint64_t>(s); };
        g_init[0] = reinterpret_cast<uintptr_t>(g_scratch) + (next() % 0x400);
        g_init[1] = reinterpret_cast<uintptr_t>(g_scratch) + (next() % 0x400);
        g_init[2] = reinterpret_cast<uintptr_t>(g_scratch) + (next() % 0x400);
        g_init[3] = reinterpret_cast<uintptr_t>(g_scratch) + (next() % 0x400);
        for (int i = 4; i < 16; ++i) g_init[i] = next();
        std::memset(g_scratch, 0, sizeof(g_scratch));
        for (size_t i = 0; i < sizeof(g_scratch); i += 8) {
            uint64_t v = next();
            std::memcpy(g_scratch + i, &v, 8);
        }
        g_rsp_addr = 0;
        std::printf("{\"addr\":%llu", static_cast<unsigned long long>(a));
        std::printf(",\"init\":[");
        for (int i = 0; i < 16; ++i) std::printf("%s%llu", i ? "," : "",
                                                 static_cast<unsigned long long>(g_init[i]));
        std::printf("],\"ra\":%llu", static_cast<unsigned long long>(
                    body->fn(g_init[0], g_init[1], g_init[2], g_init[3])));
        Sink sink;
        std::printf(",\"scratch\":\"");
        sink.hex(g_scratch, 0x800);
        std::printf("%s", sink.buf);

        Sink s2;
        if (g_rsp_addr) {
            s2.hex(reinterpret_cast<const void*>(g_rsp_addr - 0x200), 0x400);
        } else {
            std::memset(s2.buf, '0', 0x800);
            s2.buf[0x800] = 0;
        }
        std::printf("\",\"scratch_len\":%zu", sink.n);
        std::printf(",\"stack\":\"%s\"}\n", s2.buf);
        std::fflush(stdout);
    }
    return 0;
}
