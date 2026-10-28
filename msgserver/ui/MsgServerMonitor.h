#ifndef MSG_SERVER_MONITOR_H
#define MSG_SERVER_MONITOR_H
// ===== Path-A wave 9d: the dialog monitor singleton =====
// 14002a480 DlgCreateMonitor  — new(0x70) + ctor -> DAT_140975948
// 140029ff0 ctor              — host@+0x00, zeros, the
//                               new(8) anchor {self+0x10},
//                               +0x28/30/38 zero, InitCS(+0x40),
//                               +0x68 zero
// 14002a510 dtor              — DeleteCS(+0x40) FIRST, then
//                               CloseHandle(+0x68), free(+0x28)
//                               + zero 28/30/38, Del(*(+0x10)),
//                               Del(this) when flags&1
// 140028960 getter            — returns the global
// The failure log carries NO format args (RAW).
#include <cstdint>
#include <cstddef>
namespace msg {
struct SDlgMonSeams {
    void* (*New)(size_t n);        // operator new
    void  (*Del)(void* p);         // operator delete
    void  (*InitCS)(void* cs);     // InitializeCriticalSection
    void  (*DeleteCS)(void* cs);   // DeleteCriticalSection
    int   (*CloseHandle)(void* h); // CloseHandle
    void  (*LogErr)(const char* s);// log_InlineLogERROR(&DAT_1406d9c10)
    void** ppGlobal;               // &DAT_140975948
};
// ctor (140029ff0): returns the object pointer
void* DlgMonCtor(void* p, void* host, const SDlgMonSeams& s);
// create-if-absent (14002a480): 1 = ok, 0 = failure
int   DlgMonCreate(void* host, const SDlgMonSeams& s);
// getter (140028960)
void* DlgMonGet(const SDlgMonSeams& s);
// dtor (14002a510)
void* DlgMonDtor(void* p, uint32_t flags, const SDlgMonSeams& s);
struct SDlgMonLayout {           // the RAW 0x70 layout
    void*  pHost;                // +0x00
    uint32_t u08;                // +0x08
    uint32_t u0c;                // +0x0c
    void** ppAnchor;             // +0x10 -> the new(8) node
    void*  pBuf28;               // +0x28 (freed in dtor)
    void*  p30;                  // +0x30
    void*  p38;                  // +0x38
    unsigned char cs[0x28];      // +0x40 critical section
    void*  h68;                  // +0x68 HANDLE
};
}
#endif
