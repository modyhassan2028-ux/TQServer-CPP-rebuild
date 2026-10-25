// ============================================================
// Peerage.dll — unit D22: the CMsgLogin/CMsgPeerage wire
// family + the module ProcessMsg (1415571b0/1e0/240,
// 141557350/440/580/5e0/610/690/740/880, 141551310/320/
// 3c0). Mock msg objects: the real CMsgBase layout with
// the buffer tail at +0x408 and a heap buffer.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "../Exe/Dll/Peerage/Port/PeerageMsgWire.h"
#include "../Exe/Dll/Peerage/Port/PeerageModule.h"
#include "../Exe/Dll/Peerage/Port/PeeragePromote.h"

using namespace peerage;

static int g_nLog = 0;
static std::vector<std::string> g_vLog;

// the mock msg: the tail at +0x408 points at a real
// buffer; +0x410 the packer mock
struct MockMsg {
    void* m_pVt;
    char m_abPad08[0x400];
    char* m_pBuf;        // +0x408
    void* m_pPacker;     // +0x410
};
static_assert(offsetof(MockMsg, m_pBuf) == 0x408);
static MockMsg* MakeMsg(int nType, uint32_t uId,
                       int nCount = 0) {
    static MockMsg msgs[8];
    static int nNext = 0;
    MockMsg* m = &msgs[nNext++ % 8];
    memset(m, 0, sizeof *m);
    m->m_pBuf = (char*)calloc(1, 0x1000);
    m->m_pPacker = (void*)1;
    // the header (as the ctors build it)
    *(uint16_t*)(m->m_pBuf + 0) = 0xa8;
    *(uint16_t*)(m->m_pBuf + 2) = 0x810;
    *(uint16_t*)(m->m_pBuf + 4) = (uint16_t)nType;
    *(uint32_t*)(m->m_pBuf + 8) = uId;
    *(int32_t*)(m->m_pBuf + 0xc) = nCount;
    return m;
}

// ---- the seams ----
struct SeamInit {
    SeamInit() {
        g_fnInlineLogError = []() { g_nLog++; };
        g_fnCMsgCreate = [](void* p, char*, uint16_t)
            -> bool {
            // set msg+10 (the wire id at +0x0a)
            *(int16_t*)((char*)p + 10) = 0x3ea;
            return true; };
        g_fnFree = [](void*) {};
    }
};
static SeamInit g_seamInit;

int main() {
    setbuf(stdout, nullptr);
    // NOTE: std::function seams set at STATIC-init time
    // get overwritten by the .cpp TU defaults (the
    // C++ static-init order fiasco) — set in main
    g_fnMsgLoad = [](void*) -> uint8_t {
        return 1; };

    // ---- 1. MsgLoginCreate (1415571b0) ----
    {
        g_nLog = 0;
        MockMsg* m = MakeMsg(0, 0);
        assert(MsgLoginCreate((CMsgBase*)m, nullptr, 0));
        // the Create seam sets 0x3ea
        g_fnCMsgCreate = [](void* p, char*, uint16_t)
            -> bool {
            *(int16_t*)((char*)p + 10) = 0x810;
            return true; };
        assert(!MsgLoginCreate((CMsgBase*)m, nullptr, 0));
        g_fnCMsgCreate = [](void*, char*, uint16_t)
            -> bool { return false; };
        assert(!MsgLoginCreate((CMsgBase*)m, nullptr, 0));
        g_fnCMsgCreate = [](void* p, char*, uint16_t)
            -> bool {
            *(int16_t*)((char*)p + 10) = 0x3ea;
            return true; };
        puts("D22-1 logincreate ok");
    }

    // ---- 2. MsgPeerageCreate (1415575e0) ----
    {
        MockMsg* m = MakeMsg(0, 0);
        assert(!MsgPeerageCreate((CMsgBase*)m, nullptr, 0));
        g_fnCMsgCreate = [](void* p, char*, uint16_t)
            -> bool {
            *(int16_t*)((char*)p + 10) = 0x810;
            return true; };
        assert(MsgPeerageCreate((CMsgBase*)m, nullptr, 0));
        g_fnCMsgCreate = [](void*, char*, uint16_t)
            -> bool { return false; };
        assert(!MsgPeerageCreate((CMsgBase*)m, nullptr, 0));
        g_fnCMsgCreate = [](void* p, char*, uint16_t)
            -> bool {
            *(int16_t*)((char*)p + 10) = 0x3ea;
            return true; };
        puts("D22-2 peeragecreate ok");
    }

    // ---- 3. MsgLoginSend (1415571e0) ----
    {
        g_nLog = 0;
        MsgLoginSend((void*)1, 2, nullptr);
        assert(g_nLog == 1);
        // a real recipient: vt+0x30 called
        static void* vt[8] = {};
        static bool bCalled = false;
        static void (*vt30)(void*) = [](void*) {
            bCalled = true; };
        vt[0x30 / 8] = (void*)vt30;
        static struct { void** vt; } recv = { vt };
        MsgLoginSend((void*)9, 2, &recv);
        assert(bCalled);
        assert(g_nLog == 1);
        puts("D22-3 loginsend ok");
    }

    // ---- 4. BuildMsgType1 (141557350) ----
    {
        static std::string sLast;
        static void* vt[16] = {};
        static bool (*vt48)(void*, char*) =
            [](void*, char* s) -> bool {
                sLast = s; return true; };
        vt[0x48 / 8] = (void*)vt48;
        MockMsg* m = MakeMsg(0, 0);
        m->m_pVt = vt;
        g_fnBuild1Arg4 = []() -> uint64_t {
            return 555; };
        // the unified D20 seam (the append result returns)
        g_fnMsgAppend = [](void* pMsg, char* pStr) -> bool {
            return ((bool (*)(void*, char*))
                        (*(void***)pMsg)[0x48 / 8])(
                pMsg, pStr);
        };
        char cOk = BuildMsgType1(
            (CMsgBase*)m, 42u, 7u, 9ull, 123456789ull,
            -3);
        assert(cOk == 1);
        assert(*(uint16_t*)m->m_pBuf == 0xa8);
        assert(*(uint16_t*)(m->m_pBuf + 2) == 0x810);
        assert(*(uint16_t*)(m->m_pBuf + 4) == 1);
        assert(*(uint32_t*)(m->m_pBuf + 8) == 42);
        assert(sLast == "7 9 123456789 555 -3");
        puts("D22-4 type1 ok");
    }

    // ---- 5. BuildMsgType2 / Type4 ----
    {
        MockMsg* m = MakeMsg(0, 0);
        uint64_t r = BuildMsgType2((CMsgBase*)m, 300, 77);
        assert(r == 1);
        assert(*(uint16_t*)(m->m_pBuf + 4) == 2);
        assert(*(uint16_t*)(m->m_pBuf + 8) == 300);
        assert(*(uint16_t*)(m->m_pBuf + 10) == 77);
        assert(*(uint32_t*)(m->m_pBuf + 0xc) == 0);
        assert(*(uint16_t*)(m->m_pBuf + 0) == 0xa8);
        // type 4: memcpy 0x60
        char src[0x60];
        memset(src, 0xAB, sizeof src);
        r = BuildMsgType4((CMsgBase*)m, 0, src);
        assert(r == 1);
        assert(*(uint16_t*)(m->m_pBuf + 4) == 4);
        assert(memcmp(m->m_pBuf + 8, src, 0x60) == 0);
        assert(*(uint16_t*)(m->m_pBuf + 2) == 0x810);
        puts("D22-5 type2/4 ok");
    }

    // ---- 6. AppendStringPacked (141557610) ----
    {
        g_nLog = 0;
        MockMsg* m = MakeMsg(0, 0);
        static unsigned uSize = 0;
        g_fnPackerAddString = [](void* pk, char* s) {
            (void)pk; (void)s; };
        g_fnPackerGetSize = [](void*) -> unsigned {
            return uSize; };
        uSize = 5;
        assert(AppendStringPacked(m, (char*)"x") == 1);
        // 5 + 0xa7 = 0xac
        assert(*(uint16_t*)m->m_pBuf == 0xac);
        uSize = 0x10000;
        AppendStringPacked(m, (char*)"y");
        // (short)0x10000 == 0 -> 0 + 0xa7 = 0xa7
        assert(*(uint16_t*)m->m_pBuf == 0xa7);
        // null -> log + 0
        uint32_t r2 = AppendStringPacked(m, nullptr);
        assert(r2 == 0);
        assert(g_nLog == 1);
        puts("D22-6 addstring ok");
    }

    // ---- 7. SendPeerageMsg (141557690) ----
    {
        g_nLog = 0;
        static void* vt[16] = {};
        static std::vector<std::string> vCalls;
        static void (*vt10)(void*, uint64_t, uint64_t,
                            uint16_t) =
            [](void*, uint64_t a, uint64_t b,
               uint16_t c) {
                vCalls.push_back("10:" +
                    std::to_string(a) + "," +
                    std::to_string(b) + "," +
                    std::to_string(c)); };
        static void (*vt18)(void*, uint64_t, uint16_t)
            = [](void*, uint64_t a, uint16_t b) {
                vCalls.push_back("18:" +
                    std::to_string(a) + "," +
                    std::to_string(b)); };
        static void (*vt20)(void*) =
            [](void*) { vCalls.push_back("20"); };
        static void (*vt38)(void*) =
            [](void*) { vCalls.push_back("38"); };
        vt[0x10 / 8] = (void*)vt10;
        vt[0x18 / 8] = (void*)vt18;
        vt[0x20 / 8] = (void*)vt20;
        vt[0x38 / 8] = (void*)vt38;
        static struct { void** vt; } recv = { vt };
        // type 1: (a, buf+8 u64, buf+0x68 u16)
        MockMsg* m1 = MakeMsg(1, 4242);
        *(uint16_t*)(m1->m_pBuf + 0x68) = 9;
        SendPeerageMsg(m1, 77, &recv);
        assert(vCalls.back() == "10:77,4242,9");
        // type 2
        MockMsg* m2 = MakeMsg(2, 300);
        SendPeerageMsg(m2, 88, &recv);
        assert(vCalls.back() == "18:88,300");
        // type 3 / 4
        MockMsg* m3 = MakeMsg(3, 0);
        SendPeerageMsg(m3, 1, &recv);
        assert(vCalls.back() == "20");
        MockMsg* m4 = MakeMsg(4, 0);
        SendPeerageMsg(m4, 1, &recv);
        assert(vCalls.back() == "38");
        // type 9: NOTHING (no branch)
        vCalls.clear();
        MockMsg* m9 = MakeMsg(9, 0);
        SendPeerageMsg(m9, 1, &recv);
        assert(vCalls.empty());
        // null recipient -> log
        SendPeerageMsg(m9, 1, nullptr);
        assert(g_nLog == 1);
        puts("D22-7 dispatch ok");
    }

    // ---- 8. AppendPeerageRecord (141557740) ----
    {
        MockMsg* m = MakeMsg(0, 0, 0);
        const char* name = "Mahmoud";   // 7 chars
        uint64_t r = AppendPeerageRecord(
            (CMsgBase*)m, 42u, 3u, 500u, (char*)name,
            0x1122334455667788ull, 7u, 8u);
        assert(r == 1);
        // header size: count(0)*0x30 + 0xa8
        assert(*(uint16_t*)m->m_pBuf == 0xa8);
        // the record at +0x78
        uint64_t* rec = (uint64_t*)(m->m_pBuf + 0x78);
        assert(rec[0] == (((uint64_t)3 << 32) | 42u));
        // rec[1] = 500 + the 16-byte name at +4
        assert((uint32_t)rec[1] == 500);
        assert(memcmp((char*)&rec[1] + 4, "Mahmoud",
                      8) == 0);
        // the strncpy spans rec[1][4..7] + rec[2]
        // + rec[3][0..3]: "Mahmoud\0" 16-byte pad
        // -> rec[2] = 'o','u','d',0.. = 0x0064756f
        assert(rec[2] == 0x0064756full);
        assert(rec[3] == 0);
        assert(rec[4] == 0x1122334455667788ull);
        assert(rec[5] == (((uint64_t)8 << 32) | 7u));
        // count 1
        assert(*(int32_t*)(m->m_pBuf + 0xc) == 1);
        // second record: at +0xa8, size updates
        r = AppendPeerageRecord((CMsgBase*)m, 43u, 0u, 600u,
                                nullptr, 1ull, 2u, 3u);
        assert(r == 1);
        assert(*(uint16_t*)m->m_pBuf ==
               (uint16_t)(1 * 0x30 + 0xa8));
        uint64_t* rec2 = (uint64_t*)
            (m->m_pBuf + 0x78 + 0x30);
        assert(rec2[0] == 43u);
        assert(*(int32_t*)(m->m_pBuf + 0xc) == 2);
        // null name: no strncpy (zeros stay)
        assert(rec2[1] == 600);
        puts("D22-8 record ok");
    }

    // ---- 9. deleting dtors + stubs ----
    {
        MockMsg* m = MakeMsg(0, 0);
        assert(MsgLoginDeletingDtor((CMsgBase*)m, 0)
               == (CMsgBase*)m);
        assert(m->m_pVt == (void*)2);  // CMsg vft
        int nFreed = 0;
        g_fnFree = [&](void*) { nFreed++; };
        MsgLoginDeletingDtor((CMsgBase*)m, 1);
        assert(nFreed == 1);
        g_fnPackerDtor = [](void*) {
            g_vLog.push_back("packerDtor"); };
        MsgPeerageDeletingDtor((CMsgBase*)m, 0);
        assert(g_vLog.back() == "packerDtor");
        assert(m->m_pVt == (void*)2);
        MsgPeerageDeletingDtor((CMsgBase*)m, 1);
        assert(nFreed == 2);
        assert(ModuleStubOne() == 1);
        ModuleStubVoid();
        puts("D22-9 dtors ok");
    }

    // ---- 10. ModuleProcessMsg (1415513c0) ----
    {
        // the real CModule layout: login at +0x20,
        // peerage at +0x430, svc at +0x18
        static char mod[sizeof(CModule)];
        memset(mod, 0, sizeof mod);
        CModule* pMod = (CModule*)mod;
        // the msg's vt+0x10: (msg, id, svc at +0x18)
        static void* vtMsg[8] = {};
        static uint32_t g_lastId = 0;
        static void* g_lastSvc = nullptr;
        static void (*msgVt10)(void*, uint32_t,
                               void*) =
            [](void*, uint32_t id, void* svc) {
                g_lastId = id; g_lastSvc = svc; };
        vtMsg[0x10 / 8] = (void*)msgVt10;
        // the mock msg IS the module's login msg: the
        // tail pointer must point at a heap buffer
        static MockMsg* mm = MakeMsg(0, 0);
        mm->m_pVt = vtMsg;
        memcpy(&pMod->m_msgLogin, mm,
               sizeof(MockMsg));
        // the packer tail of msgLogin: +0x20+0x408
        *(void**)(mod + 0x18) = (void*)0xABCD;
        *(uint64_t*)(mod + 0x28) = 0;   // msg+8 qword
        // the hdr: {len, 0x3ea}
        uint16_t hdr[2] = {2, 0x3ea};
        uint16_t u = ModuleProcessMsg(pMod, 66,
                                      hdr, 2);
        assert(u == 0);   // msg+8 qword low u16
        assert(g_lastId == 66);
        assert(g_lastSvc == (void*)0xABCD);
        // msg+8 -> the returned u16
        *(uint64_t*)(mod + 0x28) = 0x77;
        u = ModuleProcessMsg(pMod, 67, hdr, 2);
        assert(u == 0x77);
        assert(g_lastId == 67);
        // no msg (load gate fails) -> 0, no call
        g_fnMsgLoad = [](void*) -> uint8_t {
            return 0; };
        u = ModuleProcessMsg(pMod, 68, hdr, 2);
        assert(u == 0);
        assert(g_lastId == 67);   // unchanged
        puts("D22-10 processmsg ok");
    }

    puts("PEERAGE-D22-OK");
    return 0;
}
