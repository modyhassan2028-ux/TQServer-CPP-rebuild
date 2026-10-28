#ifndef MSG_IOS_SERVER_CONFIG_H
#define MSG_IOS_SERVER_CONFIG_H
// 1403687d0 CMsgIOSServerConfig::Process
// PATH NOTE: no iosserverconfig source path exists in the __FILE__ table;
// the file name is inferred from the class and DECLARED as such.
namespace msg {
struct SMsgConfigSeams { void (*LogEnter)(void); };
class CMsgIOSServerConfig {
public:
    void Process(SMsgConfigSeams& s) { s.LogEnter(); }   // the whole body
};
} // namespace msg
#endif
