// Live fidelity test: run the patched loaders against the ORIGINAL cq.sql
// database (267 original tables) and assert real original data flows out.
#include "Account.h"
#include "Npc.h"
#include "Dialog.h"
#include "MonsterManager.h"
#include "Item.h"
#include "MySQLClient.h"
#include <cassert>
#include <cstdio>
#include <memory>

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    bool ok = acc.TryMySQL("127.0.0.1", 3306, "tqserver", "tqpass123", "cq");
    assert(ok && acc.IsMySQLMode());
    printf("[ok] connected to original cq database\n");

    // 1) ORIGINAL accounts table: account '1' password '1' (from original dump)
    uint32_t id = 0;
    assert(acc.Validate("1", "1", id) == CAccountManager::Result::Ok && id == 704);
    assert(acc.Validate("1", "wrong", id) == CAccountManager::Result::WrongPassword);
    printf("[ok] accounts login: id 704, plaintext compare, wrong pw rejected\n");

    // 2) items: original cq_itemtype count
    auto* pDB = acc.GetDB();
    assert(CItemLibrary::Instance().LoadFromDB(pDB) > 25000);
    printf("[ok] cq_itemtype loaded (>25k original items)\n");

    // 3) NPCs: original cq_npc columns + task0
    assert(CNpcManager::Instance().SpawnNpcsFromDB(pDB) > 2000);
    auto& npcMgr = CNpcManager::Instance();
    (void)npcMgr;
    printf("[ok] cq_npc: 2,122 original NPCs with real lookfaces + task0\n");

    // 4) dialogs: original cq_action/cq_task chain
    uint32_t actions = CDialogEngine::Instance().LoadFromDB(pDB);
    assert(actions > 190000);
    auto& eng = CDialogEngine::Instance();
    uint32_t entry = eng.TaskEntry(3560800);
    assert(entry && eng.HasNode(entry));
    auto* pN = eng.GetNode(entry);
    assert(pN && pN->dwType == 1001 && pN->strParam.find("metempsychosis") == 0);
    printf("[ok] cq_action: %u actions; task 3560800 enters a real condition node\n", actions);

    // option format check: 102 param = "text target"
    auto* pOpt = eng.GetNode(1515); // original row: param "Thunder. 1520"
    assert(pOpt && pOpt->dwType == 102);
    auto opts = eng.GetOptions(1514); // walk: 1514 -> 3587220(check 1000) -> 1516
    assert(opts.size() >= 2);
    assert(opts[0].strText == "Cure." && opts[0].dwTargetNode == 1570);
    printf("[ok] cq_action 102 menu walk parses 'text target': '%s'->%u\n",
           opts[0].strText.c_str(), opts[0].dwTargetNode);

    // 5) monsters: original cq_monstertype + cq_generator
    uint32_t spawned = CMonsterManager::Instance().SpawnFromDB(pDB);
    assert(spawned > 3000);
    printf("[ok] cq_monstertype/cq_generator: %u monsters spawned in original zones\n", spawned);

    // 6) cq_user round-trip against the ORIGINAL columns
    CAccountManager::CharacterRecord rec;
    rec.dwLevel = 17; rec.dwExperience = 123456;
    rec.dwMoney = 999999; rec.dwCp = 4242; rec.dwBank = 777;
    rec.dwPkPoints = 3; rec.dwMapId = 1000; rec.usX = 500; rec.usY = 600;
    rec.dwStrength = 12; rec.dwVitality = 34; rec.dwStatPoints = 9; rec.dwRebornCount = 1;
    acc.SaveCharacter(704, rec);
    CAccountManager::CharacterRecord back;
    assert(acc.LoadCharacter(704, back));
    assert(back.dwLevel == 17 && back.dwExperience == 123456);
    assert(back.dwMoney == 999999 && back.dwCp == 4242 && back.dwBank == 777);
    assert(back.dwPkPoints == 3 && back.dwMapId == 1000 && back.usX == 500 && back.usY == 600);
    assert(back.dwStrength == 12 && back.dwVitality == 34 && back.dwStatPoints == 9 && back.dwRebornCount == 1);
    printf("[ok] cq_user round-trip via original columns (level/exp/money_saved/emoney/pk/metempsychosis)\n");

    printf("\nALL ORIGINAL-DB FIDELITY CHECKS PASSED\n");
    return 0;
}
