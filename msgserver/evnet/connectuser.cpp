// 140073740
#include "connectuser.h"
namespace msg {
uint64_t CConnectUser::SetType(int type, Seams& s) {
    if (type == 0) {
        m_nTickSec = 0;
        m_nMode    = 0;
        m_nType    = 0;
        return 0;
    }
    if (type != 1) {
        s.LogWrongType(type);
        return 0;                 // RAW: undefined register value
    }
    m_nMode = 0x14;
    uint32_t u = s.TimeGet(0);
    m_nType    = 1;
    m_nTickSec = u / 1000;
    return (uint64_t)((uint32_t)u * 0x10624dd3u);   // RAW artifact
}
}
