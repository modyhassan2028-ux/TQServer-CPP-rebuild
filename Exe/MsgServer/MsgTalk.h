#pragma once
#include "Msg.h"
#include <string>

#pragma pack(push, 1)
struct TalkData {
    uint32_t color;
    uint16_t style;
    uint16_t type;
    uint32_t dwTime;
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
    bool Create(const std::string& sender, const std::string& recipient, const std::string& message, ChannelType channel);
    void Process(uint32_t dwSender) override;

    const std::string& GetSender() const { return m_sender; }
    const std::string& GetRecipient() const { return m_recipient; }
    const std::string& GetMessage() const { return m_message; }

private:
    std::string m_sender;
    std::string m_recipient;
    std::string m_message;
};