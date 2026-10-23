#include "Monster.h"
#include "MapManager.h"
#include "GroundItems.h"
#include "Item.h"

CMonster::CMonster(uint32_t dwId, uint32_t dwTypeId, const std::string& name)
    : m_dwId(dwId), m_dwTypeId(dwTypeId), m_name(name) {}
CMonster::~CMonster() = default;// ------------------------------------------------------------------
// cq_action 801/802 helpers - literal ports of the original
// MsgServer functions (conquer_src 0x14038a560 / 0x14038a790 /
// 0x1401669f0) onto the rebuild's ground-item model.
// ------------------------------------------------------------------
bool CMonster::ActionDropMoney(uint32_t dwMoney, uint32_t dwOwnerId)
{
    // test edx,edx -> no money requested: silently done
    if (dwMoney == 0)
        return true;
    // [rsp+0x70] = level: level < 80 (0x50) AND money <= 10 -> skip drop
    if (m_dwLevel < 80 && dwMoney <= 10)
        return true;
    uint32_t dwVal = dwMoney;
    // FUN_140175470 LuckyTime: power 1 -> [data+0x20], power 2 -> 1, else 0.
    // money = [mon+0x2c] * lucky / 100  (FUN_140164ee0 base, /100 via
    // the 0x51eb851f magic division)
    if (m_dwLuckyTime != 0)
        dwVal = m_dwDropMoneyBase * m_dwLuckyTime / 100;
    // FUN_140168a10 [mon+0x10f8] drop bonus flag; FUN_1401649c0 [mon+0x100]
    // depth <= 3 -> >>3, else >>2
    if (m_bDropBonus)
        dwVal >>= (m_dwDropBonusLevel <= 3 ? 3 : 2);
    if (dwVal == 0)
        return true;
    // FUN_1402d1110(mapgroup, 2, &xy): find a valid drop cell near the
    // monster - modeled as the monster's own cell passability check
    auto pMap = CMapManager::Instance().GetMap(m_dwMapId);
    if (!pMap || !pMap->IsPassable(m_usX, m_usY)) {
        // ORIGINAL log: "CMonster::DropMoney(): monster_type[%d], dwMoney[%u]."
        printf("[MONSTER] DropMoney(): monster_type[%u], dwMoney[%u].\n",
               m_dwTypeId, dwVal);
        return false;
    }
    CGroundItemManager::Instance().AddMoneyDrop(m_dwMapId, m_usX, m_usY,
                                                dwVal, dwOwnerId);
    return true;
}

bool CMonster::ActionDropItem(uint32_t dwItemType, uint32_t dwOwnerId)
{
    // test edx,edx: no item type -> silently done
    if (dwItemType == 0)
        return true;
    // FUN_1402d1110(mapgroup, 2, &xy) drop-cell gate
    auto pMap = CMapManager::Instance().GetMap(m_dwMapId);
    if (!pMap || !pMap->IsPassable(m_usX, m_usY))
        return false;
    // 0x14037c800 init fails when cq_itemtype has no such record ->
    // "table:cq_itemtype, monster(type:%u) drop item, can not found
    //  itemtype:%u." + return false
    if (!CItemLibrary::Instance().Lookup(dwItemType)) {
        printf("[MONSTER] table:cq_itemtype, monster(type:%u) drop item, "
               "can not found itemtype:%u.\n", m_dwTypeId, dwItemType);
        return false;
    }
    CGroundItemManager::Instance().AddItemDrop(m_dwMapId, m_usX, m_usY,
                                               dwItemType, dwOwnerId);
    return true;
}

bool CMonster::SpawnMoneyPile(uint64_t qwAmount, uint8_t cFlag)
{
    // FUN_1401669f0: MsgMapItem money pile at a random cell near the
    // monster (original FUN_140373ad0/0x140373ae0 draw from the
    // monster's rand context mon+0xe78; modeled as the +-2 spread the
    // FUN_1402d1110 grid uses). The flag byte rides the record.
    (void)cFlag;
    if (qwAmount == 0)
        return true;
    int nDx = (int)(std::rand() % 5) - 2;
    int nDy = (int)(std::rand() % 5) - 2;
    int nX = (int)m_usX + nDx;
    int nY = (int)m_usY + nDy;
    if (nX < 0 || nY < 0)
        return false;   // ORIGINAL: rdi+rand < 0 -> false
    auto pMap = CMapManager::Instance().GetMap(m_dwMapId);
    if (!pMap || !pMap->IsPassable((uint16_t)nX, (uint16_t)nY))
        return false;
    CGroundItemManager::Instance().AddMoneyDrop(m_dwMapId, (uint16_t)nX,
                                                (uint16_t)nY, (uint32_t)qwAmount, 0);
    return true;
}
