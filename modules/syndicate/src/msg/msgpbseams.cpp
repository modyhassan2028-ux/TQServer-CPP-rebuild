// msgpbseams.cpp — the protobuf seams that the PB message headers declare and that no translation unit
// defined. Only the ones the protobuf files do not define themselves live here: g_pfnPbEF830,
// g_pfnPbF0330, g_pfnPbF0450 and g_pfnPbF10A0 are defined at the top of the two PB files that use them,
// and duplicating those is a link error rather than a convenience.
//
// Every name that the protobuf files do not define themselves lives here, and nothing more: the other
// twenty-one turned out to be defined at the top of the message files that use them, which is a link error
// to repeat rather than a convenience. The original note follows.
//
// Each of these is a real call into another module (protobuf itself, or the module's own helpers), so
// they stay seams and default to null like every other seam in this tree. The types are the
// declarations' own, copied rather than guessed: a seam is only useful if a test can wire a function of
// exactly the right shape into it.
#include <cstdint>

namespace syndicate {

void (*g_pfnMessageLiteCtor)(void*) = nullptr;   // the import at 0x141823280, patched into a test
void (*g_fn_1417e8050)() = nullptr;   // 0x1417e8050, called by the token constructor and its answer discarded

}  // namespace syndicate
