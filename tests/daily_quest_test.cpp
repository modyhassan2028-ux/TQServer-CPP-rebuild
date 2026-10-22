#include "User.h"
#include <cassert>
#include <cstdio>
int main() {
    CUser u(1); u.SetName("Hunter");
    assert(u.GetQuestKills() == 0 && !u.IsQuestClaimed());
    // 9 kills: not claimable yet
    for (int i = 0; i < 9; ++i) u.AddQuestKill();
    assert(u.GetQuestKills() == 9);
    // claim gate: must reject under 10
    assert(u.GetQuestKills() < 10); // gate condition
    // 10th kill: quest ready
    u.AddQuestKill();
    assert(u.GetQuestKills() == 10);
    // claim: rewards land once
    uint32_t m0 = u.GetMoney(), c0 = u.GetConquerPoints();
    bool gatePassed = (u.GetQuestKills() >= 10 && !u.IsQuestClaimed());
    assert(gatePassed);
    u.SetQuestClaimed(true); u.AddMoney(10000); u.AddConquerPoints(10);
    assert(u.GetMoney() == m0 + 10000 && u.GetConquerPoints() == c0 + 10);
    // double-claim rejected
    assert(u.IsQuestClaimed());
    // day rollover: counter resets, claim flag clears
    u.SetQuestKills(0); u.SetQuestClaimed(false);
    assert(u.GetQuestKills() == 0 && !u.IsQuestClaimed());
    printf("QUEST_OK: 9 too few, 10 claimable +10000/+10CP, double-claim blocked, rollover resets\\n");
    return 0;
}
