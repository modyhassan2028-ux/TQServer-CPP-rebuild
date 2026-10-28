// 1405935c0
#include "CBoothActor.h"
namespace msg {
void CBoothActor::RecordEmoney(int type, int source, int number, int extra,
                               Seams& s) {
    void* user = s.GetUserByVt(m_pOwner);
    if (user == nullptr) {
        s.LogFail(0, type, source, number);
        return;
    }
    s.RecordEmoney(user, type, source, number, extra);
}
}
