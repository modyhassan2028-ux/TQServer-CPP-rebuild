#pragma once
#include "Msg.h"
#include <string>

// Packet 1001 - MsgConnect (login handshake, v1 simplified).
// Real 6159 flow routes through AccountServer with SRP6; this rebuild
// accepts the account/password payload directly and creates the session.
class CMsgConnect : public tq::CMsg {
public:
    CMsgConnect() = default;

    bool Create(uint32_t dwId, uint32_t dwData, const std::string& account, const std::string& password);
    void Process(uint32_t dwSender, void* pContext) override; // pContext = CNetClient*
    void Process(uint32_t dwSender) override;

    const std::string& GetAccount() const { return m_account; }
    const std::string& GetPassword() const { return m_password; }

private:
    std::string m_account;
    std::string m_password;
};
