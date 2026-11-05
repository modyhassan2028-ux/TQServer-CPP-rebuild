// synpboutstream.cpp — see synpboutstream.h
#include "modules/syndicate/src/synpboutstream.h"

#include <cstddef>
#include <string>

namespace tq {

void (*g_fnPbOutCheck1)(const char*, int32_t, const char*) = nullptr;
void (*g_fnPbOutCheck2)(const char*, int32_t, const char*, const char*) = nullptr;

const char* const kSynPbOutFile =
    "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc";

// 0x1417e66f0 — StringOutputStream::BackUp
void SynPbStringOutBackUp(void* pSelf, int32_t nCount) {
    uint8_t* p = (uint8_t*)pSelf;
    if (nCount < 0) {
        // 1417e6718 cmp [rsp+0xf8],0 / jl block ; 1417e6732 line 0xbc ; 1417e6777 append
        g_fnPbOutCheck1(kSynPbOutFile, 0xbc, "CHECK failed: (count) >= (0): ");
    }
    std::string* pTarget = *(std::string**)(p + 0x08);
    // 1417e67b9 movsxd rdi,count ; 1417e67c9 rcx = target ; size() ; 1417e67d3 cmp rdi,rax / ja
    if ((uint64_t)(int64_t)nCount > (uint64_t)pTarget->size()) {
        // 1417e67e8 line 0xbd ; 1417e682d append 0x1418403f0
        g_fnPbOutCheck1(kSynPbOutFile, 0xbd,
                        "CHECK failed: (count) <= (target_->size()): ");
    }
    // 1417e686f rcx = target ; size() ; 1417e6884 rax = count ; sub rdx,rax ; resize(rdx)
    pTarget->resize(pTarget->size() - (size_t)(int64_t)nCount);
}

// 0x1417e74c0 — CopyingOutputStreamAdaptor::BackUp
void SynPbCopyingAdaptorBackUp(void* pSelf, int32_t nCount) {
    uint8_t* p = (uint8_t*)pSelf;
    if (nCount < 0) {
        // 1417e74e8 cmp [rsp+0x158],0 / jl ; 1417e7502 line 0x165 ; append 0x141840790
        g_fnPbOutCheck1(kSynPbOutFile, 0x165, "CHECK failed: (count) >= (0): ");
    }
    // 1417e7599 eax = [self+0x28] ; 1417e759c cmp [self+0x2c],eax ; jne block
    if (*(int32_t*)(p + 0x2c) != *(int32_t*)(p + 0x28)) {
        // 1417e75b4 line 0x166 ; appends 0x141840800 and 0x141840838
        g_fnPbOutCheck2(kSynPbOutFile, 0x166,
                        "CHECK failed: (buffer_used_) == (buffer_size_): ",
                        " BackUp() can only be called after Next().");
    }
    // 1417e7652 eax = [self+0x2c] ; 1417e7655 cmp count,eax ; jg block
    if (nCount > *(int32_t*)(p + 0x2c)) {
        // 1417e7674 line 0x168 ; appends 0x1418408c0 and 0x1418408f0
        g_fnPbOutCheck2(kSynPbOutFile, 0x168,
                        "CHECK failed: (count) <= (buffer_used_): ",
                        " Can't back up over more bytes than were returned by the last call "
                        "to Next().");
    }
    // 1417e771b eax = count ; 1417e7722 ecx = [self+0x2c] ; sub ecx,eax ; store back
    *(int32_t*)(p + 0x2c) = *(int32_t*)(p + 0x2c) - nCount;
}

}  // namespace tq
