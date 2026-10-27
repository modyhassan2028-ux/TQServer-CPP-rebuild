// D86: RAW-verbatim port of FUN_1417873a0.
#include "modules/syndicate/src/SyndicateRankName.h"
namespace syndicate {
void* (*g_fnD86StrMgr)();
void* (*g_fnD86GetStr)(void*, const char*);
void* SyndicateRankName(int nRank) {
    void* pMgr = g_fnD86StrMgr();
    if (nRank < 0x1a5) {
        if (nRank == 0x1a4)
            return g_fnD86GetStr(pMgr, "STR_SYN_COMMANDER_MATE");
        if (nRank == 200)
            return g_fnD86GetStr(pMgr, "STR_SYN_MEMBER");
        if (nRank == 0xd2)
            return g_fnD86GetStr(pMgr, "STR_SYN_SENIOR_MEMBER");
    } else if (nRank < 0x349) {
        if (nRank == 0x348)
            return g_fnD86GetStr(pMgr, "STR_SYN_HONOR_ASSEMBLYMAN");
        switch (nRank) {
        case 0x1ea: return g_fnD86GetStr(pMgr, "STR_SYN_ELITE_MEMBER");
        case 0x1eb: return g_fnD86GetStr(pMgr, "STR_SYN_LILY_ELITE_MEMBER");
        case 0x1ec: return g_fnD86GetStr(pMgr, "STR_SYN_FLOWER_R_ELITE_MEMBER");
        case 0x1ed: return g_fnD86GetStr(pMgr, "STR_SYN_PK_ELITE_MEMBER");
        case 0x1ee: return g_fnD86GetStr(pMgr, "STR_SYN_EDU_ELITE_MEMBER");
        case 0x1ef: return g_fnD86GetStr(pMgr, "STR_SYN_MONEY_ELITE_MEMBER");
        case 0x1f0: return g_fnD86GetStr(pMgr, "STR_SYN_TOTEM_ELITE_MEMBER");
        case 0x1f1: return g_fnD86GetStr(pMgr, "STR_SYN_EMONEY_ELITE_MEMBER");
        case 0x1f2: return g_fnD86GetStr(pMgr, "STR_SYN_FLOWER_W_ELITE_MEMBER");
        case 0x1fe: return g_fnD86GetStr(pMgr, "STR_SYN_VIZIR_ASSISTANT");
        case 0x1ff: return g_fnD86GetStr(pMgr, "STR_SYN_ASSEMBLYMAN_ASSISTANT");
        case 0x208: return g_fnD86GetStr(pMgr, "STR_SYN_VIZIR_MATE");
        case 0x209: return g_fnD86GetStr(pMgr, "STR_SYN_ASSEMBLYMAN_MATE");
        case 0x24e: return g_fnD86GetStr(pMgr, "STR_SYN_EXECUTIVE_OFFICER");
        case 0x24f: return g_fnD86GetStr(pMgr, "STR_SYN_LILY_EXEC_OFFICER");
        case 0x250: return g_fnD86GetStr(pMgr, "STR_SYN_FLOWER_R_EXEC_OFFICER");
        case 0x251: return g_fnD86GetStr(pMgr, "STR_SYN_PK_EXEC_OFFICER");
        case 0x252: return g_fnD86GetStr(pMgr, "STR_SYN_EDU_EXEC_OFFICER");
        case 0x253: return g_fnD86GetStr(pMgr, "STR_SYN_MONEY_EXEC_OFFICER");
        case 0x254: return g_fnD86GetStr(pMgr, "STR_SYN_TOTEM_EXEC_OFFICER");
        case 0x255: return g_fnD86GetStr(pMgr, "STR_SYN_EMONEY_EXEC_OFFICER");
        case 0x256: return g_fnD86GetStr(pMgr, "STR_SYN_FLOWER_W_EXEC_OFFICER");
        case 0x25a: return g_fnD86GetStr(pMgr, "STR_SYN_LEADER_FAVORITE");
        case 0x262: return g_fnD86GetStr(pMgr, "STR_SYN_LEADER_MATE_ASSISTANT");
        case 0x263: return g_fnD86GetStr(pMgr, "STR_SYN_VICE_LEADER_ASSISTANT");
        case 0x26c: return g_fnD86GetStr(pMgr, "STR_SYN_VICE_LEADER_MATE");
        case 0x28a: return g_fnD86GetStr(pMgr, "STR_SYN_VICE_COMMANDER");
        case 0x2a8: return g_fnD86GetStr(pMgr, "STR_SYN_HONOR_COMMANDER");
        case 0x2b2: return g_fnD86GetStr(pMgr, "STR_SYN_COMMANDER");
        }
    } else {
        switch (nRank) {
        case 0x352: return g_fnD86GetStr(pMgr, "STR_SYN_ASSEMBLYMAN");
        case 0x353: return g_fnD86GetStr(pMgr, "STR_SYN_LILY_ASSEMBLYMAN_RANK");
        case 0x354: return g_fnD86GetStr(pMgr, "STR_SYN_FLOWER_R_ASSEMBLYMAN");
        case 0x355: return g_fnD86GetStr(pMgr, "STR_SYN_PK_ASSEMBLYMAN");
        case 0x356: return g_fnD86GetStr(pMgr, "STR_SYN_EDU_ASSEMBLYMAN");
        case 0x357: return g_fnD86GetStr(pMgr, "STR_SYN_MONEY_ASSEMBLYMAN");
        case 0x358: return g_fnD86GetStr(pMgr, "STR_SYN_TOTEM_ASSEMBLYMAN");
        case 0x359: return g_fnD86GetStr(pMgr, "STR_SYN_EMONEY_ASSEMBLYMAN");
        case 0x35a: return g_fnD86GetStr(pMgr, "STR_SYN_FLOWER_W_ASSEMBLYMAN");
        case 0x35b: return g_fnD86GetStr(pMgr, "STR_SYN_LUTIP_ASSEMBLYMAN");
        case 0x370: return g_fnD86GetStr(pMgr, "STR_SYN_HONOR_VIZIR");
        case 0x37a: return g_fnD86GetStr(pMgr, "STR_SYN_VIZIR");
        case 0x398: return g_fnD86GetStr(pMgr, "STR_SYN_LEADER_MATE");
        case 0x3d4: return g_fnD86GetStr(pMgr, "STR_SYN_HONOR_VICE_LEADER");
        case 0x3de: return g_fnD86GetStr(pMgr, "STR_SYN_VICE_LEADER");
        case 1000: return g_fnD86GetStr(pMgr, "STR_SYN_LEADER");
        }
    }
    return g_fnD86GetStr(pMgr, "STR_ERROR");
}
} // namespace syndicate
