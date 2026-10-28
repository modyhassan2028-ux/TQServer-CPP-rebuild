// 14004c300
#include <cstring>
#include "crossclientthread.h"
namespace msg {
int CCrossClientThread::OnProcess(Seams& s) {
    s.TickEnter(kTickWait);
    s.WaitMessage(m_pDrainer, kWaitMs);
    s.TickLeave(kTickWait);
    s.TickEnter(kTickBody);
    for (;;) {
        if (s.GetMessage(m_pDrainer, -1, -1, kMsgLen, &m_In) == 0) {
            break;
        }
        uint32_t id = m_In.id;
        if (id != kIdLocalTest) {
            s.TickEnter(kTickLocal);
            bool skip = false;
            if (m_bFlag == 0) {
                if (id == kIdB0Check) {
                    if (m_In.body.b0 != kB0Expected) skip = true;
                } else if (id != 0x3f1 && id != 0x11173 && id != 0x11174) {
                    skip = true;
                }
            }
            if (!skip) {
                s.ProcessLocalMsg(m_pKernel, id, &m_In.body, m_In.size);
            }
            s.TickLeave(kTickLocal);
            continue;
        }
        s.TickEnter(kTickClient);
        if (m_bFlag == 0) {
            s.TickLeave(kTickClient);
            continue;
        }
        if (s.IsClientBody(m_pKernel, &m_In.body) == 0) {
            s.TickLeave(kTickClient);
            continue;
        }
        int h = s.GetSession(m_pKernel, &m_In.body);
        if (h == 0) {
            s.TickLeave(kTickClient);
            continue;
        }
        m_Out.zero  = 0;
        m_Out.ff    = 0xffffffffu;
        m_Out.kind  = m_In.body.kind;
        m_Out.total = (uint16_t)(m_In.body.len + 0x10);
        m_Out.v     = h;
        std::memcpy(m_Out.payload, m_In.body.payload,
                    (size_t)m_In.body.len);
        bool ok;
        if ((uint32_t)(m_In.body.len + 0x10) < (uint32_t)kOutMax) {
            ok = (m_Out.total != 0);
        } else {
            ok = false;
        }
        if (ok && s.SendBuiltPacket(this, &m_Out) == 0) {
            s.TickLeave(kTickClient);
            s.TickLeave(kTickBody);
            return 1;
        }
        s.TickLeave(kTickClient);
    }
    s.TickLeave(kTickBody);
    return 1;
}
}
