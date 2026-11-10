// Generated from the decompiled bodies of NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_family.py.
#include "modules/npcserver/unattributed/stl-internals.h"
#include "modules/npcserver/unattributed/front-of-image.h"

namespace tq {

void NpcInvalidParameter(void) {
    if (g_pfnNpcInvalidParameter != nullptr) g_pfnNpcInvalidParameter();
}

// 0x140080020 - iterator-check
long long FUN_140080020(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (*(unsigned long long*)(lBase + 0x20) <= (unsigned long long)pThis[1]) {
        NpcInvalidParameter();
    }
    return pThis[1];
}

// 0x140080100 - delete-thunk
void FUN_140080100(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140080130 - delete-thunk
void FUN_140080130(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140080170 - iterator-check
long long FUN_140080170(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (*(unsigned long long*)(lBase + 0x20) <= (unsigned long long)pThis[1]) {
        NpcInvalidParameter();
    }
    return pThis[1];
}

// 0x140080680 - iterator-compare
bool FUN_140080680(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] == pSecond[1];
}

// 0x140080ba0 - iterator-compare
bool FUN_140080ba0(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] == pSecond[1];
}

// 0x140080f00 - iterator-compare
bool FUN_140080f00(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] != pSecond[1];
}

// 0x140080f40 - iterator-check
long long FUN_140080f40(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x28)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x10;
}

// 0x140080fd0 - iterator-compare
bool FUN_140080fd0(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] != pSecond[1];
}

// 0x140081010 - delete-thunk
void FUN_140081010(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140081020 - delete-thunk
void FUN_140081020(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140081030 - decref
void FUN_140081030(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081070 - delete-thunk
void FUN_140081070(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140081080 - delete-thunk
void FUN_140081080(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140081090 - decref
void FUN_140081090(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x1400810d0 - decref
void FUN_1400810d0(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081110 - decref
void FUN_140081110(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081150 - decref
void FUN_140081150(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081190 - iterator-check
long long FUN_140081190(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (*(unsigned long long*)(lBase + 0x20) <= (unsigned long long)pThis[1]) {
        NpcInvalidParameter();
    }
    return pThis[1];
}

// 0x1400811d0 - iterator-check
long long FUN_1400811d0(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x28)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x10;
}

// 0x140081270 - delete-thunk
void FUN_140081270(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140081290 - delete-thunk
void FUN_140081290(void** pThis) {
    ::operator delete(*pThis);
}

// 0x1400812d0 - new-and-store
void** FUN_1400812d0(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140081640 - new-and-store
void** FUN_140081640(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140081710 - new-and-store
void** FUN_140081710(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140081800 - new-and-store
void** FUN_140081800(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140081840 - new-and-store
void** FUN_140081840(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x1400818a0 - iterator-compare
bool FUN_1400818a0(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] != pSecond[1];
}

// 0x140081bc0 - iterator-compare
bool FUN_140081bc0(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] != pSecond[1];
}

// 0x140081dc0 - decref
void FUN_140081dc0(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081e30 - decref
void FUN_140081e30(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081e90 - decref
void FUN_140081e90(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081ed0 - decref
void FUN_140081ed0(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081f10 - decref
void FUN_140081f10(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140081f50 - iterator-check
long long FUN_140081f50(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x30)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x18;
}

// 0x140081f90 - iterator-check
long long FUN_140081f90(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (*(unsigned long long*)(lBase + 0x20) <= (unsigned long long)pThis[1]) {
        NpcInvalidParameter();
    }
    return pThis[1];
}

// 0x140081fd0 - iterator-check
long long FUN_140081fd0(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x28)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x10;
}

// 0x140082010 - iterator-check
long long FUN_140082010(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x28)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x10;
}

// 0x1400820a0 - delete-thunk
void FUN_1400820a0(void** pThis) {
    ::operator delete(*pThis);
}

// 0x1400820c0 - delete-thunk
void FUN_1400820c0(void** pThis) {
    ::operator delete(*pThis);
}

// 0x1400820e0 - delete-thunk
void FUN_1400820e0(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140082170 - new-and-store
void** FUN_140082170(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140082200 - new-and-store
void** FUN_140082200(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140082470 - new-and-store
void** FUN_140082470(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x1400825b0 - new-and-store
void** FUN_1400825b0(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x1400828c0 - new-and-store
void** FUN_1400828c0(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140082930 - new-and-store
void** FUN_140082930(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140082c70 - decref
void FUN_140082c70(char* pThis) {
    long long* pRef = *(long long**)(pThis + 24);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140082cc0 - decref
void FUN_140082cc0(char* pThis) {
    long long* pRef = *(long long**)(pThis + 24);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140082d10 - decref
void FUN_140082d10(char* pThis) {
    long long* pRef = *(long long**)(pThis + 32);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140083100 - delete-thunk
void FUN_140083100(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140083120 - delete-thunk
void FUN_140083120(void** pThis) {
    ::operator delete(*pThis);
}

// 0x1400834c0 - new-and-store
void** FUN_1400834c0(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140083540 - new-and-store
void** FUN_140083540(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140083b50 - decref
void FUN_140083b50(char* pThis) {
    long long* pRef = *(long long**)(pThis + 8);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140084100 - delete-thunk
void FUN_140084100(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140084120 - delete-thunk
void FUN_140084120(void** pThis) {
    ::operator delete(*pThis);
}

// 0x140084180 - new-and-store
void** FUN_140084180(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x140084250 - new-and-store
void** FUN_140084250(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x1400845b0 - decref
void FUN_1400845b0(char* pThis) {
    long long* pRef = *(long long**)(pThis + 24);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x140084600 - decref
void FUN_140084600(char* pThis) {
    long long* pRef = *(long long**)(pThis + 24);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x14008d950 - iterator-compare
bool FUN_14008d950(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] == pSecond[1];
}

// 0x14008d9b0 - iterator-compare
bool FUN_14008d9b0(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] == pSecond[1];
}

// 0x14008db20 - iterator-check
long long FUN_14008db20(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x30)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x18;
}

// 0x14008e0c0 - iterator-compare
bool FUN_14008e0c0(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] != pSecond[1];
}

// 0x14008e100 - iterator-compare
bool FUN_14008e100(long long* pFirst, long long* pSecond) {
    if (*pFirst == 0 || *pFirst != *pSecond)
        NpcInvalidParameter();
    return pFirst[1] != pSecond[1];
}

// 0x14008e150 - delete-thunk
void FUN_14008e150(void** pThis) {
    ::operator delete(*pThis);
}

// 0x14008e180 - delete-thunk
void FUN_14008e180(void** pThis) {
    ::operator delete(*pThis);
}

// 0x14008e190 - iterator-check
long long FUN_14008e190(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x30)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x18;
}

// 0x14008e1d0 - iterator-check
long long FUN_14008e1d0(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x30)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x18;
}

// 0x14008e210 - iterator-check
long long FUN_14008e210(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x30)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x18;
}

// 0x14008e770 - new-and-store
void** FUN_14008e770(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x14008e7b0 - new-and-store
void** FUN_14008e7b0(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x14008e870 - iterator-check
long long FUN_14008e870(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x30)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x18;
}

// 0x14008e8b0 - iterator-check
long long FUN_14008e8b0(long long* pThis) {
    long long* pNode = (long long*)*pThis;
    long long lBase;
    if (pNode == nullptr) {
        NpcInvalidParameter();
        pNode = (long long*)*pThis;
        lBase = 0;
        if (pNode == nullptr) goto done;
    }
    lBase = *pNode;
done:
    if (pThis[1] == *(long long*)(lBase + 0x30)) {
        NpcInvalidParameter();
    }
    return pThis[1] + 0x18;
}

// 0x14008e940 - delete-thunk
void FUN_14008e940(void** pThis) {
    ::operator delete(*pThis);
}

// 0x14008e960 - delete-thunk
void FUN_14008e960(void** pThis) {
    ::operator delete(*pThis);
}

// 0x14008f1a0 - new-and-store
void** FUN_14008f1a0(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x14008f1f0 - new-and-store
void** FUN_14008f1f0(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x14008f3c0 - delete-thunk
void FUN_14008f3c0(void** pThis) {
    ::operator delete(*pThis);
}

// 0x14008f3e0 - delete-thunk
void FUN_14008f3e0(void** pThis) {
    ::operator delete(*pThis);
}

// 0x14008fa30 - new-and-store
void** FUN_14008fa30(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x14008fa80 - new-and-store
void** FUN_14008fa80(void** pThis) {
    void* pNew = ::operator new(8);
    if (pNew == nullptr) {
        pNew = nullptr;
    } else {
        *(void**)pNew = pThis;
    }
    *pThis = pNew;
    return pThis;
}

// 0x14008fad0 - decref
void FUN_14008fad0(char* pThis) {
    long long* pRef = *(long long**)(pThis + 72);
    if (pRef != nullptr) {
        int nUses = __atomic_load_n((int*)((char*)pRef + 0x10), __ATOMIC_SEQ_CST) - 1;
        __atomic_store_n((int*)((char*)pRef + 0x10), nUses, __ATOMIC_SEQ_CST);
        if (nUses == 0) {
            (*(void (**)(long long*))(*pRef))(pRef);
            int nWeak = __atomic_load_n((int*)((char*)pRef + 0x14), __ATOMIC_SEQ_CST) - 1;
            __atomic_store_n((int*)((char*)pRef + 0x14), nWeak, __ATOMIC_SEQ_CST);
            if (nWeak == 0)
                (*(void (**)(long long*))(*pRef + 0x08))(pRef);
        }
    }
}

// 0x14008fcb0 - delete-thunk
void FUN_14008fcb0(void** pThis) {
    ::operator delete(*pThis);
}

// 0x14008fcd0 - delete-thunk
void FUN_14008fcd0(void** pThis) {
    ::operator delete(*pThis);
}

const NpcStlEntry g_aNpcStl_140080000[] = {
    { "140080020", "iterator-check", (void*)&FUN_140080020, 32, 1, 0 },
    { "140080100", "delete-thunk", (void*)&FUN_140080100, 0, 0, 0 },
    { "140080130", "delete-thunk", (void*)&FUN_140080130, 0, 0, 0 },
    { "140080170", "iterator-check", (void*)&FUN_140080170, 32, 1, 0 },
    { "140080680", "iterator-compare", (void*)&FUN_140080680, 1, 0, 0 },
    { "140080ba0", "iterator-compare", (void*)&FUN_140080ba0, 1, 0, 0 },
    { "140080f00", "iterator-compare", (void*)&FUN_140080f00, 0, 0, 0 },
    { "140080f40", "iterator-check", (void*)&FUN_140080f40, 40, 0, 16 },
    { "140080fd0", "iterator-compare", (void*)&FUN_140080fd0, 0, 0, 0 },
    { "140081010", "delete-thunk", (void*)&FUN_140081010, 0, 0, 0 },
    { "140081020", "delete-thunk", (void*)&FUN_140081020, 0, 0, 0 },
    { "140081030", "decref", (void*)&FUN_140081030, 8, 16, 20 },
    { "140081070", "delete-thunk", (void*)&FUN_140081070, 0, 0, 0 },
    { "140081080", "delete-thunk", (void*)&FUN_140081080, 0, 0, 0 },
    { "140081090", "decref", (void*)&FUN_140081090, 8, 16, 20 },
    { "1400810d0", "decref", (void*)&FUN_1400810d0, 8, 16, 20 },
    { "140081110", "decref", (void*)&FUN_140081110, 8, 16, 20 },
    { "140081150", "decref", (void*)&FUN_140081150, 8, 16, 20 },
    { "140081190", "iterator-check", (void*)&FUN_140081190, 32, 1, 0 },
    { "1400811d0", "iterator-check", (void*)&FUN_1400811d0, 40, 0, 16 },
    { "140081270", "delete-thunk", (void*)&FUN_140081270, 0, 0, 0 },
    { "140081290", "delete-thunk", (void*)&FUN_140081290, 0, 0, 0 },
    { "1400812d0", "new-and-store", (void*)&FUN_1400812d0, 8, 0, 0 },
    { "140081640", "new-and-store", (void*)&FUN_140081640, 8, 0, 0 },
    { "140081710", "new-and-store", (void*)&FUN_140081710, 8, 0, 0 },
    { "140081800", "new-and-store", (void*)&FUN_140081800, 8, 0, 0 },
    { "140081840", "new-and-store", (void*)&FUN_140081840, 8, 0, 0 },
    { "1400818a0", "iterator-compare", (void*)&FUN_1400818a0, 0, 0, 0 },
    { "140081bc0", "iterator-compare", (void*)&FUN_140081bc0, 0, 0, 0 },
    { "140081dc0", "decref", (void*)&FUN_140081dc0, 8, 16, 20 },
    { "140081e30", "decref", (void*)&FUN_140081e30, 8, 16, 20 },
    { "140081e90", "decref", (void*)&FUN_140081e90, 8, 16, 20 },
    { "140081ed0", "decref", (void*)&FUN_140081ed0, 8, 16, 20 },
    { "140081f10", "decref", (void*)&FUN_140081f10, 8, 16, 20 },
    { "140081f50", "iterator-check", (void*)&FUN_140081f50, 48, 0, 24 },
    { "140081f90", "iterator-check", (void*)&FUN_140081f90, 32, 1, 0 },
    { "140081fd0", "iterator-check", (void*)&FUN_140081fd0, 40, 0, 16 },
    { "140082010", "iterator-check", (void*)&FUN_140082010, 40, 0, 16 },
    { "1400820a0", "delete-thunk", (void*)&FUN_1400820a0, 0, 0, 0 },
    { "1400820c0", "delete-thunk", (void*)&FUN_1400820c0, 0, 0, 0 },
    { "1400820e0", "delete-thunk", (void*)&FUN_1400820e0, 0, 0, 0 },
    { "140082170", "new-and-store", (void*)&FUN_140082170, 8, 0, 0 },
    { "140082200", "new-and-store", (void*)&FUN_140082200, 8, 0, 0 },
    { "140082470", "new-and-store", (void*)&FUN_140082470, 8, 0, 0 },
    { "1400825b0", "new-and-store", (void*)&FUN_1400825b0, 8, 0, 0 },
    { "1400828c0", "new-and-store", (void*)&FUN_1400828c0, 8, 0, 0 },
    { "140082930", "new-and-store", (void*)&FUN_140082930, 8, 0, 0 },
    { "140082c70", "decref", (void*)&FUN_140082c70, 24, 16, 20 },
    { "140082cc0", "decref", (void*)&FUN_140082cc0, 24, 16, 20 },
    { "140082d10", "decref", (void*)&FUN_140082d10, 32, 16, 20 },
    { "140083100", "delete-thunk", (void*)&FUN_140083100, 0, 0, 0 },
    { "140083120", "delete-thunk", (void*)&FUN_140083120, 0, 0, 0 },
    { "1400834c0", "new-and-store", (void*)&FUN_1400834c0, 8, 0, 0 },
    { "140083540", "new-and-store", (void*)&FUN_140083540, 8, 0, 0 },
    { "140083b50", "decref", (void*)&FUN_140083b50, 8, 16, 20 },
    { "140084100", "delete-thunk", (void*)&FUN_140084100, 0, 0, 0 },
    { "140084120", "delete-thunk", (void*)&FUN_140084120, 0, 0, 0 },
    { "140084180", "new-and-store", (void*)&FUN_140084180, 8, 0, 0 },
    { "140084250", "new-and-store", (void*)&FUN_140084250, 8, 0, 0 },
    { "1400845b0", "decref", (void*)&FUN_1400845b0, 24, 16, 20 },
    { "140084600", "decref", (void*)&FUN_140084600, 24, 16, 20 },
    { "14008d950", "iterator-compare", (void*)&FUN_14008d950, 1, 0, 0 },
    { "14008d9b0", "iterator-compare", (void*)&FUN_14008d9b0, 1, 0, 0 },
    { "14008db20", "iterator-check", (void*)&FUN_14008db20, 48, 0, 24 },
    { "14008e0c0", "iterator-compare", (void*)&FUN_14008e0c0, 0, 0, 0 },
    { "14008e100", "iterator-compare", (void*)&FUN_14008e100, 0, 0, 0 },
    { "14008e150", "delete-thunk", (void*)&FUN_14008e150, 0, 0, 0 },
    { "14008e180", "delete-thunk", (void*)&FUN_14008e180, 0, 0, 0 },
    { "14008e190", "iterator-check", (void*)&FUN_14008e190, 48, 0, 24 },
    { "14008e1d0", "iterator-check", (void*)&FUN_14008e1d0, 48, 0, 24 },
    { "14008e210", "iterator-check", (void*)&FUN_14008e210, 48, 0, 24 },
    { "14008e770", "new-and-store", (void*)&FUN_14008e770, 8, 0, 0 },
    { "14008e7b0", "new-and-store", (void*)&FUN_14008e7b0, 8, 0, 0 },
    { "14008e870", "iterator-check", (void*)&FUN_14008e870, 48, 0, 24 },
    { "14008e8b0", "iterator-check", (void*)&FUN_14008e8b0, 48, 0, 24 },
    { "14008e940", "delete-thunk", (void*)&FUN_14008e940, 0, 0, 0 },
    { "14008e960", "delete-thunk", (void*)&FUN_14008e960, 0, 0, 0 },
    { "14008f1a0", "new-and-store", (void*)&FUN_14008f1a0, 8, 0, 0 },
    { "14008f1f0", "new-and-store", (void*)&FUN_14008f1f0, 8, 0, 0 },
    { "14008f3c0", "delete-thunk", (void*)&FUN_14008f3c0, 0, 0, 0 },
    { "14008f3e0", "delete-thunk", (void*)&FUN_14008f3e0, 0, 0, 0 },
    { "14008fa30", "new-and-store", (void*)&FUN_14008fa30, 8, 0, 0 },
    { "14008fa80", "new-and-store", (void*)&FUN_14008fa80, 8, 0, 0 },
    { "14008fad0", "decref", (void*)&FUN_14008fad0, 72, 16, 20 },
    { "14008fcb0", "delete-thunk", (void*)&FUN_14008fcb0, 0, 0, 0 },
    { "14008fcd0", "delete-thunk", (void*)&FUN_14008fcd0, 0, 0, 0 },
};

const int g_nNpcStl_140080000 = 86;

}  // namespace tq
