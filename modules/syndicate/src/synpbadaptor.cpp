// synpbadaptor.cpp — see synpbadaptor.h
#include "modules/syndicate/src/synpbadaptor.h"

namespace tq {

void* (*g_fnPbBuffer)(void*) = nullptr;
void (*g_fnPb7140)(void*) = nullptr;
void (*g_fnPb7190)(void*) = nullptr;
void (*g_fnPb6AD0)(void*) = nullptr;
void (*g_fnPbAdaptorFree)(void*) = nullptr;
void (*g_fnPbAdaptorCheck1)(const char*, int32_t, const char*) = nullptr;
void (*g_fnPbAdaptorCheck2)(const char*, int32_t, const char*, const char*) = nullptr;

const char* const kSynPbAdaptorFile =
    "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc";

namespace {

// the underlying CopyingInputStream's two virtual rows this class calls
int32_t StreamRead(void* pIn, void* pBuf, int32_t nSize) {
    typedef int32_t (*Fn)(void*, void*, int32_t);
    return ((Fn)(*(void***)pIn)[1])(pIn, pBuf, nSize);
}
bool StreamSkip(void* pIn, int32_t nCount) {
    typedef bool (*Fn)(void*, int32_t);
    return ((Fn)(*(void***)pIn)[2])(pIn, nCount);
}

}  // namespace

// 0x1417e6b70
bool SynPbAdaptorNext(void* pSelf, void** ppData, int32_t* pnSize) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e6b88 movzx eax,[this+0x11] ; test ; je ; xor al,al
    if (p[0x11] != 0) return false;
    // 1417e6b9c call 0x1417e7140
    g_fnPb7140(pSelf);
    // 1417e6ba6 cmp [this+0x30],0 ; jle
    if (*(int32_t*)(p + 0x30) > 0) {
        // 1417e6bb5 buffer ; 1417e6bc2 +0x2c ; 1417e6bce +0x30 ; sub
        uint8_t* pBuf = (uint8_t*)g_fnPbBuffer(p + 0x20);
        pBuf += (int64_t)*(int32_t*)(p + 0x2c);
        pBuf -= (int64_t)*(int32_t*)(p + 0x30);
        *ppData = pBuf;
        *pnSize = *(int32_t*)(p + 0x30);
        *(int32_t*)(p + 0x30) = 0;
        return true;
    }
    // 1417e6bff..1417e6c2e: buffer, then input_->Read(buffer, buffer_size_)
    void* pBuf = g_fnPbBuffer(p + 0x20);
    int32_t nRead = StreamRead(*(void**)(p + 0x08), pBuf, *(int32_t*)(p + 0x28));
    *(int32_t*)(p + 0x2c) = nRead;
    if (nRead <= 0) {
        // 1417e6c52 cmp [this+0x2c],0 ; jge ; 1417e6c59 mov BYTE [this+0x11],1
        if (nRead < 0) p[0x11] = 1;
        g_fnPb7190(pSelf);       // 1417e6c62
        return false;
    }
    // 1417e6c70..1417e6c82: byte_count_ += buffer_used_
    *(int64_t*)(p + 0x18) = *(int64_t*)(p + 0x18) + (int64_t)*(int32_t*)(p + 0x2c);
    *pnSize = *(int32_t*)(p + 0x2c);
    *ppData = g_fnPbBuffer(p + 0x20);
    return true;
}

// 0x1417e6cc0
void SynPbAdaptorBackUp(void* pSelf, int32_t nCount) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e6cf0 cmp [this+0x30],0 ; jne fail  (and the buffer must be non-null)
    bool bBad = (*(int32_t*)(p + 0x30) != 0);
    if (!bBad) {
        bBad = (g_fnPbBuffer(p + 0x20) == nullptr);
    }
    if (bBad) {
        // 1417e6d1f line 0x10c ; appends 0x141840470 and 0x1418404b0
        g_fnPbAdaptorCheck2(kSynPbAdaptorFile, 0x10c,
                            "CHECK failed: backup_bytes_ == 0 && buffer_.get() != NULL: ",
                            " BackUp() can only be called after Next().");
    }
    // 1417e6dbd eax = [this+0x2c] ; 1417e6dc0 cmp count,eax ; jg fail
    if (nCount > *(int32_t*)(p + 0x2c)) {
        // 1417e6ddc line 0x10e ; file 0x1418404e0 ; appends 0x141840530 and 0x141840560
        g_fnPbAdaptorCheck2(kSynPbAdaptorFile, 0x10e,
                            "CHECK failed: (count) <= (buffer_used_): ",
                            " Can't back up over more bytes than were returned by the last "
                            "call to Next().");
    }
    // 1417e6e72 cmp count,0 ; jl fail
    if (nCount < 0) {
        // 1417e6e92 line 0x111 ; file 0x1418405b0 ; appends 0x141840600 and 0x141840620
        g_fnPbAdaptorCheck2(kSynPbAdaptorFile, 0x111,
                            "CHECK failed: (count) >= (0): ",
                            " Parameter to BackUp() can't be negative.");
    }
    // 1417e6f40 mov [this+0x30],count
    *(int32_t*)(p + 0x30) = nCount;
}

// 0x1417e6f60
bool SynPbAdaptorSkip(void* pSelf, int32_t nCount) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e6f82 cmp count,0 ; jl fail
    if (nCount < 0) {
        // 1417e6f9c line 0x118 ; file 0x141840650 ; appends 0x1418406a0
        g_fnPbAdaptorCheck1(kSynPbAdaptorFile, 0x118, "CHECK failed: (count) >= (0): ");
    }
    // 1417e7019 movzx eax,[this+0x11] ; test ; je ; xor al,al
    if (p[0x11] != 0) return false;
    // 1417e7037 cmp [this+0x30],count ; jl
    if (*(int32_t*)(p + 0x30) >= nCount) {
        // 1417e704b ecx = [this+0x30] ; sub ecx,count ; store ; mov al,1
        *(int32_t*)(p + 0x30) = *(int32_t*)(p + 0x30) - nCount;
        return true;
    }
    // 1417e706a ecx = [this+0x30] ; eax = count ; sub eax,ecx ; [count] = eax ; [this+0x30] = 0
    int32_t nLeft = nCount - *(int32_t*)(p + 0x30);
    *(int32_t*)(p + 0x30) = 0;
    // 1417e70ae call [input vft + 0x10] (its vt[2]); then byte_count_ += answer
    bool bOk = StreamSkip(*(void**)(p + 0x08), nLeft);
    int32_t nRead = bOk ? 1 : 0;      // the call's answer is used as an int (eax)
    *(int64_t*)(p + 0x18) = *(int64_t*)(p + 0x18) + (int64_t)nRead;
    // 1417e70d2..1417e70dd: the answer is (read == count)
    return (nRead == nLeft);
}

// 0x1417e7110
int64_t SynPbAdaptorByteCount(void* pSelf) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e711a movsxd rcx,[this+0x30] ; 1417e7123 rax = [this+0x18] ; sub rax,rcx
    return *(int64_t*)(p + 0x18) - (int64_t)*(int32_t*)(p + 0x30);
}

// 0x1417e7a90
void* SynPbAdaptorDeletingDtor(void* pSelf, uint32_t uFlags) {
    g_fnPb6AD0(pSelf);                  // 1417e7aa2
    if ((uFlags & 1) != 0) {            // 1417e7aab and eax,0x1
        g_fnPbAdaptorFree(pSelf);       // 1417e7ab7
    }
    return pSelf;
}

}  // namespace tq
