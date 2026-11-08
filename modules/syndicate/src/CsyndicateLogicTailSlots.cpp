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
static uint64_t erase_all_bridge(uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t (*g_pfnLogic_1417caa00)(uint64_t, uint64_t, uint64_t, uint64_t) = erase_all_bridge;
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

// 0x141722c70 — the length error. The bytes build a std::length_error from the text at 0x141824f38
// (logic_error base at rsp+0x28, length_error at rsp+0x50 with its vtable, an exception copy at
// rsp+0x68) and hand it to _CxxThrowException at 0x1417f3154, then int3. Reproducing that object
// layout would be reproducing MSVC's ABI, so the throw is a seam that carries the text.
void (*g_pfn_throw_length_error)(const char* what) = nullptr;

void Slot_141722c70_throw_length_error(void) {
    if (g_pfn_throw_length_error != nullptr)                  // call 0x1417f3154 after the frame is built
        g_pfn_throw_length_error("vector<T> too long");        // lea rdx,[rip+0x1022b1] -> 0x141824f38
}

// 0x141724d10 — allocate count elements of 4 bytes.
void* Slot_141724d10_allocate(void* /*unused*/, uint64_t count) {
    if (count != 0) {                                         // test rdx,rdx / je alloc
        uint64_t q = 0xffffffffffffffffULL / count;            // or rax,-1 / div r8
        if (q < 4) {                                          // cmp rax,4 / jae alloc
            if (g_pfn_throw_length_error != nullptr)           // the same _CxxThrowException path
                g_pfn_throw_length_error("vector<T> too long");
            return nullptr;                                    // the bytes int3 here
        }
    }
    return ::operator new(count * 4);                          // lea rcx,[r8*4] / call 0x1417f3166
}

// 0x14172acb0 — move a block down to dst, answering dst + bytes.
uint64_t Slot_14172acb0_move_block(void* /*unused*/, void* src, void* src_end, void* dst) {
    uint64_t elems = ((uint64_t)src_end - (uint64_t)src) >> 2;  // sub r8,rdx / sar 2
    uint64_t bytes = elems * 4;                                // lea rdx,[r8*4]
    uint64_t ret = (uint64_t)dst + bytes;                       // lea rbx,[rdx+r9]
    if (elems != 0 && g_pfn_memmove_s != nullptr)               // test r8,r8 / je
        g_pfn_memmove_s(dst, bytes, src, bytes);                // dst size and count are the same word
    return ret;                                                // mov rax,rbx
}

// 0x141727380 — move src..mid so that it ends at dst_end.
uint64_t Slot_141727380_move_tail(void* src, void* mid, void* dst_end) {
    int64_t elems = (int64_t)((uint64_t)mid - (uint64_t)src) >> 2;   // sub rdx,rcx / sar 2
    uint64_t bytes = (uint64_t)elems * 4;                       // lea rax,[rdx*4]
    uint64_t dst = (uint64_t)dst_end - bytes;                    // sub rbx,rax
    if (elems > 0 && g_pfn_memmove_s != nullptr)                // test rdx,rdx / jle  (signed)
        g_pfn_memmove_s((void*)dst, bytes, src, bytes);
    return dst;                                                // mov rax,rbx
}

// 0x1417f2fdc — the six bytes here are a lone `jmp qword ptr [rip+0x3040e]`, landing on
// 0x1418233f0, which iat_slots.json resolves to MSVCR90!operator delete. It is not a .pdata row
// start because it is a thunk, not a function body.
void Slot_1417f2fdc_deallocate(void* p) {
    ::operator delete(p);                                      // jmp [MSVCR90!operator delete]
}

// 0x1417a8940 — lookup. Walks down from the root comparing the key unsigned (jae goes left), keeps
// the last node the walk turned left at, then decides whether that candidate really is >= the key.
// On a miss it answers 0. The container here is at +0x88 (end node) and +0x58 (word), which is not
// the 0x40-byte map ported earlier.
uint32_t Slot_1417a8940_lookup(void* self, uint32_t key) {
    uint8_t* s = (uint8_t*)self;
    uint64_t end_node = *(uint64_t*)(s + 0x88);                 // mov rbx,[rcx+0x88]
    uint64_t cand = end_node;                                   // mov rbx,rcx's end
    uint64_t n = *(uint64_t*)(end_node + 0x08);                 // mov rax,[rbx+8]
    while (*(uint8_t*)(n + 0x21) == 0) {                        // cmp byte [rax+0x21],0 / jne
        if (*(uint32_t*)(n + 0x18) >= key) {                    // cmp [rax+0x18],edx / jae
            cand = n;                                           // mov rbx,rax
            n = *(uint64_t*)(n + 0x00);                         // mov rax,[rax]
        } else {
            n = *(uint64_t*)(n + 0x10);                         // mov rax,[rax+0x10]
        }
    }
    uint64_t word = *(uint64_t*)(s + 0x58);                     // mov rax,[rcx+0x58]
    uint64_t end2 = *(uint64_t*)(s + 0x88);                     // mov rsi,[rcx+0x88]
    if (word == 0 && g_pfn_invalid_parameter_noinfo != nullptr)  // test rax,rax / je
        g_pfn_invalid_parameter_noinfo();
    // The bytes follow with `cmp rax,rax / je`, which always takes the jump, so only the zero case
    // can reach the failure path.
    uint64_t it_word, it_node;
    if (cand == end2 || key < *(uint32_t*)(cand + 0x18)) {      // cmp rbx,rsi / je, cmp edi,[rbx+0x18] / jb
        it_word = *(uint64_t*)(s + 0x58);                       // the fresh pair at rsp+0x30
        it_node = *(uint64_t*)(s + 0x88);
    } else {
        it_word = word;                                         // lea rcx,[rsp+0x20]
        it_node = cand;
    }
    if (it_word == 0 || it_word != *(uint64_t*)(s + 0x58)) {    // test rdi,rdi / cmp rdi,[rbp+0x58]
        if (g_pfn_invalid_parameter_noinfo != nullptr)
            g_pfn_invalid_parameter_noinfo();
    }
    if (it_node == *(uint64_t*)(s + 0x88)) return 0;            // cmp rbx,rsi / je, xor eax,eax
    uint64_t owner = (it_word != 0) ? *(uint64_t*)it_word : 0;  // mov r11,[rdi], else zero
    if (it_node != *(uint64_t*)(owner + 0x30)                   // cmp rbx,[r11+0x30] / jne
        && g_pfn_invalid_parameter_noinfo != nullptr)
        g_pfn_invalid_parameter_noinfo();
    return *(uint32_t*)(it_node + 0x1c);                        // mov eax,[rbx+0x1c]
}

// MSVCR90!memmove_s at 0x1418232a8. On the valid-argument path it is memmove, so the default keeps
// that behaviour without needing a header for the _s form.
static void memmove_s_default(void* dst, size_t /*dst_size*/, const void* src, size_t count) {
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* q = (const unsigned char*)src;
    if (d == q || count == 0) return;
    if (d < q) { for (size_t i = 0; i < count; ++i) d[i] = q[i]; }
    else { for (size_t i = count; i-- > 0;) d[i] = q[i]; }
}

void (*g_pfnLogic_141722c70)(void) = &Slot_141722c70_throw_length_error;
void* (*g_pfnLogic_141724d10)(void* alloc, uint64_t count) = &Slot_141724d10_allocate;
uint64_t (*g_pfnLogic_14172acb0)(void* unused, void* src, void* src_end, void* dst) = &Slot_14172acb0_move_block;
uint64_t (*g_pfnLogic_141727380)(void* src, void* mid, void* dst_end) = &Slot_141727380_move_tail;
void (*g_pfnLogic_1417f2fdc)(void* p) = &Slot_1417f2fdc_deallocate;
void (*g_pfn_memmove_s)(void* dst, size_t dst_size, const void* src, size_t count) = memmove_s_default;

// 0x14172d120 — _Insert_n. Path A reallocates, path B shifts the tail right, path C fills past the end
// and then closes the gap. The growth clamp and the order of the copies follow the bytes exactly.
void Slot_14172d120_insert_n(void* self, const uint64_t* it, uint64_t count, const void* value) {
    uint8_t* s = (uint8_t*)self;
    uint64_t begin = *(uint64_t*)(s + 0x18);                  // mov rax,[rcx+0x18]
    uint64_t cap = (begin == 0)                            // test rax,rax / jne
                       ? 0
                       : (*(uint64_t*)(s + 0x28) - begin) >> 2;
    if (count == 0) return;                                   // test r8,r8 / je done

    uint64_t finish = *(uint64_t*)(s + 0x20);                 // mov r13,[rcx+0x20]
    uint64_t size = (finish - begin) >> 2;                    // sub rcx,rax / sar 2
    const uint64_t max_size = 0x3fffffffffffffffULL;          // movabs rdx,0x3fff...
    if (max_size - size < count) {                            // sub rax,rcx / cmp rax,r8 / jae
        if (g_pfnLogic_141722c70 != nullptr) g_pfnLogic_141722c70();
        return;                                               // the bytes put an int3 after the call
    }
    uint64_t new_size = count + size;                         // add r8,rcx

    if (cap < new_size) {                                     // cmp rbx,r8 / jae no-realloc
        uint64_t half = cap >> 1;                             // mov rax,rbx / shr 1
        uint64_t grown = (max_size - half < cap) ? 0 : cap + half;
        if (grown < new_size) grown = new_size;               // cmp rbx,r8 / cmovb
        uint8_t* buf = (g_pfnLogic_141724d10 != nullptr)
                           ? (uint8_t*)g_pfnLogic_141724d10(s + 0x10, grown)   // lea rcx,[rsi+0x10]
                           : nullptr;
        uint64_t offset = (it[1] - *(uint64_t*)(s + 0x18)) >> 2;   // sub rax,[rsi+0x18] / sar 2
        uint8_t* dst = buf + offset * 4;                      // lea rdx,[r13+rax*4]
        uint32_t v = *(const uint32_t*)value;                 // mov eax,[r14]
        for (uint64_t n = count; n != 0; --n) {               // the fill loop at 0x14172d204
            *(uint32_t*)dst = v;
            dst += 4;
        }
        uint64_t head = (it[1] - *(uint64_t*)(s + 0x18)) >> 2;     // recomputed, as the bytes do
        if (head != 0 && g_pfn_memmove_s != nullptr)               // call [rip+0xf605b]
            g_pfn_memmove_s(buf, head * 4, (const void*)*(uint64_t*)(s + 0x18), head * 4);
        uint64_t old_finish = *(uint64_t*)(s + 0x20);              // mov rdx,[rsi+0x20]
        uint64_t tail = (old_finish - it[1]) >> 2;
        if (tail != 0 && g_pfn_memmove_s != nullptr)               // the second memmove_s
            g_pfn_memmove_s(buf + (offset + count) * 4, tail * 4, (const void*)it[1], tail * 4);
        if (*(uint64_t*)(s + 0x18) != 0 && g_pfnLogic_1417f2fdc != nullptr)   // test rcx,rcx
            g_pfnLogic_1417f2fdc((void*)*(uint64_t*)(s + 0x18));
        *(uint64_t*)(s + 0x28) = (uint64_t)(buf + grown * 4);      // lea rax,[r13+rbx*4]
        *(uint64_t*)(s + 0x20) = (uint64_t)(buf + new_size * 4);   // lea rax,[r13+rdi*4]
        *(uint64_t*)(s + 0x18) = (uint64_t)buf;                    // mov [rsi+0x18],r13
        return;
    }

    uint64_t after = (finish - it[1]) >> 2;                   // sub rax,[r15+8] / sar 2
    if (after >= count) {                                     // cmp rax,rdi / jae
        uint32_t v = *(const uint32_t*)value;                 // mov r12d,[r9]
        uint64_t tail_bytes = count * 4;                      // shl rdi,2
        uint64_t new_finish = finish - tail_bytes;            // mov rbx,r13 / sub rbx,rdi
        uint64_t stored = (g_pfnLogic_14172acb0 != nullptr)   // call 0x14172acb0
                              ? g_pfnLogic_14172acb0(self, (void*)new_finish, (void*)finish,
                                                     (void*)finish)
                              : new_finish;
        *(uint64_t*)(s + 0x20) = stored;                      // mov [rsi+0x20],rax
        if (g_pfnLogic_141727380 != nullptr)                  // call 0x141727380
            g_pfnLogic_141727380((void*)it[1], (void*)new_finish, (void*)finish);
        for (uint64_t p = it[1], end = it[1] + tail_bytes; p != end; p += 4)
            *(uint32_t*)p = v;                                // the fill loop at 0x14172d390
        return;
    }

    uint32_t v = *(const uint32_t*)value;                     // mov ebx,[r9]
    if (g_pfnLogic_14172acb0 != nullptr)                      // call with it[1] + count*4
        g_pfnLogic_14172acb0(self, (void*)it[1], (void*)finish, (void*)(it[1] + count * 4));
    uint64_t fin = *(uint64_t*)(s + 0x20);                    // mov rdx,[rsi+0x20]
    uint64_t moved = (fin - it[1]) >> 2;                      // sub rax,[r15+8] / sar 2
    uint64_t missing = count - moved;                         // mov rcx,rdi / sub rcx,rax
    uint64_t w = fin;
    for (uint64_t n = missing; n != 0; --n) { *(uint32_t*)w = v; w += 4; }   // past the old end
    *(uint64_t*)(s + 0x20) += count * 4;                      // add [rsi+0x20],rax
    uint64_t stop = *(uint64_t*)(s + 0x20) - count * 4;       // rcx = finish - count*4
    for (uint64_t p = it[1]; p != stop; p += 4) *(uint32_t*)p = v;           // close the gap
}

void (*g_pfnLogic_14172d120)(void* self, uint64_t* it, uint64_t count, const void* value) = nullptr;

// 0x141730cd0 — grow and insert one. The `test rax,-4` is not a size comparison: it asks whether the
// vector holds anything at all, since any whole number of 4-byte elements has those bits clear.
void* Slot_141730cd0_grow_insert(void* self, uint64_t* out, const uint64_t* pair,
                                 const void* value) {
    uint8_t* s = (uint8_t*)self;
    uint64_t finish = *(uint64_t*)(s + 0x20);                 // mov rcx,[rcx+0x20]
    uint64_t begin = *(uint64_t*)(s + 0x18);                  // mov r12,[rbx+0x18]
    int64_t byte_size = (int64_t)(finish - begin);            // sub rax,r12
    uint64_t offset = 0;
    if ((byte_size & ~(int64_t)3) != 0) {                      // test rax,-4 / jne
        if (begin > finish)                                   // cmp r12,rcx / jbe
            g_pfn_invalid_parameter_noinfo();
        uint64_t scary = pair[0];                             // mov rax,[r13]
        if (scary != 0 && scary != *(uint64_t*)(s + 0x00))    // test / cmp rax,[rbx] / je
            g_pfn_invalid_parameter_noinfo();
        offset = (pair[1] - begin) >> 2;                      // mov rdi,[r13+8] / sar 2
    }

    uint64_t it[2] = {pair[0], pair[1]};                      // the pair rebuilt on the frame
    if (g_pfnLogic_14172d120 != nullptr)                      // call 0x14172d120
        g_pfnLogic_14172d120(self, it, 1, value);

    uint64_t begin2 = *(uint64_t*)(s + 0x18);                 // re-read: the insert may have moved it
    if (begin2 > *(uint64_t*)(s + 0x20))                      // cmp r12,[rbx+0x20] / jbe
        g_pfn_invalid_parameter_noinfo();
    uint64_t scary2 = *(uint64_t*)(s + 0x00);                 // mov rbx,[rbx]
    uint64_t owner;
    if (scary2 == 0) {                                        // test rbx,rbx / jne
        g_pfn_invalid_parameter_noinfo();
        owner = 0;                                            // mov r11,rsi (rsi is zero)
    } else {
        owner = *(uint64_t*)scary2;                           // mov r11,[rbx]
    }
    uint64_t target = begin2 + offset * 4;                    // lea rdi,[r12+rdi*4]
    if (target > *(uint64_t*)(owner + 0x20))                  // cmp rdi,[r11+0x20] / ja
        g_pfn_invalid_parameter_noinfo();
    uint64_t owner2 = (scary2 != 0) ? *(uint64_t*)scary2 : 0; // test rbx / je / mov rsi,[rbx]
    if (target < *(uint64_t*)(owner2 + 0x18))                 // cmp rdi,[rsi+0x18] / jae
        g_pfn_invalid_parameter_noinfo();

    out[0] = scary2;                                          // mov [rbp],rax
    out[1] = target;                                          // mov [rbp+8],rax
    return out;                                               // mov rax,rbp
}

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

namespace tq {

// ============================================================================
// 0x1417caa00 — the manager's map clear. Instruction by instruction, the bytes are:
//   1417caa19  rax=[rcx+0x38]; 1417caa22 rdx=[rax]        the end node, then end->left
//   1417caa25  rax=[rcx+0x08]; stash {[this+8], the node}  the iterator
//   1417caa44  rdi=[r12+0x38]                             re-read every pass
//   1417caa49  iterator _DEBUG check: word null or != [this+8] -> invalid_parameter
//   1417caa5b  rbx==rdi -> the epilogue that answers 1
//   1417caa64  inc ebp / cmp 0xf4240 / ja -> the DEAD_LOOP_BREAK report
//   1417caa72  the word again, then [r11+0x30] against the node: the second _DEBUG check
//   1417caa91  rdi=[rbx+0x20] the value; the four destroys, each skipped when it is null
//   1417caaca  cmpb $0,[rbx+0x29] -> set means invalid_parameter and straight to the loop
//   1417caadb  the increment: right subtree's left spine, else climb while the node is a
//              right child (1417cab20), landing on 1417cab33 when the climb ends
// Every offset below is one of those.
// ============================================================================
uint64_t (*g_pfnLogic_14179db30)(void* p, uint32_t n) = nullptr;
uint64_t (*g_pfnLogic_1417a1180)(void* p) = nullptr;
uint64_t (*g_pfnLogic_14179a150)(void* p) = nullptr;
uint64_t (*g_pfnLogic_14179a020)(void* p) = nullptr;
void (*g_pfn_log_141823030)(const char* fmt, const char* expr, const char* which,
                            const char* file, int line) = nullptr;

// the four strings the image holds, byte for byte
static const char kDeadLoopFmt[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";   // 0x141824ca8
static const char kDeadLoopExpr[] = "DEAD_LOOP_BREAK";                   // 0x141832a18
static const char kDeadLoopVar[] = "uLoopCount";                         // 0x141832a28
static const char kDeadLoopFile[] =                                      // 0x141839fe0
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synmanager.cpp";
static const char kSyndicateFile[] =                                     // 0x1418319b0
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicate.cpp";

bool Slot_1417caa00_erase_all(void* self) {
    uint8_t* p = (uint8_t*)self;
    uint32_t uLoop = 0;                                   // xor ebp,ebp
    void* pEnd = *(void**)(p + 0x38);                     // mov rax,[rcx+0x38]
    void* pNode = *(void**)pEnd;                          // mov rdx,[rax]
    void* pWord = *(void**)(p + 0x08);                    // mov rax,[rcx+0x08]
    for (;;) {
        void* pEndNow = *(void**)(p + 0x38);               // 1417caa44 mov rdi,[r12+0x38]
        if (pWord == nullptr || pWord != *(void**)(p + 0x08)) {   // 1417caa49 + 1417caa4e
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();
        }
        if (pNode == pEndNow)                             // 1417caa5b cmp rdi,rbx / je
            return true;

        ++uLoop;                                          // 1417caa64 inc ebp
        if (uLoop > 0xf4240u) {                           // 1417caa66 cmp / ja 1417cab3b
            if (g_pfn_log_141823030 != nullptr)
                g_pfn_log_141823030(kDeadLoopFmt, kDeadLoopExpr, kDeadLoopVar, kDeadLoopFile,
                                    0x117);
            return true;                                  // falls into the 1417cab65 epilogue
        }

        if (pWord == nullptr) {                           // 1417caa72 test rsi,rsi / jne
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();         // 1417caa77
        }
        void* pOwner = (pWord != nullptr) ? *(void**)pWord : nullptr;   // 1417caa82 mov r11,[rsi]
        if (pNode == *(void**)((uint8_t*)pOwner + 0x30)) {            // 1417caa85 cmp [r11+0x30]
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();         // 1417caa8b
        }

        void* pValue = *(void**)((uint8_t*)pNode + 0x20);  // 1417caa91 mov rdi,[rbx+0x20]
        if (pValue != nullptr) {                           // 1417caa95 test rdi,rdi / je
            if (g_pfnLogic_14179db30 != nullptr)           // 1417caa9a edx=0x3ff
                g_pfnLogic_14179db30(pValue, 0x3ff);
            if (g_pfnLogic_1417a1180 != nullptr)           // 1417caaaa
                g_pfnLogic_1417a1180(pValue);
            if (g_pfnLogic_14179a150 != nullptr)           // 1417caab2
                g_pfnLogic_14179a150(pValue);
            if (g_pfnLogic_14179a020 != nullptr)           // 1417caaba
                g_pfnLogic_14179a020(pValue);
        }

        if (pWord == nullptr) {                            // 1417caabf test rsi,rsi / jne
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();          // 1417caac4
        }
        if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {    // 1417caaca cmpb $0,0x29(%rbx) / je
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();          // 1417caad0
            continue;                                      // 1417caad6 jmp 1417caa44
        }

        void* pRight = *(void**)((uint8_t*)pNode + 0x10);  // 1417caadb mov rax,[rbx+0x10]
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) != 0) {   // 1417caadf cmpb $0,0x29(%rax) / jne cab11
            void* pUp = *(void**)((uint8_t*)pNode + 0x08); // 1417cab11 mov rax,[rbx+0x08]
            if (*(uint8_t*)((uint8_t*)pUp + 0x29) != 0) {  // 1417cab15 / jne cab33
                pNode = pUp;                               // 1417cab33 mov rbx,rax
                continue;
            }
            while (pNode == *(void**)((uint8_t*)pUp + 0x10)) {   // 1417cab20 cmp [rax+0x10],rbx
                pNode = pUp;                                     // 1417cab26 mov rbx,rax
                pUp = *(void**)((uint8_t*)pUp + 0x08);           // 1417cab29 mov rax,[rax+0x08]
                if (*(uint8_t*)((uint8_t*)pUp + 0x29) != 0)      // 1417cab2d / je cab20
                    break;
            }
            pNode = pUp;                                   // 1417cab33
            continue;
        }
        pNode = pRight;                                    // 1417caae5 mov rbx,rax
        void* pLeft = *(void**)pRight;                     // 1417caae8 mov rax,[rax]
        while (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) { // 1417caaeb / je caa44 ; 1417cab0a
            pNode = pLeft;                                 // 1417cab00 mov rbx,rax
            pLeft = *(void**)pLeft;                        // 1417cab03 mov rax,[rax]
        }
    }
}

static uint64_t erase_all_bridge(uint64_t a, uint64_t, uint64_t, uint64_t) {
    return Slot_1417caa00_erase_all((void*)(uintptr_t)a) ? 1u : 0u;
}

}  // namespace tq

namespace tq {

// ============================================================================
// 0x14178f470 — "IF_OK(m_pRec)" from syndicate.cpp, line 0x8a8 (2216). Fourteen
// instructions; the decode is:
//   14178f474  cmpq $0,0x428(%rcx)        the guard
//   14178f47c  jne 0x14178f4b4            -> the hit
//   14178f47e  r9 = 0x1418319b0           the file string (syndicate.cpp)
//   14178f485  r8 = 0x141828944           "m_pRec"
//   14178f48c  rdx = 0x14182666c          "IF_OK"
//   14178f493  rcx = 0x141824ca8          "%s(%s) in %s, %d"  (0xa1ef either side)
//   14178f49a  [rsp+0x20] = 0x8a8         the line
//   14178f4a2  call *0x141823030          CQBase.dll!log_InlineLogERROR
//   14178f4a8  rax = 0x141827409          .rdata: a lone NUL, i.e. the empty string
//   14178f4b4  rcx = [rcx+0x428]          m_pRec
//   14178f4bb  edx = 1
//   14178f4c0  rax = [rcx]                its vtable
//   14178f4c3  call *0x10(%rax)           slot 2 with (m_pRec, 1)
//   14178f4c9  rdx = [rax]                the vtable of what came back
//   14178f4d0  jmp *0x78(%rdx)            slot 15, a tail jump: its answer is ours
// 0x141827409 is read out of .rdata and is one zero byte, so the miss answers "".

const char* Slot_14178f470(void* self) {
    uint8_t* p = (uint8_t*)self;
    if (*(void**)(p + 0x428) == nullptr) {                     // cmpq $0,0x428(%rcx)
        if (g_pfn_log_141823030 != nullptr)                    // call *0x141823030
            g_pfn_log_141823030(kDeadLoopFmt, "IF_OK", "m_pRec", kSyndicateFile, 0x8a8);
        static const char kEmpty141827409[] = "";               // lea rax,[0x141827409]
        return kEmpty141827409;
    }
    void* pRec = *(void**)(p + 0x428);                         // mov rcx,[rcx+0x428]
    void*** vt = *(void****)pRec;                              // mov rax,[rcx]
    void* rc = ((void* (*)(void*, uint32_t))vt[0x10 / 8])(pRec, 1);   // call *0x10(%rax)
    void*** vt2 = *(void****)rc;                               // mov rdx,[rax]
    return (const char*)((void* (*)(void*))vt2[0x78 / 8])(rc); // jmp *0x78(%rdx)
}

}  // namespace tq

namespace tq {

// ============================================================================
// 0x141797e00 — the id predicate on the map at this+0x290. Instruction by instruction:
//   141797e14  rbx = [rcx+0x290]        the end node
//   141797e1b  edi = edx                the id is kept for the two comparisons below
//   141797e1d  rbp = rcx                this
//   141797e20  rax = [rbx+0x08]         the end node's parent: the root
//   141797e24  cmpb $0,0x1d(%rax) / jne the nil byte of this layout is +0x1d
//   141797e30  cmp edx,[rax+0x18] / jae -> left, and the node becomes the candidate
//              (0x141797e3b: rbx = rax, rax = [rax]); below it, rax = [rax+0x10] (right)
//   141797e41  cmpb $0,0x1d(%rax) / je  back to 0x141797e30
//   141797e47  rax = [rcx+0x260]        the container word
//   141797e4e  rsi = [rcx+0x290]        the end node again
//   141797e55  the candidate and the word are stashed at [rsp+0x28] / [rsp+0x20]
//   141797e5f  test rax,rax / je 0x141797e69, then cmp rax,rax / je 0x141797e6f.
//              The second compare is rax against itself, so the only way into the error
//              path is a null word; that is stated plainly here rather than given a
//              meaning the bytes do not have.
//   141797e6f  candidate == the end node            -> the end-node pair
//   141797e74  cmp [rbx+0x18],edi / jb              -> the end-node pair (id below the key)
//   141797e79  otherwise the stashed {word, candidate} pair
//   141797e9d  the chosen pair is copied to [rsp+0x40]/[rsp+0x48]
//   141797eb7  the word is re-read: null, or not the pair's first word -> error path
//   141797ed0  cmp 0x48(%rsp),%rbx with rbx = [rbp+0x290]: setne al
// So the answer is "the chosen node is not the end node".

bool Slot_141797e00(void* self, uint32_t id) {
    uint8_t* p = (uint8_t*)self;
    const uint64_t uEnd = *(uint64_t*)(p + 0x290);          // mov rbx,[rcx+0x290]
    const uint32_t uId = id;                                // mov edi,edx
    uint64_t uCand = uEnd;                                  // rbx starts as the end node
    uint64_t uNode = *(uint64_t*)(uEnd + 0x08);             // mov rax,[rbx+0x08]
    while (*(uint8_t*)(uNode + 0x1d) == 0) {                // cmpb $0,0x1d(%rax) / jne
        if (uId >= *(uint32_t*)(uNode + 0x18)) {            // cmp edx,[rax+0x18] / jae
            uCand = uNode;                                  // mov rbx,rax
            uNode = *(uint64_t*)uNode;                      // mov rax,[rax]  (left)
        } else {
            uNode = *(uint64_t*)(uNode + 0x10);             // mov rax,[rax+0x10]  (right)
        }
    }

    const uint64_t uWord = *(uint64_t*)(p + 0x260);         // mov rax,[rcx+0x260]
    const uint64_t uEnd2 = *(uint64_t*)(p + 0x290);         // mov rsi,[rcx+0x290]
    if (uWord == 0) {                                      // test rax,rax / je
        if (g_pfn_invalid_parameter_noinfo != nullptr)
            g_pfn_invalid_parameter_noinfo();               // 141797e69
        // cmp rax,rax / je 0x141797e6f is always taken, so execution continues
    }
    (void)uEnd2;

    uint64_t uPair0, uPair1;
    if (uCand == uEnd2 || uId < *(uint32_t*)(uCand + 0x18)) {   // 141797e6f / 141797e74 jb
        uPair0 = *(uint64_t*)(p + 0x260);                  // [rsp+0x30] = [rbp+0x260]
        uPair1 = *(uint64_t*)(p + 0x290);                  // [rsp+0x38] = [rbp+0x290]
    } else {
        uPair0 = uWord;                                    // [rsp+0x20]
        uPair1 = uCand;                                    // [rsp+0x28]
    }

    const uint64_t uWord2 = *(uint64_t*)(p + 0x260);       // 141797eb7
    if (uWord2 == 0 || uWord2 != uPair0) {                 // test rax,rax / je, cmp 0x40(%rsp)
        if (g_pfn_invalid_parameter_noinfo != nullptr)
            g_pfn_invalid_parameter_noinfo();               // 141797eca
    }
    return *(uint64_t*)(p + 0x290) != uPair1;              // cmp 0x48(%rsp),%rbx / setne
}

}  // namespace tq

namespace tq {

// ============================================================================
// 0x14179a020 — the last destroy call. Every load, slot and jump the bytes perform:
//   14179a02f  rdi = this
//   14179a032  rcx = this+0x2a0 ; 14179a039 call 0x141727640
//   14179a03e  ebx = 0x19, then the loop 14179a050 .. 14179a12b (`inc ebx / cmp 0x28 / jl`)
//   14179a050  rcx = [rdi+0x428] (m_pRec), edx = ebx, rax = [rcx], call *0x10  -> p1
//   14179a062  rdx = [p1], call *0x40                                          -> eax
//   14179a068  the answer is spilled at [rsp+0x60]; zero means next id
//   14179a074  rcx = [rdi+0x438], edx = eax, call 0x1417cad00                  -> hit
//   14179a085  hit null -> 0x14179a0f9
//   14179a087  [hit+0x428] null -> the report at 0x14179a091 and then 0x14179a0e1
//   14179a0bd  otherwise rcx = [hit+0x428], edx = 9, call *0x10 -> p2, call *0x48 -> eax
//   14179a0d8  test eax,eax / setne al / test al,al / jne 0x14179a0f9
//   14179a0e1  rcx = this+0x2a0, rdx = &[rsp+0x30], r8 = &[rsp+0x60], call 0x14172ae00
//   14179a0f9  rcx = [rdi+0x428], edx = ebx, call *0x10 -> p3, then call *0xb0 with edx = 0
//   14179a117  rcx = [rdi+0x428], edx = 0, call *0x38
// 0x141727640 and 0x14172ae00 are not ported: two seams, null by default. 0x1417cad00 is
// ported, so it is called through its own injectable pointer.
static void map_clear_bridge(void* p);
void (*g_pfnLogic_141727640)(void* p) = map_clear_bridge;
void (*g_pfnLogic_14172ae00)(void* container, void* out, void* key) = nullptr;

static void EraseIdRange(void* self, size_t nContainerOff, uint32_t uFirst, uint32_t uLast) {
    uint8_t* p = (uint8_t*)self;                              // mov rdi,rcx
    if (g_pfnLogic_141727640 != nullptr)                      // 14179a039 call 0x141727640
        g_pfnLogic_141727640(p + nContainerOff);              // lea rcx,[rcx+0x2a0] (0x2e0 in a150)

    for (uint32_t i = uFirst; i < uLast; ++i) {               // mov ebx,0x19 / cmp 0x28 / jl
        void* pRec = *(void**)(p + 0x428);                    // 14179a050 mov rcx,[rdi+0x428]
        void*** vtRec = *(void****)pRec;                      // mov rax,[rcx]
        void* p1 = ((void* (*)(void*, uint32_t))vtRec[0x10 / 8])(pRec, i);   // call *0x10
        void*** vt1 = *(void****)p1;                          // mov rdx,[rax]
        uint32_t uId = ((uint32_t (*)(void*))vt1[0x40 / 8])(p1);             // call *0x40
        uint32_t uKey = uId;                                  // mov [rsp+0x60],eax
        if (uId == 0) continue;                               // test eax,eax / je 14179a126

        void* pHit = (void*)(uintptr_t)g_pfnLogic_1417cad00(
            (uint64_t)(uintptr_t)(p + 0x438), (uint64_t)uId, 0, 0);          // call 0x1417cad00
        if (pHit == nullptr) goto release;                    // test rax,rax / je 14179a0f9

        if (*(void**)((uint8_t*)pHit + 0x428) == nullptr) {   // cmpq $0,0x428(%rax) / jne
            if (g_pfn_log_141823030 != nullptr)               // 14179a0b5 call *0x141823030
                g_pfn_log_141823030(kDeadLoopFmt, "IF_OK", "m_pRec", kSyndicateFile, 0x956);
            goto erase;                                       // 14179a0bb jmp 14179a0e1
        }
        {
            void* pRec2 = *(void**)((uint8_t*)pHit + 0x428);  // 14179a0bd mov rcx,[rax+0x428]
            void*** vt2 = *(void****)pRec2;                   // mov rax,[rcx]
            void* p2 = ((void* (*)(void*, uint32_t))vt2[0x10 / 8])(pRec2, 9);  // edx = 9
            void*** vt3 = *(void****)p2;                      // mov rdx,[rax]
            uint32_t uRc = ((uint32_t (*)(void*))vt3[0x48 / 8])(p2);           // call *0x48
            if (uRc != 0) goto release;                       // setne al / test / jne 14179a0f9
        }
    erase:
        if (g_pfnLogic_14172ae00 != nullptr) {                // 14179a0f2 call 0x14172ae00
            uint8_t aOut[0x30] = {0};                         // [rsp+0x30]
            g_pfnLogic_14172ae00(p + nContainerOff, aOut, &uKey);   // lea r8,[rsp+0x60]
        }
        continue;                                             // jmp 14179a126

    release:
        {
            void* pRec3 = *(void**)(p + 0x428);                // 14179a0f9
            void*** vt4 = *(void****)pRec3;
            void* p3 = ((void* (*)(void*, uint32_t))vt4[0x10 / 8])(pRec3, i);  // edx = ebx
            void*** vt5 = *(void****)p3;
            ((uint32_t (*)(void*, uint32_t))vt5[0xb0 / 8])(p3, 0);             // call *0xb0
            void* pRec4 = *(void**)(p + 0x428);                // 14179a117
            void*** vt6 = *(void****)pRec4;
            ((uint32_t (*)(void*, uint32_t))vt6[0x38 / 8])(pRec4, 0);          // call *0x38
        }
    }
}

// The two entry points differ in exactly two immediates and one displacement, which is what
// the byte comparison of the two rows shows: 69 instructions each, 57 byte-identical, and the
// 12 that differ are `add $0x2a0` vs `$0x2e0`, `mov $0x19` vs `$0xa`, `cmp $0x28` vs `$0x19`,
// plus the rel32-encoded targets that must differ because the code sits elsewhere.
void Slot_14179a020(void* self) { EraseIdRange(self, 0x2a0, 0x19, 0x28); }
void Slot_14179a150(void* self) { EraseIdRange(self, 0x2e0, 0x0a, 0x19); }

}  // namespace tq

namespace tq {

// ============================================================================
// 0x14179db30 — the memberwise tidy. The body is nine copies of one block plus a masked
// one; the block is transcribed once and called with each member's constants (the table
// is in the header). One block, instruction by instruction:
//   14179db53  rbp = [this+cap]              the capacity end
//   14179db57  cmp [this+fin],rbp / jbe      fin above cap -> 0x1418233c0
//   14179db63  r13 = [this+fin]
//   14179db67  r12 = [this+begin]
//   14179db6b  cmp [this+cap],r13 / jbe      the same check through memory
//   14179db77  r14 = [this+begin]
//   14179db7b  rdx = the member's type row, rcx = &[rsp+0x60], call 0x141787c50
//   14179db8c  rbx = [rax]                   the allocator word
//   14179db8f  test r12,r12 / je, then cmp r14,r12 / je   the begin check
//   14179db9f  r8 = rbp - r13 (sar 3), r9 = rbx, rdx = rbp, rcx = r13, call 0x14179cde0
// The masked block at 14179dfa9 does the same with r9 = 0x14178efd0 and 0x14179cf10, and it
// reads the begin into rsi instead of r12 — that is the only structural difference.
static void* type_store_bridge(void* out, const void* type);
void* (*g_pfnLogic_141787c50)(void* out, const void* type) = type_store_bridge;
void (*g_pfnLogic_14179cde0)(void* first, void* last, uint64_t count, void* alloc) = nullptr;
void (*g_pfnLogic_14179cf10)(void* first, void* last, uint64_t count, void* fn) = nullptr;

static void TidyVectorMember(uint8_t* p, size_t nBegin, size_t nFinish, size_t nCap,
                             const void* pType) {
    void* uCap = *(void**)(p + nCap);                     // 14179db53 mov 0x70(%rcx),%rbp
    if (*(void**)(p + nFinish) > uCap) {                  // cmp %rbp,0x68(%rcx) / jbe
        if (g_pfn_invalid_parameter_noinfo != nullptr)
            g_pfn_invalid_parameter_noinfo();             // 14179db5d
    }
    void* uFin = *(void**)(p + nFinish);                  // 14179db63 mov 0x68(%rdi),%r13
    void* uBegin = *(void**)(p + nBegin);                 // 14179db67 mov 0x50(%rdi),%r12
    if (uFin > *(void**)(p + nCap)) {                     // cmp 0x70(%rdi),%r13 / jbe
        if (g_pfn_invalid_parameter_noinfo != nullptr)
            g_pfn_invalid_parameter_noinfo();             // 14179db71
    }
    void* uBegin2 = *(void**)(p + nBegin);                // 14179db77 mov 0x50(%rdi),%r14

    uint8_t aAlloc[0x20] = {0};                           // lea rcx,[rsp+0x60]
    void* pAlloc = nullptr;
    if (g_pfnLogic_141787c50 != nullptr) {                // 14179db87 call 0x141787c50
        void* pRet = g_pfnLogic_141787c50(aAlloc, pType);  // lea rdx,[the type row]
        pAlloc = *(void**)pRet;                           // 14179db8c mov (%rax),%rbx
    }
    if (uBegin == nullptr || uBegin != uBegin2) {          // 14179db8f / 14179db94
        if (g_pfn_invalid_parameter_noinfo != nullptr)
            g_pfn_invalid_parameter_noinfo();             // 14179db99
    }
    if (g_pfnLogic_14179cde0 != nullptr) {                // 14179dbb2 call 0x14179cde0
        const uint64_t uCount =
            (uint64_t)(((uintptr_t)uCap - (uintptr_t)uFin) >> 3);   // sub %r13,%r8 / sar 3
        g_pfnLogic_14179cde0(uFin, uCap, uCount, pAlloc); // rcx=fin, rdx=cap, r8, r9
    }
}

void Slot_14179db30(void* self, uint32_t uFlags) {
    uint8_t* p = (uint8_t*)self;
    const uint32_t u = (uint16_t)uFlags;                  // movzwl %dx,%esi

    if (u & 0x1)   TidyVectorMember(p, 0x50, 0x68, 0x70, (const void*)0x1417862c0);
    if (u & 0x2)   TidyVectorMember(p, 0x80, 0x98, 0xa0, (const void*)0x141786320);
    if (u & 0x4)   TidyVectorMember(p, 0xb0, 0xc8, 0xd0, (const void*)0x141786380);
    if (u & 0x8)   TidyVectorMember(p, 0xe0, 0xf8, 0x100, (const void*)0x1417863e0);
    if (u & 0x10)  TidyVectorMember(p, 0x110, 0x128, 0x130, (const void*)0x141786440);
    if (u & 0x20)  TidyVectorMember(p, 0x140, 0x158, 0x160, (const void*)0x1417864a0);
    if (u & 0x40)  TidyVectorMember(p, 0x170, 0x188, 0x190, (const void*)0x141786500);
    if (u & 0x80)  TidyVectorMember(p, 0x1a0, 0x1b8, 0x1c0, (const void*)0x141786560);
    if (u & 0x100) TidyVectorMember(p, 0x1d0, 0x1e8, 0x1f0, (const void*)0x1417865c0);

    if (u & 0x1f) {                                       // 14179dfa9 test $0x1f,%sil / je
        void* uCap = *(void**)(p + 0x220);                // 14179dfaf mov 0x220(%rdi),%rbx
        if (*(void**)(p + 0x218) > uCap) {                // cmp %rbx,0x218(%rdi) / jbe
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();         // 14179dfbf
        }
        void* uFin = *(void**)(p + 0x218);                // 14179dfc5 mov 0x218(%rdi),%rbp
        void* uBegin = *(void**)(p + 0x200);              // 14179dfcc mov 0x200(%rdi),%rsi
        if (uFin > *(void**)(p + 0x220)) {                // cmp 0x220(%rdi),%rbp / jbe
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();         // 14179dfdc
        }
        if (uBegin == nullptr || uBegin != *(void**)(p + 0x200)) {   // 14179dfe2 / 14179dfe7
            if (g_pfn_invalid_parameter_noinfo != nullptr)
                g_pfn_invalid_parameter_noinfo();         // 14179dff0
        }
        if (g_pfnLogic_14179cf10 != nullptr) {            // 14179e00d call 0x14179cf10
            const uint64_t uCount =
                (uint64_t)(((uintptr_t)uCap - (uintptr_t)uFin) >> 3);    // sub %rbp,%r8 / sar 3
            g_pfnLogic_14179cf10(uFin, uCap, uCount, (void*)0x14178efd0); // r9 = 0x14178efd0
        }
    }
}

}  // namespace tq

namespace tq {

// ============================================================================
// 0x141787c50 — three instructions, transcribed exactly:
//   141787c50  mov %rdx,(%rcx)     the type row goes into the caller's slot
//   141787c53  mov %rcx,%rax       the slot is the answer
//   141787c56  ret
void* Slot_141787c50(void* out, const void* type) {
    *(const void**)out = type;                            // mov %rdx,(%rcx)
    return out;                                          // mov %rcx,%rax
}

// 0x141726210 — free one subtree. The node layout here is the +0x1d one (nil byte at +0x1d,
// left +0x00, right +0x10). Instruction anchors:
//   14172621f  cmpb $0,0x1d(%rdx) / jne  the nil node ends the walk
//   141726223  rdi = rdx (the node), rsi = rcx (the container), rbx = rdx
//   141726230  rdx = [rbx+0x10] ; rcx = rsi ; call 0x141726210   the right subtree first
//   14172623c  rbx = [rbx]        the left child is taken before the free
//   14172623f  rcx = rdi ; call 0x1417f2fdc                      operator delete on the node
//   141726247  cmpb $0,0x1d(%rbx) ; 14172624b rdi = rbx ; je 0x141726230
void Slot_141726210(void* container, void* node) {
    uint8_t* c = (uint8_t*)container;
    void* uNode = node;                                   // mov %rdx,%rdi
    void* uSaved = node;                                  // mov %rdx,%rbx
    if (*(uint8_t*)((uint8_t*)uNode + 0x1d) != 0) return; // cmpb $0,0x1d(%rdx) / jne
    for (;;) {
        Slot_141726210(c, *(void**)((uint8_t*)uSaved + 0x10));   // 141726230 the right child
        uSaved = *(void**)uSaved;                         // 14172623c mov (%rbx),%rbx
        if (g_pfnLogic_1417f2fdc != nullptr)              // 141726242 call 0x1417f2fdc
            g_pfnLogic_1417f2fdc(uNode);                  // rcx = rdi
        uNode = uSaved;                                   // 14172624b mov %rbx,%rdi
        if (*(uint8_t*)((uint8_t*)uSaved + 0x1d) != 0) break;   // 141726247 / je 141726230
    }
}

// 0x141727640 — the whole tree, then the head is reset:
//   14172764f  rax = [rcx+0x30]                    the head
//   141727656  rsi = [rax+0x08]                    the root
//   14172765a  rdi = rsi
//   14172765d  cmpb $0,0x1d(%rsi) / jne 141727683
//   141727663  rdx = [rdi+0x10] ; rcx = rbx ; call 0x141726210    one subtree
//   14172766f  rdi = [rdi]                        the left child
//   141727672  rcx = rsi ; call 0x1417f2fdc       the node itself
//   14172767a  cmpb $0,0x1d(%rdi) ; 14172767e rsi = rdi ; je 141727663
//   141727683  [head+0x08] = head ; 141727694 [this+0x38] = 0 ; [head] = head ;
//              [head+0x10] = head
void Slot_141727640(void* container) {
    uint8_t* c = (uint8_t*)container;
    void* uHead = *(void**)(c + 0x30);                    // mov 0x30(%rcx),%rax
    void* uRoot = *(void**)((uint8_t*)uHead + 0x08);      // mov 0x8(%rax),%rsi
    void* uCur = uRoot;                                   // mov %rsi,%rdi
    void* uSaved = uRoot;                                 // rsi
    while (*(uint8_t*)((uint8_t*)uCur + 0x1d) == 0) {     // cmpb $0,0x1d(%rsi) / jne
        Slot_141726210(c, *(void**)((uint8_t*)uCur + 0x10));    // 14172766a call 0x141726210
        void* pLeft = *(void**)uCur;                      // 14172766f mov (%rdi),%rdi
        if (g_pfnLogic_1417f2fdc != nullptr)              // 141727675 call 0x1417f2fdc
            g_pfnLogic_1417f2fdc(uSaved);                 // rcx = rsi
        uSaved = pLeft;                                   // 14172767e mov %rdi,%rsi
        uCur = pLeft;                                     // rdi
    }
    void* uH1 = *(void**)(c + 0x30);                      // 141727683
    *(void**)((uint8_t*)uH1 + 0x08) = uH1;                // [head+0x08] = head
    *(uint64_t*)(c + 0x38) = 0;                           // 141727694 size = 0
    void* uH2 = *(void**)(c + 0x30);
    *(void**)uH2 = uH2;                                   // [head] = head
    void* uH3 = *(void**)(c + 0x30);
    *(void**)((uint8_t*)uH3 + 0x10) = uH3;                // [head+0x10] = head
}

static void map_clear_bridge(void* p) { Slot_141727640(p); }
static void* type_store_bridge(void* out, const void* type) { return Slot_141787c50(out, type); }

}  // namespace tq

namespace tq {

// ============================================================================
// 0x14179cde0 / 0x14179cf10 — the range routines. One transcription, four callees injected.
// The 0x14179cde0 anchors, in order (the twin's flow is the same, only the targets differ):
//   14179cdf9  rax = r9 (fn) ; 14179cdfc r9 = rdx ; 14179cdfc..ce0b (last-first)>>3
//   14179ce0f  cmp $0x20 / jle 14179ceb6          a small range skips straight to the tail
//   14179ce20  test %rsi,%rsi / jle 14179cee2     the count decides which exit is taken
//   14179ce37  call partition(&out, first, last, fn)   out = [rsp+0x20], [rsp+0x28]
//   14179ce46  rcx = (last - mid) & ~7             the byte width of the right part
//   14179ce4c  cqto; sub %rdx,%rax; sar 1          the count halved, sign-adjusted
//   14179ce5e  cqto; sub %rdx,%rax; sar 1; add     then a quarter of it is added
//   14179ce6e  rax = (split - first) & ~7          the byte width of the left part
//   14179ce7b  cmp %rcx,%rax / jge 14179ce8d       recurse into the smaller side only
//   14179ce8d  call 0x14179cde0(mid, last, count, fn) then last = split
//   14179ce83  call 0x14179cde0(first, split, count, fn) then first = mid
//   14179ceac  cmp (last-first)>>3,0x20 / jg       the loop keeps the larger side
//   14179ceb6  cmp $0x1 / jle                     nothing to do for one element
//   14179cec8  call tail(first, last, fn, 0)
//   14179cee2  cmp $0x20 / jle 14179ceb6          the exhausted exit re-checks the range
//   14179cef1  call exhaustedA(first, last, fn) ; 14179cf01 call exhaustedB(...) ; return
// The signed shifts are kept as the sequence, not as a division: (v - sign(v)) >> 1.

struct RangeRoutine {
    void (*pfnSelf)(void* first, void* last, int64_t count, void* fn);   // the row that recurses
    void (*pfnPartition)(void* out, void* first, void* last, void* fn);
    void (*pfnTail)(void* first, void* last, void* fn, void* zero);
    void (*pfnExhaustedA)(void* first, void* last, void* fn);
    void (*pfnExhaustedB)(void* first, void* last, void* fn);
};

static int64_t SignAdjustShift1(int64_t v) {                 // cqto ; sub %rdx,%rax ; sar 1
    const int64_t nSign = (v < 0) ? -1 : 0;
    return (v - nSign) >> 1;
}

static void RunRange(const RangeRoutine& r, void* pFirst, void* pLast, int64_t nCount,
                     void* pfn) {
    uint8_t* first = (uint8_t*)pFirst;                        // mov %rcx,%rdi
    uint8_t* last = (uint8_t*)pLast;                          // mov %rdx,%rbx
    int64_t nLeft = nCount;                                   // mov %r8,%rsi
    int64_t nElems = (int64_t)((last - first) >> 3);           // sub/sar $3
    uint8_t* aOut[2] = {nullptr, nullptr};                    // [rsp+0x20] / [rsp+0x28]

    if (nElems <= 0x20) goto tail;                            // cmp $0x20 / jle

    for (;;) {
        if (nLeft <= 0) {                                     // 14179ce20 test/jle
            if (nElems > 0x20) {                              // 14179cee2 cmp $0x20 / jle
                if (r.pfnExhaustedA != nullptr)
                    r.pfnExhaustedA(first, last, pfn);        // 14179cef1
                if (r.pfnExhaustedB != nullptr)
                    r.pfnExhaustedB(first, last, pfn);        // 14179cf01
            }
            return;                                           // jmp 14179cecd
        }

        if (r.pfnPartition != nullptr)                        // 14179ce37 call partition
            r.pfnPartition(aOut, first, last, pfn);
        uint8_t* pMid = aOut[1];                              // mov 0x28(%rsp),%rbp
        uint8_t* pSplit = aOut[0];                            // mov 0x20(%rsp)
        const int64_t nRightBytes = (int64_t)((last - pMid) & ~(int64_t)7);   // 14179ce4e/ce54
        nLeft = SignAdjustShift1(nLeft);                       // 14179ce5b mov %rax,%rsi
        nLeft = nLeft + SignAdjustShift1(nLeft);               // 14179ce6b add %rax,%rsi
        const int64_t nLeftBytes = (int64_t)((pSplit - first) & ~(int64_t)7); // 14179ce6e..ce77

        if (nLeftBytes >= nRightBytes) {                       // cmp %rcx,%rax / jge
            r.pfnSelf(pMid, last, nLeft, pfn);                 // 14179ce93 (calls itself)
            last = pSplit;                                     // 14179ce98
        } else {
            r.pfnSelf(first, pSplit, nLeft, pfn);              // 14179ce83 (calls itself)
            first = pMid;                                      // 14179ce88
        }
        nElems = (int64_t)((last - first) >> 3);               // 14179cea2..cea8
        if (nElems <= 0x20) break;                             // 14179ceb0 jg
    }

tail:
    if (nElems <= 1) return;                                   // 14179ceb6 cmp $0x1 / jle
    if (r.pfnTail != nullptr)                                  // 14179cec8
        r.pfnTail(first, last, pfn, nullptr);                   // r8 = fn, r9 = 0
}

void (*g_pfnLogic_141795a30)(void* out, void* first, void* last, void* fn) = nullptr;
void (*g_pfnLogic_141795d40)(void* out, void* first, void* last, void* fn) = nullptr;
void (*g_pfnLogic_141793d50)(void* first, void* last, void* fn, void* zero) = nullptr;
void (*g_pfnLogic_141793fd0)(void* first, void* last, void* fn, void* zero) = nullptr;
void (*g_pfnLogic_141795ca0)(void* first, void* last, void* fn) = nullptr;
void (*g_pfnLogic_141795f70)(void* first, void* last, void* fn) = nullptr;
void (*g_pfnLogic_141797670)(void* first, void* last, void* fn) = nullptr;
void (*g_pfnLogic_1417976e0)(void* first, void* last, void* fn) = nullptr;

void Slot_14179cde0(void* pFirst, void* pLast, int64_t nCount, void* pfn);

static RangeRoutine RangeOf_14179cde0() {
    RangeRoutine r;
    r.pfnSelf = Slot_14179cde0;
    r.pfnPartition = g_pfnLogic_141795a30;
    r.pfnTail = g_pfnLogic_141793d50;
    r.pfnExhaustedA = g_pfnLogic_141795ca0;
    r.pfnExhaustedB = g_pfnLogic_141797670;
    return r;
}

void Slot_14179cf10(void* pFirst, void* pLast, int64_t nCount, void* pfn);

static RangeRoutine RangeOf_14179cf10() {
    RangeRoutine r;
    r.pfnSelf = Slot_14179cf10;
    r.pfnPartition = g_pfnLogic_141795d40;
    r.pfnTail = g_pfnLogic_141793fd0;
    r.pfnExhaustedA = g_pfnLogic_141795f70;
    r.pfnExhaustedB = g_pfnLogic_1417976e0;
    return r;
}

void Slot_14179cde0(void* pFirst, void* pLast, int64_t nCount, void* pfn) {
    RunRange(RangeOf_14179cde0(), pFirst, pLast, nCount, pfn);
}

void Slot_14179cf10(void* pFirst, void* pLast, int64_t nCount, void* pfn) {
    RunRange(RangeOf_14179cf10(), pFirst, pLast, nCount, pfn);
}

}  // namespace tq

namespace tq {

// ============================================================================
// The four heap rows. Every offset and every comparison below is one instruction:
//   141795cb5  sub %rcx,%rsi / sar $0x3       the element count
//   141795cbc  cmp $0x1,%rsi / jle            nothing to heap below two elements
//   141795cca  cqto / sub %rdx,%rax / sar     count/2, sign-adjusted, as the bytes do it
//   141795ce0  mov -0x8(%rdi,%rbx,8),%r9      the parent's own element, loaded first
//   141795ce5  dec %rbx                       ... then the index is the decremented one
//   141795cf6  call 0x1417929f0               (0x141795fc6 call 0x141792b70 in the twin)
void (*g_pfnLogic_1417929f0)(void* first, uint64_t index, uint64_t count, void* elem) = nullptr;
void (*g_pfnLogic_141792b70)(void* first, uint64_t index, uint64_t count, void* elem) = nullptr;

static int64_t SignAdjustedHalf(int64_t v) {              // cqto / sub %rdx,%rax / sar 1
    return (v - (v < 0 ? -1 : 0)) >> 1;
}

// 0x141795ca0 (sift 0x1417929f0) and 0x141795f70 (sift 0x141792b70) — build the heap.
static void MakeHeapAt(void* pFirst, void* pLast, bool bSecond) {
    uint8_t* p = (uint8_t*)pFirst;
    int64_t nCount = ((int64_t)((uint8_t*)pLast - p)) >> 3;      // 141795cb5..cb8
    if (nCount <= 1) return;                                      // 141795cbc cmp/jle
    int64_t nParent = SignAdjustedHalf(nCount);                   // 141795cca..cd2
    if (nParent <= 0) return;                                     // 141795cd5 test/jle
    for (;;) {
        uint64_t uElem = *(uint64_t*)(p + nParent * 8 - 8);        // 141795ce0 mov -0x8(%rdi,%rbx,8)
        --nParent;                                                // 141795ce5 dec %rbx
        if (bSecond) {                                            // 141795fc6
            if (g_pfnLogic_141792b70 != nullptr)
                g_pfnLogic_141792b70(p, (uint64_t)nParent, (uint64_t)nCount, (void*)uElem);
        } else {                                                  // 141795cf6
            if (g_pfnLogic_1417929f0 != nullptr)
                g_pfnLogic_1417929f0(p, (uint64_t)nParent, (uint64_t)nCount, (void*)uElem);
        }
        if (nParent <= 0) break;                                  // 141795cfb test/jle
    }
}

// 0x141797670 (sift 0x1417929f0) and 0x1417976e0 (sift 0x141792b70) — drain the heap.
static void SortHeapAt(void* pFirst, void* pLast, bool bSecond) {
    uint8_t* p = (uint8_t*)pFirst;
    int64_t nBytes = (int64_t)((uint8_t*)pLast - p);              // 141797685 sub %rcx,%rbx
    if ((nBytes >> 3) <= 1) return;                               // 14179768f cmp/jle
    for (;;) {
        uint64_t uHead = *(uint64_t*)p;                           // 141797695 mov (%rdi),%rax
        uint64_t uTail = *(uint64_t*)(p + nBytes - 8);             // 141797698 mov -0x8(%rdi,%rbx,1),%r9
        *(uint64_t*)(p + nBytes - 8) = uHead;                     // 1417976a2 the head lands on the tail
        int64_t nCount = (nBytes - 8) >> 3;                        // 1417976a7..6ad
        if (bSecond) {                                            // 141797727
            if (g_pfnLogic_141792b70 != nullptr)
                g_pfnLogic_141792b70(p, 0, (uint64_t)nCount, (void*)uTail);
        } else {                                                  // 1417976b7
            if (g_pfnLogic_1417929f0 != nullptr)
                g_pfnLogic_1417929f0(p, 0, (uint64_t)nCount, (void*)uTail);
        }
        nBytes -= 8;                                              // 1417976c1 sub $0x8,%rbx
        if ((nBytes >> 3) <= 1) break;                            // 1417976cc cmp/jg
    }
}

void Slot_141795ca0(void* pFirst, void* pLast, void* /*pfn*/) { MakeHeapAt(pFirst, pLast, false); }
void Slot_141795f70(void* pFirst, void* pLast, void* /*pfn*/) { MakeHeapAt(pFirst, pLast, true); }
void Slot_141797670(void* pFirst, void* pLast, void* /*pfn*/) { SortHeapAt(pFirst, pLast, false); }
void Slot_1417976e0(void* pFirst, void* pLast, void* /*pfn*/) { SortHeapAt(pFirst, pLast, true); }

}  // namespace tq

namespace tq {

// ============================================================================
// 0x141792b70 — the sift behind 0x141795f70 / 0x1417976e0. Unlike its twin below, it is
// handed the comparator as a fifth argument (`mov 0x60(%rsp),%r13`, then `call *%r13`), so
// it needs no out-slot and no tail call. Every step is one instruction:
//   141792b93  lea 0x2(%rdx,%rdx,1),%rbx        child = 2*index + 2
//   141792bb0  mov -0x8(%rdi,%rbx,8),%rdx       the child pair, larger index first in rcx
//   141792bb9  call *%r13                       the comparator: (child, child-1)
//   141792bc0  dec %rbx                         a true answer prefers the left child
//   141792bc7  mov %rax,(%rdi,%rsi,8)           the child moves into the hole
//   141792bd8  cmp %rbp,%rbx / jne               one lone child is still promoted
//   141792bf0  cqto / sub %rdx,%rax / sar        (hole-1)/2, the sign adjusted halving
//   141792c07  call *%r13                       the up pass: (parent, elem)
//   141792c37  mov %r12,(%rdi,%rsi,8)           the saved element lands in the hole
void Slot_141792b70(void* pFirst, int64_t nIndex, int64_t nCount, void* pElem,
                    bool (*pfnLess)(void* a, void* b)) {
    uint64_t* p = (uint64_t*)pFirst;                              // mov %rcx,%rdi
    const int64_t nStart = nIndex;                                // mov %rdx,%r14
    int64_t nHole = nIndex;                                       // mov %rdx,%rsi
    int64_t nChild = 2 * nIndex + 2;                              // 141792b93
    if (nChild < nCount) {                                        // 141792b9b cmp/jge
        for (;;) {
            uint64_t uRight = p[nChild];                          // 141792bb5 mov (%rdi,%rbx,8),%rcx
            uint64_t uLeft = p[nChild - 1];                       // 141792bb0 mov -0x8(...),%rdx
            if (pfnLess != nullptr && pfnLess((void*)uRight, (void*)uLeft))
                --nChild;                                         // 141792bc0 dec %rbx
            p[nHole] = p[nChild];                                 // 141792bc7
            nHole = nChild;                                       // 141792bcb mov %rbx,%rsi
            nChild = 2 * nChild + 2;                              // 141792bce
            if (nChild >= nCount) break;                          // 141792bd6 jl
        }
    }
    if (nChild == nCount) {                                       // 141792bd8 cmp/jne
        p[nHole] = p[nCount - 1];                                 // 141792be2
        nHole = nCount - 1;                                       // 141792be6 lea -0x1(%rbp),%rsi
    }
    int64_t nParent = SignAdjustedHalf(nHole - 1);                // 141792bea..bf3
    if (nStart < nHole) {                                         // 141792bf6 cmp/jge
        for (;;) {
            uint64_t uParent = p[nParent];                        // 141792c00 mov (%rdi,%rbx,8),%rcx
            if (pfnLess == nullptr || !pfnLess((void*)uParent, pElem))
                break;                                            // 141792c0c je
            p[nHole] = uParent;                                   // 141792c18
            nHole = nParent;                                      // 141792c1c mov %rbx,%rsi
            nParent = SignAdjustedHalf(nParent - 1);              // 141792c12..c25
            if (nStart >= nHole) break;                           // 141792c28 jl
        }
    }
    p[nHole] = (uint64_t)(uintptr_t)pElem;                         // 141792c37 mov %r12,(%rdi,%rsi,8)
}

}  // namespace tq
