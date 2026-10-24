// MsgServer unit M7 - the libevent worker thread
#include "../Exe/MsgServer/Port/MsgEvnetRoutine.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace msg;

int main() {
    std::vector<std::string> vLog;
    int nDispatch = 0;
    MsgEvnetData d;
    void* pBase = (void*)0x22;
    d.m_fnGetBase = [&]{ return pBase; };
    d.m_fnDispatch = [&]{ ++nDispatch; };
    d.m_fnLog = [&](const char* s){
        vLog.push_back(s); };

    // the running loop: base set -> dispatch
    assert(MsgEvnetRoutine(d) == 0);
    assert(vLog.size() == 2);
    assert(vLog[0] == "EvnetRoutine worker "
                      "thread is up and running");
    assert(vLog[1] == "EvnetRoutine worker "
                      "thread exited");
    assert(nDispatch == 1);

    // the +0x178 gate: a null base -> NO dispatch
    // (but the thread still logs up + exited)
    pBase = nullptr;
    vLog.clear();
    assert(MsgEvnetRoutine(d) == 0);
    assert(vLog.size() == 2);
    assert(nDispatch == 1);

    printf("MSG_EVNET_OK: FUN_1404f8110 (the LITERAL "
           "'EvnetRoutine' typo logs) + FUN_1404f72a0 "
           "(the +0x178 event-base gate around the "
           "FUN_1405426b0 dispatch), exit code 0\n");
    return 0;
}
