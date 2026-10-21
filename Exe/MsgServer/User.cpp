#include "User.h"
#include "MsgTalk.h"
#include <iostream>
#include "NetCore.h"
#include "Npc.h"
#include "MsgNpcInfo.h"

CUser::CUser(uint32_t dwId) : m_dwId(dwId) {}
CUser::~CUser() = default;

void CUser::Teleport(uint32_t dwMapId, uint16_t usX, uint16_t usY) {
    m_dwMapId = dwMapId;
    m_usX = usX;
    m_usY = usY;
    std::cout << "[GM System] Teleported User " << m_name << " (ID: " << m_dwId << ") to Map "
              << dwMapId << " (" << usX << ", " << usY << ")\n";
    SendSysMsg("Teleported to Map " + std::to_string(dwMapId) + " at (" + std::to_string(usX) + ", " + std::to_string(usY) + ")");

    // announce the NPCs of the destination map (CMsgNpcInfo 2030)
    for (auto& pNpc : CNpcManager::Instance().GetNpcsOnMap(dwMapId)) {
        CMsgNpcInfo info;
        if (info.Create(pNpc->GetId(), pNpc->GetLookface(), pNpc->GetX(), pNpc->GetY(),
                        pNpc->GetDir(), pNpc->GetName()))
            SendMsg(info.GetBuf(), info.GetSize());
    }
}

void CUser::SendSysMsg(const std::string& message) {
    CMsgTalk talk;
    if (talk.Create("SYSTEM", m_name, "[GM Control] " + message, CMsgTalk::Channel_Broadcast))
        SendMsg(talk.GetBuf(), talk.GetSize());
}

void CUser::SendMsg(const void* pBuf, uint16_t usSize) {
    if (m_pNet)
        static_cast<CNetClient*>(m_pNet)->Send(pBuf, usSize);
}