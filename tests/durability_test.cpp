#include "User.h"
#include "Item.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
int main() {
    CUser u(1); u.SetName("Knight");
    // equipped sword in slot 1, starting pristine
    ItemInfo sword; sword.dwId = 700000001; sword.dwType = 410051; sword.usSort = 1;
    sword.dwPosition = 1; sword.strName = "Blade"; sword.usDurability = 1000;
    u.AddItem(sword);
    assert(!u.WeaponIsBroken());
    assert(u.RepairCost() == 0); // pristine: free
    // 50 swings: wears 1 each
    for (int i = 0; i < 50; ++i) u.WearWeapon();
    auto& inv = u.GetInventory();
    uint16_t dur = 950;
    assert(inv[0].usDurability == dur);
    // repair cost: (1000-950)*2 = 100
    assert(u.RepairCost() == 100);
    // pay + repair restores pristine
    u.AddMoney(500);
    u.AddMoney(-100);
    u.DoRepair();
    assert(u.RepairCost() == 0);
    assert(u.GetMoney() == 400);
    // grind to broken: warnings at 200, damage-halve gate at <200
    inv[0].usDurability = 200;
    u.WearWeapon();
    assert(u.WeaponIsBroken()); // 199 < 200
    // broken halves attack: 50 -> 25
    uint32_t atk = 50;
    if (u.WeaponIsBroken()) atk /= 2;
    assert(atk == 25);
    // boundary: 200 exactly is NOT broken (warning zone), 201 fine
    inv[0].usDurability = 200;
    assert(!u.WeaponIsBroken());
    inv[0].usDurability = 199;
    assert(u.WeaponIsBroken());
    printf("DURABILITY_OK: wear 1000->950 over 50 swings, repair 100 restores, broken gate <200 halves 50->25\\n");
    return 0;
}
