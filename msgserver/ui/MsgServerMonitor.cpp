// ===== Path-A wave 9d: RAW-verbatim =====
#include "MsgServerMonitor.h"
#include <cstring>
namespace msg {
void* DlgMonCtor(void* p, void* host, const SDlgMonSeams& s) {
    SDlgMonLayout* o = (SDlgMonLayout*)p;
    o->pHost = host;                    // *param_1 = param_2
    o->u08 = 0;
    o->u0c = 0;
    void** node = (void**)s.New(8);
    if (node != nullptr) {
        *node = (void*)((char*)p + 0x10);   // anchor self-ref
    }
    o->ppAnchor = node;                 // +0x10
    o->pBuf28 = nullptr;                // +0x28
    o->p30 = nullptr;                   // +0x30
    o->p38 = nullptr;                   // +0x38
    s.InitCS(o->cs);                    // +0x40
    o->h68 = nullptr;                   // +0x68
    return p;
}
int DlgMonCreate(void* host, const SDlgMonSeams& s) {
    if (*s.ppGlobal == nullptr) {
        void* p = s.New(0x70);
        if (p == nullptr) {
            *s.ppGlobal = nullptr;
        } else {
            *s.ppGlobal = DlgMonCtor(p, host, s);
        }
        if (*s.ppGlobal == nullptr) {
            s.LogErr("");               // RAW: no format args
            return 0;
        }
    }
    return 1;
}
void* DlgMonGet(const SDlgMonSeams& s) {
    return *s.ppGlobal;
}
void* DlgMonDtor(void* p, uint32_t flags, const SDlgMonSeams& s) {
    SDlgMonLayout* o = (SDlgMonLayout*)p;
    s.DeleteCS(o->cs);                  // RAW: CS deleted FIRST
    if (o->h68 != nullptr) {
        s.CloseHandle(o->h68);
    }
    if (o->pBuf28 != nullptr) {
        s.Del(o->pBuf28);
    }
    o->pBuf28 = nullptr;
    o->p30 = nullptr;
    o->p38 = nullptr;
    s.Del(o->ppAnchor);                 // the new(8) anchor
    if ((flags & 1) != 0) {
        s.Del(p);
    }
    return p;
}
}
