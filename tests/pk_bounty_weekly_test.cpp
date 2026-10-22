// pure logic: PK bounty math + weekly champion selection (PKBounty.h)
#include "../Exe/MsgServer/PKBounty.h"
#include <cassert>
#include <cstdio>
#include <string>

int main() {
    using namespace pk;

    // bounty money scales with outlaw level and blood on the name
    assert(BountyMoney(10, 0) == 2000);
    assert(BountyMoney(50, 30) == 11500);   // 200*50 + 50*30
    assert(BountyMoney(1, 100) == 5200);     // 200 + 5000

    // bounty CP: flat 10 + pk/10
    assert(BountyCp(0) == 10);
    assert(BountyCp(30) == 13);
    assert(BountyCp(100) == 20);

    // slain outlaw loses half their PK points
    assert(PkAfterBountyDeath(100) == 50);
    assert(PkAfterBountyDeath(31) == 15);
    assert(PkAfterBountyDeath(0) == 0);

    // champion needs kMinWeeklyWins and a strict majority
    assert(PickWeeklyChampion({}) == "");
    assert(PickWeeklyChampion({{"Alpha", 1}}) == "");          // 1 win: not enough
    assert(PickWeeklyChampion({{"Alpha", 2}}) == "Alpha");     // exactly 2 crowns
    assert(PickWeeklyChampion({{"Alpha", 5}, {"Beta", 3}}) == "Alpha");
    assert(PickWeeklyChampion({{"Alpha", 3}, {"Beta", 3}}) == "");  // tie: nobody
    assert(PickWeeklyChampion({{"Alpha", 3}, {"Beta", 3}, {"Gamma", 4}}) == "Gamma");

    // champion fund bonus
    assert(ChampionFundBonus() == 1000000ull);

    printf("PK_BOUNTY_WEEKLY_OK: bounty money/CP math, pk relief, champion min-wins/tie rules\\n");
    return 0;
}
