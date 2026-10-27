#include "ResStrings.h"
#include <cstdio>
#include <fstream>

CResStrings& CResStrings::Instance() {
    static CResStrings s_mgr;
    return s_mgr;
}

void CResStrings::LoadFromFile(const std::string& strPath) {
    std::ifstream f(strPath.c_str());
    if (!f.is_open()) return;
    std::string strLine;
    while (std::getline(f, strLine)) {
        if (strLine.empty() || strLine[0] == ';') continue;
        size_t t = strLine.find('=');
        if (t == std::string::npos || t == 0) continue;
        // ORIGINAL En_Res.ini: KEY=text, possibly with trailing CR
        std::string strKey = strLine.substr(0, t);
        std::string strVal = strLine.substr(t + 1);
        if (!strVal.empty() && strVal.back() == '\r') strVal.pop_back();
        m_strings[strKey] = strVal;
    }
}

std::string CResStrings::Get(const std::string& strKey) const {
    auto it = m_strings.find(strKey);
    return it == m_strings.end() ? std::string() : it->second;
}
