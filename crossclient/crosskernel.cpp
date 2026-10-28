// 140052b30
#include "crosskernel.h"
#include <cstdio>
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

// ---------------------------------------------------------------
// 140054380 CCrossKernel::ProcessLocalMsg
// ---------------------------------------------------------------
namespace msg {
int CCrossKernel::ProcessLocalMsg(uint32_t id, const uint32_t* buf,
                                  SeamsLocal& s) {
    if (buf == nullptr) { s.LogNull(); return 0; }
    uint8_t out[0x418];
    if (id < 0x11172u) {
        if (id == 0x11171u) {
            int a = -1; unsigned b = 0, c = 0xffffffffu;
            if (s.Sscanf3((const char*)buf, &a, &b, &c) == 3) {
                s.AddUserSocket(this, b, (unsigned)a, c);
                char tmp[0x80];
                std::memset(tmp, 0, 0x80);
                snprintf(tmp, 0x7f, "%u %u", (unsigned)a, c);
                tmp[0x7f] = 0;
                s.Post(this, 0x0e, 0x2738, 0x80, tmp);
            } else {
                s.LogBadAdd();
            }
        } else if (id == 0x3f0u) {
            int i = 0;
            if ((int)buf[0] > 0) {
                const uint32_t* p = buf + 2;
                do {
                    if (*p != 0) s.SetUserSocket(this, *p, buf[1]);
                    i++;
                    p++;
                } while (i < (int)buf[0]);
            }
        } else if (id == 0x3f1u) {
            s.DelUserSocketOne(this, buf[0]);
        } else if (id == 0x3fcu) {
            std::memset(out, 0, sizeof out);
            int len = (int)buf[4] + 0x10;
            if (len < 0x419) {
                uint16_t v0 = (uint16_t)buf[3];
                uint16_t v0e = (uint16_t)buf[2];
                std::memcpy(out + 0x00, &v0, 2);
                std::memcpy(out + 0x04, &buf[0], 4);
                std::memcpy(out + 0x08, &buf[1], 4);
                std::memcpy(out + 0x0c, &len, 2);
                std::memcpy(out + 0x0e, &v0e, 2);
                std::memcpy(out + 0x10, buf + 5, buf[4]);
                if (len != 0) s.Post(this, 0, 0, 0, out);   // client vt+0x28
            }
        } else if (id == 0x3ffu) {
            std::memset(out, 0, sizeof out);
            unsigned n = buf[0];
            int total = (int)buf[4] + 0x10 + (int)n * 4;
            int post_len = 0;
            if (total < 0x419) {
                uint16_t a0 = (uint16_t)buf[3], a2 = (uint16_t)buf[2];
                std::memcpy(out + 0x00, &a0, 2);
                std::memcpy(out + 0x04, &n, 4);
                std::memcpy(out + 0x08, &buf[1], 4);
                std::memcpy(out + 0x0c, &total, 2);
                std::memcpy(out + 0x0e, &a2, 2);
                std::memcpy(out + 0x10, buf + 5, buf[4] + n * 4);
                post_len = total;
            }
            if (post_len != 0) s.Post(this, 0, 0, (uint32_t)post_len, out);
        }
    } else if (id == 0x11172u) {
        unsigned u = 0;
        if (s.Sscanf1((const char*)buf, &u) == 1) s.DelUserSocket(this, u);
        else s.LogBadDel();
    } else if (id == 0x11173u) {
        if (buf[0] == 1) s.ClientOne(nullptr);
        else s.ClientZero(nullptr, 0);
    } else if (id == 0x11174u) {
        s.ClientBlock(nullptr, buf + 1, (int)buf[0]);
    }
    return 1;
}
} // namespace msg
