#pragma once
#include "Msg.h"
#include "StringPacker.h"
#include <string>
#include <cstdint>

#pragma pack(push, 1)
// ORIGINAL msgdialog.cpp header payload (FUN_1403a6400 layout):
// [u32 time][u16 x][u16 y][u16 size][u8 color][u8 uimode]
struct DialogData {
    uint32_t dwTime;
    uint16_t usX;
    uint16_t usY;
    uint16_t usSize;
    uint8_t byColor;
    uint8_t byMode;
};
#pragma pack(pop)

// ORIGINAL CMsgDialog (msgserver\mapgroupkernel\network\msgdialog.cpp)
// packet id 2032 (0x7f0) - the NPC dialog packet the 6159 client renders.
class CMsgDialog : public tq::CMsg {
public:
    static constexpr uint16_t MSGDIALOG_ID = 2032; // *(pObj + 8) = 0x7f0

    // ui modes exactly as the original Create() callers use them:
    // 101->1 text, 102->2 option, 103->3 input, 104->4 listbox, 105->6 link
    enum UiMode : uint8_t {
        Mode_Text = 1,
        Mode_Option = 2,
        Mode_Input = 3,
        Mode_Listbox = 4,
        Mode_Link = 6
    };

    CMsgDialog() = default;

    // ORIGINAL FUN_1403a6400: one packed string, mode + color + size in header
    bool Create(uint8_t byMode, const char* szText, uint8_t byColor, uint16_t usSize);
    // ORIGINAL FUN_1403a6510: mode 4 (listbox) with two ints and no string
    bool CreateListbox(int n1, int n2);

    void Process(uint32_t dwSender) override;

private:
    bool Build(const DialogData& data, const tq::CStringPacker& packer);
};
