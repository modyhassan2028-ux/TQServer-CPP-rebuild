#pragma once
#include "Msg.h"
#include <string>

#pragma pack(push, 1)
// ORIGINAL FUN_14015b300 (CMsgTalk::Create, msgtalk.cpp) body layout:
// [u32 time][u32 id][u16 color][u16 style][u32 systime][u32 p9][u32 p10][u8 p11]
// strings via StringPacker: from, to, suffix, message
struct TalkData {
    uint32_t dwTime;     // ORIGINAL +0 (TimeGet)
    uint32_t dwId;      // ORIGINAL +4 (param_6): sender id, 0 for SYSTEM
    uint16_t usColor;   // ORIGINAL +8 (param_7)
    uint16_t usStyle;   // ORIGINAL +10 (param_8): TQ style constants (2000..)
    uint32_t dwSysTime; // ORIGINAL +12 (SysTimeGet)
    uint32_t dwP9;      // ORIGINAL +20 (param_9)
    uint32_t dwP10;     // ORIGINAL +24 (param_10)
    uint8_t  byP11;     // ORIGINAL +28 (param_11)
};
#pragma pack(pop)

class CMsgTalk : public tq::CMsg {
public:
    enum ChannelType {
        Channel_Talk = 2000,
        Channel_Whisper = 2001,
        Channel_Team = 2003,
        Channel_Syndicate = 2004,
        Channel_World = 2007,
        Channel_Broadcast = 2011
    };

    CMsgTalk();
    // sender id defaults to 0 (SYSTEM); usStyle = TQ style constant
    bool Create(const std::string& sender, const std::string& recipient,
                const std::string& message, ChannelType channel, uint32_t dwId = 0,
                uint16_t usColor = 0xFFFF, uint8_t byP11 = 0);
    // ORIGINAL cq_action type 125 (case 0x7d): broadcast via
    // FUN_14015b300(buf, "SYSTEM", "ALLUSERS", text): id=0, color=0xffff,
    // style=0xff, p9=p10=0, p11=1 (best-evidence stack values)
    bool CreateBroadcast(const std::string& message);
    void Process(uint32_t dwSender) override;

    const std::string& GetSender() const { return m_sender; }
    const std::string& GetRecipient() const { return m_recipient; }
    const std::string& GetMessage() const { return m_message; }

private:
    std::string m_sender;
    std::string m_recipient;
    std::string m_message;
};