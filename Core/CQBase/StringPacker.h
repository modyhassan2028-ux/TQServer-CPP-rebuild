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
        void SetBuf(char* pBuf, uint32_t nSize, bool bCopy);

    private:
        std::vector<std::string> m_strings;
        std::vector<char> m_packedBuffer;
    };
}