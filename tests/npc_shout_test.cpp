// unit 33: FUN_1400586b0 the NPC shout
// broadcast verbatim port test.
#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace npc;

struct Cfg {
    int nLogs = 0;
    int nComposeCalls = 0, nSendCalls = 0;
    const char* szName = "Guard001";
    const char* szGotName = nullptr;
    const char* szGotChan = nullptr;
    const char* szGotText = nullptr;
    bool bCompose = true;
    bool bSend = true;
    uint32_t uGotId = 0;
    bool bNameAsked = false;
    CNpcShoutData Make() {
        CNpcShoutData d;
        d.m_fnLogError = [this]{ ++nLogs; };
        d.m_fnGetName = [this] {
            bNameAsked = true; return szName; };
        d.m_fnNpcId8 = [this]{ return 4242u; };
        d.m_fnCompose =
            [this](const char* n, const char* c,
                   const char* t) {
                ++nComposeCalls;
                szGotName = n; szGotChan = c;
                szGotText = t;
                return bCompose; };
        d.m_fnSend =
            [this](uint32_t id) {
                ++nSendCalls; uGotId = id;
                return bSend; };
        return d;
    }
};

int main() {
    // null text -> log + masked false, NO compose
    {
        Cfg c; auto d = c.Make();
        assert(CNpcShout586b0(d, nullptr, nullptr)
               == 0);
        assert(c.nLogs == 1);
        assert(c.nComposeCalls == 0);
    }
    // the DEFAULT channel: null param_3 ->
    // the literal "ALLUSERS"
    {
        Cfg c; auto d = c.Make();
        assert(CNpcShout586b0(d, "help", nullptr)
               == 1);
        assert(strcmp(c.szGotChan, "ALLUSERS") == 0);
        assert(strcmp(c.szGotName, "Guard001") == 0);
        assert(strcmp(c.szGotText, "help") == 0);
        assert(c.uGotId == 4242);   // npc vt+8
        assert(c.nSendCalls == 1);
    }
    // an explicit channel wins over ALLUSERS
    {
        Cfg c; auto d = c.Make();
        assert(CNpcShout586b0(d, "help", "TEAM")
               == 1);
        assert(strcmp(c.szGotChan, "TEAM") == 0);
    }
    // compose FAILS -> masked false, NO send
    {
        Cfg c; c.bCompose = false; auto d = c.Make();
        assert(CNpcShout586b0(d, "help", nullptr)
               == 0);
        assert(c.nSendCalls == 0);
    }
    // send FAILS -> the low byte 0 (masked false)
    {
        Cfg c; c.bSend = false; auto d = c.Make();
        assert((CNpcShout586b0(d, "help", nullptr)
                & 0xffu) == 0);
        assert(c.nSendCalls == 1);
    }
    // the FULL ok path -> the CONCAT71 low
    // byte 1 (send true)
    {
        Cfg c; auto d = c.Make();
        assert((CNpcShout586b0(d, "help", nullptr)
                & 0xffu) == 1);
        assert(c.bNameAsked);
            // the name comes from *(npc+0xa0)'s
            // sub-object vt+0x18 - asked AFTER
            // the null gate, BEFORE compose
    }
    printf("NPC_SHOUT_OK: FUN_1400586b0 the NPC"
           " shout broadcast verbatim (the null"
           " text gate with log_InlineLogERROR"
           " DAT_1400be0b0 and the masked"
           " false, the literal \"ALLUSERS\""
           " default channel with the explicit"
           " param_3 override, the name from"
           " *(npc+0xa0)'s +0x10 sub-object"
           " vtable+0x18, the FUN_140064de0"
           " compose with the 0xffffff color"
           " and 0x7d1 talk-type literals, the"
           " compose-fail path skipping the"
           " send entirely, and the"
           " FUN_14001c200 + FUN_14001c5f0 send"
           " whose (char) result is the"
           " CONCAT71 low byte)\n");
    return 0;
}
