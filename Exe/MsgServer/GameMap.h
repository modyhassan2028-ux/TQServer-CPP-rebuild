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
    std::vector<uint32_t> GetUserIds() const;

    // load real collision data from a .DMap file (original client maps)
    bool LoadCollision(const std::string& dmapPath);
    bool HasRealCollision() const { return m_dmap.IsLoaded(); }
    bool RandomWalkableCell(uint32_t& xOut, uint32_t& yOut) { return m_dmap.RandomWalkable(xOut, yOut); }

private:
    uint32_t m_dwId;
    std::string m_name;
    std::unordered_map<uint32_t, std::shared_ptr<CUser>> m_users;
    CDMap m_dmap;
    bool m_bSafeZone{false};
    uint32_t m_dwSynId{0};
    uint32_t m_dwStatus{0};
    uint32_t m_dwTypeFlag{0};
    std::unordered_map<int, int64_t> m_mapInfo;
};