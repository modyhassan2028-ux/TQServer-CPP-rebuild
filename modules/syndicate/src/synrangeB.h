// ============================================================================
// synrangeB.h — RAW Syndicate.dll v6159 · the second block of checked-iterator and
//   tree-end plumbing, 0x1417c5980..0x1417c61d0. Node layout throughout is the ported
//   one (synnode.h): left +0x00, parent +0x08, right +0x10, key +0x18, value +0x20,
//   nil byte +0x29 for the id instantiation and +0x41 for the name instantiation.
//   This block holds NO log_InlineLogERROR call: only _invalid_parameter_noinfo
//   (0x1418233c0) and operator delete.
// ============================================================================
#ifndef SYNDICATE_SYNRANGEB_H
#define SYNDICATE_SYNRANGEB_H

#include <cstdint>

namespace syndicate { extern void (*g_fnInvalidParam)(void); }

namespace tq {

// ---- the value accessors: qword[1] + 0x18, guarded by the head's own +0x30 qword
void* SynIterValueId(void* pIter);     // 0x1417c5d40
void* SynIterValueName(void* pIter);   // 0x1417c61d0

// ---- the predecessor steps (left child, then right spine; otherwise climb while the node
//      is its parent's left child). Reaching the sentinel is an invalid parameter.
void SynIterPrevId(void* pIter);       // 0x1417c5fa0 (nil byte +0x29)
void SynIterPrevName(void* pIter);     // 0x1417c6040 (nil byte +0x41)

// ---- the two ends of a tree, from the head node
void* SynMapMinId(void* pHead);        // 0x1417c5c50  left spine
void* SynMapMaxId(void* pHead);        // 0x1417c5ec0  right spine
void* SynMapMinName(void* pHead);      // 0x1417c5f30  left spine, +0x41
void* SynMapMaxName(void* pHead);      // 0x1417c5f00  right spine, +0x41

// ---- the tiny shapes
void* SynIterCopy16(void* pOut, void* pSrc);            // 0x1417c5e60
void* SynIterCopy16Flag(void* pOut, void* pSrc, void* pFlag);  // 0x1417c5ae0
void* SynPairInit(void* pOut, void* pKey, void* pValue);        // 0x1417c5980 (0x1417c5990 same)
void  SynIterRelease(void* pUnused, void* pTarget);              // 0x1417c5c80
void* SynIterIdent(void* pIn);                                   // 0x1417c5c70
void* SynIterClearIdent(void* pIn);                              // 0x1417c59a0
void* SynIterOff40(void* pIn);                                   // 0x1417c5c90
uint64_t SynIterMaxSize(void);                                   // 0x1417c5f50

}  // namespace tq

#endif  // SYNDICATE_SYNRANGEB_H
