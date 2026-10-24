#include "FactionMatch.h"

CFactionMatchMgr& CFactionMatchMgr::Instance() {
    static CFactionMatchMgr s;
    return s;
}
CCrossCtfMgr& CCrossCtfMgr::Instance() {
    static CCrossCtfMgr s;
    return s;
}
