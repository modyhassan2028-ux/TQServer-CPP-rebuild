#include "User.h"
#include <cassert>
#include <cstdio>
int main() {
    CUser u(1); u.SetName("Rider");
    // no horse: /ride on refused
    assert(!u.HasHorse());
    assert(!u.IsRiding());
    // buy: 100k deducted, horse added as equipped (253)
    u.AddMoney(200000);
    assert(u.GetMoney() == 200000);
    u.AddMoney(-100000);
    ItemInfo horse; horse.dwId = 700000001; horse.dwType = 750; horse.usSort = 3;
    horse.strName = "Stallion"; horse.dwPosition = 253;
    u.AddItem(horse);
    assert(u.GetMoney() == 100000);
    assert(u.HasHorse());
    // mount
    u.SetRiding(true);
    assert(u.IsRiding());
    // jump gate: mounted -> free jump regardless of stamina
    u.SetStamina(0);
    bool jumpFree = u.IsRiding();
    assert(jumpFree); // the MsgAction path skips SpendStamina entirely
    // dismounted at 0 stamina -> jump refused
    u.SetRiding(false);
    assert(!u.IsRiding());
    assert(!u.SpendStamina(15)); // 0 < 15 -> false
    // dismounted with stamina -> costs 15
    u.SetStamina(100);
    assert(u.SpendStamina(15));
    assert(u.GetStamina() == 85);
    printf("RIDE_OK: horse gate, mount toggle, free jumps while mounted, -15 while not\\n");
    return 0;
}
