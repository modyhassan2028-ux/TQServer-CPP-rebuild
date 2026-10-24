#include "NpcTransform.h"

namespace npc {

// ORIGINAL MulDiv (Win32 kernel32): rounds to nearest,
// negative products keep sign; c==0 -> -1.
int NpcMulDiv(int nNumber, int nNumerator, int nDenominator) {
    if (nDenominator == 0) return -1;
    long long ll = (long long)nNumber * (long long)nNumerator;
    if (ll >= 0) return (int)((ll + nDenominator / 2) / nDenominator);
    return (int)((ll - nDenominator / 2) / nDenominator);
}

// ===== ORIGINAL FUN_14002b270 (CNpcManager::SpawnNewNpcID) =====
// uint FUN_14002b270(uint *param_1)  [param_1 = DAT_1401045b8+0x30]
//   if (*(longlong*)(param_1+0x18) != 0)          // queue holds ids
//       return FUN_14002a690((longlong*)(param_1+10)); // pop ring - TBD
//   if (*param_1 < 499999) { *param_1 = *param_1 + 1; return *param_1; }
//   *param_1 = 0x61a81;
//   log_InlineLogERROR(&DAT_1400c3fd0);
//       // DAT_1400c3fd0 (GBK) =
//       // "CNpcManager::SpawnNewNpcID() MONSTER的ID空间回卷 at %s, %d"
//   return *param_1;
uint32_t CNpcTransform::SpawnNewNpcID() {
    if (m_pAllocator->m_qwQueueRemain != 0) {
        // ORIGINAL: FUN_14002a690(instance+0x28) ring-buffer
        // pop (via FUN_140026b80 index walk) - TBD
        return m_fnPopQueueId();
    }
    if (m_pAllocator->m_dwCounter < 499999u) {
        m_pAllocator->m_dwCounter = m_pAllocator->m_dwCounter + 1;
        return m_pAllocator->m_dwCounter;
    }
    m_pAllocator->m_dwCounter = 0x61a81;
    Log("CNpcManager::SpawnNewNpcID() MONSTER\xB5\xC4ID\xBF\xD5\xBC\xE4\xBB\xD8\xBE\xED at %s, %d");
    return m_pAllocator->m_dwCounter;
}

// ===== ORIGINAL FUN_140049310 (position gate) =====
// bool FUN_140049310(longlong param_1, int x, int y)
//   [param_1 = *(CNpc+0x98); sub-object at param_1+0x10]
//   if (-1 < x): w = vcall+0x28(subobj); if (x < w):
//   if (-1 < y): h = vcall+0x20(subobj); if (y < h):
//       return vcall+0x18(subobj, x, y) == 0;
//   return false;
bool CNpcTransform::PosValid(int nX, int nY) {
    if (0 <= nX) {
        int nW = m_fnMapWidth();
        if (nX < nW) {
            if (0 <= nY) {
                int nH = m_fnMapHeight();
                if (nY < nH) {
                    return m_fnMapCell(nX, nY) == 0;
                }
            }
        }
    }
    return false;
}

// ===== ORIGINAL FUN_14005a660 (CNpc::CheckTransform) =====
// ulonglong FUN_14005a660(longlong param_1)  [param_1 = CNpc base]
//   if (*(longlong*)(param_1+0xa0) == 0):
//       log_InlineLogERROR(&DAT_1400be0b0);  // "!%s(%s)! in %s, %d"
//       return 0;
//   uVar4 = vcall+0x50(param_1+0x10); if ((char)uVar4 == 0) return 0;
//   bVar1 = *(byte*)(param_1+0x108); uVar4 = 0;
//   if (bVar1 != 0 && bVar1 < 3 && *(int*)(param_1+0x110) != 0):
//     if (*(uint*)(param_1+0x10c) != 0 && *(int*)(param_1+0x128) == 0
//        && *(int*)(param_1+300 /*0x12c*/) == 0):
//       if (bVar1 == 1):
//         if (*(int*)(param_1+0x118) != 0):
//           uVar4 = FUN_140002480((int*)(param_1+0x114));
//           // FUN_140002480: (p[0] + p[1]) <= tq::TimeGet(0)/1000
//           if (uVar4) return 1;
//       else:
//         if (bVar1 != 2):
//           log_InlineLogERROR(
//             "CNpc::CheckTransform, wrong monster transform flag:%u");
//           return 0;
//         if (*(uint*)(param_1+0x10c) >= 0x3e9):
//           denom = vcall+0x10(*(*(param_1+0xa0)+0x10), 4);
//           i = MulDiv(denom, *(int*)(param_1+0x10c), 1000);
//           if (*(int*)(param_1+0x1c) <= i) return 1;
//   return 0;
bool CNpcTransform::CheckTransform() {
    if (m_pA0 == nullptr) {                    // +0xa0
        Log("log_InlineLogERROR(&DAT_1400be0b0) !%s(%s)! in %s, %d");
        return false;
    }
    if (!m_fnReady50()) {                      // vcall+0x50
        return false;
    }
    uint8_t bFlag = m_ucFlag108;               // +0x108
    if (bFlag != 0 && bFlag < 3 && m_nType110 != 0) {   // +0x110
        if (m_dw10c != 0 && m_nGate128 == 0
            && m_nGate12c == 0) {             // +0x10c/0x128/0x12c
            if (bFlag == 1) {
                if (m_nDelta118 != 0) {       // +0x118
                    // ORIGINAL FUN_140002480(npc+0x114):
                    // (t114 + t118) <= TimeGet(0)/1000
                    uint32_t uNow = m_fnTimeGet() / 1000u;
                    if ((uint32_t)(m_nTime114 + m_nDelta118)
                        <= uNow)
                        return true;
                }
            } else {
                if (bFlag != 2) {
                    Log("CNpc::CheckTransform, wrong monster "
                        "transform flag:%u");
                    return false;
                }
                if (m_dw10c >= 0x3e9u) {      // >= 1001
                    int nBase = m_fnA0GetVal4();
                    int i = NpcMulDiv(nBase,
                        (int)m_dw10c, 1000);
                    if (m_nLev1c <= i)         // +0x1c
                        return true;
                }
            }
        }
    }
    return false;
}

// ===== ORIGINAL FUN_14005a3b0 (CNpc::Transform) =====
// ulonglong FUN_14005a3b0(longlong param_1)  [param_1 = CNpc base]
//   if (*(longlong*)(param_1+0xa0) == 0): log(DAT_1400be0b0); return 0;
//   if (*(longlong*)(param_1+0x98) == 0): log(DAT_1400be0b0); return 0;
//   [locals: local_38 val, local_34, local_30, local_2c, local_28,
//    local_24, local_20, local_1c, local_18 - all zeroed]
//   if (*(longlong**)(param_1+0x100) == 0) return 0;
//   local_1c = vtable+8(*(*(param_1+0x100)));
//   local_28 = *(uint*)(param_1+0x80);
//   if (local_28 < 0x61a81 || 499999 < local_28) local_20 = 0;
//   else local_20 = FUN_14002b270(FUN_14001c7a0());
//   local_24 = *(uint*)(param_1+0x110);
//   local_30 = vcall+0x38(param_1+0x10);  local_2c = vcall+0x40(param_1+0x10);
//   local_34 = vtable+8(*(*(param_1+0x98)));
//   local_18.0 = *(byte*)(param_1+0x108);
//   if (!FUN_140049310(*(param_1+0x98), local_30, local_2c)):
//       log_InlineLogERROR("CNpc::Transform, wrong postion (%d, %d)", ...);
//       return 0;
//   rec = vcall+0x30(FUN_140025be0(FUN_14001c7a0()), local_24);
//   if (rec == 0):
//       log_InlineLogERROR("CNpc::Transform, wrong transform monster type: %d");
//       return 0;                              // (uVar6 = 0)
//   if (flag == 1) local_38 = vcall+0x10(*(rec+0x10), 4);
//   else if (flag == 2):
//       denom = vcall+0x10(*(*(param_1+0xa0)+0x10), 4);
//       numer = vcall+0x10(*(rec+0x10), 4);
//       local_38 = MulDiv(*(int*)(param_1+0x1c), numer, denom);
//   else:
//       log("CNpc::Transform, wrong monster transform flag:%u"); return 0;
//   uVar2 = vcall+0x10(*(rec+0x10), 4); if (uVar2 <= local_38) local_38 = uVar2;
//   uVar6 = vtable+0x88(*(*(param_1+0x100)), &local_38);
//   if (uVar6):
//       *(int*)(param_1+0x118) = 0; *(int*)(param_1+0x114) = 0;
//       *(byte*)(param_1+0x108) = 0; return 1;
//   return 0;
bool CNpcTransform::Transform() {
    if (m_pA0 == nullptr) {                    // +0xa0
        Log("log_InlineLogERROR(&DAT_1400be0b0) !%s(%s)! in %s, %d");
        return false;
    }
    if (m_p98 == nullptr) {                   // +0x98
        Log("log_InlineLogERROR(&DAT_1400be0b0) !%s(%s)! in %s, %d");
        return false;
    }
    uint32_t dwVal = 0;                       // local_38
    int32_t nLocal34 = 0, nLocal30 = 0, nLocal2c = 0;
    uint32_t dwLocal28 = 0; int32_t nLocal24 = 0;
    uint32_t dwLocal20 = 0, dwLocal1c = 0, dwLocal18 = 0;
    if (m_p100 == nullptr)                    // +0x100
        return false;
    dwLocal1c = m_fnGet100V8();               // vtable+8
    dwLocal28 = m_dwId80;                     // +0x80
    if (dwLocal28 < 0x61a81u || 499999u < dwLocal28) {
        dwLocal20 = 0;
    } else {
        dwLocal20 = SpawnNewNpcID();         // FUN_14001c7a0
                                              // + FUN_14002b270
    }
    nLocal24 = m_nType110;                    // +0x110
    nLocal30 = m_fnPos38();                   // vcall+0x38
    nLocal2c = m_fnPos40();                   // vcall+0x40
    nLocal34 = (int32_t)m_fnGet98V8();        // vtable+8 on +0x98
    dwLocal18 = m_ucFlag108;                  // +0x108
    if (!PosValid(nLocal30, nLocal2c)) {     // FUN_140049310
        Log("CNpc::Transform, wrong postion (%d, %d)");
        return false;
    }
    void* pvRec = m_fnFindType(nLocal24);    // FUN_14001c7a0 ->
                                              // FUN_140025be0 ->
                                              // vcall+0x30
    if (pvRec == nullptr) {
        Log("CNpc::Transform, wrong transform monster type: %d");
        return false;                        // uVar6 = 0
    }
    NpcTypeRecord* pRec = (NpcTypeRecord*)pvRec;
    if (m_ucFlag108 == 1) {
        dwVal = (uint32_t)m_fnTypeRecGetVal4(pRec);
    } else if (m_ucFlag108 == 2) {
        int nDenominator = m_fnA0GetVal4();
        int nNumerator = m_fnTypeRecGetVal4(pRec);
        dwVal = (uint32_t)NpcMulDiv(m_nLev1c, nNumerator,
                                    nDenominator);
    } else {
        Log("CNpc::Transform, wrong monster transform flag:%u");
        return false;
    }
    uint32_t uCap = (uint32_t)m_fnTypeRecGetVal4(pRec);
    if (uCap <= dwVal)
        dwVal = uCap;                         // cap at record value
    bool bOk = m_fnSend100V88(dwVal);         // vtable+0x88
    if (bOk) {
        m_nDelta118 = 0;                      // +0x118 = 0
        m_nTime114 = 0;                       // +0x114 = 0
        m_ucFlag108 = 0;                      // +0x108 = 0
        return true;
    }
    return false;
}

} // namespace npc
