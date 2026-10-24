// CNpcWorld state machine - faithful port test
// (FUN_14001d390 CNpcWorld::OnTimer, FUN_14001c700 ConnectOK,
//  FUN_14001c2c0 rate gate)
#include "../Exe/NpcServer/NpcWorld.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace npc;

int main() {
    uint32_t s_now = 1000;
    std::vector<std::string> out;
    CNpcWorld w;
    w.m_fnTime = [&]{ return s_now; };
    w.m_fnPrint = [&](const char* s){ out.push_back(s); };
    w.m_fnAuth = [&](uint32_t k, const char* a, const char* b){
        assert(k == 0x3ade68b1);         // state-0 key
        assert(std::string(a) == "NpcServer Tqdig");
        assert(std::string(b) == "skl8934##VJICW ");
        return true; };
    bool bConn = false;
    w.m_fnConnect = [&](int, void*){ bConn = true; };
    int nTick = 0;
    w.m_fnTick = [&]{ ++nTick; };
    w.m_fnGenStats = []{
        return std::vector<GenStat>{
            {5,3,10}, {7,7,10}, {4,9,10}}; };
    w.m_dwStatInterval = 30;            // +0x20

    // state 0 -> auth ok -> connect
    w.OnTimer();
    assert(w.m_nState == 1 && bConn);
    assert(out.empty());                 // no print in case 0

    // state 1: retry print gated every 5s
    w.OnTimer();                        // t=1000, last=1000 -> no
    assert(out.empty());
    s_now = 5999; w.OnTimer();          // 5s later -> print
    assert(out.size() == 1 &&
           out[0] == "Login game server . . .");

    // ConnectOK: state 2 + login second + message
    s_now = 8000;
    w.OnConnectOK();
    assert(w.m_nState == 2);
    assert(w.m_dwGenDelay == 8);
    assert(out.size() == 2 && out[1].rfind(
        "Login OK. generator monster after", 0) == 0);

    // inside the 10s delay: no tick (login sec = 8)
    s_now = 18000 - 1; w.OnTimer();
    assert(nTick == 0);
    // at sec 18 (login 8 + 10): "Generator begin."
    s_now = 18000; w.OnTimer();
    assert(out.size() == 3 &&
           out[2] == "Generator begin.");
    assert(nTick == 0);   // tick starts the NEXT timer tick
    s_now = 18100; w.OnTimer();
    assert(nTick == 1);
    s_now = 18200; w.OnTimer();
    assert(nTick == 2);
    // stats at +0x20 = 30: stat last reset to 0 on gen
    // begin -> fires at sec 48
    s_now = 48000; w.OnTimer();
    assert(nTick == 3);
    assert(out.size() == 4);
    // stats: active 1 (5>3), full 1 (7==7), over 1 (4<9)
    assert(out[3].find("\t1 + 1 + 1 / 16\n") !=
           std::string::npos);

    // state 3 restart uses key 0x3ade68b2
    w.m_nState = 3;
    w.m_fnAuth = [&](uint32_t k, const char*, const char*){
        assert(k == 0x3ade68b2); return false; };
    w.OnTimer();
    assert(w.m_nState == 1);             // no connect on fail

    // default state -> MYASSERT branch
    w.m_nState = 9;
    w.OnTimer();
    assert(w.m_bAsserted);
    assert(out.size() == 4);             // nothing printed

    printf("NPC_WORLD_OK: state machine (0/1/2/3), 5s retry "
           "gate, 10s generator delay, stats walk, MYASSERT\n");
    return 0;
}
