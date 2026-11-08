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

void* (*g_pfnLogic_14177ace0)(void* self) = nullptr;
void* (*g_pfnLogic_1417495d0)(void* arg) = nullptr;
void (*g_pfnLogic_141732040)(void* arg, void* elem) = nullptr;

void (*g_pfnLogic_141730cd0)(void* self, void* out_or_arg, void* pair, const void* value) = nullptr;

// 0x1417495d0 — clear the vector. Worth reading carefully: the byte count is computed from the
// finish pointer minus itself, so the memmove is always zero length and the function's whole effect
// is to move finish back to begin. The port shows that instead of writing a loop the bytes do not
// contain.
void Slot_1417495d0_clear_vector(void* self) {
    uint8_t* s = (uint8_t*)self;
    uint64_t finish = *(uint64_t*)(s + 0x20);                 // mov rsi,[rcx+0x20]
    if (*(uint64_t*)(s + 0x18) > finish)                      // cmp [rcx+0x18],rsi / jbe
        g_pfn_invalid_parameter_noinfo();
    uint64_t begin = *(uint64_t*)(s + 0x18);                  // mov rdi,[rbx+0x18]
    if (begin > *(uint64_t*)(s + 0x20))                       // cmp rdi,[rbx+0x20] / jbe
        g_pfn_invalid_parameter_noinfo();
    if (*(uint64_t*)(s + 0x18) > begin)                       // cmp [rbx+0x18],rdi / ja
        g_pfn_invalid_parameter_noinfo();
    if (begin > *(uint64_t*)(s + 0x20))                       // cmp rdi,[rbx+0x20] / jbe
        g_pfn_invalid_parameter_noinfo();
    uint64_t scary = *(uint64_t*)(s + 0x00);                  // mov rbp,[rbx]
    if (*(uint64_t*)(s + 0x18) > finish)                      // cmp [rbx+0x18],rsi / ja
        g_pfn_invalid_parameter_noinfo();
    if (finish > *(uint64_t*)(s + 0x20))                      // cmp rsi,[rbx+0x20] / jbe
        g_pfn_invalid_parameter_noinfo();
    if (scary != 0 && scary != *(uint64_t*)(s + 0x00))        // the self-comparison the bytes make
        g_pfn_invalid_parameter_noinfo();
    if (begin == finish)                                     // cmp rdi,rsi / je done
        return;

    int64_t count = (int64_t)(*(uint64_t*)(s + 0x20) - finish) >> 2;   // sar 2, so zero here
    uint64_t bytes = (uint64_t)count * 4;                    // lea rdx,[rax*4]
    uint64_t new_finish = bytes + begin;                     // lea rbp,[rdx+rdi]
    if (count > 0) {                                         // test rax,rax / jle
        // the bytes would memmove(begin, finish, bytes); with bytes 0 it does nothing
    }
    *(uint64_t*)(s + 0x20) = new_finish;                     // mov [rbx+0x20],rbp
}

// 0x141732040 — append one element.
void Slot_141732040_push_back(void* self, const uint32_t* value) {
    uint8_t* s = (uint8_t*)self;
    uint64_t begin = *(uint64_t*)(s + 0x18);                  // mov rcx,[rcx+0x18]
    uint64_t cap_elems = (begin == 0)                        // test rcx,rcx / jne
                             ? 0
                             : (*(uint64_t*)(s + 0x28) - begin) >> 2;
    uint64_t finish = *(uint64_t*)(s + 0x20);                 // mov rdi,[rbx+0x20]
    uint64_t size = (finish - begin) >> 2;                    // sar rax,2
    if (size < cap_elems) {                                   // cmp rax,r8 / jae grow
        *(uint32_t*)finish = *value;                          // mov eax,[rdx] / mov [rdi],eax
        *(uint64_t*)(s + 0x20) = finish + 4;                  // lea rax,[rdi+4] / mov [rbx+0x20],rax
        return;
    }
    if (begin > finish)                                       // cmp rcx,rdi / jbe
        g_pfn_invalid_parameter_noinfo();
    uint64_t pair[2] = {*(uint64_t*)(s + 0x00), finish};      // the two words the frame builds
    if (g_pfnLogic_141730cd0 != nullptr)                      // call 0x141730cd0
        g_pfnLogic_141730cd0(self, pair, pair, value);
}

// 0x14177ace0 — the end node. Only the first store is guarded by the null test; the bytes then write
// +0x08 and +0x10 without looking again, which is kept here rather than tidied into a check.
void* Slot_14177ace0_new_node(void) {
    uint8_t* n = (uint8_t*)::operator new(0x30);              // mov ecx,0x30 / call operator new
    if (n != nullptr)                                         // test rax,rax / je
        *(uint64_t*)n = 0;                                    // xor ecx,ecx / mov [rax],rcx
    *(uint64_t*)(n + 0x08) = 0;                               // lea rdx,[rax+8] / mov [rdx],rcx
    *(uint64_t*)(n + 0x10) = 0;                               // lea rdx,[rax+0x10] / mov [rdx],rcx
    *(uint8_t*)(n + 0x28) = 1;                                // mov byte [rax+0x28],1
    *(uint8_t*)(n + 0x29) = 0;                                // mov byte [rax+0x29],0
    return n;                                                 // rax
}

// 0x1417a8520 — lower_bound with the key passed by pointer.
uint64_t* Slot_1417a8520_lower_bound(void* self, uint64_t* out, const uint32_t* key) {
    uint8_t* s = (uint8_t*)self;
    uint8_t* head = *(uint8_t**)(s + kEndNode);               // mov rbx,[rcx+0x30]
    uint8_t* node = *(uint8_t**)(head + kParent);             // mov rax,[rbx+8]
    uint8_t* candidate = head;                                // rbx stays the candidate
    if (*(uint8_t*)(node + kIsNil) == 0) {                    // cmp byte [rax+0x29],0 / jne
        do {
            if (*(uint32_t*)(node + kKey) < *key)             // mov r9d,[r8] / cmp [rax+0x18],r9d
                node = *(uint8_t**)(node + kRight);           // mov rax,[rax+0x10]
            else {
                candidate = node;                             // mov rbx,rax
                node = *(uint8_t**)(node + kLeft);            // mov rax,[rax]
            }
        } while (*(uint8_t*)(node + kIsNil) == 0);            // cmp byte [rax+0x29],0 / je
    }

    uint64_t scary = *(uint64_t*)(s + kScary);                // mov rax,[rcx]
    uint64_t end = *(uint64_t*)(s + kEndNode);                // mov rdi,[rcx+0x30]
    if (scary == 0)                                           // test rax,rax / je
        g_pfn_invalid_parameter_noinfo();
    // the bytes then compare rax with itself, so that check can never fire

    const bool use_candidate = (uint64_t)candidate != end &&           // cmp rbx,rdi / je
                               !(*key < *(uint32_t*)(candidate + kKey));  // cmp [r12],eax / jb
    if (use_candidate) {
        out[0] = scary;                                       // mov [rbp],rax
        out[1] = (uint64_t)candidate;                         // mov [rbp+8],rax
    } else {
        out[0] = *(uint64_t*)(s + kScary);                    // mov rax,[rsi] / mov [rsp+0x30],rax
        out[1] = *(uint64_t*)(s + kEndNode);                  // mov rax,[rsi+0x30] / mov [rsp+0x38],rax
    }
    return out;                                               // mov rax,rbp
}

// 0x14177c6c0 — the map constructor. The 8-byte allocation is not padding: the byte store
// `mov [rax],rbx` puts the map itself in it, so the word at [map] leads back to the owner, which is
// exactly the shape the iterator checks in the ported walks expect.
void* Slot_14177c6c0_ctor(void* self) {
    uint8_t* s = (uint8_t*)self;
    void** proxy = (void**)::operator new(8);                 // mov ecx,8 / call operator new
    void* stored = nullptr;
    if (proxy != nullptr) {                                   // test rax,rax / je
        *proxy = self;                                        // mov qword [rax],rbx
        stored = proxy;
    }
    *(void**)s = stored;                                      // mov qword [rbx],rax

    void* head = (g_pfnLogic_14177ace0 != nullptr)            // call 0x14177ace0
                     ? g_pfnLogic_14177ace0(self) : nullptr;
    *(void**)(s + 0x30) = head;                               // mov [rbx+0x30],rax
    *(uint8_t*)((uint8_t*)head + 0x29) = 1;                   // mov byte [rax+0x29],1  (_Isnil)
    *(void**)((uint8_t*)head + 0x08) = head;                  // parent = itself
    *(void**)head = head;                                     // left = itself
    *(void**)((uint8_t*)head + 0x10) = head;                  // right = itself
    *(uint64_t*)(s + 0x38) = 0;                               // mov qword [rbx+0x38],0
    return self;                                              // mov rax,rbx
}

// 0x1417a6960 — per-element pass over the container at +0x38..+0x40.
void Slot_1417a6960_iterate(void* self, void* arg) {
    uint8_t* s = (uint8_t*)self;
    if (g_pfnLogic_1417495d0 != nullptr)                      // mov rcx,rdx / call 0x1417495d0
        g_pfnLogic_1417495d0(arg);

    uint64_t cur = *(uint64_t*)(s + 0x38);                    // mov rbx,[rbp+0x38]
    if (cur > *(uint64_t*)(s + 0x40))                         // cmp rbx,[rbp+0x40] / jbe
        g_pfn_invalid_parameter_noinfo();
    uint64_t word = *(uint64_t*)(s + 0x20);                   // mov rdi,[rbp+0x20]

    for (;;) {
        uint64_t end = *(uint64_t*)(s + 0x40);                // mov rsi,[rbp+0x40]
        if (*(uint64_t*)(s + 0x38) > end)                     // cmp [rbp+0x38],rsi / jbe
            g_pfn_invalid_parameter_noinfo();
        if (word != 0 && word != *(uint64_t*)(s + 0x20))      // test rdi / cmp rdi,[rbp+0x20] / je
            g_pfn_invalid_parameter_noinfo();
        if (cur == end)                                       // cmp rbx,rsi / je done
            break;

        uint64_t owner;
        if (word == 0) {                                      // test rdi,rdi / jne
            g_pfn_invalid_parameter_noinfo();
            owner = 0;                                        // xor r11d,r11d
        } else {
            owner = *(uint64_t*)word;                         // mov r11,[rdi]
        }
        if (!(cur < *(uint64_t*)(owner + 0x20)))              // cmp rbx,[r11+0x20] / jb
            g_pfn_invalid_parameter_noinfo();

        uint64_t elem = *(uint64_t*)cur;                      // mov rdx,[rbx]
        if (elem != 0) {                                      // test rdx,rdx / je skip
            if (g_pfnLogic_141732040 != nullptr)              // mov rcx,r12 / call 0x141732040
                g_pfnLogic_141732040(arg, (void*)elem);
        }

        uint64_t owner2;
        if (word == 0) {                                      // the same check again before the step
            g_pfn_invalid_parameter_noinfo();
            owner2 = 0;
        } else {
            owner2 = *(uint64_t*)word;
        }
        if (!(cur < *(uint64_t*)(owner2 + 0x20)))             // cmp rbx,[r11+0x20] / jb
            g_pfn_invalid_parameter_noinfo();
        cur += 8;                                             // add rbx,8
    }
}

// 0x141779090 — range scan. Every failed bound re-checks through the same
// __invalid_parameter_noinfo the other walks use, and the element answering zero is skipped, not
// treated as a match.
uint64_t* Slot_141779090_search(void* self, uint64_t* out, uint32_t id, uint32_t kind) {
    uint8_t* s = (uint8_t*)self;
    uint64_t begin = *(uint64_t*)(s + 0x20);                  // mov rdi,[rcx+0x20]
    *out = 0;                                                 // mov qword [rdx],0
    if (begin > *(uint64_t*)(s + 0x28))                       // cmp rdi,[rcx+0x28] / jbe
        g_pfn_invalid_parameter_noinfo();
    out[1] = begin;                                           // mov [rbx+8],rdi
    *out = *(uint64_t*)(s + 0x08);                            // mov rax,[rsi+8] / mov [rbx],rax

    for (;;) {
        uint64_t end = *(uint64_t*)(s + 0x28);                 // mov rdi,[rsi+0x28]
        if (*(uint64_t*)(s + 0x20) > end)                      // cmp [rsi+0x20],rdi / jbe
            g_pfn_invalid_parameter_noinfo();
        uint64_t scary = *(uint64_t*)(s + 0x08);               // mov rax,[rsi+8]
        if (scary != 0 && scary != *out)                        // test / cmp rax,[rbx] / je
            g_pfn_invalid_parameter_noinfo();
        if (end == out[1])                                     // cmp rdi,[rbx+8] / je done
            break;

        uint64_t cur = *out;                                   // mov rax,[rbx]
        if (cur == 0)                                          // test rax,rax / jne
            g_pfn_invalid_parameter_noinfo();
        cur = *out;                                            // the bytes reload before the deref
        uint64_t owner = *(uint64_t*)cur;                      // mov rax,[rax]
        if (out[1] >= *(uint64_t*)(owner + 0x20))              // cmp [rbx+8],rax / jb
            g_pfn_invalid_parameter_noinfo();

        uint64_t elem = *(uint64_t*)out[1];                    // mov rdi,[rax]
        if (elem != 0) {                                       // test rdi,rdi / je advance
            void** vt = *(void***)elem;
            void* pass1 = ((void* (*)(void*, uint32_t))vt[0x8 / 8])((void*)elem, 2);  // call [rax+8]
            void** vt2 = *(void***)pass1;
            uint32_t got_id = (uint32_t)((uint64_t (*)(void*))vt2[0x40 / 8])(pass1);  // [rdx+0x40]
            if (got_id == id) {                                // cmp eax,r12d / sete / je
                void** vt3 = *(void***)elem;
                void* pass2 = ((void* (*)(void*, uint32_t))vt3[0x8 / 8])((void*)elem, 3);
                void** vt4 = *(void***)pass2;
                uint32_t got_kind = (uint32_t)((uint64_t (*)(void*))vt4[0x48 / 8])(pass2);
                if (got_kind == kind)                          // cmp eax,ebp / sete / jne
                    break;
            }
        }

        uint64_t cur2 = *out;                                  // mov rax,[rbx]
        if (cur2 == 0)                                         // test rax,rax / jne
            g_pfn_invalid_parameter_noinfo();
        cur2 = *out;
        uint64_t owner2 = *(uint64_t*)cur2;                    // mov rax,[rax]
        if (out[1] >= *(uint64_t*)(owner2 + 0x20))             // cmp [rbx+8],rax / jb
            g_pfn_invalid_parameter_noinfo();
        out[1] += 8;                                           // add qword [rbx+8],8
    }
    return out;                                                // mov rax,rbx
}

// 0x141779400 — the tail call 0x14177f980 makes once a key was found.
uint64_t Slot_141779400(void* found, uint32_t id, uint32_t kind) {
    uint8_t* f = (uint8_t*)found;
    uint64_t it[2] = {0, 0};                                   // rsp+0x20 / rsp+0x28
    Slot_141779090_search(found, it, id, kind);                // call 0x141779090

    uint64_t endn = *(uint64_t*)(f + 0x28);                    // mov rsi,[rbx+0x28]
    if (*(uint64_t*)(f + 0x20) > endn)                         // cmp [rbx+0x20],rsi / jbe
        g_pfn_invalid_parameter_noinfo();
    uint64_t scary = *(uint64_t*)(f + 0x08);                   // mov rax,[rbx+8]
    if (scary == 0 || scary != it[0])                          // test / cmp rax,rdi / je
        g_pfn_invalid_parameter_noinfo();
    uint64_t cur = it[1];                                      // mov rbx,[rsp+0x28]
    if (endn == cur)                                           // cmp rsi,rbx / je zero
        return 0;

    uint64_t owner;
    if (it[0] == 0) {                                          // test rdi,rdi / jne
        g_pfn_invalid_parameter_noinfo();
        owner = 0;                                             // xor r11d,r11d
    } else {
        owner = *(uint64_t*)it[0];                             // mov r11,[rdi]
    }
    if (!(cur < *(uint64_t*)(owner + 0x20)))                   // cmp rbx,[r11+0x20] / jb
        g_pfn_invalid_parameter_noinfo();

    uint8_t* elem = *(uint8_t**)cur;                           // mov rcx,[rbx]
    if (elem == nullptr)                                       // test rcx,rcx / je zero
        return 0;
    void** vt = *(void***)elem;
    void* pass = ((void* (*)(void*, uint32_t))vt[0x10 / 8])(elem, 4);   // call [rax+0x10], edx=4
    void** vt2 = *(void***)pass;
    return ((uint64_t (*)(void*))vt2[0x48 / 8])(pass);         // jmp [rdx+0x48]
}

void Slot_14177c770_seed(void* value) { g_singleton_14177c770 = value; }
void Slot_1417b6210_seed(void* value) { g_singleton_1417b6210 = value; }

// The tail target is ported now, so the seam defaults to the real body instead of nothing. Nothing
// about 0x14177f980 changes: it still calls through this pointer, which is what makes the chain
// testable, but it no longer stops at a null.
uint64_t (*g_pfnLogic_141779400)(void* found, uint32_t id, uint32_t kind) = Slot_141779400;

// 0x14177f980 — kind-gated dispatch. The `lea eax,[r8-1] / cmp eax,2 / ja` is an unsigned range
// test, so kinds 1, 2 and 3 take the work path and everything else, including 0, is reported.
uint64_t Slot_14177f980(void* self, uint32_t id, uint32_t kind, uint64_t /*r9*/) {
    if ((uint32_t)(kind - 1) > 2u) {                         // lea eax,[r8-1] / cmp eax,2 / ja
        if (g_pfn_log_InlineLogERROR != nullptr)             // lea rcx,[rip+..] / mov edx,ebx
            g_pfn_log_InlineLogERROR((const void*)(uintptr_t)0x14182eec8ULL,
                                     (const void*)(uintptr_t)kind, nullptr, nullptr, 0);
        return 0;                                            // xor eax,eax
    }

    void* a = Slot_1417b6210_singleton();                     // call 0x1417b6210
    uint32_t hit = (uint32_t)Slot_1417ac810_vcall_1f8(a, id);  // call 0x1417ac810, edx = id
    if (hit == 0)                                            // mov esi,eax / test eax,eax / je
        return 0;

    void* b = Slot_14177c770_singleton();                     // call 0x14177c770
    uint64_t found = Slot_14177c0a0_find(b, hit);             // call 0x14177c0a0, edx = hit
    if (found == 0)                                          // test rax,rax / jne
        return 0;

    if (g_pfnLogic_141779400 == nullptr)                     // jmp 0x141779400, a tail call
        return 0;
    return g_pfnLogic_141779400((void*)(uintptr_t)found, id, kind);
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
