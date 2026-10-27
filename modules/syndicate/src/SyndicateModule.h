// ============================================================
// Syndicate.dll port — unit T1/D26: the module shell —
// syndicate::CModule (0x4608, 17 embedded CMsg objects) +
// the tq::CMsg / gs::IModule glue + ModuleCreate.
// Addresses verbatim: 14177e290 (tq CMsg vft ctor),
// 14177e2d0/2e0/2f0 (the three Process-error loggers),
// 14177e300 (CMsg scalar dtor), 14177e330/380 (IModule
// dtor/scalar), 14177e340/350/360/370 (zero stubs),
// 14177e3b0/3e0 (CMsgLog dtor/scalar), 14177e430/460
// (CMsgSynChgDomName dtor/scalar), 14177e4c0 (the module
// dtor: base + 15 msg dtors + the two vft pairs),
// 14177e600 (deleting dtor, RAX & ~0xffff mask),
// 14177e620 (Startup: kernel vt+0x30(0x16) + the mgr
// singleton + the service startup), 14177e6c0 (GetMsg:
// the 17-way id dispatch), 14177e890 (Init: 18 vt+8
// registrations + 4 vt+0x10 sets + vt+0x18(0x16)),
// 14177eaa0 (the 1417ac5e0 passthrough),
// 14177eac0 (return-1 stub), 14177ead0 (the ctor-family
// init: vft pair, id@+8, kernel@+0x420, 17 msg ctors),
// 14177ec00 (scalar deleting dtor), 14177ec30
// (ProcessMsg: GetMsg + msg vt+0x18(id) + msg[1] u16),
// 14177ec90 (ModuleCreate: op_new(0x4608) + init + Init).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- the vftable markers (seam-supplied constants) ----
extern void* g_pTqCMsgVft;          // tq::CMsg
extern void* g_pIModuleVft;         // gs::IModule
extern void* g_pCModuleVft;         // syndicate::CModule
extern void* g_pCMsgLogVft;         // syndicate::CMsgLog
extern void* g_pCMsgSynChgDomNameVft;

// ---- allocation / log seams ----
extern void* (*g_fnOpNew)(size_t);
extern void (*g_fnOpDelete)(void*);
extern void (*g_fnSynLogError)();   // DAT_141824ca8

// ---- the base dtor (1417a9ed0) + the mgr singleton
// (1417b6210) + the service startup (1417a96f0) ----
extern void (*g_fnBaseDtor)(void* p, uint64_t a,
                            uint64_t b, uint64_t c);
extern void* (*g_fnGetServiceInst)();
extern char (*g_fnSvcStartup)(void* mgr, void* pKern,
                              uint64_t a, uint64_t b);

// ---- the kernel (module+0x420) vt seams ----
// vt+0x08: (kernel, id, module) — register
extern void (*g_fnKRegMsg)(void*, uint16_t, void*);
// vt+0x10: (kernel, id, module)
extern void (*g_fnKSetMsg)(void*, uint16_t, void*);
// vt+0x18: (kernel, n, obj) -> char
extern char (*g_fnKSet)(void*, int, void*);
// vt+0x30: (kernel, n) -> obj
extern void* (*g_fnKQuery)(void*, int);

// ---- the embedded-msg seams ----
// the 17 ctors (14177ead0 order) — index docs in the
// .cpp; each: (void* pMsg)
extern void (*g_aMsgCtor[17])(void* pMsg);
// the 14 dtors (14177e4c0 order) — each:
// (void* pMsg, uint64_t a, uint64_t b). NOTE: the
// msgs at +0x1498 / +0x10 have their vft-pair dtors
// INLINED between the calls (the SynChgDomName pair
// after dtor 9, the CMsgLog pair after dtor 13) —
// verbatim; the msg at +0x18a8 gets no dtor in the
// original
extern void (*g_aMsgDtor[14])(void* pMsg, uint64_t a,
                              uint64_t b);
// FUN_1417ac5e0 passthrough (14177eaa0):
// (mgr, obj, str1, str2)
extern void (*g_fnSvcPassA)(void*, uint64_t,
                            const char*, const char*);

// ---- the module (0x4608 raw buffer; kernel @+0x420,
// id @+8, 17 msgs at the documented offsets) ----
struct CModule {
    uint8_t m_ab[0x4608];
};

// 14177e290
void CtorTqCMsgVft(void* p);
// 14177e2d0 / 2e0 / 2f0 (the literal Process-error logs)
void CMsgProcessErrPInfo();
void CMsgProcessErrIdActor();
void CMsgProcessErrIdActorPInfo();
// 14177e300
void* CMsgScalarDtor(void* p, uint8_t uFlags);
// 14177e330 / 380
void DtorIModuleBase(void* p);
void* IModuleScalarDtor(void* p, uint8_t uFlags);
// 14177e340/350/360/370 (zero stubs)
uint64_t StubRet0a();
uint64_t StubRet0b();
uint64_t StubRet0c();
uint64_t StubRet0d();
// 14177e3b0 / 3e0
void DtorCMsgLog(void* p);
void* CMsgLogScalarDtor(void* p, uint8_t uFlags);
// 14177e430 / 460
void DtorCMsgSynChgDomName(void* p);
void* CMsgSynChgDomNameScalarDtor(void* p,
                                   uint8_t uFlags);
// 14177e4c0 (p, the destruct flags a/b/c)
void DtorCModule(void* p, uint64_t uA, uint64_t uB,
                 uint64_t uC);
// 14177e600
uint64_t DeletingDtorModule(void* p);
// 14177e620
uint64_t ModuleStartup(void* p, uint64_t uA,
                       uint64_t uB);
// 14177e6c0: (module, hdr, len) — hdr[0] = the size
// gate, hdr[1] = the msg type id
void* ModuleGetMsg(void* p, uint16_t* puHdr,
                   uint16_t uLen);
// 14177e890
bool ModuleInit(void* p);
// 14177eaa0
void SvcPassThrough(void* p, uint64_t uObj,
                    const char* pStr1,
                    const char* pStr2);
// 14177eac0
uint64_t StubRet1();
// 14177ead0: (p, kernel, id) — the ctor-family init
void* InitCModule(void* p, uint64_t uKernel,
                  uint32_t uId);
// 14177ec00
void* ScalarDeletingDtorModule(void* p,
                               uint64_t uFlags);
// 14177ec30: (module, id, hdr, len) — the dispatch +
// msg vt+0x18(id) + (uint16)msg[1]
uint16_t ModuleProcessMsg(void* p, uint32_t uId,
                          uint16_t* puHdr,
                          uint16_t uLen);
// 14177ec90
void* ModuleCreate(uint64_t uA, uint32_t uId);

} // namespace syndicate
