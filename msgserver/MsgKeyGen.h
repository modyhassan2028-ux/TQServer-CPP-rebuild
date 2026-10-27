// ============================================================
// MsgServer strict port - unit M11
// ORIGINAL: the key.dat generator
//  FUN_140508610 (the generator)
//  FUN_140508720 (the seed setter:
//    DAT_140976720 = FUN_1405082d0())
//  FUN_1405082d0 (the machine fingerprint
//    seed - seam here, 0x2c58 stack, module
//    identity hash in the ORIGINAL)
// The LITERAL flow of FUN_140508610:
//  200 bytes via tq::RandGet(0x100) ->
//  key[0..3] = the seed DAT_140976720 ->
//  FUN_140509280(0, &obj) = new DES(0x890),
//    DES::vftable ->
//  if (obj) { vt+8(obj, key, 4);
//             vt+0(obj); }        (the dtor)
//  -> fopen("key.dat","wb") ->
//     fwrite(key, 0x96, 1, f);
//     fclose(f)
// NOTE the literal size split: 200 generated
//  but only 0x96 = 150 written to key.dat
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgKeyGenData {
    // tq::RandGet(0x100) -> 0..255
    std::function<int()> m_fnRandGet;
    // FUN_1405082d0 (the machine seed)
    std::function<uint32_t()> m_fnGetSeed;
    // FUN_140509280(0,...): new DES(0x890)
    // (null models the allocation failure)
    std::function<void*()> m_fnDesNew;
    // the vt+8 slot call: (obj, key, 4)
    std::function<void(void*, uint8_t*,
                       uint32_t)> m_fnDesSlot8;
    // the vt+0 slot call (the dtor)
    std::function<void(void*)> m_fnDesDtor;
    // fopen("key.dat","wb") -> fwrite -> fclose
    // returns true when the file was opened
    std::function<bool(uint8_t*, uint32_t,
                       const char* mode)>
        m_fnWriteFile;
};

// ===== ORIGINAL FUN_140508610 @ 140508610 =====
void MsgGenKeyFile(MsgKeyGenData& rD);

// ===== ORIGINAL FUN_140508720 @ 140508720 =====
// inline in the ORIGINAL: DAT_140976720 =
//   FUN_1405082d0()

} // namespace msg
