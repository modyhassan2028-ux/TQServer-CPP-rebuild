#ifndef C_AURA_MGR_H
#define C_AURA_MGR_H
// 14024e750 CAuraMgr::SendAuraInfo(role)
//   role == 0 -> "CAuraMgr::SendAuraInfo role pointer is null, idPlayer:%u."
//                (the %u argument was dropped by the decompiler: the
//                 idPlayer value comes from the seam, documented)
//   p = 14024e590(); if (p) 14041ac50(p, role)
namespace msg {
class CAuraMgr {
public:
    struct Seams {
        void* (*GetInstance)();                   // 14024e590
        void (*SendInfo)(void* inst, void* role); // 14041ac50
        void (*LogNullRole)(unsigned idPlayer);
    };
    void SendAuraInfo(void* role, Seams& s);
};
}
#endif
