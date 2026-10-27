#include "NpcCreate.h"
#include "MsgAiNpcInfo.h"
#include <cstring>

namespace npc {

// ===== ORIGINAL FUN_14005e2e0 (CNpc::Create) =====
// security cookie (DAT_140103510 ^ stack) omitted - no
// functional effect. Structure of the original:
//   if (id == 0)                    -> log DAT_1400be0b0, ret 0
//   rec = typeLookup(type)          -> null: log, ret 0
//   npc[0x14] (+0xa0) = rec
//   byte +0x108 = recVal(rec, 0x35)
//   dword +0x10c  = recVal(rec, 0x36)
//   dword +0x110  = recVal(rec, 0x37)
//   if (byte +0x108 == 1 && +0x10c != 0):
//       dword +0x114 = +0x10c
//       dword +0x118 = TimeGet(0) / 1000
//   dword +0x80  = id
//   map = FUN_14003ca10(FUN_14001c790(), param_4)
//   +0x98 = map
//   dword +0x34 = param_5 (x); dword +0x38 = param_6 (y)
//   for (i = 5; i >= 0; i--) *(dword)(+i*4+0xe8) = 0
//   dword +0x1c = recVal(rec, 4)
//   dword +0x20 = recVal(rec, 5)
//   dword +0xa8 = max(1, recVal(rec, 0x12) * 3 / 1000)
//   dword +0xac = TimeGet(0) / 1000
//   dword +0xb8 = recVal(rec, 0x13)
//   qword  +0xbc = TimeGet(0)
//   dword +0xb0 = 0x3c
//   dword +0xb4 = TimeGet(0) / 1000
//   dword +0x8c = param_8
//   dword +0x28 = param_8 == 0 ? 0 : param_9
//   if ((recVal(rec, 0x15) >> 8) & 1):
//       dword +0x84 = param_10; dword +0x18 = 8
//   if (recVal(rec, 0x27) != 0):
//       name lookup + init @+0xc0 + refcount release
//   if (map == 0):
//       recVt18(*(rec+0x10), 1)
//       log "CNpc::Create(), Create Npc(type:%d, name:%s)
//            can't find map(%u) at %s, %d"
//       ret 0
//   mapEnter(map, npc+0x10)
//   if (!((recVal(rec, 0x15) >> 8) & 0xFF)):   // ~AH & 1
//       x = vt40(npc+0x10); y = vt38(npc+0x10)
//       if (mapPosFree(map, y, x)):
//           dword +0x1c = recVal(rec, 4)
//           dword +0x20 = recVal(rec, 5)
//           dword +0x2c = 0; dword +0x18 = 0
//   if (param_7 == 0 && param_12 && param_11 && param_14):
//       gen = FUN_14006a4c0(type, mapId, x, y, 4, 4)
//       if (gen == 0):
//           log DAT_1400be0b0
//           ret reportGenFail(param_11, param_12, param_14)
//           & 0xffffffffffffff00
//   else:
//       gen = findGenerator(param_7)
//       if (gen == 0):
//           log_InlineLogDBERROR(DAT_1400c9620)
//           ret 0
//   +0x100 = gen
//   if (FUN_14001c1c0(id)): vt90(gen, npcVt8(npc))
//   else: vt90(gen, npcVt8(npc)); globalRegister()
//   dword +0x128 = param_12
//   byte  +0x130 = param_13
//   dword +0x12c = param_11
//   dword +0x134 = param_15
//   uVar13 = param_15
//   if (param_11 && param_12 && param_14):
//       uVar13 = FUN_14005dc80(npc, param_14)
//   return CONCAT71(uVar13 >> 8, 1)
uint64_t CNpcObject::Create(uint32_t dwId, uint32_t dwType,
                            uint32_t dwMapId, int nX, int nY,
                            int nGenId, int nParam8, uint32_t dwParam9,
                            uint32_t dwParam10, int nParam11,
                            int nParam12, uint8_t bParam13,
                            int nParam14, uint32_t dwParam15) {
    if (dwId == 0) {
        m_vecLogs.push_back(
            "log_InlineLogERROR(&DAT_1400be0b0) !%s(%s)! in %s, %d");
        return 0;                        // & 0xff..00
    }
    NpcTypeRecord* pRec = m_fnFindType(dwType);
    At<void*>(0xa0) = pRec;              // param_1[0x14]
    if (pRec == nullptr) {
        m_vecLogs.push_back(
            "log_InlineLogERROR(&DAT_1400be0b0) !%s(%s)! in %s, %d");
        return 0;
    }
    // byte +0x108 = recVal(0x35)  (undefined1 truncation)
    At<uint8_t>(0x108) = (uint8_t)m_fnRecVal(pRec, 0x35);
    // dword +0x10c = recVal(0x36)
    At<uint32_t>(0x10c) = m_fnRecVal(pRec, 0x36);
    // dword +0x110 = recVal(0x37)
    At<uint32_t>(0x110) = m_fnRecVal(pRec, 0x37);
    if (At<uint8_t>(0x108) == 1 && At<uint32_t>(0x10c) != 0) {
        At<uint32_t>(0x114) = At<uint32_t>(0x10c);
        At<uint32_t>(0x118) =
            (uint32_t)(m_fnTimeGet() / 1000);   // +0x118
    }
    At<uint32_t>(0x80) = dwId;           // *(int*)(param_1+0x10)
    void* pvMap = m_fnFindMap(dwMapId);  // FUN_14003ca10(.., p4)
    At<void*>(0x98) = pvMap;             // param_1[0x13]
    At<int32_t>(0x34) = nX;              // param_5
    At<int32_t>(0x38) = nY;              // param_1 + 7 = +0x38
    for (int i = 5; i >= 0; i--)         // lVar9 = 5 .. 0
        At<uint32_t>(0xe8 + (uint32_t)i * 4) = 0;
    At<uint32_t>(0x1c) = m_fnRecVal(pRec, 4);
    At<uint32_t>(0x20) = m_fnRecVal(pRec, 5);    // param_1+4
    // dword +0xa8 = max(1, val(0x12) * 3 / 1000)
    int iVar6 = (int)m_fnRecVal(pRec, 0x12);
    iVar6 = iVar6 * 3 / 1000;
    int iVar8 = 1;
    if (0 < iVar6) iVar8 = iVar6;
    At<int32_t>(0xa8) = iVar8;           // param_1 + 0x15
    At<uint32_t>(0xac) = (uint32_t)(m_fnTimeGet() / 1000);
    At<uint32_t>(0xb8) = m_fnRecVal(pRec, 0x13); // +0x17
    At<uint64_t>(0xbc) = m_fnTimeGet();
    At<uint32_t>(0xb0) = 0x3c;           // param_1 + 0x16
    At<uint32_t>(0xb4) = (uint32_t)(m_fnTimeGet() / 1000);
    At<int32_t>(0x8c) = nParam8;
    At<uint32_t>(0x28) = nParam8 == 0 ? 0 : dwParam9;
    // bit 8 of val(0x15)
    uint32_t uVar7 = m_fnRecVal(pRec, 0x15);
    if ((uVar7 >> 8 & 1) != 0) {
        At<uint32_t>(0x84) = dwParam10;
        At<uint32_t>(0x18) = 8;          // param_1 + 3
    }
    if ((int)m_fnRecVal(pRec, 0x27) != 0) {
        // name lookup (FUN_140042b80) + FUN_1400402d0
        const void* pvName = nullptr;
        void* pvRefObj = nullptr;
        uint8_t const* puPair[2] = { nullptr, nullptr };
        m_fnNameLookup((const void*&)pvName, &pvRefObj, puPair);
        if (puPair[0] != nullptr)
            m_fnNameInit(this, puPair[0], (uint64_t)puPair[1]);
        if (pvRefObj != nullptr)
            m_fnNameRelease(pvRefObj);   // LOCK/dec/.. dance
    }
    if (pvMap == nullptr) {              // param_1[0x13] == 0
        m_fnRecVt18(pRec);               // vtable+0x18(rec, 1)
        m_vecLogs.push_back(
            "CNpc::Create(), Create Npc(type:%d, name:%s)"
            " can't find map(%u) at %s, %d");
        return 0;                         // & 0xff..00
    }
    m_fnMapEnter(pvMap);                  // FUN_14004ddd0
    // second read of val(0x15): AH = bits 8..15
    uint32_t u15 = m_fnRecVal(pRec, 0x15);
    if ((~(u15 >> 8) & 1) != 0) {        // (~extraout_AH & 1)
        int nX2 = m_fnNpcGetX(this);     // vt40 on npc+0x10
        int nY2 = m_fnNpcGetY(this);     // vt38
        if (m_fnMapPosFree(pvMap, nY2, nX2)) {  // (map, y, x)
            At<uint32_t>(0x1c) = m_fnRecVal(pRec, 4);
            At<uint32_t>(0x20) = m_fnRecVal(pRec, 5);
            At<uint32_t>(0x2c) = 0;
            At<uint32_t>(0x18) = 0;
        }
    }
    void* pvGen = nullptr;
    if (nGenId == 0 && nParam12 != 0 && nParam11 != 0
                     && nParam14 != 0) {
        pvGen = m_fnCreateGenerator(dwType, dwMapId, nX, nY, 4, 4);
        if (pvGen == nullptr) {
            m_vecLogs.push_back(
                "log_InlineLogERROR(&DAT_1400be0b0) "
                "!%s(%s)! in %s, %d");
            // FUN_140063b90/140063c60/14001c5f0/140063c20
            uint64_t uMsg = m_fnReportGenFail(nParam11,
                                              nParam12, nParam14);
            return uMsg & 0xffffffffffffff00;
        }
    } else {
        pvGen = m_fnFindGenerator(nGenId);
        if (pvGen == nullptr) {
            m_vecLogs.push_back(
                "log_InlineLogDBERROR(&DAT_1400c9620)");
            return 0;                     // & 0xff..00
        }
    }
    At<void*>(0x100) = pvGen;             // param_1[0x20]
    uint64_t uVt8 = m_fnNpcVt8(this);     // vtable+8 slot
    if (m_fnCheckId(dwId)) {              // FUN_14001c1c0
        m_fnGenVt90(pvGen, uVt8);
    } else {
        m_fnGenVt90(pvGen, uVt8);
        m_fnGlobalRegister();             // FUN_14001c220
    }
    At<int32_t>(0x128) = nParam12;        // param_1 + 0x25
    At<uint8_t>(0x130) = bParam13;        // param_1 + 0x26
    At<int32_t>(0x12c) = nParam11;         // +300 = 0x12c
    uint64_t uVar13 = dwParam15;
    At<uint32_t>(0x134) = dwParam15;
    if (nParam11 != 0 && nParam12 != 0 && nParam14 != 0) {
        uVar13 = m_fnNpcPostCreate(this, nParam14);
    }
    // CONCAT71((int7)(uVar13 >> 8), 1)
    return (uVar13 >> 8) << 8 | 1;
}

// ===== the exact Process (FUN_1400614f0) call order =====
uint64_t NpcCreateFromAiRecord(CNpcObject* pNpc,
                               const AiNpcInfoRecord& rec) {
    return pNpc->Create(rec.dw[0],
                        rec.w(0x1a),
                        rec.dw[1],
                        rec.w(0x14),
                        rec.w(0x16),
                        (int)rec.dw[2],
                        (int)rec.dw[3],
                        rec.w(0x1c),
                        rec.dw[4],
                        (int)rec.dw[9],
                        (int)rec.dw[8],
                        rec.b(0x2c),
                        (int)rec.dw[10],
                        rec.dw[0xc]);
}

} // namespace npc
