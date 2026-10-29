#ifndef MSG_TIMEGATE_H
#define MSG_TIMEGATE_H
// 1400149a0 / 1400222e0 — the periodic-task gates used by CMsgServerDlg.
//
// The RAW has no RTTI for either one: both take the block pointer explicitly,
// so they are free functions here, not members. The names are descriptive only
// (nothing in the binary names them); the file location is inferred, the code
// is verbatim.
//
//  1400149a0(const int* blk)         interval at blk[0], last at blk[1]
//  1400222e0(const int* blk, int iv) interval passed in,    last at +0x04
//
// Both read the clock twice when they fire (tq::TimeGet(0) again before storing
// the timestamp) and both compare whole SECONDS: (uint)(last + interval) <= ms/1000.
#include <cstdint>

namespace msg {

struct SIntervalGate {
    int32_t interval;   // only read by the 1400149a0 form
    int32_t last;       // the stored second
};

struct STimeGateSeams {
    uint32_t (*TimeGet)(int mode);   // tq::TimeGet(0), milliseconds
};

// 1400149a0
bool IntervalElapsed(SIntervalGate& gate, STimeGateSeams& s);

// 1400222e0
bool IntervalElapsedWith(SIntervalGate& gate, int interval, STimeGateSeams& s);

} // namespace msg
#endif
