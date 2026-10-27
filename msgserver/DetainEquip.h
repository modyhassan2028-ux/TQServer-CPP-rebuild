#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

class CMySQLClient;

// ORIGINAL: cq_action 2205 (case 0x89d) consults the DetainEquip module:
// CurrentInstanceGet()->GetProcess(0x13) - DetainEquip.dll registers
// SetProcess mode 19 (0x13). Processor vtable +0x18 = IsTarget(uid),
// +0x10 = IsHunter(uid). The module persists detainments in cq_pk_item
// ("insert into cq_pk_item(item, target, target_name, hunter,
// hunter_name, manhunt_time, bonus) values(...)" / "DELETE FROM
// cq_pk_item WHERE id=%u LIMIT 1" - DetainEquip.dll.decompiled.c).
//
// Interim carrier until the full module port (cqserver module ABI): the
// two vtable slots read the module's own persistence table directly.
class CDetainEquipManager {
public:
    static CDetainEquipManager& Instance() {
        static CDetainEquipManager s;
        return s;
    }

    // vtable +0x18: is the user a TARGET (detained equipment to redeem)?
    bool IsTarget(uint32_t dwUid, CMySQLClient* pDB) {
        return Count(pDB, "target", dwUid) != 0;
    }
    // vtable +0x10: is the user a HUNTER (holding detained equipment)?
    bool IsHunter(uint32_t dwUid, CMySQLClient* pDB) {
        return Count(pDB, "hunter", dwUid) != 0;
    }

private:
    CDetainEquipManager() = default;
    static uint64_t Count(CMySQLClient* pDB, const char* szCol, uint32_t dwUid) {
        if (!pDB) return 0; // ORIGINAL: no db -> the check returns false
        char sql[128];
        snprintf(sql, sizeof(sql), "SELECT count(*) FROM cq_pk_item WHERE %s=%u", szCol, dwUid);
        return strtoull(pDB->Scalar(sql, "0").c_str(), nullptr, 10);
    }
};
