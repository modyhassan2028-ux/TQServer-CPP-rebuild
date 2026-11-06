// ============================================================================
// cqbase_d60 — CMsgLeagueConcubinesPB::MergePartialFromCodedStream (0x1417ebc90).
//   The fake seams below stand in for the protobuf reader. Every assertion follows the
//   instruction flow: the fast tag byte, the field-1 bool with its has-bit, the field-2
//   element path (reuse, grow, allocate 0x68, the two vftable stores, the zeroed tail),
//   the unknown-field skip, the end-of-stream tests and the answer of both exits.
// ============================================================================
#include "modules/syndicate/src/synleaguemerge.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

struct Reader {
    uint8_t a00[8];
    const uint8_t* pPtr;
    const uint8_t* pEnd;
    int32_t n18;
    int32_t n1c;
    uint32_t uLastTag;
    uint8_t b24;
    uint8_t a25[3];
    int32_t n28;
    int32_t n2c;
};

uint32_t ReadVarintSlow(Reader* pR) {
    uint32_t uValue = 0; int nShift = 0;
    while (pR->pPtr < pR->pEnd) {
        uint8_t b = *pR->pPtr++;
        uValue |= (uint32_t)(b & 0x7f) << nShift;
        if (!(b & 0x80)) break;
        nShift += 7;
    }
    return uValue;
}

int g_nSlowTags = 0, g_nSlowVars = 0, g_nSkips = 0, g_nElems = 0, g_nAllocs = 0;
int g_nReserves = 0, g_nStrCtors = 0, g_nTracks = 0, g_nDtorWrapper = 0, g_nDtorReader = 0;
bool g_bSubOk = true;
std::vector<void*> g_aElems;
uint32_t g_uFirstAssignedTag = 0;

void CtorHook(void* pReader, void* pPayload) {
    (void)pPayload;
    std::memset(pReader, 0, 0x40);
}
void WrapperHook(void* pWrapper, void* pReader) { (void)pWrapper; (void)pReader; }
uint32_t SlowTagHook(void* pReader) { ++g_nSlowTags; return ReadVarintSlow((Reader*)pReader); }
bool SlowVarHook(void* pReader, uint64_t* pValue) {
    ++g_nSlowVars; *pValue = ReadVarintSlow((Reader*)pReader); return true;
}
bool SkipHook(void* pReader, uint32_t uTag, void* pWrapper) {
    (void)pWrapper; ++g_nSkips;
    // consume the field body so the stream advances, exactly what a real skip does
    Reader* pR = (Reader*)pReader;
    switch (uTag & 7) {
    case 0: (void)ReadVarintSlow(pR); break;
    case 2: { uint32_t n = ReadVarintSlow(pR); pR->pPtr += n; break; }
    default: break;
    }
    return true;
}
bool ElemHook(void* pReader, void* pElem) {
    ++g_nElems;
    g_aElems.push_back(pElem);
    // a real element parse consumes the length prefix and the payload, which is what moves
    // the reader on to the next tag
    Reader* pR = (Reader*)pReader;
    uint32_t nLen = ReadVarintSlow(pR);
    pR->pPtr += nLen;
    return g_bSubOk;
}
void ReserveHook(void* pVec, int32_t nNewCap) { (void)pVec; ++g_nReserves; (void)nNewCap; }
void* AllocHook(size_t uBytes) { ++g_nAllocs; return std::calloc(1, uBytes); }
void StrCtorHook(void* pStr) { ++g_nStrCtors; (void)pStr; }
void TrackHook(void) { ++g_nTracks; }
void DtorWrapperHook(void* p) { (void)p; ++g_nDtorWrapper; }
void DtorReaderHook(void* p) { (void)p; ++g_nDtorReader; }

// the message: the payload at +0x08, hasbits +0x30, elems +0x38, used +0x40, size +0x44, cap +0x48
struct MsgRaw {
    std::vector<uint8_t> a;
    MsgRaw() : a(0x60, 0) {}
    uint8_t* p() { return a.data(); }
    void set(int nOff, int32_t nValue) { *(int32_t*)(a.data() + nOff) = nValue; }
    int32_t get(int nOff) { return *(int32_t*)(a.data() + nOff); }
    void* getp(int nOff) { return *(void**)(a.data() + nOff); }
    void setp(int nOff, void* p) { *(void**)(a.data() + nOff) = p; }
};

struct ReaderHarness {
    std::vector<uint8_t> aBuf;
    Reader st;
    ReaderHarness(const std::vector<uint8_t>& aBytes) : aBuf(aBytes) {
        std::memset(&st, 0, sizeof(st));
    }
    Reader* r() { return &st; }
};

}  // namespace

// the ctor seam installs the buffer, so the harness passes it through a global
namespace {
const uint8_t* g_pBufStart = nullptr;
size_t g_nBufLen = 0;
void CtorHookWithBuf(void* pReader, void* pPayload) {
    (void)pPayload; ++g_nSlowTags; --g_nSlowTags;   // no counter change
    Reader* pR = (Reader*)pReader;
    std::memset(pReader, 0, 0x40);
    pR->pPtr = g_pBufStart;
    pR->pEnd = g_pBufStart + g_nBufLen;
}
void* g_pResultElem = nullptr;
}  // namespace

int main() {
    g_fnPb64C0 = &CtorHookWithBuf;
    g_fnPb4550 = &WrapperHook;
    g_fnPb3BC0 = &SlowTagHook;
    g_fnPb3D80 = &SlowVarHook;
    g_fnPbT3F50 = &SkipHook;
    g_fnPb45D0 = &DtorWrapperHook;
    g_fnPb6510 = &DtorReaderHook;
    g_fnPb540 = &ElemHook;
    g_fnPb0110 = &ReserveHook;
    g_fnPb3166 = &AllocHook;
    g_fnPbStrCtor = &StrCtorHook;
    g_fnPbInstanceTrack = &TrackHook;

    // ---- field 1: tag 0x08, value 1 -> bool true, has-bit 1, one element-free run
    {
        std::vector<uint8_t> aBytes = {0x08, 0x01};
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        g_nElems = g_nAllocs = g_nSkips = g_nDtorWrapper = g_nDtorReader = 0;
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == true);
        CHECK(m.p()[0x50] == 1);
        CHECK(m.get(0x30) == 1);
        CHECK(g_nElems == 0);
        CHECK(g_nAllocs == 0);
        CHECK(g_nDtorWrapper == 1 && g_nDtorReader == 1);
    }

    // ---- field 1 with value 0 still sets the has-bit, and the bool stays 0
    {
        std::vector<uint8_t> aBytes = {0x08, 0x00};
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == true);
        CHECK(m.p()[0x50] == 0);
        CHECK(m.get(0x30) == 1);
    }

    // ---- field 2 twice: two elements, each allocated 0x68 with its vftable and tail zeroed
    {
        std::vector<uint8_t> aBytes = {0x12, 0x00, 0x12, 0x00};
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        void* apStore[8] = {nullptr};
        m.setp(0x38, apStore);
        m.set(0x40, 0); m.set(0x44, 0); m.set(0x48, 8);
        g_nElems = 0; g_nAllocs = 0; g_nReserves = 0; g_aElems.clear();
        g_nStrCtors = 0; g_nTracks = 0;
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == true);
        CHECK(g_nElems == 2);
        CHECK(g_nAllocs == 2);
        CHECK(g_nReserves == 0);                 // the capacity was already large enough
        CHECK(g_nStrCtors == 2);
        CHECK(g_nTracks == 2);
        CHECK(m.get(0x40) == 2);                 // used
        CHECK(m.get(0x44) == 2);                 // size
        CHECK((void*)apStore[0] == g_aElems[0]);
        CHECK((void*)apStore[1] == g_aElems[1]);
        // the vftable the original writes last, and the zeroed tail fields
        CHECK(*(void**)g_aElems[0] == (void*)0x1418415e8ULL);
        uint8_t* e = (uint8_t*)g_aElems[0];
        CHECK(*(int32_t*)(e + 0x34) == 0);
        CHECK(*(uint64_t*)(e + 0x40) == 0);
        CHECK(e[0x5c] == 0);
        CHECK(*(int32_t*)(e + 0x30) == 0);
        for (void* pElem : g_aElems) std::free(pElem);
        g_aElems.clear();
    }

    // ---- the reuse path: used 1 of size 2 -> the existing pointer is taken, no allocation
    {
        std::vector<uint8_t> aBytes = {0x12, 0x00};
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        static uint8_t aExisting[0x68];
        // the reuse takes the slot at index used (+0x40), so the pointer must sit there
        void* apStore[8] = {nullptr, aExisting};
        m.setp(0x38, apStore);
        m.set(0x40, 1); m.set(0x44, 2); m.set(0x48, 8);
        g_nElems = 0; g_nAllocs = 0;
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == true);
        CHECK(g_nAllocs == 0);
        CHECK(g_nElems == 1);
        CHECK(m.get(0x40) == 2);
        CHECK(g_aElems.back() == (void*)aExisting);
    }

    // ---- the grow path: used == size == cap forces the reserve call
    {
        std::vector<uint8_t> aBytes = {0x12, 0x00};
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        void* apStore[8] = {nullptr};
        m.setp(0x38, apStore);
        m.set(0x40, 0); m.set(0x44, 0); m.set(0x48, 0);
        g_nReserves = 0; g_nAllocs = 0; g_aElems.clear();
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == true);
        CHECK(g_nReserves == 1);
        CHECK(g_nAllocs == 1);
        for (void* pElem : g_aElems) if (pElem) std::free(pElem);
        g_aElems.clear();
    }

    // ---- an unknown field is skipped once and the parse still succeeds
    {
        std::vector<uint8_t> aBytes = {0x1a, 0x02, 0xAA, 0xBB};
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        g_nSkips = 0;
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == true);
        CHECK(g_nSkips == 1);
    }

    // ---- a failing element parse answers 0 and still destroys both objects
    {
        std::vector<uint8_t> aBytes = {0x12, 0x00};
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        void* apStore[8] = {nullptr};
        m.setp(0x38, apStore);
        m.set(0x40, 0); m.set(0x44, 0); m.set(0x48, 8);
        g_bSubOk = false; g_nDtorWrapper = g_nDtorReader = 0;
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == false);
        CHECK(g_nDtorWrapper == 1 && g_nDtorReader == 1);
        g_bSubOk = true;
        for (void* pElem : g_aElems) if (pElem) std::free(pElem);
        g_aElems.clear();
    }

    // ---- the slow tag path is used when the fast byte cannot serve
    {
        std::vector<uint8_t> aBytes = {0x88, 0x01, 0x01};   // tag 0x88 = field 0x11, wire 0
        g_pBufStart = aBytes.data(); g_nBufLen = aBytes.size();
        MsgRaw m;
        g_nSlowTags = 0; g_nSkips = 0;
        CHECK(SynPbConcubinesMerge(m.p(), nullptr) == true);
        // the byte 0x88 is negative, so the fast path cannot serve; at the end of the buffer
        // the slow read is asked once more and answers 0, which ends the loop
        CHECK(g_nSlowTags == 2);
        CHECK(g_nSkips == 1);
    }

    std::printf("SYNDICATE_D60_OK: MergePartialFromCodedStream, %d checks\n", g_nChecks);
    return 0;
}
