#ifndef CROSS_KERNEL_H
#define CROSS_KERNEL_H
// Original unit: f:\version\cqserver-78.0.11-1204\crossclient\crosskernel.cpp
// 140052b30 CCrossKernel::ProcessNetMsg
//   0x418-byte header block; the offsets differ per case and are kept
//   exactly as the RAW writes them (12-byte header for cases 0/2/3/5/6,
//   20-byte header for cases 1/4/10/7/8).
#include <cstdint>
#include <cstring>
namespace msg {
static const int kCrossPostLen = 0x418;
static const uint32_t kCrossMagic = 4200000000u;   // 0xFA56EA00 RAW
struct SCrossKernelSeams {
    uint32_t (*ResolveId)(void* self, uint32_t id);      // 140052a20
    int      (*IsSpecial)(const void* data);             // 1400f87c0, case 7
    void     (*Post)(void* self, uint32_t ch, uint32_t msg,
                     uint32_t len, const void* hdr);     // kernel vt+0x50
    void     (*LogIllegal)(uint32_t type);               // literal line
};
class CCrossKernel {
public:
    // +0x08 = the msg-port object the post goes through
    void*   m_pPort = nullptr;
    uint8_t m_Pad[0x40] = {};
    int ProcessNetMsg(int16_t type, uint32_t a, uint32_t b,
                      uint16_t c, uint16_t d, const void* data,
                      SCrossKernelSeams& s);
    // 140054380
    struct SeamsLocal {
        int  (*Sscanf3)(const char* buf, int* p1, unsigned* p2, unsigned* p3);
        int  (*Sscanf1)(const char* buf, unsigned* p);
        void (*AddUserSocket)(void* self, unsigned a, unsigned b, unsigned c);
        void (*SetUserSocket)(void* self, unsigned id, unsigned b);
        void (*DelUserSocketOne)(void* self, unsigned id);
        void (*DelUserSocket)(void* self, unsigned id);
        void (*ClientOne)(void* client);
        void (*ClientZero)(void* client, int v);
        void (*ClientBlock)(void* client, const void* p, int n);
        void (*Post)(void* self, uint32_t ch, uint32_t msg,
                     uint32_t len, const void* hdr);
        void (*LogNull)(void);
        void (*LogBadAdd)(void);
        void (*LogBadDel)(void);
    };
    int ProcessLocalMsg(uint32_t id, const uint32_t* buf, SeamsLocal& s);
};
} // namespace msg
#endif
