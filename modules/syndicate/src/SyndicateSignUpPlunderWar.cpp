// D78 — CSyndicateLogic::SignUpPlunderWarFromClient helpers.
// The two helpers below are complete ports of their RAW loops; the surrounding
// function (token, sign-up string, tails) is documented in the plan doc.
#include "SyndicateSignUpPlunderWar.h"
#include <cmath>

namespace syndicate {

STargetIdResult ComposeTargetId(void* mgr, uint32_t target, uint32_t myLeague,
                                uint32_t userLeague, uint32_t memberKey,
                                SSignUpPlunderSeams& s) {
    STargetIdResult r{0, false};
    if (target == 0) return r;                     // the RAW skips a zero target
    uint32_t id;
    if (myLeague == target) {                      // vt+0x3f0() == target
        uint32_t own = s.OwnLeagueId(mgr);         // 14174e3f0
        if (own == 0 || own == userLeague) return r;
        id = myLeague * 1000000 + own;             // iVar10 * 1000000 + uVar9
    } else {
        id = s.TargetLeagueId(mgr, target);        // 141766950
    }
    if (id == 0) return r;
    if (memberKey == id) return r;
    r.id = id;
    r.insert = true;
    return r;
}

bool SendRobOptPages(SRobOptSeams& s, void* vt, uint32_t user,
                     int64_t current, int64_t cap, uint32_t freePages,
                     const uint32_t* ids, size_t nIds) {
    if (freePages < 1) return false;               // the caller aborts on < 1
    double pagesD = std::ceil((double)(cap - current) / (double)freePages);
    int pages = (int)(int64_t)pagesD;              // (longlong)dVar1 & 0xffffffff
    void* msg = s.MsgNew();
    if (msg == nullptr) return false;
    if (!s.MsgCreate(msg, 1, pages)) {
        s.MsgDestroy(msg);
        return false;
    }
    for (size_t i = 0; i < nIds; ++i) {
        if (!s.MsgAppend(msg, (int)(ids[i] / 1000000))) {
            s.Log("CSyndicateLogic::SignUpPlunderWarFromClient msg over size");
            break;                                  // the RAW keeps going to send
        }
    }
    if (s.MsgCount(msg) != 0) {
        s.MsgSerialize(msg);
        s.SendToClient(vt, user, msg);
    }
    s.MsgDestroy(msg);
    return true;                                    // CONCAT71(...,1)
}

} // namespace syndicate
