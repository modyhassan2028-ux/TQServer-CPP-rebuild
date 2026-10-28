// 140052b30
#include "crosskernel.h"
namespace msg {
static void w32(uint8_t* h, int off, uint32_t v) {
    std::memcpy(h + off, &v, 4);
}
int CCrossKernel::ProcessNetMsg(int16_t type, uint32_t a, uint32_t b,
                                uint16_t c, uint16_t d, const void* data,
                                SCrossKernelSeams& s) {
    if (!data) { s.LogIllegal(0xffffffffu); return 0; }
    uint8_t h[kCrossPostLen];
    std::memset(h, 0, sizeof h);
    uint32_t count = a;
    switch (type) {
    case 0: case 3: {
        uint32_t id = s.ResolveId(this, a);
        if (id == 0xffffffffu) return 0;
        w32(h, 0x00, id);
        w32(h, 0x04, d);
        w32(h, 0x08, c);
        std::memcpy(h + 0x0c, data, d);
        s.Post(this, 1, 0x7533, kCrossPostLen, h);
        return 1; }
    case 1:
        w32(h, 0x00, a);
        w32(h, 0x08, c);
        w32(h, 0x10, d);
        std::memcpy(h + 0x14, data, d);
        s.Post(this, 0x0e, 0x2733, kCrossPostLen, h);
        return 1;
    case 2: {
        w32(h, 0x00, a);
        w32(h, 0x04, c);
        w32(h, 0x08, d);
        std::memcpy(h + 0x0c, data, d);
        for (uint32_t i = 0; i < count; ++i) {
            uint32_t at = d + (i - count) * 4;
            uint32_t old = 0;
            std::memcpy(&old, h + 0x0c + at, 4);
            uint32_t nid = s.ResolveId(this, old);
            if (nid != 0xffffffffu) std::memcpy(h + 0x0c + at, &nid, 4);
        }
        uint32_t len = d - count * 4;
        s.Post(this, 1, 0x753e, len, h);
        return 1; }
    case 4: case 10:
        w32(h, 0x00, a);
        w32(h, 0x08, kCrossMagic);
        w32(h, 0x0c, c);
        w32(h, 0x10, d);
        std::memcpy(h + 0x14, data, d);
        s.Post(this, 0x0e, 0x3fd, 0, h);
        return 1;
    case 5:
        if (a == 0xffffffffu) return 0;
        w32(h, 0x00, a);
        w32(h, 0x04, d);
        w32(h, 0x08, c);
        std::memcpy(h + 0x0c, data, d);
        s.Post(this, 1, 0x7533, kCrossPostLen, h);
        return 1;
    case 6: {
        w32(h, 0x00, a);
        w32(h, 0x04, c);
        w32(h, 0x08, d);
        std::memcpy(h + 0x0c, data, d);
        for (uint32_t i = 0; i < count; ++i) {
            uint32_t at = d + (i - count) * 4;
            uint32_t cur = 0xffffffffu;
            std::memcpy(&cur, h + 0x0c + at, 4);
            if (cur != 0xffffffffu)
                std::memcpy(h + 0x0c + at, &cur, 4);
        }
        uint32_t len = d - count * 4;
        s.Post(this, 1, 0x753e, len, h);
        return 1; }
    case 7: case 8:
        if (type == 7 && c == 0x3f1 && s.IsSpecial(data)) {
            w32(h, 0x00, a);
            w32(h, 0x08, 0x3f1);
            w32(h, 0x0c, 3);
            w32(h, 0x10, d);
            std::memcpy(h + 0x14, data, d);
            s.Post(this, 6, 0x3fc, kCrossPostLen, h);
        } else {
            w32(h, 0x00, a);
            w32(h, 0x08, kCrossMagic);
            w32(h, 0x0c, c);
            w32(h, 0x10, d);
            std::memcpy(h + 0x14, data, d);
            s.Post(this, 0x0e, 0x3fe, 0, h);
        }
        return 1;
    default:
        s.LogIllegal((uint32_t)type);
        return 0;
    }
}
} // namespace msg
