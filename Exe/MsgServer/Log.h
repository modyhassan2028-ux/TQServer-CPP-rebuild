#pragma once
#include <cstdio>
#include <cstdarg>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

namespace tq {
// ORIGINAL CQBase.dll tq::MyLogSave @ 0x140b8b090: vsnprintf the varargs
// into a 0x740 buffer, then log_Save(file, buf, 4) under the kernel lock
// (log_Save appends; its exact on-disk framing is not in the dump, so the
// line is appended verbatim). Relative paths land under the server CWD
// exactly like the original ("gmlog/action_log" etc.).
inline void MyLogSave(const char* pszFile, const char* pszFormat, ...) {
    if (!pszFile || !pszFormat) return;
    char szBuf[0x740] = {0};
    va_list ap; va_start(ap, pszFormat);
    vsnprintf(szBuf, sizeof(szBuf), pszFormat, ap);
    va_end(ap);
    std::string strPath(pszFile);
    for (size_t p = strPath.find('/'); p != std::string::npos; p = strPath.find('/', p + 1))
        mkdir(strPath.substr(0, p).c_str(), 0755);
    if (FILE* fp = fopen(strPath.c_str(), "a")) {
        fprintf(fp, "%s\n", szBuf);
        fclose(fp);
    }
}
} // namespace tq
