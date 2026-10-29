// ============================================================================
// CMsgLeagueConcubinesInfoPB.h — protobuf lite message, RAW Syndicate.dll v6159
//   vtable 0x1418415e8, 12 slots
//   0  0x1417eaf70  deleting dtor (base 0x1417eabe0)
//   1  0x1417ea850  GetTypeName -> "CMsgLeagueConcubinesInfoPB"
//   2  0x1417eac50  New (operator_new 0x68 + ctor 0x1417eaab0)
//   3  0x1417ea320  Clear
//   4  0x1417ea830  IsInitialized ((HasBits & 0x3ff) == 0x3ff)
//   5  0x1417de5c0  shared lite "cannot determine missing fields"
//   6  0x1417eb450  thunk: e9 0b f2 ff ff -> 0x1417dd260
//   7  0x1417eafa0  PENDING (12857 decompiled chars)
//   8  0x1417ea4c0  ByteSize (varint/len per field 1..10 + unknown)
//   9  0x1417ea380  SerializeWithCachedSizes
//  10  0x1417dee40  shared parse-from-string helper
//  11  0x1417eab30  GetCachedSize -> *(int*)(this+0x34)
// Layout from the ctor: vft 0x00, std::string 0x08, HasBits 0x30,
// cached size 0x34, fields 0x38..0x64.
#ifndef SYNDICATE_CMSGLEAGUECONCUBINESINFOPB_H
#define SYNDICATE_CMSGLEAGUECONCUBINESINFOPB_H
#include <cstdint>
#include <string>

namespace syndicate {

// seams
extern void     (*g_pfnPbFree)(void*);           // operator_delete
extern uint64_t (*g_pfnPb968050)();              // 1417e8050 (global init)
extern void*     g_pPbDefaultStr;                // DAT_141886ea0 sentinel
extern uint64_t (*g_pfnPb7DD260)(void*);         // 1417dd260 (slot6 target)
extern int64_t  (*g_pfnPbDEE40)(void*, int64_t);   // 1417dee40 (slot10)
// ---- D91 seams: the protobuf size/write kit ----
extern int32_t (*g_pfnPbVarintSize)(uint32_t);                  // 1417e4d40
extern void (*g_pfnPbWriteVarint32)(uint32_t, uint32_t, void*);  // 1417f4580
extern void (*g_pfnPbWriteString)(uint32_t, void*, void*);       // 1417f4c20
extern void (*g_pfnPbWriteBool)(uint32_t, char, void*);          // 1417f4820
extern void (*g_pfnPbWriteUnknown)(void*, void*, int32_t);       // 1417e46e0

class CMsgLeagueConcubinesInfoPB {
public:
    static constexpr uintptr_t kClassVft = 0x1418415e8;

    // 0x1417eabe0 — the class dtor body (writes both vtables)
    static void BaseDtor(void* self);
    // 0x1417eaab0 — the ctor body
    static void* Ctor(void* self);
    // 0x1417eaf70
    static void* DeleteDtor(void* self, uint32_t flag);
    // 0x1417ea850
    static void GetTypeName(std::string* out);
    // 0x1417eac50
    static void* New();
    // 0x1417ea320
    static void Clear(void* self);
    // 0x1417ea830
    static bool IsInitialized(void* self);
    // 0x1417de5c0
    static void MissingFieldsLite(std::string* out);
    // 0x1417eb450
    static uint64_t Slot6(void* self);
    // 0x1417dee40 — shared protobuf parse helper (kept as a seam,
    // its 1522-char body belongs to the lite base, not this class)
    static int64_t ParseFromString(void* self, int64_t lStr);
    // 0x1417ea4c0 — ByteSize
    static int32_t ByteSize(void* self);
    // 0x1417ea380 — SerializeWithCachedSizes
    static void SerializeWithCachedSizes(void* self, void* pBuf);
    // 0x1417eab30
    static uint32_t GetCachedSize(void* self);
};

}  // namespace syndicate
#endif
