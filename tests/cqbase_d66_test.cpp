// ============================================================================
// cqbase_d66 — ten small protobuf io bodies. Each seam records the arguments it received,
//   which is how the argument-reloading thunks and the two-argument write path are proved.
// ============================================================================
#include "modules/syndicate/src/synpbiomisc.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

uint32_t g_uA5610 = 0; void* g_pB5610 = nullptr; int g_n5610 = 0;
void* H5610(uint32_t a, void* b) { g_uA5610 = a; g_pB5610 = b; ++g_n5610; return (void*)0xAA; }
void* g_pA5740 = nullptr; void* g_pB5740 = nullptr;
void* H5740(void* a, void* b) { g_pA5740 = a; g_pB5740 = b; return (void*)0xBB; }
int32_t g_n4FB0 = 7;
int32_t H4FB0(void*) { return g_n4FB0; }
bool g_b7770 = true;
bool H7770(void*) { return g_b7770; }
void* g_p7BA0This = nullptr; void* g_p7BA0Arg = (void*)1; int g_n7BA0 = 0;
void H7BA0(void* p, void* a) { g_p7BA0This = p; g_p7BA0Arg = a; ++g_n7BA0; }
void* H37DE(void* p) { return p; }
int g_nSleepCalls = 0; uint32_t g_uSleepMs = 999;
void HSleep(uint32_t ms) { g_uSleepMs = ms; ++g_nSleepCalls; }
void* g_pData = nullptr; void* g_pSink = nullptr; int32_t g_nLen = -1;
void* HWrite(void* d, int32_t n, void* s) { g_pData = d; g_pSink = s; g_nLen = n; return d; }

}  // namespace

int main() {
    g_fnMisc5610 = &H5610;
    g_fnMisc5740 = &H5740;
    g_fnMisc4FB0 = &H4FB0;
    g_fnMisc7770 = &H7770;
    g_fnMisc7BA0 = &H7BA0;
    g_fnMisc37DE = &H37DE;
    g_fnMiscSleep = &HSleep;
    g_fnMiscWrite = &HWrite;

    // ---- the two thunks forward both arguments unchanged
    {
        int nSink = 0;
        g_n5610 = 0;
        CHECK(SynMiscThunk5610(0x1234, &nSink) == (void*)0xAA);
        CHECK(g_n5610 == 1);
        CHECK(g_uA5610 == 0x1234);
        CHECK(g_pB5610 == &nSink);

        CHECK(SynMiscThunk5740(&nSink, (void*)0x99) == (void*)0xBB);
        CHECK(g_pA5740 == &nSink);
        CHECK(g_pB5740 == (void*)0x99);
    }

    // ---- Remaining: [0x18] - (helper + [0x2c])
    {
        std::vector<uint8_t> aObj(0x40, 0);
        *(int32_t*)(aObj.data() + 0x18) = 100;
        *(int32_t*)(aObj.data() + 0x2c) = 10;
        g_n4FB0 = 7;
        CHECK(SynMiscRemaining(aObj.data()) == 83);
        g_n4FB0 = 50;
        CHECK(SynMiscRemaining(aObj.data()) == 40);
        *(int32_t*)(aObj.data() + 0x2c) = 0;
        CHECK(SynMiscRemaining(aObj.data()) == 50);
    }

    // ---- the plain forwarding row
    {
        std::vector<uint8_t> aObj(0x10, 0);
        g_b7770 = true;
        CHECK(SynMisc7770(aObj.data()) == true);
        g_b7770 = false;
        CHECK(SynMisc7770(aObj.data()) == false);
    }

    // ---- Reset: the count at +0x2c is cleared before the helper sees this+0x20
    {
        std::vector<uint8_t> aObj(0x40, 0xFF);
        *(int32_t*)(aObj.data() + 0x2c) = 5;
        g_n7BA0 = 0; g_p7BA0Arg = (void*)1;
        SynMiscReset(aObj.data());
        CHECK(*(int32_t*)(aObj.data() + 0x2c) == 0);
        CHECK(g_n7BA0 == 1);
        CHECK(g_p7BA0This == aObj.data() + 0x20);
        CHECK(g_p7BA0Arg == nullptr);
    }

    // ---- 37DE dereferences the first qword before the call
    {
        int nTarget = 0;
        void* apObj[1] = {&nTarget};
        CHECK(SynMisc37DE(apObj) == &nTarget);
    }

    // ---- the pointer comparison reads the first qword
    {
        int nTarget = 0;
        int nOther = 0;
        void* apObj[1] = {&nTarget};
        CHECK(SynMiscPtrEq(apObj, &nTarget) == true);
        CHECK(SynMiscPtrEq(apObj, &nOther) == false);
        apObj[0] = nullptr;
        CHECK(SynMiscPtrEq(apObj, nullptr) == true);
    }

    // ---- the yield is Sleep(0)
    {
        g_nSleepCalls = 0; g_uSleepMs = 999;
        SynMiscYield();
        CHECK(g_nSleepCalls == 1);
        CHECK(g_uSleepMs == 0);
    }

    // ---- writing a whole string hands data, the int length and the sink over
    {
        std::string sText = "hello world";
        int nSink = 0;
        SynMiscWriteString(&sText, &nSink);
        CHECK(g_pData == (void*)sText.data());
        CHECK(g_nLen == 11);
        CHECK(g_pSink == &nSink);

        std::string sEmpty;
        SynMiscWriteString(&sEmpty, &nSink);
        CHECK(g_nLen == 0);
    }

    // ---- the tag writer: one byte under 0x80, the thunk from 0x80 on
    {
        uint8_t aOut[8];
        std::memset(aOut, 0xEE, sizeof(aOut));
        CHECK(SynMiscWriteTag(0x08, aOut) == aOut + 1);
        CHECK(aOut[0] == 0x08);
        CHECK(SynMiscWriteTag(0x7F, aOut) == aOut + 1);
        CHECK(aOut[0] == 0x7F);

        int nSink = 0;
        g_n5610 = 0;
        CHECK(SynMiscWriteTag(0x80, &nSink) == (void*)0xAA);
        CHECK(g_n5610 == 1);
        CHECK(g_uA5610 == 0x80);        // the wide path keeps the full value
        CHECK(g_pB5610 == &nSink);
    }

    std::printf("SYNDICATE_D66_OK: ten io bodies, %d checks\n", g_nChecks);
    return 0;
}
