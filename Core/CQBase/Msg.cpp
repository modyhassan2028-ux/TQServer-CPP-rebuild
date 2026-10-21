#include "Msg.h"

namespace tq {
    CMsg::CMsg() { Init(); }
    CMsg::~CMsg() = default;
    CMsg::CMsg(const CMsg& other) : m_buffer(other.m_buffer), m_nType(other.m_nType), m_nSize(other.m_nSize) {}
    CMsg& CMsg::operator=(const CMsg& other) {
        if (this != &other) {
            m_buffer = other.m_buffer;
            m_nType = other.m_nType;
            m_nSize = other.m_nSize;
        }
        return *this;
    }

    void CMsg::Init() {
        m_buffer.clear();
        m_nType = 0;
        m_nSize = 0;
    }

    bool CMsg::Create(const MsgHead& head, const char* pBuf) {
        m_nType = head.type;
        m_nSize = head.length;
        m_buffer.resize(m_nSize);
        std::memcpy(m_buffer.data(), &head, sizeof(MsgHead));
        if (pBuf && m_nSize > sizeof(MsgHead)) {
            std::memcpy(m_buffer.data() + sizeof(MsgHead), pBuf, m_nSize - sizeof(MsgHead));
        }
        return true;
    }

    bool CMsg::Create(const char* pBuf, uint16_t nSize) {
        if (!pBuf || nSize < sizeof(MsgHead)) return false;
        const auto* head = reinterpret_cast<const MsgHead*>(pBuf);
        m_nType = head->type;
        m_nSize = nSize;
        m_buffer.assign(pBuf, pBuf + nSize);
        return true;
    }

    const char* CMsg::GetBuf() const { return m_buffer.data(); }
    uint16_t CMsg::GetHeadSize() { return sizeof(MsgHead); }
    uint16_t CMsg::GetSize() const { return m_nSize; }
    uint16_t CMsg::GetType() const { return m_nType; }
    bool CMsg::IsValid() { return !m_buffer.empty() && m_nSize >= sizeof(MsgHead); }

    void CMsg::Process(uint32_t) {}
    void CMsg::Process(uint32_t, void*) {}
    void CMsg::Process(void*) {}
}