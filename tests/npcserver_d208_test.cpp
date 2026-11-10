// D208 — NpcServer.exe 0x1400776c0 (range wrapper), 0x1400777a0 (parse range), 0x1400778c0 (consume).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

namespace {
int g_seq[16]; int g_seqN = 0;
void Note(int n) { if (g_seqN < 16) g_seq[g_seqN] = n; ++g_seqN; }   // by position, not by value

long long g_wrapper = 0; long long g_wrapperData = 0; int g_wrapperLen = 0;
int g_valid = 1; int g_targetVal = 0;
void* g_vt[10];

void BuildWrapper(void* w, const char* pszData, int nLen) {   // 0x1400776c0 is real; this seam is unused here
    (void)w; (void)pszData; (void)nLen; Note(99);
}
unsigned char ParseSlot(long long* pMsg, void* src) { (void)pMsg; (void)src; Note(1); return 1; }
unsigned char InitSlot(long long* pMsg) { (void)pMsg; Note(2); return 1; }
unsigned char ValidSlot(long long* pMsg) { (void)pMsg; Note(3); return 1; }
int ConsumeVal = 0;
void ConsumeSlot(long long p, int n) { ConsumeVal = n; Note(4); *(long long*)(p + 8) += n; *(int*)(p + 0x10) -= n; }
void OpenSlot(void* p) { (void)p; Note(5); }
unsigned char ParseEntry(long long* pMsg, void* pWrapper) { (void)pMsg; Note(7); reinterpret_cast<unsigned char*>(pWrapper)[0x24] = (unsigned char)g_valid; return 1; }
void Destroy(void* w) { (void)w; Note(6); }
}

int main() {
    g_pfnNpc_14007a700 = &Destroy;

    // the range wrapper: every field
    {
        unsigned char w[0x50];
        std::memset(w, 0xCC, sizeof w);
        unsigned char src[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
        assert(FUN_1400776c0((void**)w, (long long)src, 6) == (void**)w);
        assert(*(void**)w == nullptr);
        assert(*(void**)(w + 8) == (void*)src);
        assert(*(void**)(w + 0x10) == (void*)(src + 6));
        assert(*(int*)(w + 0x18) == 6);
        assert(*(unsigned int*)(w + 0x1c) == 0 && *(unsigned int*)(w + 0x20) == 0);
        assert(w[0x24] == 0 && w[0x25] == 0);
        assert(*(int*)(w + 0x28) == 6);                    // the limit is the length, not 0x7fffffff
        assert(*(unsigned int*)(w + 0x30) == 0x4000000 && *(unsigned int*)(w + 0x34) == 0x2000000);
        assert(*(unsigned int*)(w + 0x3c) == g_uNpcConst_1401036a0);
        assert(*(void**)(w + 0x40) == nullptr && *(void**)(w + 0x48) == nullptr);
    }

    // the parse of a range: the wrapper is opened through the slot at +0x18, then offered through +0x38, then
    // judged by the byte the parse left at +0x24
    {
        *(void**)((unsigned char*)g_vt + 0x18) = (void*)&OpenSlot;
        *(void**)((unsigned char*)g_vt + 0x38) = (void*)&ParseEntry;
        long long msg[1] = { (long long)g_vt };
        unsigned char src[4] = { 9, 9, 9, 9 };
        g_seqN = 0; g_valid = 1;
        assert(FUN_1400777a0((const char*)src, 4, msg) == 1);
        assert(g_seq[0] == 5 && g_seq[1] == 7 && g_seq[2] == 6);   // open, parse, destroy
        assert(g_seqN == 3);
        // a parse that leaves the byte clear answers zero, and the wrapper is still destroyed
        g_seqN = 0; g_valid = 0;
        assert(FUN_1400777a0((const char*)src, 4, msg) == 0);
        assert(g_seq[2] == 6 && g_seqN == 3);
    }

    // consume
    {
        unsigned char t[0x20];
        std::memset(t, 0, sizeof t);
        *(long long*)(t + 8) = 0x1000;
        *(int*)(t + 0x10) = 10;
        FUN_1400778c0((long long)t, 4);
        assert(*(long long*)(t + 8) == 0x1004 && *(int*)(t + 0x10) == 6);
        FUN_1400778c0((long long)t, 10);                  // more than is left: the count goes negative
        assert(*(long long*)(t + 8) == 0x100e && *(int*)(t + 0x10) == -4);
    }

    std::puts("NPCSERVER_D208_OK: 0x1400776c0/7a0/8c0");
    return 0;
}
