#pragma once
#include "Network/MsgHead.h"
#include <vector>
#include <cstring>
#include <cstdint>

#include <cstdlib>

namespace tq {
    // ORIGINAL CQBase.dll tq::RandGet(int) (decompiled 0x140b82fb0):
    // two rand() calls combined (r1 + r2*0x8000), mod n; n <= 0 -> 0.
    // The 801/802 family relies on the 0 case (no division by zero).
    // MSVC rand() is 15-bit; this host's is 31-bit, so both draws are
    // masked to 15 bits to keep the original 30-bit combine exact and
    // the modulo non-negative.
    inline int RandGet(int n) {
        if (n <= 0)
            return 0;
        int r1 = rand() & 0x7fff;
        int r2 = rand() & 0x7fff;
        return (r1 + r2 * 0x8000) % n;
    }

    class __declspec(dllexport) CMsg {
    public:
        CMsg();
        virtual ~CMsg();
        CMsg(const CMsg& other);
        CMsg& operator=(const CMsg& other);

        bool Create(const MsgHead& head, const char* pBuf);
        virtual bool Create(const char* pBuf, uint16_t nSize);
        const char* GetBuf() const;
        uint16_t GetHeadSize();
        uint16_t GetSize() const;
        uint16_t GetType() const;
        bool IsValid();

        // raw wire helpers: build a packet from received bytes
        void Clear();
        void AppendRaw(const uint8_t* pData, uint16_t usLen);

        virtual void Process(uint32_t dwSender);
        virtual void Process(uint32_t dwSender, void* pContext);
        virtual void Process(void* pContext);

    protected:
        void Init();

    protected:
        std::vector<char> m_buffer;
        uint16_t m_nType{0};
        uint16_t m_nSize{0};
    };
}