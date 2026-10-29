// 1400fd190
#include "strcheckkey.h"
#include <cstring>
#include <cstdio>
#if defined(_MSC_VER)
#define RAW_SNPRINTF _snprintf
#define RAW_STRTOK   strtok
#else
#define RAW_SNPRINTF snprintf
#define RAW_STRTOK   strtok
#endif
namespace msg {
int CStrCheckKey::LoadForbiddenNameFromUnifiedDB(SStrCheckSeams& s) {
    if (s.Instance() == nullptr) { s.CheckF(0x30a, "pvecNameForbidden"); return 0; }
    if (m_hdbc == nullptr)       { s.CheckF(0x30b, "m_hdbc"); return 0; }
    char sql[0x400];
    sql[0] = 0;
    std::memset(sql + 1, 0, 0x3ff);
    RAW_SNPRINTF(sql, 0x400, "SELECT * FROM tbl_str_check_key LIMIT 10000");
    sql[0x3ff] = 0;
    if (s.Query(m_hdbc, sql, std::strlen(sql)) != 0) { s.SysLog(0, sql); return 0; }
    void* res = s.StoreResult(m_hdbc);
    if (res == nullptr) { s.SysLog(1, sql); return 0; }
    unsigned rows = s.NumRows(res);
    if (rows == 0) { s.SysLog(2, nullptr); s.FreeResult(res); return 0; }
    s.DataSeek(res, 0);
    unsigned counter = 0;
    while (counter < rows) {
        const char* const* row = s.FetchRow(res);
        if (row == nullptr) break;
        if ((int)counter != 0) {          // RAW skips row 0 (the counter check)
            char buf[0x100];
            buf[0] = 0;
            std::memset(buf + 1, 0, 0xff);
            s.SafeCopy(buf, row[1], 0x100);
            void* set = s.ParseAndBuild(s.Instance(), buf);
            unsigned tokens = 0;
            char* tok = RAW_STRTOK(buf, "_");
            while (tok != nullptr) {
                tokens = tokens + 1;
                if (tokens > 1000000) { s.CheckF(0x33b, "uLoopCount"); break; }
                s.ToLower(tok);
                s.InsertToken(set, tok);
                tok = RAW_STRTOK(nullptr, "_");
            }
        }
        counter = counter + 1;
    }
    s.FreeResult(res);
    return 1;
}
} // namespace msg
