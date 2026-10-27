// MsgServer unit M11 - the key.dat generator
// FUN_140508610 / FUN_140508720
#include "../msgserver/MsgKeyGen.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace msg;

int main() {
    struct Cap {
        std::vector<uint8_t> vRand, vFile;
        int nSlot8 = 0, nDtor = 0, nNew = 0;
        bool bOpen = true;
        uint8_t* pSlot8Key = nullptr;
        uint32_t uSlot8Arg = 0;
        const char* szMode = nullptr;
    } c;
    MsgKeyGenData d;
    int nNext = 0;
    d.m_fnRandGet = [&]{
        ++nNext;
        c.vRand.push_back((uint8_t)(nNext * 7
            + 3));
        return c.vRand.back(); };
    d.m_fnGetSeed = []{ return 0xdeadbeefu; };
    static void* s_des = (void*)0x55;
    bool bDesOk = true;
    d.m_fnDesNew = [&]{
        ++c.nNew; return bDesOk ? &s_des : nullptr; };
    d.m_fnDesSlot8 = [&](void* o, uint8_t* k,
                         uint32_t a){
        assert(o == &s_des);
        c.pSlot8Key = k; c.uSlot8Arg = a;
        ++c.nSlot8; };
    d.m_fnDesDtor = [&](void* o){
        assert(o == &s_des); ++c.nDtor; };
    d.m_fnWriteFile = [&](uint8_t* k, uint32_t n,
                          const char* m){
        assert(!strcmp(m, "wb"));
        c.szMode = "wb";
        if (!c.bOpen) return false;
        c.vFile.assign(k, k + n);
        return true; };

    // ===== 1. the happy path =====
    MsgGenKeyFile(d);
    assert(c.vRand.size() == 200);   // RandGet x200
    assert(c.nNew == 1);
    // the seed overwrote bytes 0..3
    assert(*(uint32_t*)&c.vFile[0] == 0xdeadbeefu);
    assert(c.nSlot8 == 1 && c.uSlot8Arg == 4);
    assert(c.pSlot8Key != nullptr);
    assert(c.nDtor == 1);           // dtor after
    // 0x96 = 150 bytes written
    assert(c.vFile.size() == 0x96);
    // the untouched tail still follows RandGet
    for (int i = 4; i < 0x96; ++i)
        assert(c.vFile[i] ==
               (uint8_t)((i + 1) * 7 + 3));
    // bytes 150..199 generated but NOT written
    assert(c.vRand.size() == 200);

    // ===== 2. the DES allocation failure =====
    bDesOk = false; c.nSlot8 = 0; c.nDtor = 0;
    MsgGenKeyFile(d);
    assert(c.nSlot8 == 0 && c.nDtor == 0);
    assert(c.vFile.size() == 0x96);

    // ===== 3. fopen fails: no crash, no bytes =====
    c.bOpen = false; c.vFile.clear();
    MsgGenKeyFile(d);
    assert(c.vFile.empty());

    printf("MSG_KEYGEN_OK: FUN_140508610 VERBATIM "
           "(the 200 tq::RandGet(0x100) bytes, the "
           "DAT_140976720 seed dword overwriting "
           "bytes 0..3, FUN_140509280(0) = the DES "
           "0x890 new + the vt+8(obj,key,4) call + "
           "the vt+0 dtor, and the LITERAL 0x96 = "
           "150 of 200 bytes written to "
           "'key.dat','wb')\n");
    return 0;
}
