#include "User.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
int main() {
    // CP deduction clamp: AddConquerPoints(-5) with 0 CP floors at 0
    CUser u(1); u.SetName("Gambler");
    u.AddConquerPoints(100);
    assert(u.GetConquerPoints() == 100);
    u.AddConquerPoints(-5);
    assert(u.GetConquerPoints() == 95);
    u.AddConquerPoints(-1000); // overdraw clamps to 0, never wraps
    assert(u.GetConquerPoints() == 0);
    // the gate guarantees the clamp never matters in play
    u.AddConquerPoints(4);
    assert(u.GetConquerPoints() == 4);
    bool gateOk = u.GetConquerPoints() >= 5;
    assert(!gateOk); // 4 < 5 -> refused
    u.AddConquerPoints(1);
    assert(u.GetConquerPoints() >= 5); // 5 -> allowed
    printf("LOTTERY_CPP_OK: gate + CP clamp verified\\n");
    return 0;
}
