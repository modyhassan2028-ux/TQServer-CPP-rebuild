#include "MsgToolKey.h"
#include <cstring>

namespace msg {

int MsgLoadToolKey(char* pOut,
                   MsgToolKeyData& rD) {
    if (pOut == nullptr) {
        rD.m_fnLogError("null");
        ++rD.nLogErr;
        return 0;
    }
    uint32_t nCb = 0x104;   // local_568[0]
    uint32_t nType = 1;     // local_568[1]
    unsigned char localData[0x104];  // the
    // registry buffer (local_128/127)
    localData[0] = 0;
    std::memset(localData + 1, 0, 0x103);
    // ===== 1. the tool.ini path =====
    void* pFile = rD.m_fnFopen();
    if (pFile != nullptr) {
        unsigned char buf[0x410];
        size_t n = rD.m_fnFread(buf,
            pFile);
        if (n != 0) {
            size_t i = 0;
            if (n != 0) {
                do {
                    pOut[i] = buf[i * 4]
                        ^ 0x12;
                    ++i;
                } while (i < n);
            }
            rD.m_fnFclose(pFile);
            return 1;
        }
        rD.m_fnFclose(pFile);
    }
    // ===== 2. the registry fallback ==
    const char* szKey =
        "Software\\microsoft\\vis";
    void* hKey = nullptr;
    ++rD.nRegOpen;
    int rc = rD.m_fnRegOpen(szKey, &hKey);
    if (rc == 0) {
        ++rD.nRegQuery;
        rc = rD.m_fnRegQuery(hKey,
            localData, &nCb);
        ++rD.nRegClose;
        rD.m_fnRegClose(hKey);
        if (rc == 0) {
            std::strncpy(pOut,
                (char*)localData, nCb);
            return 1;
        }
    }
    return 0;
}

} // namespace msg
