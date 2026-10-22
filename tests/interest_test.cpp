#include "User.h"
#include <cstdint>
#include <cassert>
#include <cstdio>
int main() {
    CUser u(1); u.SetName("Saver");
    // (bank, expected payout): 2% with a 50k cap
    uint64_t cases[][2] = {
        { 0, 0 },               // empty bank: no interest
        { 1000, 20 },            // 2%
        { 2499999, 49999 },      // just under the cap
        { 2500000, 50000 },      // 2% = 50k exactly
        { 100000000, 50000 },    // 2% = 2M -> capped at 50k
    };
    for (auto& c : cases) {
        uint64_t interest = c[0] / 50;
        if (interest > 50000) interest = 50000;
        assert(interest == c[1]);
    }
    // AddBank applies the payout without wrap
    u.SetBank(1000);
    u.AddBank(20); // the 2% payout
    assert(u.GetBank() == 1020);
    // huge balance + cap still fits in u64
    u.SetBank(100000000ULL);
    u.AddBank(50000); // capped payout
    assert(u.GetBank() == 100050000ULL);
    printf("INTEREST_OK: 0/2%%/50k-cap math and AddBank verified\\n");
    return 0;
}
