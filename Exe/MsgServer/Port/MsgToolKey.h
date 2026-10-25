// ============================================================
// MsgServer strict port - unit M22
// ORIGINAL: FUN_1405087d0 @ 1405087d0
// the tool-key loader (two sources):
//  1. ini\tool.ini: fread(buf, 4,
//     0x104, f) -> n items; for each i:
//     out[i] = buf[i*4] ^ 0x12   (every
//     4th byte, XOR 0x12) -> return 1
//  2. registry fallback:
//     RegOpenKeyExA(HKEY_CURRENT_USER
//       (0x80000001), "Software\\
//       microsoft\\vis", 0, KEY_READ
//       (0x20019), &hkey)
//     RegQueryValueExA(hkey, "key",
//       null, &type(=1), &data, &cb
//       (=0x104)) -> RegCloseKey ->
//       strncpy(out, data, cb) -> 1
//  param == null -> log error -> 0
//  both fail -> 0
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgToolKeyData {
    // fopen/fread/fclose over
    // "ini\\tool.ini"
    std::function<void*()> m_fnFopen;
    // fread(buf, 4, 0x104, f) -> items
    std::function<size_t(unsigned char*,
        void*)> m_fnFread;
    std::function<void(void*)> m_fnFclose;
    // RegOpenKeyExA(root, name, 0,
    //   0x20019, &hk) -> LSTATUS
    std::function<int(const char*,
        void**)> m_fnRegOpen;
    // RegQueryValueExA(hk, "key", null,
    //   &type, data, &cb) -> LSTATUS
    std::function<int(void*, unsigned
        char*, uint32_t*)> m_fnRegQuery;
    std::function<void(void*)>
        m_fnRegClose;
    // the error logger for the null param
    std::function<void(const char*)>
        m_fnLogError;
    // captures
    int nLogErr = 0, nRegOpen = 0;
    int nRegQuery = 0, nRegClose = 0;
    // injectors
    bool bFileOk = true;
    size_t nItems = 0;
    bool bRegOpenOk = true;
    int nRegQueryRc = 0;
    uint32_t nRegCb = 0;
    // the fake registry data
    unsigned char regData[0x104] = {};
    const unsigned char* pRegDataPtr =
        regData;
};

// ===== ORIGINAL FUN_1405087d0 @ 1405087d0
int MsgLoadToolKey(char* pOut,
                   MsgToolKeyData& rD);

} // namespace msg
