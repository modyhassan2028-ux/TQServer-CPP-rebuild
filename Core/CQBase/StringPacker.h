#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace tq {
    class __declspec(dllexport) CStringPacker {
    public:
        CStringPacker();
        virtual ~CStringPacker();

        bool AddString(const char* pszStr);
        uint32_t GetSize();
        uint32_t GetStrAmount();
        bool GetString(uint32_t nIndex, char* pszBuf, uint32_t nBufSize);
        // ORIGINAL semantics (FUN_1403b53f0 path): SetBuf WRITES the packed
        // strings ([u8 count][u8 len][bytes]) into pBuf (serialize)
        void SetBuf(char* pBuf, uint32_t nSize, bool bCopy);
        // parse a wire buffer back into strings (receive path)
        void ParseBuf(const char* pBuf, uint32_t nSize);

    private:
        std::vector<std::string> m_strings;
        std::vector<char> m_packedBuffer;
    };
}