#ifndef SYNDICATE_VTABLEFORWARDERS_H
#define SYNDICATE_VTABLEFORWARDERS_H
#include <cstdint>

// Four forwarders at 0x14177fa10..0x14177fa86 and the selector that hands them out at 0x14177fa90.
// Every one of them reshapes a call: it replaces the receiver, moves the third argument into the second,
// and tail-jumps into a vtable slot. The slot offsets are the whole content of the family, and the
// selector is a switch that returns a function pointer, so the three-argument call surface stays the same
// while what actually runs depends on an integer.
namespace synd {

// 0x1417b6210 / 0x14173f9c0 / 0x14173d820 stay seams until their bodies are ported.
extern void* (*g_pfn1417b6210)(void*);
extern void* (*g_pfn14173f9c0)(void*, int32_t, int32_t);
extern std::int32_t (*g_pfn14173d820)(void*, int32_t, int32_t);

void ForwardSlot2B0(void* self, std::int32_t a2, std::int32_t a3);   // 0x14177fa40
void ForwardSlot2B8(void* self, std::int32_t a2, std::int32_t a3);   // 0x14177fa50
void ForwardVia14173D820(void* self, std::int32_t a2, std::int32_t a3);  // 0x14177fa60
void ForwardSlot378(void* self, std::int32_t a2, std::int32_t a3);   // 0x14177fa10

// 0x14177fa90 — returns the forwarder for 0, 1, 2, 3, and null for anything else.
void (*SelectForwarder(std::int32_t kind))(void*, std::int32_t, std::int32_t);

}  // namespace synd
#endif
