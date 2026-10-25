// MsgServer unit M29 - the CMD5Checksum
// object family + the two REAL vftables
#include "../Exe/MsgServer/Port/MsgMd5Object.h"
#include "../Exe/MsgServer/Port/MsgMd5Ctor.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

int main() {
    // ===== 1. the vftable addresses
    // (extracted from the binary:
    // file 0x799eb8 / 0x799f28)
    assert(g_pMd5ChecksumVt ==
        (const void*)0x14079b8b8ULL);
    assert(g_pMd5StandardVt ==
        (const void*)0x14079b928ULL);

    // ===== 2. the M25 ctor now stamps
    // the REAL vftable (was a marker)
    unsigned char obj[0x60];
    MsgMd5ChecksumCtor(obj);
    assert(*(void**)obj == g_pMd5ChecksumVt);

    // ===== 3. the vftable-only ctors
    // (FUN_140509110 / FUN_1405091f0)
    std::memset(obj, 0xEE, sizeof(obj));
    MsgMd5SetVftable(obj);
    assert(*(void**)obj == g_pMd5ChecksumVt);

    // ===== 4. the guarded dtor
    // dispatches vt+0x30(this, 1)
    static int nSlot6Calls = 0;
    static void* pLast = nullptr;
    static int nLastArg = -1;
    struct Slot6 {
        static void call(void* p, int a) {
            pLast = p; nLastArg = a;
            ++nSlot6Calls; } };
    void* slots[8];
    slots[6] = (void*)&Slot6::call;
    *(void***)obj = slots;   // fake vt
    assert(MsgMd5Dtor(obj) == 0);
    assert(nSlot6Calls == 1);
    assert(pLast == obj);
    assert(nLastArg == 1);
    // null -> nothing
    nSlot6Calls = 0;
    assert(MsgMd5Dtor(nullptr) == 0);
    assert(nSlot6Calls == 0);
    // returns 0 always
    MsgMd5Dtor(obj);
    assert(MsgMd5Dtor(obj) == 0);

    // ===== 5. the stubs
    assert(MsgMd5Stub140() == 0);
    assert(MsgMd5Stub160() == 0);
    MsgMd5Stub150();
    MsgMd5Stub170();

    // ===== 6. the deleting dtors
    // (FUN_140509180 / FUN_140509240)
    MsgMd5ObjData d;
    bool bDeleted = false;
    d.m_fnDelete = [&](void* p) {
        bDeleted = true;
        assert(p == obj); };
    MsgMd5SetVftable(obj);
    assert(MsgMd5DeletingDtor(obj, 1, d)
        == obj);
    assert(bDeleted && d.nDeletes == 1);
    assert(*(void**)obj == g_pMd5ChecksumVt);
    // flag 0: no delete
    bDeleted = false;
    assert(MsgMd5DeletingDtor(obj, 0, d)
        == obj);
    assert(!bDeleted && d.nDeletes == 1);

    // ===== 7. the STANDARD ctor
    // (FUN_1405091b0): the M25 ctor then
    // the vftable swap (channel 2!)
    std::memset(obj, 0xAB, sizeof(obj));
    assert(MsgMd5StandardCtor(obj) == obj);
    assert(*(void**)obj == g_pMd5StandardVt);
    // the M25 state was initialized
    uint32_t a;
    std::memcpy(&a, obj + 0x50, 4);
    assert(a == 0x67452301);
    std::memcpy(&a, obj + 0x5c, 4);
    assert(a == 0x10325476);

    printf("MSG_MD5_OBJECT_OK: "
           "FUN_140509110/120/140/150/160/"
           "170/180/240/1b0/1f0 VERBATIM "
           "+ the two REAL vftables from "
           "0x14079b8b8/0x14079b928 "
           "(Checksum: 120-aa70-140-150-"
           "160-170-180; Standard: the "
           "same with aa70->a7f0 and "
           "180->240), the guarded "
           "vt+0x30(this,1) dtor, the "
           "vftable restore + flag-gated "
           "delete, and the Standard ctor "
           "= the M25 ctor + the channel-2 "
           "vftable swap)\n");
    return 0;
}
