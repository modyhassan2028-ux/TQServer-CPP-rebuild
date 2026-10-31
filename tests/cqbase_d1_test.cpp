// D1 (CQBase) — tq::CMsg and tq::MsgHead, 0x140b9d3a0..0x140b9d650
#include "modules/cqbase/src/cmsg.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace tq;

static int g_nLog = 0;
static const char* g_szLog = nullptr;
static void HookLog(const char* fmt, ...) { g_nLog++; g_szLog = fmt; }

int main() {
    g_pfnCQBaseLog = HookLog;
    static int s_aVft[5] = { 0 };
    g_pVftCMsg = (void*)s_aVft;

    // ---- the construction: vftable in, 0x400 cleared, both head words zero
    CMsg m;
    assert(m.pVft == (void**)g_pVftCMsg);
    assert(m.GetSize() == 0 && m.GetType() == 0);
    assert(m.GetHeadSize() == 4);
    assert(m.GetBuf() == (const char*)m.abBuf);       // the buffer itself
    for (uint32_t i = 0; i < CMsg::kBufSize; ++i) assert(m.abBuf[i] == 0);
    assert(m.IsValid() == false);                     // empty is invalid

    // ---- Init clears a dirty buffer
    std::memset(m.abBuf, 0xAB, CMsg::kBufSize);
    m.Init();
    assert(m.GetSize() == 0 && m.GetType() == 0);
    assert(m.abBuf[0x3FF] == 0);

    // ---- IsValid: the boundary is five bytes plus a non-zero type
    m.abBuf[0] = 4; m.abBuf[1] = 0; m.abBuf[2] = 7;   // size 4 -> false
    assert(m.IsValid() == false);
    m.abBuf[0] = 5; m.abBuf[1] = 0;
    assert(m.IsValid() == true);
    m.abBuf[2] = 0; m.abBuf[3] = 0;                   // the type is gone
    assert(m.IsValid() == false);

    // ---- Create(head, body): the head dword then head.wSize body bytes
    CMsg m2;
    MsgHead head; head.wSize = 6; head.wType = 0x047E;
    const char* pBody = "\1\2\3\4\5\6";
    assert(m2.Create(head, nullptr) == false);        // a null body fails first
    assert(m2.GetSize() == 0);                        // and nothing was written
    assert(m2.Create(head, pBody) == true);
    assert(m2.GetSize() == 6 && m2.GetType() == 0x047E);
    assert(std::memcmp(m2.abBuf + 4, pBody, 6) == 0);

    // ---- Create(buf, size): the size must match the buffer's own word
    CMsg m3;
    char abRaw[16] = { 0 };
    abRaw[0] = 8; abRaw[1] = 0; abRaw[2] = 0x7E; abRaw[3] = 0x04;
    for (int i = 0; i < 8; ++i) abRaw[4 + i] = (char)(0x10 + i);
    assert(m3.Create(abRaw, 7) == false);             // the size disagrees
    assert(m3.GetSize() == 0);
    assert(m3.Create(abRaw, 8) == true);
    assert(m3.GetSize() == 8 && m3.GetType() == 0x047E);
    assert(std::memcmp(m3.abBuf + 4, abRaw + 4, 4) == 0);
    assert(m3.Create(nullptr, 8) == false);            // a null buffer fails

    // ---- the zero type arm copies nothing but answers false
    CMsg m4;
    char abZero[8] = { 0 };
    abZero[0] = 5;
    std::memset(m4.abBuf, 0x5A, CMsg::kBufSize);
    assert(m4.Create(abZero, 5) == false);
    assert(m4.abBuf[0] == 0x5A);                      // untouched

    // ---- the copy construction copies 0x400 and rewrites the first dword
    CMsg m5;
    std::memcpy(m5.abBuf, abRaw, 8);
    m5.abBuf[9] = (char)0x99;
    CMsg m6(m5);
    assert(std::memcmp(m6.abBuf, m5.abBuf, CMsg::kBufSize) == 0);
    assert(m6.pVft == (void**)g_pVftCMsg);            // the vftable is re-set
    assert(m6.GetSize() == 8 && m6.GetType() == 0x047E);

    // ---- the assignment walks two bytes at a time and rewrites the head
    CMsg m7;
    std::memset(m7.abBuf, 0, CMsg::kBufSize);
    m7 = m5;
    assert(std::memcmp(m7.abBuf, m5.abBuf, CMsg::kBufSize) == 0);
    assert(m7.GetSize() == 8);
    assert(m7.abBuf[0x3FF] == m5.abBuf[0x3FF]);

    // ---- the three virtuals report themselves through the log seam
    g_nLog = 0;
    m7.Process((void*)0x1234);
    assert(g_nLog == 1);
    assert(std::strcmp(g_szLog, "tq::CMsg::Process(void* pInfo) error") == 0);
    m7.Process((uint32_t)7);
    assert(std::strcmp(g_szLog, "tq::CMsg::Process(OBJID idActor) error") == 0);
    m7.Process((uint32_t)7, (void*)0x10);
    assert(g_nLog == 3);
    assert(std::strcmp(g_szLog,
                       "tq::CMsg::Process(OBJID idActor, void* pInfo) error") == 0);

    // ---- MsgHead assignment is the one dword
    MsgHead a, b; a.wSize = 5; a.wType = 9;
    b = a;
    assert(b.wSize == 5 && b.wType == 9);

    printf("CQBASE_D1_OK: tq::CMsg construction, buffer, create, copy, log\n");
    return 0;
}
