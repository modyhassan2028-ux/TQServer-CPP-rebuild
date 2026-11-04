// ============================================================================
// synleaves.h — RAW Syndicate.dll v6159 · the 46 leaf getters of the 0x1417c5900 range.
//   Every body was verified instruction by instruction with objdump and classified into
//   four shapes: an address (lea rax,[rcx+N]), an identity (mov rax,rcx), a load
//   (mov rax,[rcx+N]) and a load-plus-constant; plus the two movabs constants. There is
//   no log call and no _invalid_parameter_noinfo in any of them.
//   Aliases sharing one body (ported once, listed here for traceability):
//     identity    0x1417c5c70
//     offset 0x40 0x1417c5c90
//     clear       0x1417c59a0 / 0x1417c5c00 / 0x1417c5ea0
//     copy16+flag 0x1417c5ae0 / 0x1417c5b10 / 0x1417c5be0 / 0x1417c5e80
//     release     0x1417c5c80 / 0x1417c5cc0 / 0x1417c5d30 / 0x1417c5e00
//     constant    0x1417c5f50 (0x1fffffffffffffff)
// ============================================================================
#ifndef SYNDICATE_SYNLEAVES_H
#define SYNDICATE_SYNLEAVES_H

#include <cstdint>

namespace tq {

void* SynLeaf_1417c59b0(void* p);   // 0x1417c59b0  identity
void* SynLeaf_1417c59c0(void* p);   // 0x1417c59c0  return p + 0x29
//   0x1417c59d0 shares the body of the function above
void* SynLeaf_1417c59e0(void* p);   // 0x1417c59e0  return p + 0x10
void* SynLeaf_1417c59f0(void* p);   // 0x1417c59f0  return *(void**)(p + 0x30)
void* SynLeaf_1417c5a00(void* p);   // 0x1417c5a00  return *(void**)(p + 0x30) + 0x10
//   0x1417c5a10 shares the body of the function above
//   0x1417c5a20 shares the body of the function above
void* SynLeaf_1417c5a30(void* p);   // 0x1417c5a30  return p + 0x41
//   0x1417c5a40 shares the body of the function above
//   0x1417c5a50 shares the body of the function above
//   0x1417c5a60 shares the body of the function above
//   0x1417c5a70 shares the body of the function above
//   0x1417c5a80 shares the body of the function above
void* SynLeaf_1417c5a90(void* p);   // 0x1417c5a90  return p + 0x21
//   0x1417c5aa0 shares the body of the function above
//   0x1417c5ab0 shares the body of the function above
//   0x1417c5ac0 shares the body of the function above
//   0x1417c5ad0 shares the body of the function above
void* SynLeaf_1417c5b00(void* p);   // 0x1417c5b00  return *(void**)(p + 0x8)
//   0x1417c5b70 shares the body of the function above
//   0x1417c5bc0 shares the body of the function above
//   0x1417c5bd0 shares the body of the function above
//   0x1417c5c10 shares the body of the function above
void* SynLeaf_1417c5c20(void* p);   // 0x1417c5c20  return p + 0x28
void* SynLeaf_1417c5c30(void* p);   // 0x1417c5c30  return p + 0x8
void* SynLeaf_1417c5c40(void* p);   // 0x1417c5c40  return p + 0x18
//   0x1417c5ca0 shares the body of the function above
//   0x1417c5cb0 shares the body of the function above
void* SynLeaf_1417c5cd0(void* p);   // 0x1417c5cd0  return p + 0x20
//   0x1417c5ce0 shares the body of the function above
//   0x1417c5cf0 shares the body of the function above
//   0x1417c5d00 shares the body of the function above
//   0x1417c5d10 shares the body of the function above
//   0x1417c5d20 shares the body of the function above
//   0x1417c5d80 shares the body of the function above
//   0x1417c5d90 shares the body of the function above
//   0x1417c5da0 shares the body of the function above
//   0x1417c5db0 shares the body of the function above
//   0x1417c5dc0 shares the body of the function above
void* SynLeaf_1417c5dd0(void* p);   // 0x1417c5dd0  return *(void**)(p + 0x30) + 0x8
//   0x1417c5de0 shares the body of the function above
//   0x1417c5df0 shares the body of the function above
//   0x1417c5e50 shares the body of the function above
uint64_t SynLeaf_1417c5eb0(void);   // 0x1417c5eb0  the constant 0x666666666666666
uint64_t SynLeaf_1417c5ef0(void);   // 0x1417c5ef0  the constant 0xfffffffffffffff

}  // namespace tq

#endif  // SYNDICATE_SYNLEAVES_H
