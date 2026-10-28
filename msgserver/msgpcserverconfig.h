#ifndef MSG_PC_SERVER_CONFIG_H
#define MSG_PC_SERVER_CONFIG_H
// 1403624b0 CMsgPCServerConfig::Process
// PATH NOTE: inferred file name, declared as such (no __FILE__ entry).
#include "msgiosserverconfig.h"
namespace msg {
class CMsgPCServerConfig {
public:
    void Process(SMsgConfigSeams& s) { s.LogEnter(); }   // the whole body
};
} // namespace msg
#endif
