// The checked vector accessors: every one of them re-reads the owner through the first slot and reports an
// out-of-range position through _invalid_parameter_noinfo before answering anything.
#ifndef TQ_NPCSERVER_VECTOR_ACCESSORS_H
#define TQ_NPCSERVER_VECTOR_ACCESSORS_H

namespace tq {

extern void (*g_pfnNpcInvalidParameter)(void);

long long  FUN_140026600(long long* pIter);          // returns the position
long long  FUN_140026700(long long* pIter);          // the same body
long long* FUN_140026640(long long* pIter);          // position += 8
long long* FUN_140026740(long long* pIter);          // position += 4
long long  FUN_1400268f0(long long* pIter);          // returns position + 0x18, refusing the end slot
long long  FUN_140026a30(long long* pIter);          // the same body

struct NpcVectorAccessorEntry {
    const char* pszAddress;
    const char* pszKind;      // "position" | "step" | "tail"
    void*       pfn;
    long long   nValue;       // the step, or the node offset for the tail accessors
};

extern const NpcVectorAccessorEntry g_aNpcVectorAccessor[];
extern const int g_nNpcVectorAccessor;

}  // namespace tq

#endif
