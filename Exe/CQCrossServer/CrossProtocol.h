// Cross-server wire protocol (v1), reconstructed from the decompiled
// CQCrossServer.exe (CCrossServerKernel / crossshell.cpp model):
// the hub accepts game-server connections, records them by server id and
// relays messages between servers (SendMsgToOtherServer / BroadcastOtherServerMsg).
// This header is pure encode/decode - shared by the hub binary and the
// MsgServer-side client, and unit-testable on any platform.
#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include "Network/MsgHead.h"

namespace cross {

// wire message types (MsgHead.type)
enum : uint16_t {
    MsgType_Hello     = 9001, // server -> hub: register id + name
    MsgType_Talk      = 9002, // server -> hub: relay a chat line to every other server
    MsgType_Roster    = 9003, // server -> hub: full player roster snapshot
    MsgType_Heartbeat = 9004, // server -> hub: keepalive + online count
    MsgType_WhoReq    = 9005, // server -> hub: request the aggregated cross roster
    MsgType_WhoResp   = 9006, // hub -> server: every server's roster in one packet
    MsgType_ServerUp  = 9007, // hub -> all: a server connected
    MsgType_ServerDown= 9008, // hub -> all: a server went away

    // ---- COUNTRY system (crossmsgserveraction.cpp switch, the
    // hub-side handlers keyed on MsgHead.type offset +0x430) ----
    // case 0 (~29462): country status query. Reads m_pCountrySysMgr
    //   name (FUN_14001a6a0), leader/title (FUN_14001a6d0) and the
    //   country_date (FUN_14001bc50) for (idserver, idleague), packs
    //   them with CStringPacker::AddString x2 and writes the
    //   country_date back at msg+8.
    // case 1 (~29507): country war state + score update (FUN_14000d620
    //   country lookup, FUN_1400218f0 score write, reply packed via
    //   FUN_1400246a0 and sent with FUN_14000a0b0) - TBD wire format.
    // case 2 (~29579): FUN_14001ee50(countryMgr, .., idserver) - the
    //   plunder-war join flow - TBD.
    // case 4 (~29589): FUN_14001a240(countryMgr, ..) + direct reply.
    // case 5 (~29605): FUN_14000a310(kernel, buf, 0, 0xffffff, 0x961)
    //   - cross-server broadcast of a system talk (type 0x961).
    // case 6 (~29609): FUN_14001d790(countryMgr, .., idserver) - TBD.
    MsgType_CountryStatusReq  = 9009, // server -> hub: case 0 query
    MsgType_CountryStatusResp = 9010, // hub -> server: name/title/date
    MsgType_CountryBroadcast  = 9011, // hub -> all: case 5 system talk
    // case 1 (~29507): war score query. The original first resolves
    //   FUN_14000d620(kernel, msg+0x420) - the member's country id
    //   (0xffffffff when absent) - and only members WITH a country
    //   get the packed reply (FUN_1400246a0 packs the country id,
    //   FUN_14000a0b0 sends it, ~20268 shows the same -1 gate).
    MsgType_CountryScoreReq  = 9012, // server -> hub: case 1 query
    MsgType_CountryScoreResp = 9013, // hub -> server: country + score
};

// case 0 query/response payloads (see CCountrySysMgr accessors)
struct CountryStatusReq {
    uint32_t dwIdServer;   // msg+8 in the original layout
    uint32_t dwIdLeague;   // msg+0x10
};
// case 1 payload: uid is read from msg+0x420 in the original
struct CountryScoreReq {
    uint32_t dwUserId;    // FUN_14000d620 key
    uint32_t dwIdServer;  // FUN_14001bc50 arg
    uint32_t dwIdLeague;   // FUN_14001bc50 arg
};
struct CountryScoreResp {
    uint32_t dwCountryId;  // FUN_14000d620 result (never -1 here)
    uint32_t dwCountryDate; // FUN_14001bc50 -> FUN_140022ce0
};
struct CountryStatusResp {
    char szLeagueName[64];  // AddString #1 ("" when league unknown)
    char szLeaderTitle[64]; // AddString #2
    uint32_t dwCountryDate; // written back to the request msg+8
};

constexpr uint32_t MAX_ROSTER = 64;
constexpr uint32_t NAME_LEN = 24;
constexpr uint32_t PLAYER_LEN = 16;
constexpr uint32_t TEXT_LEN = 160;

#pragma pack(push, 1)
struct HelloData { uint32_t dwServerId; char szName[NAME_LEN]; };
struct TalkData  { uint32_t dwServerId; char szFrom[PLAYER_LEN]; char szText[TEXT_LEN]; };
struct RosterEntry { char szName[PLAYER_LEN]; uint16_t usLevel; };
struct RosterData { uint32_t dwServerId; uint32_t dwCount; RosterEntry entries[MAX_ROSTER]; };
struct HeartbeatData { uint32_t dwServerId; uint32_t dwOnline; };
struct WhoRespServer { char szServer[NAME_LEN]; uint32_t dwOnline; RosterEntry entries[MAX_ROSTER]; };
struct WhoRespData { uint32_t dwServers; WhoRespServer servers[8]; };
struct ServerUpDownData { uint32_t dwServerId; char szName[NAME_LEN]; };
#pragma pack(pop)

template <typename T>
inline std::vector<uint8_t> Encode(uint16_t usType, const T& data) {
    static_assert(sizeof(T) >= 1, "empty payload not supported");
    tq::MsgHead head;
    head.type = usType;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + sizeof(T));
    std::vector<uint8_t> pkt(sizeof(tq::MsgHead) + sizeof(T));
    std::memcpy(pkt.data(), &head, sizeof(head));
    std::memcpy(pkt.data() + sizeof(head), &data, sizeof(T));
    return pkt;
}

// frame decoder state: feed bytes, get (type, payload) per complete packet
class FrameDecoder {
public:
    // returns true when a full packet was decoded into outType/outPayload
    bool Feed(const uint8_t* pData, uint32_t dwLen, uint16_t& outType,
              std::vector<uint8_t>& outPayload) {
        m_buf.insert(m_buf.end(), pData, pData + dwLen);
        return Drain(outType, outPayload);
    }
    // drain the next already-buffered packet (no new bytes)
    bool Drain(uint16_t& outType, std::vector<uint8_t>& outPayload) {
        for (;;) {
            if (m_buf.size() < sizeof(tq::MsgHead)) return false;
            tq::MsgHead head;
            std::memcpy(&head, m_buf.data(), sizeof(head));
            if (head.length < sizeof(tq::MsgHead) || head.length > 8192) {
                m_buf.clear(); // poisoned stream: resync is impossible, drop
                return false;
            }
            if (m_buf.size() < head.length) return false;
            outType = head.type;
            outPayload.assign(m_buf.begin() + sizeof(tq::MsgHead),
                              m_buf.begin() + head.length);
            m_buf.erase(m_buf.begin(), m_buf.begin() + head.length);
            return true;
        }
    }
private:
    std::vector<uint8_t> m_buf;
};

inline void CopyStr(char* pDst, uint32_t dwCap, const std::string& str) {
    std::memset(pDst, 0, dwCap);
    std::strncpy(pDst, str.c_str(), dwCap - 1);
}

} // namespace cross
