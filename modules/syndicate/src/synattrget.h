// ============================================================================
// synattrget.h — RAW Syndicate.dll v6159 · the CSynAttr field readers. Each one takes the
//   address of the owning record pointer, guards it with IF_OK(m_pRec) reported at
//   synattr.cpp, then asks the record for the sub-record of one kind (slot 0x10) and reads
//   that through its slot 0x48. Nine instantiations, one per kind.
// ============================================================================
#ifndef SYNDICATE_SYNATTRGET_H
#define SYNDICATE_SYNATTRGET_H

namespace tq {

// ppRec is the address of the record pointer, exactly what the binary dereferences
void* SynAttrValueKind3(void* ppRec);      // 0x1417862c0, synattr.cpp:0x31c
void* SynAttrValueKind4(void* ppRec);      // 0x141786320, synattr.cpp:0x329
void* SynAttrValueKind5(void* ppRec);      // 0x141786380, synattr.cpp:0x336
void* SynAttrValueKind6(void* ppRec);      // 0x1417863e0, synattr.cpp:0x343
void* SynAttrValueKind7(void* ppRec);      // 0x141786440, synattr.cpp:0x350
void* SynAttrValueKindC(void* ppRec);      // 0x1417864a0, synattr.cpp:0x3f8
void* SynAttrValueKindD(void* ppRec);      // 0x141786500, synattr.cpp:0x405
void* SynAttrValueKindE(void* ppRec);      // 0x141786560, synattr.cpp:0x412
void* SynAttrValueKindF(void* ppRec);      // 0x1417865c0, synattr.cpp:0x41f

}  // namespace tq

#endif  // SYNDICATE_SYNATTRGET_H
