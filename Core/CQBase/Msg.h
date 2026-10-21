#pragma once
#include "Network/MsgHead.h"
#include <vector>
#include <cstring>

namespace tq {
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