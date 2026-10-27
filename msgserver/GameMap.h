#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <vector>
#include "DMap.h"

class CUser;
class CMonster;

class CGameMap {
public:
    // safe zone = no PK damage and no monster attacks (classic city protection)
    bool IsSafeZone() const { return m_bSafeZone; }
    void SetSafeZone(bool b) { m_bSafeZone = b; }
    // ---- ORIGINAL map attributes (cq_action 306, case 0x132) ----
    // synid: FUN_140117780 get / FUN_1402cb7b0 set
    uint32_t GetSynId() const { return m_dwSynId; }
    void SetSynId(uint32_t v) { m_dwSynId = v; }
    // status flags (map+0x78): "test" = (v & flags) != 0;
    // FUN_1402c6e30(map, v, on/off) sets/clears bits
    bool TestStatus(uint32_t v) const { return (v & m_dwStatus) != 0; }
    void SetStatus(uint32_t v, bool bOn) { if (bOn) m_dwStatus |= v; else m_dwStatus &= ~v; }
    // type flag: vcall+0x58 tag 4, read as a bitmask
    uint32_t GetTypeFlag() const { return m_dwTypeFlag; }
    // ORIGINAL tagged map info: tag 3 = mapdoc, 0xb = portal0_x,
    // 0xc = portal0_y, 0xf = res_lev; get vcall+0x10, set vcall+0x60 (+0x70 save)
    int64_t GetMapInfo(int nTag) const {
        auto it = m_mapInfo.find(nTag);
        return it == m_mapInfo.end() ? 0 : it->second;
    }
    void SetMapInfo(int nTag, int64_t v) { m_mapInfo[nTag] = v; }
public:
    CGameMap(uint32_t dwId, const std::string& name);
    ~CGameMap();

    uint32_t GetId() const { return m_dwId; }
    const std::string& GetName() const { return m_name; }

    bool AddUser(std::shared_ptr<CUser> user);
    bool RemoveUser(uint32_t dwUserId);
    bool IsPassable(uint16_t usX, uint16_t usY) const;
    // ORIGINAL FUN_14015f9d0: cellmap bounds gate — x in [0, width)
    // (vtable+0x28) and y in [0, height) (vtable+0x20). Without a .DMap
    // the port stays with the synthetic free-movement convention (true).
    bool IsValidPos(int nX, int nY) const;

    // ORIGINAL map vtable+0x3d8 (FUN_1404864f0 zone gate, with the
    // in-map flag set for sorts 6..7): 0 = attacks refused here. The
    // original safe-zone/arena logic rides the map/port system; the
    // port carries the permissive default + the flag.
    bool AllowsAttackTarget(bool bSort67) const { (void)bSort67; return !m_bSafeZone; }
    // ORIGINAL map vtable+0x278 (PK map flag in the gate cascade)
    void SetPkMap(bool b) { m_bPkMap = b; }
    bool IsPkMap() const { return m_bPkMap; }
    // ORIGINAL short at mapgroup+0xef4 (PK counter in the >999 cascade)
    void SetPkCount(uint32_t v) { m_dwPkCount = v; }
    uint32_t GetPkCount() const { return m_dwPkCount; }
    bool m_bPkMap{false};
    uint32_t m_dwPkCount{0};
    std::vector<uint32_t> GetUserIds() const;

    // load real collision data from a .DMap file (original client maps)
    bool LoadCollision(const std::string& dmapPath);
    bool HasRealCollision() const { return m_dmap.IsLoaded(); }
    bool RandomWalkableCell(uint32_t& xOut, uint32_t& yOut) { return m_dmap.RandomWalkable(xOut, yOut); }

private:
    uint32_t m_dwId;
    std::string m_name;
    std::unordered_map<uint32_t, std::shared_ptr<CUser>> m_users;
    // ORIGINAL map-object list also carries ground items; cq_action 2013
    // (case 0x7dd) removes ground objects of a type from the map.
    struct GroundItem { uint32_t dwType; uint32_t dwItemId; };
    std::vector<GroundItem> m_groundItems;
    // cq_action 2101 (case 0x835, ACTION_TRAP_CREATE): trap record built
    // from the sscanf fields and passed to FUN_1403ab040 (create) and the
    // map-object tree insert (vcall+0x28). Field order per the original
    // struct layout: f1/f2 are the leading ushorts, f3/f4 dwords, f5/f6 the
    // x/y ushorts, f7 int, f8/f9 trailing ushorts.
    struct CTrap {
        uint16_t wField1;   // 591/51 in rows (effect kind)
        uint16_t wField2;   // 5/11 in rows
        uint32_t dwField3;  // 0 in rows
        uint32_t dwMapId;   // %user_map_id in rows
        uint16_t usX, usY;
        int32_t  nField7;
        uint16_t wField8, wField9;
        uint32_t dwOwnerId; // removal path: user 0x1400 blob (FUN_1403a7180)
        uint32_t dwTrapId;
        bool bActive;
    };
    std::vector<CTrap> m_traps;
    uint32_t m_dwNextTrapId{1};
  public:
    uint32_t AddTrap(uint16_t wF1, uint16_t wF2, uint32_t dwF3, uint32_t dwMapId,
                     uint16_t usX, uint16_t usY, int32_t nF7, uint16_t wF8, uint16_t wF9,
                     uint32_t dwOwnerId) {
        m_traps.push_back({wF1, wF2, dwF3, dwMapId, usX, usY, nF7, wF8, wF9, dwOwnerId,
                           m_dwNextTrapId++, true});
        return m_traps.back().dwTrapId;
    }
    // cq_action 2102 (case 0x836): remove traps owned by the acting user
    // via the 0x1400 blob (FUN_1403a7180). Returns traps removed.
    uint32_t RemoveTrapsOwnedBy(uint32_t dwOwnerId) {
        uint32_t n = 0;
        for (auto it = m_traps.begin(); it != m_traps.end(); ) {
            if (it->dwOwnerId == dwOwnerId) { it = m_traps.erase(it); n++; }
            else ++it;
        }
        return n;
    }
    const std::vector<CTrap>& GetTraps() const { return m_traps; }
  public:
    void AddGroundItem(uint32_t dwType, uint32_t dwItemId) { m_groundItems.push_back({dwType, dwItemId}); }
    // returns number removed (ORIGINAL FUN_140145f60 path; its client packet
    // format is documented open in PORTING_LOG)
    uint32_t RemoveGroundItemsOfType(uint32_t dwType, uint32_t dwMax) {
        uint32_t n = 0;
        for (auto it = m_groundItems.begin(); it != m_groundItems.end() && n < dwMax; ) {
            if (it->dwType == dwType) { it = m_groundItems.erase(it); n++; }
            else ++it;
        }
        return n;
    }
    CDMap m_dmap;
    bool m_bSafeZone{false};
    uint32_t m_dwSynId{0};
    uint32_t m_dwStatus{0};
    uint32_t m_dwTypeFlag{0};
    std::unordered_map<int, int64_t> m_mapInfo;
};