// Differential harness: the original machine code runs in tools/emu/emu.py and the ported body
// runs here, both on the same bytes at the same address, so the only difference is the code.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include "modules/syndicate/src/synlift.h"
#include "modules/syndicate/src/synlift_stage.h"

using namespace tq;
static const uintptr_t SCRATCH = 0x300000000ULL;
static const size_t SCRATCH_SIZE = 0x20000;

static uint64_t splitmix(uint64_t& s) {
    uint64_t z = (s += 0x9e3779b97f4a7c15ULL);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}
static uint32_t crc32(const void* p, size_t n) {
    static uint32_t tab[256]; static bool init = false;
    if (!init) { for (uint32_t i = 0; i < 256; i++) { uint32_t c = i; for (int k = 0; k < 8; k++) c = (c & 1) ? 0xedb88320u ^ (c >> 1) : c >> 1; tab[i] = c; } init = true; }
    const uint8_t* b = (const uint8_t*)p; uint32_t c = 0xffffffffu;
    for (size_t i = 0; i < n; i++) c = tab[(c ^ b[i]) & 0xff] ^ (c >> 8);
    return c ^ 0xffffffffu;
}

static void case_141740e80() {
    uint64_t s = 0x141740e80ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x141740e80ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_141740e80(rcx, rdx, r8, r9);
        std::printf("141740e80 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_141763e04() {
    uint64_t s = 0x141763e04ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x141763e04ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_141763e04(rcx, rdx, r8, r9);
        std::printf("141763e04 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_141763feb() {
    uint64_t s = 0x141763febULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x141763febULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_141763feb(rcx, rdx, r8, r9);
        std::printf("141763feb %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_141788c20() {
    uint64_t s = 0x141788c20ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x141788c20ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_141788c20(rcx, rdx, r8, r9);
        std::printf("141788c20 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_14179db30() {
    uint64_t s = 0x14179db30ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x14179db30ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_14179db30(rcx, rdx, r8, r9);
        std::printf("14179db30 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_1417a4180() {
    uint64_t s = 0x1417a4180ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x1417a4180ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_1417a4180(rcx, rdx, r8, r9);
        std::printf("1417a4180 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_1417ac510() {
    uint64_t s = 0x1417ac510ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x1417ac510ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_1417ac510(rcx, rdx, r8, r9);
        std::printf("1417ac510 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_1417b07c0() {
    uint64_t s = 0x1417b07c0ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x1417b07c0ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_1417b07c0(rcx, rdx, r8, r9);
        std::printf("1417b07c0 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_141821720() {
    uint64_t s = 0x141821720ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x141821720ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_141821720(rcx, rdx, r8, r9);
        std::printf("141821720 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
static void case_141821741() {
    uint64_t s = 0x141821741ULL;
    for (int c = 0; c < 8; c++) {
        uint8_t* buf = (uint8_t*)SCRATCH;
        uint64_t f = 0x141821741ULL * 0x100 + c;
        for (size_t i = 0; i < SCRATCH_SIZE; i += 8) { uint64_t v = splitmix(f); std::memcpy(buf + i, &v, 8); }
        uint64_t rcx = SCRATCH + (splitmix(s) % 0x800), rdx = SCRATCH + (splitmix(s) % 0x800);
        uint64_t r8 = SCRATCH + (splitmix(s) % 0x800), r9 = SCRATCH + (splitmix(s) % 0x800);
        uint64_t rax = SynLift_141821741(rcx, rdx, r8, r9);
        std::printf("141821741 %d %llx %08x\n", c, (unsigned long long)rax, crc32((void*)SCRATCH, SCRATCH_SIZE));
    }
}
int main() {
    void* p = mmap((void*)SCRATCH, SCRATCH_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
    if (p != (void*)SCRATCH) { std::printf("mmap failed\n"); return 2; }
    static void (*const cases[])() = { case_141740e80, case_141763e04, case_141763feb, case_141788c20, case_14179db30, case_1417a4180, case_1417ac510, case_1417b07c0, case_141821720, case_141821741 };
    static const char* const names[] = { "141740e80", "141763e04", "141763feb", "141788c20", "14179db30", "1417a4180", "1417ac510", "1417b07c0", "141821720", "141821741" };
    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        pid_t pid = fork();
        if (pid == 0) { cases[i](); std::fflush(stdout); _exit(0); }
        int st = 0; waitpid(pid, &st, 0);
        if (!WIFEXITED(st) || WEXITSTATUS(st) != 0) { std::printf("%s CRASH\n", names[i]); std::fflush(stdout); }
    }
    return 0;
}
