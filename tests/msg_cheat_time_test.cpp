// M43: FUN_140001ce0 - the event-time normalizer
#include "../Exe/MsgServer/Port/MsgCheatTime.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace msg;

int main() {
    MsgCheatTimeCtx c;

    // 1) null source -> 0x227
    char y[16] = {0}, m[16] = {0}, d[16] = {0}, h[16] = {0};
    assert(!c.Normalize(y, m, d, h, nullptr));
    assert(c.m_vecErrLogs.size() == 1);
    assert(c.m_vecErrLogs[0].find("0x227") !=
           std::string::npos);

    // 2) EMPTY source -> 0x228 (the walk quirk)
    assert(!c.Normalize(y, m, d, h, ""));
    assert(c.m_vecErrLogs.size() == 2);
    assert(c.m_vecErrLogs[1].find("0x228") !=
           std::string::npos);

    // 3) Bias == -0x1e0 (GMT+8): split only, no convert
    c.m_fnBias = []{ return -0x1e0; };
    std::memset(y, 0, 16); std::memset(m, 0, 16);
    std::memset(d, 0, 16); std::memset(h, 0, 16);
    assert(c.Normalize(y, m, d, h, "26092412"));
    // u16 split: "26","09","24","12" - caller zeroed,
    // so strtoul-visible strings are "26","09"...
    assert(std::string(y) == "26");
    assert(std::string(m) == "09");
    assert(std::string(d) == "24");
    assert(std::string(h) == "12");

    // 4) Bias = 0 (UTC): mktime/localtime in UTC seam
    //    "26092412" -> 12:00 -> -8h -> 04:00 same day
    c.m_fnBias = []{ return 0; };
    c.m_fnMktime = [](std::tm* p) -> int64_t {
        assert(p->tm_year == 126 && p->tm_mon == 8);
        assert(p->tm_mday == 24 && p->tm_hour == 12);
        return 1000000;               // opaque stamp
    };
    c.m_fnLocaltime =
        [](int64_t t, std::tm* p) -> bool {
            // t2 = 1000000 - 0x7080 - 0 = 966896
            assert(t == 1000000 - 0x7080);
            p->tm_year = 126; p->tm_mon = 8;
            p->tm_mday = 24; p->tm_hour = 4;
            return true;
        };
    assert(c.Normalize(y, m, d, h, "26092412"));
    assert(std::string(y) == "26");
    assert(std::string(m) == "9");    // UNPADDED quirk
    assert(std::string(d) == "24");
    assert(std::string(h) == "4");    // UNPADDED quirk

    // 5) localtime null -> 0x244 -> 0
    c.m_fnLocaltime = [](int64_t, std::tm*) -> bool {
        return false;
    };
    assert(!c.Normalize(y, m, d, h, "26092412"));
    assert(c.m_vecErrLogs.size() == 3);
    assert(c.m_vecErrLogs[2].find("0x244") !=
           std::string::npos);

    // 6) LITERAL guard quirk: a 1-char source PASSES the
    //    walk (only EMPTY fails) and 8 bytes are read
    //    (the caller's zeroed buffer backstops it)
    char src2[16] = "2";   // only '2' then zeros
    c.m_fnBias = []{ return -0x1e0; };
    std::memset(y, 0, 16); std::memset(m, 0, 16);
    std::memset(d, 0, 16); std::memset(h, 0, 16);
    assert(c.Normalize(y, m, d, h, src2));
    assert(std::string(y) == "2");

    puts("MSG_CHEAT_TIME_OK: null/empty guards, u16 field "
         "split, GMT+8 bypass, -8h adjust (0x7080), "
         "UNPADDED itoa quirk, 0x244 localtime fail");
    return 0;
}
