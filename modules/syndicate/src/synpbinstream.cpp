// synpbinstream.cpp — verbatim bodies, RAW Syndicate.dll v6159
//   every line below is traceable to objdump -d -M intel output for
//   0x1417e5ca0 / 0x1417e5f20 / 0x1417e6050; the C dump agrees on all three.
#include "modules/syndicate/src/synpbinstream.h"

namespace tq {

// 0x1417e0d30 + 2x 0x1417e0990 + 0x1417e0ee0 + 0x1417e0da0, declared in the header
void (*g_pfnPbCheckFail2)(const char*, int32_t, const char*, const char*) = nullptr;

// the four .rdata literals (objdump -s --start-address=0x14183fea0 .. 0x1418400c0)
const char* const kSynPbZeroCopyLiteFile =
    "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc";
const char* const kSynPbChkLastReturnedPositive =
    "CHECK failed: (last_returned_size_) > (0): ";
const char* const kSynPbChkBackUpAfterNext =
    "BackUp() can only be called after a successful Next().";
const char* const kSynPbChkCountLeLastReturned =
    "CHECK failed: (count) <= (last_returned_size_): ";
const char* const kSynPbChkCountGeZeroBackUp =
    "CHECK failed: (count) >= (0): ";
const char* const kSynPbChkCountGeZeroSkip =
    "CHECK failed: (count) >= (0): ";

namespace {
inline int32_t& Pos(void* pSelf) {
    return *(int32_t*)((uint8_t*)pSelf + 0x18);
}
inline int32_t& LastReturned(void* pSelf) {
    return *(int32_t*)((uint8_t*)pSelf + 0x1c);
}
inline int32_t& Size(void* pSelf) {
    return *(int32_t*)((uint8_t*)pSelf + 0x10);
}
}  // namespace

// ============================================================================
// 0x1417e5ca0 — BackUp(int count)
//   void BackUp(int count) {
//     if (last_returned_size_ <= 0) {            // cmp [rax+0x1c],0 ; jle block
//       GOOGLE_CHECK_GT(last_returned_size_, 0)
//         << "BackUp() can only be called after a successful Next().";
//     }                                          // line 0x53 (83), TWO literals appended
//     if (count > last_returned_size_) {         // cmp count,eax ; jg block
//       GOOGLE_CHECK_LE(count, last_returned_size_);   // line 0x55 (85)
//     }
//     if (count < 0) {                           // cmp count,0 ; jl block
//       GOOGLE_CHECK_GE(count, 0);               // line 0x56 (86)
//     }
//     position_ -= count;                        // sub ecx,eax -> [rax+0x18]
//     last_returned_size_ = 0;                   // [rax+0x1c] = 0
//   }
//   No return value is produced: the tail is `add rsp,0x140; pop rdi; ret` with rax
//   holding the last `this` store, so the caller never consumes an answer.
// ============================================================================
void SynPbArrayInBackUp(void* pSelf, int32_t nCount) {
    // 1417e5cd0  cmp DWORD PTR [rax+0x1c],0x0 / 1417e5cd4 jle -> block A
    if (LastReturned(pSelf) <= 0) {
        // 1417e5ce9 r9d = 0x53, 1417e5cef r8 = 0x14183fea0, edx = 3
        // 1417e5d2e append 0x14183fef0, 1417e5d42 append 0x14183ff20
        // 1417e5d59 finish, 1417e5d7a entry dtor
        g_pfnPbCheckFail2(kSynPbZeroCopyLiteFile, 0x53,
                          kSynPbChkLastReturnedPositive,
                          kSynPbChkBackUpAfterNext);
    }
    // 1417e5d87 mov eax,[rax+0x1c] / 1417e5d8a cmp count,eax / 1417e5d91 jg -> block B
    if (nCount > LastReturned(pSelf)) {
        // 1417e5da3 r9d = 0x55, r8 = 0x14183ff60, append 0x14183ffb0 at 1417e5df7
        syndicate::g_pfnPbCheckFail(kSynPbZeroCopyLiteFile, 0x55,
                         kSynPbChkCountLeLastReturned);
    }
    // 1417e5e2a cmp count,0x0 / 1417e5e32 jl -> block C
    if (nCount < 0) {
        // 1417e5e47 r9d = 0x56, r8 = 0x14183fff0, append 0x141840040 at 1417e5e9e
        syndicate::g_pfnPbCheckFail(kSynPbZeroCopyLiteFile, 0x56,
                         kSynPbChkCountGeZeroBackUp);
    }
    // 1417e5edf mov eax,count / 1417e5ee6 mov ecx,[rcx+0x18] / 1417e5ee9 sub ecx,eax
    // 1417e5ef3 store -> +0x18.  RAW: plain 32-bit wrap, no saturation.
    Pos(pSelf) = (int32_t)((uint32_t)Pos(pSelf) - (uint32_t)nCount);
    // 1417e5efe mov DWORD PTR [rax+0x1c],0x0
    LastReturned(pSelf) = 0;
}

// ============================================================================
// 0x1417e5f20 — Skip(int count)
//   bool Skip(int count) {
//     if (count < 0) {                           // cmp [rsp+0xa8],0 ; jl block
//       GOOGLE_CHECK_GE(count, 0);               // line 0x5c (92), one literal
//     }
//     last_returned_size_ = 0;                   // 1417e5fd9, written BEFORE the test
//     if (count > size_ - position_) {           // cmp count, eax(size-pos) ; jle else
//       position_ = size_;                       // 1417e6001..1417e6014
//       return false;                            // xor al,al
//     }
//     position_ += count;                        // 1417e6025 add ecx,[rsp+0xa8]
//     return true;                               // mov al,0x1
//   }
// ============================================================================
bool SynPbArrayInSkip(void* pSelf, int32_t nCount) {
    // 1417e5f42 cmp DWORD PTR [rsp+0xa8],0x0 / 1417e5f4a jl -> block
    if (nCount < 0) {
        // 1417e5f5c r9d = 0x5c, r8 = 0x141840060, append 0x1418400b0 at 1417e5fa4
        syndicate::g_pfnPbCheckFail(kSynPbZeroCopyLiteFile, 0x5c,
                         kSynPbChkCountGeZeroSkip);
    }
    // 1417e5fd1 mov rax,[rsp+0xa0] / 1417e5fd9 mov DWORD PTR [rax+0x1c],0x0
    LastReturned(pSelf) = 0;
    // 1417e5ff0 mov ecx,[rax+0x18](position) / 1417e5ff3 mov eax,[rdx+0x10](size)
    // 1417e5ff6 sub eax,ecx / 1417e5ff8 cmp count,eax / 1417e5fff jle -> advance
    const int32_t nAvail = (int32_t)((uint32_t)Size(pSelf) - (uint32_t)Pos(pSelf));
    if (nCount > nAvail) {
        // 1417e6011 mov eax,[rax+0x10] / 1417e6014 mov DWORD PTR [rcx+0x18],eax
        Pos(pSelf) = Size(pSelf);
        // 1417e6017 xor al,al
        return false;
    }
    // 1417e6025 mov ecx,[rax+0x18] / 1417e6028 add ecx,[rsp+0xa8] / 1417e6037 store
    Pos(pSelf) = (int32_t)((uint32_t)Pos(pSelf) + (uint32_t)nCount);
    // 1417e603a mov al,0x1
    return true;
}

// ============================================================================
// 0x1417e6050 — ByteCount()
//   1417e6050 mov QWORD PTR [rsp+0x8],rcx
//   1417e6055 mov rax,QWORD PTR [rsp+0x8]
//   1417e605a movsxd rax,DWORD PTR [rax+0x18]
//   1417e605e ret
//   A 6-instruction body: sign-extends the 32-bit position_ at +0x18. The byte-
//   identical copies at 0x1417e64a0 / 0x1417e68b0 belong to other classes' vtables.
// ============================================================================
int64_t SynPbArrayInByteCount6050(void* pSelf) {
    return (int64_t)Pos(pSelf);   // movsxd -> int32 widened with sign
}

}  // namespace tq
