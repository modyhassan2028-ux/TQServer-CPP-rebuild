#ifndef STR_CHECK_KEY_H
#define STR_CHECK_KEY_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\mapgroupkernel\strcheckkey.cpp
// (proven: the CHECKF literals inside 1400fd190 name both the file and
//  CStrCheckKey::pvecNameForbidden)
#include <cstdint>
#include <cstddef>
namespace msg {
struct SStrCheckSeams {
    void*    (*Instance)();                          // DAT_140975cd0
    void     (*CheckF)(unsigned line, const char* sym);
    void     (*SysLog)(int which, const char* sql);  // 0 query-fail, 1 store-null, 2 rows-zero
    int      (*Query)(void* hdbc, const char* sql, size_t len);
    void*    (*StoreResult)(void* hdbc);
    unsigned (*NumRows)(void* res);
    void     (*DataSeek)(void* res, unsigned long off);
    const char* const* (*FetchRow)(void* res);
    void     (*SafeCopy)(char* dst, const char* src, size_t n);
    void*    (*ParseAndBuild)(void* inst, const char* text); // 1400fcd20/140037d00/1400fb4c0
    void     (*ToLower)(char* s);                            // _strlwr
    void     (*InsertToken)(void* set, const char* token);   // 140037d80
    void     (*FreeResult)(void* res);
};
class CStrCheckKey {
public:
    uint8_t m_Pad[0x58];
    void*   m_hdbc = nullptr;        // +0x58
    int LoadForbiddenNameFromUnifiedDB(SStrCheckSeams& s);   // 1400fd190
};
} // namespace msg
#endif
