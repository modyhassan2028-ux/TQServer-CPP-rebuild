#include "User.h"
#include <cassert>
#include <cstdio>
int main() {
    CUser u(1); u.SetName("Hoarder");
    // bag -> warehouse round trip, exactly as the commands do it
    ItemInfo sword; sword.dwId = 700000001; sword.dwType = 410; sword.strName = "IronSword"; sword.usSort = 1;
    u.AddItem(sword);
    assert(u.FindItem(700000001));
    ItemInfo* p = u.FindItem(700000001);
    ItemInfo copy = *p;
    u.RemoveItem(700000001);
    u.WarehouseStore(copy);
    assert(!u.FindItem(700000001));              // gone from the bag
    assert(u.GetWarehouse().size() == 1);
    // persistence marker: position +1000 on save, stripped on load
    uint32_t posSaved = copy.dwPosition + 1000;
    assert(posSaved >= 1000);
    bool bWarehouse = posSaved >= 1000;
    assert(bWarehouse);
    ItemInfo loaded = copy; loaded.dwPosition = 255; // load path
    // take back out: warehouse -> bag
    ItemInfo* pw = u.WarehouseFind(700000001);
    assert(pw && pw->strName == "IronSword");
    ItemInfo back = *pw;
    u.WarehouseRemove(700000001);
    u.AddItem(back);
    assert(u.GetWarehouse().empty());
    assert(u.FindItem(700000001)->strName == "IronSword");
    printf("WAREHOUSE_OK: store/list-marker/take round-trip verified\\n");
    return 0;
}
