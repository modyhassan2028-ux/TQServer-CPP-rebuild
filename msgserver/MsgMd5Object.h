// ============================================================
// MsgServer strict port - unit M29
// The CMD5Checksum object family +
// BOTH vftables EXTRACTED FROM THE
// BINARY (file 0x799eb8 / 0x799f28):
//  CMD5Checksum::vftable
//   @ 0x14079b8b8:
//   +0x00 FUN_140509120 (the guarded
//         deleting-dtor dispatch)
//   +0x08 FUN_14050aa70 (Update - a
//         later unit)
//   +0x10 FUN_140509140 (ret 0)
//   +0x18 FUN_140509150 (ret void)
//   +0x20 FUN_140509160 (ret 0)
//   +0x28 FUN_140509170 (ret void)
//   +0x30 FUN_140509180 (vftable
//         restore + optional delete)
//  CMD5ChecksumStandard::vftable
//   @ 0x14079b928: the same except
//   +0x08 FUN_14050a7f0 (the Standard
//   Update - a later unit) and
//   +0x30 FUN_140509240.
// ORIGINALS:
//  FUN_140509110 / FUN_1405091f0:
//   *obj = the CMD5Checksum vftable
//  FUN_140509120: if obj -> vt+0x30(
//   obj, 1); returns 0
//  FUN_140509140/160: return 0
//  FUN_140509150/170: return void
//  FUN_140509180/240: *obj = the
//   vftable; if (b & 1) delete(obj);
//   return obj
//  FUN_1405091b0: FUN_14050a570 (the
//   M25 ctor) then *obj = the
//   STANDARD vftable (the channel-2
//   swap of the M24 factory)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

// the REAL vftable addresses
// (extracted, verbatim)
extern const void* g_pMd5ChecksumVt;
extern const void* g_pMd5StandardVt;

struct MsgMd5ObjData {
    std::function<void(void*)> m_fnDelete
        = [](void*) {};
    int nDeletes = 0;
};

// ===== FUN_140509110 / FUN_1405091f0
void MsgMd5SetVftable(void* pObj);
// ===== FUN_140509120
uint64_t MsgMd5Dtor(void* pObj);
// ===== the stubs
uint64_t MsgMd5Stub140();
void MsgMd5Stub150();
uint64_t MsgMd5Stub160();
void MsgMd5Stub170();
// ===== FUN_140509180 / FUN_140509240
void* MsgMd5DeletingDtor(void* pObj,
                          uint8_t bFlags,
                          MsgMd5ObjData& rD);
// ===== FUN_1405091b0
void* MsgMd5StandardCtor(void* pObj);

} // namespace msg
