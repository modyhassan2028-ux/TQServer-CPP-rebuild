// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_iterators.py.
#include "modules/npcserver/unattributed/stl-iterators.h"
#include "modules/npcserver/unattributed/stl-internals.h"

namespace tq {

long long (*g_pfnNpc_140080450)(long long*, long long) = nullptr;
long long (*g_pfnNpc_140080560)(long long*, long long) = nullptr;
long long (*g_pfnNpc_140080610)(long long*, long long) = nullptr;
long long (*g_pfnNpc_1400848c0)(long long*) = nullptr;
long long (*g_pfnNpc_140085580)(long long*, long long) = nullptr;
long long (*g_pfnNpc_1400857f0)(long long*) = nullptr;
long long (*g_pfnNpc_14008dd10)(long long*) = nullptr;
long long (*g_pfnNpc_14008dfc0)(long long*, long long) = nullptr;
long long (*g_pfnNpc_14008e4e0)(long long*) = nullptr;
long long (*g_pfnNpc_14008e580)(long long*) = nullptr;
long long (*g_pfnNpc_14008e610)(long long*) = nullptr;

// 0x1400804c0 - forwarder
long long* FUN_1400804c0(long long* pThis, long long nValue) {
    if (g_pfnNpc_140080450 != nullptr) g_pfnNpc_140080450(pThis, nValue);
    return pThis;
}

// 0x1400817d0 - forwarder
long long* FUN_1400817d0(long long* pThis, long long nValue) {
    if (g_pfnNpc_140080560 != nullptr) g_pfnNpc_140080560(pThis, nValue);
    return pThis;
}

// 0x140081880 - forwarder
long long* FUN_140081880(long long* pThis, long long nValue) {
    if (g_pfnNpc_140080610 != nullptr) g_pfnNpc_140080610(pThis, nValue);
    return pThis;
}

// 0x140082310 - pair-construct
unsigned long long* FUN_140082310(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x1400827c0 - pair-construct
unsigned long long* FUN_1400827c0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x1400833f0 - pair-construct
unsigned long long* FUN_1400833f0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x140083430 - pair-construct
unsigned long long* FUN_140083430(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x140085a30 - forwarder
long long* FUN_140085a30(long long* pThis) {
    if (g_pfnNpc_1400848c0 != nullptr) g_pfnNpc_1400848c0(pThis);
    return pThis;
}

// 0x140085f40 - forwarder
long long* FUN_140085f40(long long* pThis, long long nValue) {
    if (g_pfnNpc_140085580 != nullptr) g_pfnNpc_140085580(pThis, nValue);
    return pThis;
}

// 0x1400863b0 - forwarder
long long* FUN_1400863b0(long long* pThis) {
    if (g_pfnNpc_1400857f0 != nullptr) g_pfnNpc_1400857f0(pThis);
    return pThis;
}

// 0x140086410 - forwarder
long long* FUN_140086410(long long* pThis) {
    if (g_pfnNpc_1400848c0 != nullptr) g_pfnNpc_1400848c0(pThis);
    return pThis;
}

// 0x140086da0 - forwarder
long long* FUN_140086da0(long long* pThis) {
    if (g_pfnNpc_1400857f0 != nullptr) g_pfnNpc_1400857f0(pThis);
    return pThis;
}

// 0x14008e750 - forwarder
long long* FUN_14008e750(long long* pThis) {
    if (g_pfnNpc_14008dd10 != nullptr) g_pfnNpc_14008dd10(pThis);
    return pThis;
}

// 0x14008e830 - forwarder
long long* FUN_14008e830(long long* pThis, long long nValue) {
    if (g_pfnNpc_14008dfc0 != nullptr) g_pfnNpc_14008dfc0(pThis, nValue);
    return pThis;
}

// 0x14008e980 - pair-construct
unsigned long long* FUN_14008e980(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x14008ea50 - forwarder
long long* FUN_14008ea50(long long* pThis) {
    if (g_pfnNpc_14008e580 != nullptr) g_pfnNpc_14008e580(pThis);
    return pThis;
}

// 0x14008ea70 - forwarder
long long* FUN_14008ea70(long long* pThis) {
    if (g_pfnNpc_14008e4e0 != nullptr) g_pfnNpc_14008e4e0(pThis);
    return pThis;
}

// 0x14008ea90 - pair-construct
unsigned long long* FUN_14008ea90(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x14008ead0 - forwarder
long long* FUN_14008ead0(long long* pThis) {
    if (g_pfnNpc_14008e610 != nullptr) g_pfnNpc_14008e610(pThis);
    return pThis;
}

// 0x14008eaf0 - pair-construct
unsigned long long* FUN_14008eaf0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x14008f0e0 - forwarder
long long* FUN_14008f0e0(long long* pThis) {
    if (g_pfnNpc_14008e4e0 != nullptr) g_pfnNpc_14008e4e0(pThis);
    return pThis;
}

// 0x14008f4a0 - pair-construct
unsigned long long* FUN_14008f4a0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource) {
    pPair[0] = 0;
    pPair[1] = nSecond;
    if (pSource == nullptr) {
        NpcInvalidParameter();
    }
    pPair[0] = pSource[0];
    return pPair;
}

// 0x14008f4e0 - forwarder
long long* FUN_14008f4e0(long long* pThis) {
    if (g_pfnNpc_14008e610 != nullptr) g_pfnNpc_14008e610(pThis);
    return pThis;
}

const NpcIteratorEntry g_aNpcIter_140080000[] = {
    { "1400804c0", "forwarder", (void*)&FUN_1400804c0, 5369234512LL },
    { "1400817d0", "forwarder", (void*)&FUN_1400817d0, 5369234784LL },
    { "140081880", "forwarder", (void*)&FUN_140081880, 5369234960LL },
    { "140082310", "pair-construct", (void*)&FUN_140082310, 0LL },
    { "1400827c0", "pair-construct", (void*)&FUN_1400827c0, 0LL },
    { "1400833f0", "pair-construct", (void*)&FUN_1400833f0, 0LL },
    { "140083430", "pair-construct", (void*)&FUN_140083430, 0LL },
    { "140085a30", "forwarder", (void*)&FUN_140085a30, 5369252032LL },
    { "140085f40", "forwarder", (void*)&FUN_140085f40, 5369255296LL },
    { "1400863b0", "forwarder", (void*)&FUN_1400863b0, 5369255920LL },
    { "140086410", "forwarder", (void*)&FUN_140086410, 5369252032LL },
    { "140086da0", "forwarder", (void*)&FUN_140086da0, 5369255920LL },
    { "14008e750", "forwarder", (void*)&FUN_14008e750, 5369290000LL },
    { "14008e830", "forwarder", (void*)&FUN_14008e830, 5369290688LL },
    { "14008e980", "pair-construct", (void*)&FUN_14008e980, 0LL },
    { "14008ea50", "forwarder", (void*)&FUN_14008ea50, 5369292160LL },
    { "14008ea70", "forwarder", (void*)&FUN_14008ea70, 5369292000LL },
    { "14008ea90", "pair-construct", (void*)&FUN_14008ea90, 0LL },
    { "14008ead0", "forwarder", (void*)&FUN_14008ead0, 5369292304LL },
    { "14008eaf0", "pair-construct", (void*)&FUN_14008eaf0, 0LL },
    { "14008f0e0", "forwarder", (void*)&FUN_14008f0e0, 5369292000LL },
    { "14008f4a0", "pair-construct", (void*)&FUN_14008f4a0, 0LL },
    { "14008f4e0", "forwarder", (void*)&FUN_14008f4e0, 5369292304LL },
};

const int g_nNpcIter_140080000 = 23;

}  // namespace tq
