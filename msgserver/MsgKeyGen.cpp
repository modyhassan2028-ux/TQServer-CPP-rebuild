#include "MsgKeyGen.h"

namespace msg {

// ===== ORIGINAL FUN_140508610 @ 140508610 =====
void MsgGenKeyFile(MsgKeyGenData& rD) {
    // local_e8: 200 bytes (of a 208 block)
    uint8_t key[200];
    for (int i = 0; i < 200; ++i)
        key[i] = (uint8_t)rD.m_fnRandGet();
    // local_e8[0] = DAT_140976720 (the seed
    // dword overwrites the first 4 bytes)
    uint32_t uSeed = rD.m_fnGetSeed();
    *(uint32_t*)key = uSeed;
    // FUN_140509280(0, &local_f8) = new DES
    void* pDes = rD.m_fnDesNew();
    if (pDes != nullptr) {
        rD.m_fnDesSlot8(pDes, key, 4);
        rD.m_fnDesDtor(pDes);
    }
    // fopen("key.dat","wb") + fwrite(0x96)
    rD.m_fnWriteFile(key, 0x96, "wb");
}

} // namespace msg
