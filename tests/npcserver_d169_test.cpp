// D169 — version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp, FUN_1400017b0 @ 0x1400017b0.
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include "version/cqserver-78.0.11-1204/npcserver/clientsocket.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_logs = 0, g_ctors = 0, g_dtors = 0, g_slots = 0, g_ctorId = 0;
static char g_kind[32] = {0}, g_expr[64] = {0}, g_file[160] = {0};
static int g_line = 0;
static void* g_kernel = nullptr;
static void* g_slotThis = nullptr; static uint16_t g_slotId = 0; static void* g_slotData = nullptr;
static unsigned int g_slotLen = 0; static uint32_t g_slotU4 = 0;
static int g_stateOnSlot = -1;

static void LogHook(const void* m, ...) {
    ++g_logs;
    assert(m == (const void*)&g_symNpcStr_1400be0b0);
    va_list ap; va_start(ap, m);
    const char* kind = va_arg(ap, const char*);
    const char* expr = va_arg(ap, const char*);
    const char* file = va_arg(ap, const char*);
    int line = va_arg(ap, int);
    va_end(ap);
    std::snprintf(g_kind, sizeof g_kind, "%s", kind);
    std::snprintf(g_expr, sizeof g_expr, "%s", expr);
    std::snprintf(g_file, sizeof g_file, "%s", file);
    g_line = line;
}
static void* KernelHook(long long h) { (void)h; return g_kernel; }
static void CtorHook(void* p, int id) { (void)p; ++g_ctors; g_ctorId = id; }
static void DtorHook(void* p) { (void)p; ++g_dtors; }

static unsigned char* g_obj = nullptr;
static void Slot3(void* self, uint16_t id, void* data, unsigned int len, uint32_t u4) {
    ++g_slots; g_slotThis = self; g_slotId = id; g_slotData = data; g_slotLen = len; g_slotU4 = u4;
    if (g_stateOnSlot >= 0) *(int*)(g_obj + 0x830) = g_stateOnSlot;
}

static unsigned char* MakeSocket(int nCount, int nState, unsigned short uSize, unsigned short uId, uint32_t u4) {
    unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
    *(int*)(p + 0x814) = nCount;
    *(int*)(p + 0x830) = nState;
    *(unsigned short*)(p + 0x14) = uSize;
    *(unsigned short*)(p + 0x16) = uId;
    *(uint32_t*)(p + 0x18) = u4;
    for (int i = 0; i < 0x40; ++i) p[0x1c + i] = (unsigned char)(0x60 + i);
    return p;
}

static void Reset(void) {
    g_logs = g_ctors = g_dtors = g_slots = 0;
    g_kind[0] = g_expr[0] = g_file[0] = 0; g_line = 0; g_stateOnSlot = -1;
}

int main() {
    void* vtbl[6] = { nullptr, nullptr, nullptr, (void*)&Slot3, nullptr, nullptr };
    void* kernelObj[1] = { (void*)vtbl };          // the object's first word is its table
    g_kernel = kernelObj;

    g_pfnNpcInlineLogError = &LogHook;
    g_pfnNpcKernelFrom_1400022e0 = &KernelHook;
    g_pfnNpcTickAnalystCtor = &CtorHook;
    g_pfnNpcTickAnalystDtor = &DtorHook;

    const char* kPath = "f:\\version\\cqserver-78.0.11-1204\\npcserver\\clientsocket.cpp";

    // no kernel thread: CHECK m_pKernelThread at 0x184
    {
        unsigned char* p = MakeSocket(0, 2, 0, 0, 0);
        Reset();
        FUN_1400017b0((long long)p);
        assert(g_logs == 1 && std::strcmp(g_kind, "CHECK") == 0);
        assert(std::strcmp(g_expr, "m_pKernelThread") == 0);
        assert(std::strcmp(g_file, kPath) == 0 && g_line == 0x184);
        assert(g_ctors == 0 && g_slots == 0);
        std::free(p);
    }

    // a kernel thread that yields no kernel: CHECK pKernel at 0x187
    {
        unsigned char* p = MakeSocket(0, 2, 0, 0, 0);
        *(long long*)(p + 0x828) = 0x1234;
        Reset(); g_kernel = nullptr;
        FUN_1400017b0((long long)p);
        assert(g_logs == 1 && std::strcmp(g_expr, "pKernel") == 0 && g_line == 0x187);
        g_kernel = kernelObj;
        std::free(p);
    }

    // not connected, and connected with nothing buffered
    {
        unsigned char* p = MakeSocket(40, 1, 12, 0, 0);
        *(long long*)(p + 0x828) = 0x1234;
        Reset(); FUN_1400017b0((long long)p);
        assert(g_logs == 0 && g_ctors == 0 && g_slots == 0);
        *(int*)(p + 0x830) = 2; *(int*)(p + 0x814) = 0;
        Reset(); FUN_1400017b0((long long)p);
        assert(g_logs == 0 && g_ctors == 0 && g_slots == 0);
        std::free(p);
    }

    // too little buffered for the 9-byte minimum header
    {
        unsigned char* p = MakeSocket(8, 2, 12, 0, 0);
        *(long long*)(p + 0x828) = 0x1234;
        Reset(); FUN_1400017b0((long long)p);
        assert(g_logs == 0 && g_ctors == 0 && g_slots == 0);
        std::free(p);
    }

    // the packet length must be within the buffered bytes
    {
        unsigned char* p = MakeSocket(10, 2, 12, 0, 0);
        *(long long*)(p + 0x828) = 0x1234;
        Reset(); FUN_1400017b0((long long)p);
        assert(g_ctors == 0 && g_slots == 0);
        std::free(p);
    }

    // below 4 bytes and above 0x400 are both refused after the buffered check
    {
        unsigned char* p = MakeSocket(10, 2, 3, 0, 0);
        *(long long*)(p + 0x828) = 0x1234;
        Reset(); FUN_1400017b0((long long)p);
        assert(g_ctors == 0);
        *(unsigned short*)(p + 0x14) = 0x401; *(int*)(p + 0x814) = 0x500;
        Reset(); FUN_1400017b0((long long)p);
        assert(g_ctors == 0);
        std::free(p);
    }

    // one packet: the analyst brackets the virtual call, the payload is this+0x1c, length is size-8
    {
        unsigned char* p = MakeSocket(20, 2, 12, 0x7788, 0xDEADBEEF);
        *(long long*)(p + 0x828) = 0x1234;
        g_obj = p;
        Reset();
        FUN_1400017b0((long long)p);
        assert(g_ctors == 1 && g_ctorId == 0x4e && g_dtors == 1);
        assert(g_slots == 1);
        assert(g_slotThis == (void*)kernelObj && g_slotId == 0x7788);
        assert(g_slotData == (void*)(p + 0x1c) && g_slotLen == 4 && g_slotU4 == 0xDEADBEEF);
        assert(*(int*)(p + 0x814) == 8);              // twelve bytes consumed
        assert(g_logs == 0);                          // the loop stopped at the <9 check
        std::free(p);
    }

    // the virtual call drops the connection, so ClearPacket reports failure and IF_NOT logs at 0x1a7
    {
        unsigned char* p = MakeSocket(24, 2, 12, 1, 2);
        *(long long*)(p + 0x828) = 0x1234;
        g_obj = p;
        Reset(); g_stateOnSlot = 0;
        FUN_1400017b0((long long)p);
        assert(g_slots == 1 && g_ctors == 1 && g_dtors == 1);
        assert(g_logs == 1 && std::strcmp(g_kind, "IF_NOT") == 0);
        assert(std::strcmp(g_expr, "this->ClearPacket(nNetPacketSize)") == 0);
        assert(std::strcmp(g_file, kPath) == 0 && g_line == 0x1a7);
        std::free(p);
    }

    std::printf("NPCSERVER_D169_OK: clientsocket.cpp FUN_1400017b0\n");
    return 0;
}
