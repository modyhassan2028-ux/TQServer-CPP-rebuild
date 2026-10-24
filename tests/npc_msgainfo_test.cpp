// CMsgAiNpcInfo (FUN_140061220/270/2a0/3a0/430/490/4f0)
#include "../Exe/NpcServer/MsgAiNpcInfo.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace npc;

int main() {
    // ===== ctor layout =====
    CMsgAiNpcInfo m;
    assert(m.m_dwMsgId == 0 && m.m_dwSize == 0);
    assert(m.Buf()->w(0x18) == 0);

    // ===== Create (FUN_1400612a0) =====
    bool bOk = m.Create(2, 1,2,3,4,5,6,7,8,9,10,11);
    assert(!bOk);                        // ver != 1
    assert(m.m_vecLogs.size() == 1);      // DAT_1400be0b0
    assert(m.Create(1, 100,200,300,400,500,600,700,800,
                    0xAB, 1000, 2000));
    assert(m.m_dwSize == 0x38);           // +0xc
    assert(m.m_dwMsgId == 0x4e21);        // +8
    AiNpcInfoRecord* p = m.Buf();
    assert(p->dw[0] == 100);              // *p = param_3
    assert(p->dw[1] == 400);              // p[1] = param_6
    assert(p->dw[2] == 200);              // p[2] = param_4
    assert(p->dw[3] == 0 && p->dw[4] == 0);  // zeroed
    assert(p->w(0x14) == 500);
    assert(p->w(0x16) == 600);
    assert(p->w(0x18) == 1);              // the tag
    assert(p->w(0x1a) == 300);
    assert(p->w(0x1c) == 0);
    assert(p->dw[8] == 700 && p->dw[9] == 800);
    assert(p->b(0x2c) == 0xAB);
    assert(p->dw[10] == 1000);
    assert(p->dw[0xc] == 0);              // never written
    assert(p->dw[0xd] == 2000);

    // ===== CreateFromBuffer (FUN_1400613a0) =====
    CMsgAiNpcInfo m2;
    uint8_t raw[0x38]; memset(raw, 0, sizeof(raw));
    assert(!m2.CreateFromBuffer(raw));    // tag != 1
    assert(m2.m_vecLogs.size() == 1);
    *(uint16_t*)(raw + 0x18) = 1;
    *(uint32_t*)(raw + 0x00) = 77;
    assert(m2.CreateFromBuffer(raw));
    assert(m2.m_dwSize == 0x38 && m2.m_dwMsgId == 0x4e21);
    assert(m2.Buf()->dw[0] == 77);

    // ===== SetBuffer (FUN_140061430) =====
    CMsgAiNpcInfo m3;
    assert(!m3.SetBuffer(nullptr, 0x38));
    assert(m3.SetBuffer(raw, 0x38));
    assert(m3.Buf()->dw[0] == 77);

    // ===== Destroy flags (FUN_140061490) =====
    // (non-deleting call: object survives)
    m3.Destroy(0);

    // ===== Process (FUN_1400614f0) =====
    {
        CMsgAiNpcInfo t;
        int nFind = 0, nNew = 0, nCreate = 0,
            nF0 = 0, nReg = 0, n98 = 0;
        bool bCreateOk = true;
        uint32_t dwQueriedId = 0;
        t.m_fnFindNpcById = [&](uint32_t id){
            ++nFind; dwQueriedId = id; return (void*)nullptr; };
        t.m_fnNewNpc = [&]{ ++nNew;
            static CNpcObj o; return &o; };
        t.m_fnNpcCreate = [&](CNpcObj*, const AiNpcInfoRecord&){
            ++nCreate; return bCreateOk; };
        t.m_fnNpcFailF0 = [&](CNpcObj*){ ++nF0; };
        t.m_fnNpcRegister = [&](CNpcObj*){ ++nReg; };
        t.m_fnNpcNotify98 = [&](CNpcObj*){ ++n98; };
        t.Create(1, 55, 0,0,0,0,0,0,0,0,0,1);   // id 55, +0x34=1

        t.Process(nullptr);              // conn == 0
        assert(nFind == 0);
        t.Process((void*)0x1);
        assert(nFind == 1 && dwQueriedId == 55);
        assert(nNew == 1 && nCreate == 1);
        assert(nReg == 1 && nF0 == 0);
        assert(n98 == 1);                // record +0x34 != 0

        // npc already exists: nothing happens
        t.m_fnFindNpcById = [](uint32_t){ return (void*)0x1; };
        t.Process((void*)0x1);
        assert(nNew == 1 && nCreate == 1 && nReg == 1);

        // Create fails -> vtable+0xf0 only
        t.m_fnFindNpcById = [](uint32_t){ return nullptr; };
        bCreateOk = false;
        t.Process((void*)0x1);
        assert(nF0 == 1 && nReg == 1 && nNew == 2);

        // new CNpc fails (operator_new 0) -> nothing
        t.m_fnNewNpc = [&]{ ++nNew; return (CNpcObj*)nullptr; };
        t.Process((void*)0x1);
        assert(nNew == 3 && nCreate == 2);

        // record +0x34 == 0 -> no +0x98 call
        bCreateOk = true;
        t.m_fnNewNpc = [&]{ ++nNew;
            static CNpcObj o; return &o; };
        t.Create(1, 66, 0,0,0,0,0,0,0,0,0,0);   // +0x34=0
        t.m_fnFindNpcById = [](uint32_t){ return nullptr; };
        t.Process((void*)0x1);
        assert(n98 == 1);                // unchanged
    }

    printf("NPC_MSGAINFO_OK: ctor/Create 0x38 record "
           "(tag word@0x18=1, id 0x4e21), CreateFromBuffer "
           "tag gate, SetBuffer null gate, Process "
           "lookup/create/fail-f0/register/+0x98 paths\n");
    return 0;
}
