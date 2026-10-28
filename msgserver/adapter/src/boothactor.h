#ifndef C_BOOTH_ACTOR_H
#define C_BOOTH_ACTOR_H
// 1405935c0 CBoothActor::RecordEmoney(type, source, number, extra)
//   h = (*(vt+0x98))(*(void**)(this+0x10));
//   h == 0 -> "CBoothActor::RecordEmoney, failed in record emoney,
//             user:%u, type:%d, source:%d, number:%d"
//   else 1401742b0(h, type, source, number, extra)
#include <cstdint>
#include <cstddef>
namespace msg {
class CBoothActor {
public:
    struct Seams {
        void* (*GetUserByVt)(void* obj);          // (*(vt+0x98))(obj)
        void (*RecordEmoney)(void* user, int type, int source,
                             int number, int extra);   // 1401742b0
        void (*LogFail)(unsigned user, int type, int source, int number);
    };
    void RecordEmoney(int type, int source, int number, int extra,
                      Seams& s);
    uint8_t m_Pad[0x10] = {};
    void*   m_pOwner = nullptr;                   // +0x10
};
}
#endif
