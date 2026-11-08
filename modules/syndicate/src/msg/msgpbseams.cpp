// msgpbseams.cpp — the protobuf seams that the PB message headers declare and that no translation unit
// defined. Only the ones the protobuf files do not define themselves live here: g_pfnPbEF830,
// g_pfnPbF0330, g_pfnPbF0450 and g_pfnPbF10A0 are defined at the top of the two PB files that use them,
// and duplicating those is a link error rather than a convenience.
//
// Each of these is a real call into another module (protobuf itself, or the module's own helpers), so
// they stay seams and default to null like every other seam in this tree. The types are the
// declarations' own, copied rather than guessed: a seam is only useful if a test can wire a function of
// exactly the right shape into it.
#include <cstdint>

namespace syndicate {

uint64_t (*g_pfnPb3A50)(void*, uint32_t*) = nullptr;                 // 0x1417e3a50
uint64_t (*g_pfnPb3BC0)(void*) = nullptr;                            // 0x1417e3bc0
void (*g_pfnPb4550)(void*, void*) = nullptr;                         // 0x1417e4550
void (*g_pfnPb45D0)(void*) = nullptr;                                // 0x1417e45d0
void (*g_pfnPb64C0)(void*, void*) = nullptr;                         // 0x1417e64c0
uint64_t (*g_pfnPb6510)(void*) = nullptr;                            // 0x1417e6510
uint64_t (*g_pfnPb8050)() = nullptr;                                 // 0x1417e8050
void (*g_pfnPbCheckFail)(const char*, int, const char*) = nullptr;   // protobuf's CHECK failure
void (*g_pfnPbDelArray)(void*) = nullptr;                            // operator delete of an array
void (*g_pfnPbE0110)(void*, int32_t) = nullptr;                      // 0x1417ee110
char (*g_pfnPbF3F50)(void*, uint32_t, void*) = nullptr;              // 0x1417f3f50
void (*g_pfnPbF4DC0)(uint32_t, void*, void*) = nullptr;              // 0x1417f4dc0
uint64_t (*g_pfnPbF51E0)(void*, void*) = nullptr;                    // 0x1417f51e0
void (*g_pfnPbInitGuard)(void*) = nullptr;                           // the per-message init guard
int32_t (*g_pfnPbVarintSize)(uint32_t) = nullptr;                    // protobuf varint size
void (*g_pfnPbWriteString)(uint32_t, void*, void*) = nullptr;        // protobuf WriteString
void (*g_pfnPbWriteUnknown)(void*, void*, int32_t) = nullptr;         // protobuf WriteUnknown
void (*g_pfnPbWriteVarint32)(uint32_t, uint32_t, void*) = nullptr;   // protobuf WriteVarint32
void* g_pPbDefaultStr = nullptr;                                     // protobuf's shared empty string
void (*g_fn_1417e8050)() = nullptr;                                   // 0x1417e8050, answered and ignored
void (*g_pfnMessageLiteCtor)(void*) = nullptr;                        // the import at 0x141823280

}  // namespace syndicate
