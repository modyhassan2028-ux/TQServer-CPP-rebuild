// native-test stub: CCrossClient needs winsock on Windows; the fidelity
// test does not exercise cross links, so provide no-op bodies
#include "CrossServer/CrossClient.h"
namespace cross {
bool CCrossClient::Start() { return false; }
void CCrossClient::Stop() {}
void CCrossClient::SendTalk(const std::string&, const std::string&) {}
void CCrossClient::RequestWho(uint32_t) {}
bool CCrossClient::RequestSceneTransfer(uint32_t u, uint32_t a, uint32_t b) {
    m_dwLastTransferUser = u; m_dwLastTransferA = a; m_dwLastTransferB = b;
    printf("[CROSS] scene transfer: user %u -> scene %u mode %u\n", u, a, b);
    return true;
}
bool CCrossClient::RequestFrontierTransfer(uint32_t u, uint32_t a, uint32_t b) {
    m_dwLastTransferUser = u; m_dwLastTransferA = a; m_dwLastTransferB = b;
    printf("[CROSS] frontier transfer: user %u -> server %u flag %u\n", u, a, b);
    return true;
}
void CCrossClient::Run() {}
void CCrossClient::PushRoster() {}
}
namespace cross {
CCrossClient& CCrossClient::Instance() { static CCrossClient s; return s; }
}
