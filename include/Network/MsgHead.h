#pragma once
#include <cstdint>

#pragma pack(push, 1)
namespace tq {
    struct MsgHead {
        uint16_t length;
        uint16_t type;
    };
}
#pragma pack(pop)