// Instruction-by-instruction port of the twelve CSyndicateLogic slots described in the
// header. Nothing is inferred beyond the registers the bytes read.
#include "CsyndicateLogicTailSlots.h"
#include <cstddef>

namespace tq {

namespace {
constexpr size_t kLeft = 0x00, kParent = 0x08, kRight = 0x10, kKey = 0x18, kIsNil = 0x29;
constexpr size_t kScary = 0x00, kEndNode = 0x30;
inline uint8_t* node_at(uint8_t* p, size_t off) {
    return p ? *(uint8_t**)(p + off) : nullptr;
}
}  // namespace


static uint64_t none4(uint64_t, uint64_t, uint64_t, uint64_t) { return 0; }
static uint64_t none2(uint64_t, uint64_t) { return 0; }
static uint64_t none1(uint64_t) { return 0; }

uint64_t (*g_pfnLogic_1417cadb0)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417caa00)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417cad90)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417cb000)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417873a0)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417a8a50)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417a8940)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_14177f980)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;

static uint64_t lookup_bridge(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    return Slot_1417cad00_lookup((void*)(uintptr_t)a, (uint32_t)b, c, d);
}
uint64_t (*g_pfnLogic_1417cad00)(uint64_t, uint64_t, uint64_t, uint64_t) = lookup_bridge;

static void noop_method(void*, uint64_t) {}
void (*g_pfnLogic_1417a6960)(void* value, uint64_t arg) = noop_method;

// 0x1417a8a50 — the guard used by the CSyndicateLogic slots that forward at +0x20.
// Its own record stops at 0x1417a8a7e, so the body below was carved from the bytes through the
// real ending at 0x1417a8af6: the early `xor al,al / ret`, the second half that calls the walk,
// and the `mov al,1` tail. Nothing here comes from the truncated record.
bool Slot_1417a8a50(void* self, uint32_t id, uint64_t arg3, uint64_t /*r9*/) {
    if (id == 0)                                        // test edx,edx / jne
        return false;                                   // xor al,al

    uint8_t* map = (uint8_t*)self + 0x18;               // lea rbx,[rcx+0x18]
    uint8_t* it[2] = {nullptr, nullptr};                 // rsp+0x20 / rsp+0x28
    Slot_1417c8f70_lower_bound(map, it, &id);            // call 0x1417a8520 (same routine)

    uint8_t* scary = it[0];                              // mov rdi,[rsp+0x20]
    uint8_t* head = *(uint8_t**)(map + kEndNode);        // mov rbp,[rbx+0x30]
    if (scary == nullptr || scary != *(uint8_t**)(map + kScary))
        g_pfn_invalid_parameter_noinfo();                          // the iterator check

    uint8_t* node = it[1];                               // mov rbx,[rsp+0x28]
    if (node != head) {                                  // cmp rbx,rbp / je tail
        uint8_t* owner;
        if (scary == nullptr) {                          // test rdi,rdi / jne
            g_pfn_invalid_parameter_noinfo();
            owner = nullptr;                             // xor r11d,r11d
        } else {
            owner = *(uint8_t**)(scary + 0x00);          // mov r11,[rdi]
        }
        if (node == *(uint8_t**)(owner + kEndNode))      // cmp rbx,[r11+0x30]
            g_pfn_invalid_parameter_noinfo();

        void* value = *(void**)(node + 0x20);            // mov rcx,[rbx+0x20]
        if (value != nullptr) {                          // test rcx,rcx / je tail
            g_pfnLogic_1417a6960(value, arg3);           // mov rdx,rsi / call 0x1417a6960
        }
    }
    return true;                                         // mov al,1
}
uint64_t (*g_pfnLogic_141797e00)(uint64_t, uint64_t) = none2;
uint64_t (*g_pfnLogic_14178f470)(uint64_t) = none1;

static void noop_void() {}
void (*g_pfn_invalid_parameter_noinfo)(void) = noop_void;

// 0x1417c8f70 — std::_Tree lower_bound. Static member offsets are the ones the bytes use;
// they are named structurally because no symbol survives to name them.

void* Slot_1417c8f70_lower_bound(void* container_void, void* out_void, const uint32_t* key_in) {
    uint8_t* container = (uint8_t*)container_void;
    uint8_t** out = (uint8_t**)out_void;

    uint8_t* end = *(uint8_t**)(container + kEndNode);   // mov rbx,[rcx+0x30]
    uint8_t* node = *(uint8_t**)(end + kParent);         // mov rax,[rbx+0x8]  (the root)
    // rbx in the original starts as the END node (`mov rbx,[rcx+0x30]` before the walk) and is
    // only moved when the walk turns left, which is why an untouched candidate answers "end".
    uint8_t* candidate = end;
    uint32_t key = 0;

    if (*(uint8_t*)(node + kIsNil) == 0) {               // cmp byte [rax+0x29],0 / jne L22
        key = *key_in;                                   // mov r9d,[r8]
        for (;;) {
            if (*(uint32_t*)(node + kKey) < key) {       // cmp [rax+0x18],r9d / jb  -> right
                node = *(uint8_t**)(node + kRight);
            } else {                                     // else remember and go left
                candidate = node;
                node = *(uint8_t**)(node + kLeft);
            }
            if (*(uint8_t*)(node + kIsNil) != 0)         // cmp byte [rax+0x29],0 / je loop
                break;
        }
    }

    uint8_t* scary = *(uint8_t**)(container + kScary);   // mov rax,[rcx]
    uint8_t* head = *(uint8_t**)(container + kEndNode);  // mov rdi,[rcx+0x30]
    if (!scary)                                          // test rax,rax / jz L30
        g_pfn_invalid_parameter_noinfo();                          // L30: the error path, then continue

    uint8_t** pair;                                      // rcx in the original: rsp+0x20 or +0x30
    uint8_t* slot[2];
    if (candidate == head || *(uint32_t*)(candidate + kKey) < key) {
        slot[0] = scary;                                 // the end iterator: {scary, head}
        slot[1] = head;
        pair = slot;
    } else {
        slot[0] = scary;                                 // {scary, the found node}
        slot[1] = candidate;
        pair = slot;
    }

    out[0] = pair[0];                                    // mov rax,[rcx]  / mov [rbp],rax
    out[1] = pair[1];                                    // mov rax,[rcx+8] / mov [rbp+8],rax
    return out;                                          // mov rax,rbp
}

// 0x1417cad00 — the lookup the three wrappers call. Every load, compare and offset below is
// the one the bytes perform; both branches that reach 0x1418233c0 are the _DEBUG iterator
// checks, and like the original they continue rather than throw.
// The static slots the two getters read and write. In the image these are rip-relative words in
// .data; here they are file-scope pointers, which is the same lifetime without a relocation.
static void zero_bytes(uint8_t* p, size_t n) {            // byte writes, so no alignment UB
    for (size_t i = 0; i < n; ++i) p[i] = 0;
}

static void* g_singleton_14177c770 = nullptr;
static void* g_singleton_1417b6210 = nullptr;

void* (*g_pfnLogic_14177c6c0)(void* mem) = nullptr;
void (*g_pfn_log_InlineLogERROR)(const void* p0, const void* p1, const void* p2,
                                 const void* p3, uint32_t line) = nullptr;

// 0x14177c770 — the 0x40-byte singleton.
void* Slot_14177c770_singleton(void) {
    if (g_singleton_14177c770 != nullptr)                    // mov rax,[rip+..] / test / jne
        return g_singleton_14177c770;

    void* mem = ::operator new(0x40);                        // lea ecx,[rax+0x40] / call new
    void* built = nullptr;
    if (mem != nullptr) {                                    // test rax,rax / je
        if (g_pfnLogic_14177c6c0 != nullptr)                  // call 0x14177c6c0
            built = g_pfnLogic_14177c6c0(mem), built = mem;
        else
            built = mem;
    }
    g_singleton_14177c770 = built;                           // mov [rip+..],rbx
    if (g_singleton_14177c770 == nullptr) {                  // test rbx,rbx / jne
        if (g_pfn_log_InlineLogERROR != nullptr)             // line 0xa6, four pointers
            g_pfn_log_InlineLogERROR((const void*)(uintptr_t)0x141824ca8ULL,
                                     (const void*)(uintptr_t)0x141828160ULL,
                                     (const void*)(uintptr_t)0x141828170ULL,
                                     (const void*)(uintptr_t)0x14182db40ULL, 0xa6);
    }
    return g_singleton_14177c770;                            // mov rax,rbx
}

// 0x1417b6210 — the 0x88-byte singleton, built inline with two vtable stores and the rest cleared.
void* Slot_1417b6210_singleton(void) {
    if (g_singleton_1417b6210 != nullptr)                    // mov rax,[rip+..] / test / jne
        return g_singleton_1417b6210;

    uint8_t* mem = (uint8_t*)::operator new(0x88);            // mov ecx,0x88 / call new
    uint8_t* built = nullptr;
    if (mem != nullptr) {                                    // test rax,rax / je
        *(void**)mem = (void*)(uintptr_t)0x141834928ULL;      // lea rcx,[rip+..] / mov [rax],rcx
        *(void**)mem = (void*)(uintptr_t)0x141835068ULL;      // second vtable store wins, as written
        for (size_t off = 0x8; off <= 0x58; off += 8)         // the cleared words
            zero_bytes(mem + off, 8);
        *(uint8_t*)(mem + 0x60) = 0;                          // mov byte [rax+0x60],cl
        zero_bytes(mem + 0x61, 8);                            // then four unaligned words
        zero_bytes(mem + 0x69, 8);
        zero_bytes(mem + 0x71, 8);
        zero_bytes(mem + 0x79, 8);
        built = mem;
    }
    g_singleton_1417b6210 = built;                           // mov [rip+..],rax
    if (g_singleton_1417b6210 == nullptr) {                  // test rax,rax / jne
        if (g_pfn_log_InlineLogERROR != nullptr)             // line 0xdd, four pointers
            g_pfn_log_InlineLogERROR((const void*)(uintptr_t)0x141824ca8ULL,
                                     (const void*)(uintptr_t)0x141828160ULL,
                                     (const void*)(uintptr_t)0x141828170ULL,
                                     (const void*)(uintptr_t)0x141835bd0ULL, 0xdd);
    }
    return g_singleton_1417b6210;                            // mov rax,rax at the shared tail
}

// 0x14177c0a0 — find by key. The walk keeps its candidate in rbx starting at the head, exactly
// like 0x1417c8f70, but this one answers the stored value and decides "absent" by comparing the
// wanted key with the candidate's key rather than by reaching the end node.
uint64_t Slot_14177c0a0_find(void* self, uint32_t key) {
    uint8_t* head = *(uint8_t**)((uint8_t*)self + kEndNode);       // mov rbx,[rcx+0x30]
    uint8_t* node = *(uint8_t**)(head + kParent);                  // mov rax,[rbx+8]
    uint8_t* candidate = head;                                     // rbx = the head
    if (*(uint8_t*)(node + kIsNil) == 0) {                         // cmp byte [rax+0x29],sil
        do {
            if (*(uint32_t*)(node + kKey) < key)                   // cmp [rax+0x18],edx / jae
                node = *(uint8_t**)(node + kRight);                 // mov rax,[rax+0x10]
            else {
                candidate = node;                                   // mov rbx,rax
                node = *(uint8_t**)(node + kLeft);                  // mov rax,[rax+0]
            }
        } while (*(uint8_t*)(node + kIsNil) == 0);                  // cmp byte [rax+0x29],sil / jne
    }

    uint8_t* scary = *(uint8_t**)((uint8_t*)self + kScary);         // mov rax,[rcx]
    uint8_t* end = *(uint8_t**)((uint8_t*)self + kEndNode);         // mov rbp,[rcx+0x30]
    if (scary == nullptr)                                           // test rax,rax / jz
        g_pfn_invalid_parameter_noinfo();
    // the bytes then compare rax with itself and always fall through, so no second check happens
    if (candidate == end)                                           // cmp rbx,rbp / jz end
        return 0;
    if (key < *(uint32_t*)(candidate + kKey))                       // cmp edx,[rbx+0x18] / jb
        return 0;

    uint8_t* copy0 = scary;                                         // the second iterator copy
    uint8_t* copy1 = candidate;
    if (*(uint8_t**)((uint8_t*)self + kScary) == nullptr ||
        *(uint8_t**)((uint8_t*)self + kScary) != copy0)
        g_pfn_invalid_parameter_noinfo();
    if (end == copy1)                                               // cmp rbp,rbx / jz
        return 0;

    uint8_t* owner;
    if (copy0 == nullptr) {
        g_pfn_invalid_parameter_noinfo();
        owner = nullptr;                                            // xor r11d,r11d path
    } else {
        owner = *(uint8_t**)(copy0 + 0x00);                          // mov rsi,[rdi]
    }
    if (copy1 == *(uint8_t**)(owner + kEndNode))                    // cmp rbx,[rsi+0x30]
        g_pfn_invalid_parameter_noinfo();
    return *(uint64_t*)(copy1 + 0x20);                              // mov rax,[rbx+0x20]
}

// 0x141724850 — mov rcx,[rcx] / jmp 0x1417f2fdc, and 0x1417f2fdc is MSVCR90's
// ??3@YAXPEAX@Z, operator delete(void*). This frees the object the holder points at.
void Slot_141724850_delete_through(void* holder) {
    delete (void*)*(void**)holder;                       // mov rcx,[rcx] / jmp operator delete
}

// 0x1417ac810 — mov rcx,[rcx+8] / mov rax,[rcx] / jmp qword ptr [rax+0x1f8]
uint64_t Slot_1417ac810_vcall_1f8(void* self, uint32_t id) {
    uint8_t* inner = *(uint8_t**)((uint8_t*)self + 0x8);  // mov rcx,[rcx+8]
    void** vtbl = *(void***)inner;                        // mov rax,[rcx]
    auto fn = (uint64_t (*)(void*, uint32_t))(vtbl[0x1f8 / 8]);
    return fn(inner, id);                                 // jmp [rax+0x1f8], edx unchanged
}

uint64_t Slot_1417cad00_lookup(void* self, uint32_t id, uint64_t /*r8*/, uint64_t /*r9*/) {
    if (id == 0)                                        // test edx,edx / jz L37
        return 0;

    uint8_t* container = (uint8_t*)self + 0x8;           // lea rbx,[rcx+0x8]
    uint8_t* it[2] = {nullptr, nullptr};                 // rsp+0x20 / rsp+0x28
    Slot_1417c8f70_lower_bound(container, it, &id);      // the id spilled at [rsp+0x10] is the key

    uint8_t* scary = it[0];                              // mov rdi,[rsp+0x20]
    uint8_t* head = *(uint8_t**)(container + kEndNode);  // mov rsi,[rbx+0x30]
    if (scary == nullptr || scary != *(uint8_t**)(container + kScary))
        g_pfn_invalid_parameter_noinfo();                          // L18

    uint8_t* node = it[1];                               // mov rbx,[rsp+0x28]
    if (node == head)                                    // cmp rbx,rsi / jz L37
        return 0;

    uint8_t* owner;
    if (scary == nullptr) {                              // test rdi,rdi / jz
        g_pfn_invalid_parameter_noinfo();
        owner = nullptr;                                 // xor r11d,r11d
    } else {
        owner = *(uint8_t**)(scary + 0x00);              // mov r11,[rdi]
    }
    if (node == *(uint8_t**)(owner + kEndNode))          // cmp rbx,[r11+0x30]
        g_pfn_invalid_parameter_noinfo();

    return *(uint64_t*)(node + 0x20);                    // mov rax,[rbx+0x20]
}

int Slot_1417cad90(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t r = g_pfnLogic_1417cad00((uint64_t)(uintptr_t)self, rdx, r8, r9);
    return r != 0;
}

// 0x1417cadb0: mov ebx,edx / mov edx,r8d / call 0x1417cad00 / test rax,rax / jz 0
//              mov edx,ebx / mov rcx,rax / jmp 0x141797e00
// The second argument is truncated to 32 bits before the lookup, and the hit is passed on
// with the ORIGINAL id (also 32-bit) as the second argument.
uint64_t Slot_1417cadb0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint32_t id = (uint32_t)rdx;
    uint64_t hit = g_pfnLogic_1417cad00((uint64_t)(uintptr_t)self, (uint64_t)(uint32_t)r8, r8, r9);
    if (!hit)
        return 0;
    return g_pfnLogic_141797e00(hit, (uint64_t)id);
}

// 0x1417cb000: call 0x1417cad00 / test rax,rax / jnz L7 / mov rax,0x141827409
//              L7: mov rcx,rax / jmp 0x14178f470
// Only rcx is meaningful at the tail jump: rdx/r8/r9 still hold whatever the lookup left in
// them, which is volatile state, so the seam takes rcx alone rather than forwarding garbage.
uint64_t Slot_1417cb000(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t hit = g_pfnLogic_1417cad00((uint64_t)(uintptr_t)self, rdx, r8, r9);
    uint64_t arg = hit ? hit : (uint64_t)(uintptr_t)0x141827409;
    return g_pfnLogic_14178f470(arg);
}

// 0x1417abe60: mov rcx,[rcx+0x10] / jmp 0x1417cadb0
uint64_t Slot_1417abe60(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417cadb0(m, rdx, r8, r9);
}

// 0x1417ac010: mov rcx,[rcx+0x10] / jmp 0x1417caa00
uint64_t Slot_1417ac010(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417caa00(m, rdx, r8, r9);
}

// 0x1417ab1d0: mov rcx,[rcx+0x10] / jmp 0x1417cad90
uint64_t Slot_1417ab1d0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417cad90(m, rdx, r8, r9);
}

// 0x1417ab1c0: mov rcx,[rcx+0x10] / jmp 0x1417cb000
uint64_t Slot_1417ab1c0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417cb000(m, rdx, r8, r9);
}

// 0x1417aeba0: mov ecx,edx / jmp 0x1417873a0 — the argument is zero-extended into rcx and
// `this` is not passed at all.
uint64_t Slot_1417aeba0(void* /*self*/, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t arg = (uint64_t)(uint32_t)rdx;
    return g_pfnLogic_1417873a0(arg, rdx, r8, r9);
}

// 0x1417aaf90: mov eax,0xf / ret
int Slot_1417aaf90(void* /*self*/) { return 0xf; }

// 0x1417aafa0: mov eax,0xf / ret
int Slot_1417aafa0(void* /*self*/) { return 0xf; }

// 0x1417abc50: cmp edx,0x3de / setge al
int Slot_1417abc50(void* /*self*/, int32_t arg) { return (arg >= 0x3de) ? 1 : 0; }

// 0x1417abc60: cmp edx,0x37a / setle al
int Slot_1417abc60(void* /*self*/, int32_t arg) { return (arg <= 0x37a) ? 1 : 0; }

// 0x1417af2f0: mov rcx,[rcx+0x20] / test rcx,rcx / jz L4 / jmp 0x1417a8a50
//              L4 sets only al, i.e. answers false.
int Slot_1417af2f0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x20);
    if (!m)
        return 0;
    return (int)g_pfnLogic_1417a8a50(m, rdx, r8, r9);
}

// 0x1417af310: mov rcx,[rcx+0x20] / jz 0 / jmp 0x1417a8940
int Slot_1417af310(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x20);
    if (!m)
        return 0;
    return (int)g_pfnLogic_1417a8940(m, rdx, r8, r9);
}

// 0x1417afac0: mov rcx,[rcx+0x28] / jz 0 / jmp 0x14177f980
int Slot_1417afac0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x28);
    if (!m)
        return 0;
    return (int)g_pfnLogic_14177f980(m, rdx, r8, r9);
}

}  // namespace tq
