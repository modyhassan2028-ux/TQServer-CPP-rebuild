#pragma once
#include "Msg.h"
#include "Item.h"
#include <cstdint>

// Packet 1009 (0x3F1) - MsgItem, 87 bytes total.
// Wire layout extracted from decompiled v6159 CMsgItem::Create/Process:
//   +0  head (len=87, type=1009)
//   +4  dwIdItem      (internal+4)
//   +8  dwData        (internal+8)
//   +12 dwData2/amount
//   +16 usAction (u16) (internal+0x10, switched on in Process: 1=buy 2=sell 3=drop 4=use ...)
//   +22 dwData3
//   +26 dwParam
//   +31 item attributes (14 u32 from the item object getters)

#pragma pack(push, 1)
struct ItemData { // 83 bytes after MsgHead
    uint32_t dwIdItem;   // +4
    uint32_t dwData;     // +8
    uint32_t dwData2;    // +12 (amount)
    uint16_t usAction;   // +16
    uint16_t usPad;      // +18
    uint32_t dwData3;    // +22
    uint32_t dwParam;    // +26
    uint8_t  ucPad;      // +30
    uint32_t dwAttrs[14]; // +31..+86
};
#pragma pack(pop)

class CMsgItem : public tq::CMsg {
public:
    enum ItemAction {
        Action_Buy = 1,
        Action_Sell = 2,
        Action_Drop = 3,
        Action_Use = 4,
        Action_Equip = 5,
        Action_Unequip = 6
    };

    // inventory result codes echoed to the client (classic semantics)
    enum ItemResult {
        Result_Ok = 0,
        Result_FullInventory = 1,
        Result_NotEnoughMoney = 2,
        Result_ItemNotFound = 3,
        Result_CannotUse = 4
    };

    CMsgItem() = default;

    bool Create(const ItemInfo& item, uint16_t usAction, uint32_t dwData = 0);
    void Process(uint32_t dwSender) override;

    // wire accessors
    uint32_t GetItemId() const { return m_data.dwIdItem; }
    uint16_t GetAction() const { return m_data.usAction; }
    uint32_t GetData() const { return m_data.dwData; }
    uint32_t GetAmount() const { return m_data.dwData2; }
    uint32_t GetParam() const { return m_data.dwParam; }

private:
    ItemData m_data{};
};
