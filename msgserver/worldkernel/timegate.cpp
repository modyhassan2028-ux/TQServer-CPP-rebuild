#include "timegate.h"

namespace msg {

// 1400149a0
bool IntervalElapsed(SIntervalGate& gate, STimeGateSeams& s) {
    uint32_t now = s.TimeGet(0);
    if ((uint32_t)(gate.last + gate.interval) <= now / 1000) {
        uint32_t now2 = s.TimeGet(0);            // the RAW reads the clock again
        gate.last = (int32_t)(now2 / 1000);
        return true;
    }
    return false;
}

// 1400222e0
bool IntervalElapsedWith(SIntervalGate& gate, int interval, STimeGateSeams& s) {
    uint32_t now = s.TimeGet(0);
    if ((uint32_t)(interval + gate.last) <= now / 1000) {
        uint32_t now2 = s.TimeGet(0);
        gate.last = (int32_t)(now2 / 1000);
        return true;
    }
    return false;
}

} // namespace msg
