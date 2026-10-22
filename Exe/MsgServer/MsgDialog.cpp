#include "MsgDialog.h"
#include "StringPacker.h"
#include "User.h"
#include "UserManager.h"
#include <ctime>
#include <cstring>
#include <cstdio>

// ORIGINAL CMsgDialog::Create (FUN_1403a6400):
//   header[p+0x428]: time=u32 TimeGet, [4][6]=0, [8]=u16 size,
//   [10]=u8 color, [11]=u8 uimode; then CStringPacker::AddString(text)
bool CMsgDialog::Create(uint8_t byMode, const char* szText, uint8_t byColor, uint16_t usSize) {
    if (!szText) return false;

    tq::CStringPacker packer;
    packer.AddString(szText);

    DialogData data{};
    data.dwTime = static_cast<uint32_t>(time(nullptr));
    data.usX = 0;               // [4] = 0
    data.usY = 0;               // [6] = 0
    data.usSize = usSize;       // [8] = wSize
    data.byColor = byColor;     // [10] = color
    data.byMode = byMode;       // [11] = uimode

    return Build(data, packer);
}

// ORIGINAL CMsgDialog::Create2 (FUN_1403a6510) - listbox: two ints, no string
bool CMsgDialog::CreateListbox(int n1, int n2) {
    tq::CStringPacker packer; // empty

    DialogData data{};
    data.dwTime = static_cast<uint32_t>(time(nullptr));
    // the two ints ride in the header x/y slots the same way the
    // original packs them (listbox start/count)
    data.usX = static_cast<uint16_t>(n1);
    data.usY = static_cast<uint16_t>(n2);
    data.usSize = 0;
    data.byColor = 0;
    data.byMode = Mode_Listbox;

    return Build(data, packer);
}

bool CMsgDialog::Build(const DialogData& data, const tq::CStringPacker& cPacker) {
    tq::CStringPacker& packer = const_cast<tq::CStringPacker&>(cPacker);
    tq::MsgHead head;
    head.type = MSGDIALOG_ID;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + sizeof(DialogData) + packer.GetSize());

    m_buffer.clear();
    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &data, sizeof(data));
    packer.SetBuf(m_buffer.data() + sizeof(head) + sizeof(data), packer.GetSize(), true);

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

// incoming MsgDialog from the client (listbox picks). The 6159 flow is:
// option text comes back via MsgTalk(1004) to the NPC instead, so the
// original server-side Process here only handles the 104 listbox answer.
void CMsgDialog::Process(uint32_t dwSender) {
    auto user = CUserManager::Instance().GetUser(dwSender);
    if (!user) return;
    printf("[DIALOG] unexpected client MsgDialog from %s\n", user->GetName().c_str());
}
