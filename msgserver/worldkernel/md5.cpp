#include "md5.h"

namespace msg {

// 14050a570
CMD5Checksum* CMD5Checksum::Init(CMD5Checksum* self, void* vftable) {
    self->vft_ = vftable;
    self->zero1_ = 0;
    self->zero2_ = 0;
    self->zero3_ = 0;
    self->zero4_ = 0;
    self->zero5_ = 0;
    self->zero6_ = 0;
    self->zero7_ = 0;
    self->zero8_ = 0;
    self->at48_ = 0;
    self->at4c_ = 0;
    self->h0_ = 0x67452301;
    self->h1_ = 0xefcdab89;
    self->h2_ = 0x98badcfe;
    self->h3_ = 0x10325476;
    return self;
}

} // namespace msg
