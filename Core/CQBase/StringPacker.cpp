#include "StringPacker.h"
#include <cstring>

namespace tq {
    CStringPacker::CStringPacker() = default;
    CStringPacker::~CStringPacker() = default;

    bool CStringPacker::AddString(const char* pszStr) {
        if (!pszStr) return false;
        m_strings.emplace_back(pszStr);
        return true;
    }

    uint32_t CStringPacker::GetSize() {
        uint32_t total = 1; // Amount byte
        for (const auto& s : m_strings) {
            total += 1 + static_cast<uint32_t>(s.length());
        }
        return total;
    }

    uint32_t CStringPacker::GetStrAmount() {
        return static_cast<uint32_t>(m_strings.size());
    }

    bool CStringPacker::GetString(uint32_t nIndex, char* pszBuf, uint32_t nBufSize) {
        if (nIndex >= m_strings.size() || !pszBuf || nBufSize == 0) return false;
        const auto& s = m_strings[nIndex];
        if (s.length() >= nBufSize) return false;
        std::memcpy(pszBuf, s.c_str(), s.length() + 1);
        return true;
    }

    void CStringPacker::SetBuf(char* pBuf, uint32_t nSize, bool) {
        // serialize m_strings into pBuf: [u8 amount][u8 len][bytes]...
        if (!pBuf || nSize == 0) return;
        uint32_t offset = 0;
        uint8_t count = static_cast<uint8_t>(m_strings.size());
        pBuf[offset++] = static_cast<char>(count);
        for (const auto& s : m_strings) {
            uint32_t len = static_cast<uint32_t>(s.length());
            if (offset + 1 + len > nSize) break;
            pBuf[offset++] = static_cast<char>(len);
            std::memcpy(pBuf + offset, s.data(), len);
            offset += len;
        }
    }

    void CStringPacker::ParseBuf(const char* pBuf, uint32_t nSize) {
        m_strings.clear();
        if (!pBuf || nSize == 0) return;
        uint8_t count = static_cast<uint8_t>(*pBuf);
        uint32_t offset = 1;
        for (uint8_t i = 0; i < count && offset < nSize; ++i) {
            uint8_t len = static_cast<uint8_t>(pBuf[offset++]);
            if (offset + len > nSize) break;
            m_strings.emplace_back(pBuf + offset, len);
            offset += len;
        }
    }
}