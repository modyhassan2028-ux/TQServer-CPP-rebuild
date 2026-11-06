// Generated with family CT — both allocators hooked, both the normal and the null small-node path.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_ct.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uint32_t g_nSize = 0; static int g_nSmall = 0, g_nSent = 0; static bool g_bNullSmall = false;
static void* g_pSentArg = nullptr;
static unsigned char aSmall[0x20], aSent[0x80], aThis[0x80];

static void* SmallHook(uint32_t uSize) { ++g_nSmall; g_nSize = uSize;
    if (g_bNullSmall) return nullptr;
    std::memset(aSmall, 0xCC, sizeof(aSmall)); return aSmall; }
static void* SentHook(void* pThis) { ++g_nSent; g_pSentArg = pThis;
    std::memset(aSent, 0xCC, sizeof(aSent)); return aSent; }

int main() {
    g_fnCT_small_1417f3166 = &SmallHook;
    g_fnCT_sent_141726c30 = &SentHook;
    g_fnCT_sent_141726c90 = &SentHook;
    g_fnCT_sent_141726cf0 = &SentHook;
    g_fnCT_sent_141726d50 = &SentHook;
    g_fnCT_sent_141726db0 = &SentHook;
    g_fnCT_sent_141726ec0 = &SentHook;
    g_fnCT_sent_14173bc00 = &SentHook;
    g_fnCT_sent_14173bcb0 = &SentHook;
    g_fnCT_sent_141746a00 = &SentHook;
    g_fnCT_sent_141746a60 = &SentHook;
    g_fnCT_sent_141755f90 = &SentHook;
    g_fnCT_sent_141756200 = &SentHook;
    g_fnCT_sent_141756260 = &SentHook;
    g_fnCT_sent_1417562c0 = &SentHook;
    g_fnCT_sent_1417563b0 = &SentHook;
    g_fnCT_sent_141756410 = &SentHook;
    g_fnCT_sent_141756470 = &SentHook;
    g_fnCT_sent_1417564d0 = &SentHook;
    g_fnCT_sent_1417565b0 = &SentHook;
    g_fnCT_sent_141756610 = &SentHook;
    g_fnCT_sent_141776670 = &SentHook;
    g_fnCT_sent_14177ace0 = &SentHook;
    g_fnCT_sent_14178a6a0 = &SentHook;
    g_fnCT_sent_14178a700 = &SentHook;
    g_fnCT_sent_1417935d0 = &SentHook;
    g_fnCT_sent_141793680 = &SentHook;
    g_fnCT_sent_141793760 = &SentHook;
    g_fnCT_sent_1417a76e0 = &SentHook;
    g_fnCT_sent_1417c8590 = &SentHook;

    {   // 0x141730c50
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141730c50(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x1d) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141730c50(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141730e00
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141730e00(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141730e00(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141730ef0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141730ef0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x51) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141730ef0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141730f70
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141730f70(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x49) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141730f70(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141731060
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141731060(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x1d) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141731060(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141731150
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141731150(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x1b) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141731150(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141732180
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141732180(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x1b) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141732180(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141733570
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141733570(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141733570(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141733630
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141733630(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x49) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141733630(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x1417336b0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_1417336b0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x1d) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_1417336b0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141735800
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141735800(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x51) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141735800(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14173dd50
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14173dd50(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x61) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14173dd50(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14173ddd0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14173ddd0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x21) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14173ddd0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14173df20
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14173df20(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x21) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14173df20(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14173f600
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14173f600(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x61) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14173f600(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14174c430
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14174c430(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x3d) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14174c430(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14174c4b0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14174c4b0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14174c4b0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14174cc70
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14174cc70(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x3d) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14174cc70(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14174d6b0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14174d6b0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14174d6b0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141769b70
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141769b70(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141769b70(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141769d20
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141769d20(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x59) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141769d20(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141769da0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141769da0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141769da0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141769e20
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141769e20(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x61) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141769e20(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141769ea0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141769ea0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141769ea0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141769f20
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141769f20(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x61) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141769f20(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141769fa0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141769fa0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141769fa0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176a020
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176a020(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x69) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176a020(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176a0a0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176a0a0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176a0a0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176a120
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176a120(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x2d) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176a120(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176dbc0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176dbc0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176dbc0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176dcf0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176dcf0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x59) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176dcf0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176dd70
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176dd70(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176dd70(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176ddf0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176ddf0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176ddf0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176de70
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176de70(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176de70(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176def0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176def0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x69) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176def0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176df70
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176df70(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176df70(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14176f530
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14176f530(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x2d) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14176f530(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141775750
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141775750(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x61) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141775750(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141775ac0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141775ac0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x61) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141775ac0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141777e60
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141777e60(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x39) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141777e60(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x141777f20
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_141777f20(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x39) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_141777f20(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14177c1b0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14177c1b0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14177c1b0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14177c6c0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14177c6c0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14177c6c0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14178d990
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14178d990(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14178d990(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14178da10
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14178da10(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x49) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14178da10(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14178dc50
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14178dc50(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14178dc50(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14178dcd0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14178dcd0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x49) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14178dcd0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14179cc60
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14179cc60(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x61) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14179cc60(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14179cce0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14179cce0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x21) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14179cce0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x14179cd60
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_14179cd60(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_14179cd60(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x1417a90d0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_1417a90d0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_1417a90d0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x1417a93c0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_1417a93c0(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x29) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_1417a93c0(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }
    {   // 0x1417cea20
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_nSize = 0; g_pSentArg = nullptr; g_bNullSmall = false;
        void* pR = SynContainerCtor_1417cea20(aThis);
        CHECK(g_nSmall == 1); CHECK(g_nSize == 8); CHECK(g_nSent == 1);
        CHECK(g_pSentArg == (void*)aThis);                  // rcx = this at the sentinel call
        CHECK(pR == (void*)aThis);                          // returns this
        CHECK(*(void**)(aThis + 0x0) == (void*)aSmall);      // this->f00 = small node
        CHECK(*(void**)(aThis + 0x30) == (void*)aSent);      // this->f30
        CHECK(*(unsigned char*)(aSent + 0x21) == 0x1);      // mark
        CHECK(*(void**)(aSent + 0x8) == (void*)aSent);       // parent = self
        CHECK(*(void**)(aSent + 0x0) == (void*)aSent);       // left = self
        CHECK(*(void**)(aSent + 0x10) == (void*)aSent);      // right = self
        CHECK(*(void**)(aThis + 0x38) == nullptr);           // this->f38 = 0
        std::memset(aThis, 0, sizeof(aThis));
        g_nSmall = g_nSent = 0; g_bNullSmall = true;
        pR = SynContainerCtor_1417cea20(aThis);                     // null small node
        CHECK(g_nSmall == 1); CHECK(g_nSent == 1);
        CHECK(*(void**)(aThis + 0x0) == nullptr);            // the xor eax,eax path
        CHECK(pR == (void*)aThis);
    }

    std::printf("SYNDICATE_THUNKS_CT_OK: 53 bodies, %d checks\n", g_nChecks);
    return 0;
}
