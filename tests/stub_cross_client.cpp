// native-test stub: CCrossClient needs winsock on Windows; the fidelity
// test does not exercise cross links, so provide no-op bodies
#include "CrossServer/CrossClient.h"
namespace cross {
bool CCrossClient::Start() { return false; }
void CCrossClient::Stop() {}
void CCrossClient::SendTalk(const std::string&, const std::string&) {}
void CCrossClient::RequestWho(uint32_t) {}
void CCrossClient::Run() {}
void CCrossClient::PushRoster() {}
}
namespace cross {
CCrossClient& CCrossClient::Instance() { static CCrossClient s; return s; }
}
