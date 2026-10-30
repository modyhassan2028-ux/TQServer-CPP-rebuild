// ============================================================================
// stl_iterators.h — RAW Flower.dll v6159
//   The compiler-emitted checked iterator operations Flower.dll carries. Every
//   one of them keeps the MSVC debug-iterator shape: a pair {container, offset}
//   where the container's size sits at +0x20 and, for tree iterators, the head
//   node's sentinel at +0x30. The bounds failure is the CRT's
//   _invalid_parameter_noinfo, exposed here as a seam.
//     0x140d94090 eq   0x140d940d0 ne   0x140d94210 eq (second copy)
//     0x140d94190 deref offset          0x140d941d0 ++
//     0x140d942f0 tree value at +0x18   0x140d94600 += n
//     0x140d94330 throws length_error("vector<T> too long")
//     0x140d943a0 logic_error copy ctor 0x140d94410 length_error copy ctor
// ============================================================================
#ifndef FLOWER_STL_ITERATORS_H
#define FLOWER_STL_ITERATORS_H
#include <cstdint>

namespace flower {
namespace stl {

struct CheckedIterator {
    void* pContainer;    // +0x00
    uintptr_t uOffset;   // +0x08
};

// _invalid_parameter_noinfo, the CRT hook the original calls
extern void (*g_pfnInvalidParameter)();
void InvalidParameter();

bool IterEq(const CheckedIterator* a, const CheckedIterator* b);    // 0x140d94090
bool IterNe(const CheckedIterator* a, const CheckedIterator* b);    // 0x140d940d0
bool IterEq2(const CheckedIterator* a, const CheckedIterator* b);   // 0x140d94210
uintptr_t IterOffset(const CheckedIterator* it);                    // 0x140d94190
CheckedIterator* IterNext(CheckedIterator* it);                     // 0x140d941d0
uintptr_t IterTreeValue(const CheckedIterator* it);                 // 0x140d942f0
CheckedIterator* IterAdvance(CheckedIterator* it, uintptr_t n);     // 0x140d94600
void ThrowVectorTooLong();                                          // 0x140d94330
void LogicErrorCopyCtor(void* pSelf, const void* pOther);           // 0x140d943a0
void LengthErrorCopyCtor(void* pSelf, const void* pOther);          // 0x140d94410

}  // namespace stl
}  // namespace flower
#endif
