#ifndef C_CHAT_GAME_BLOCK_H
#define C_CHAT_GAME_BLOCK_H
// 14003a8e0 CChatGameBlock::QueryBlock(map, x, y)
//   x /= 0x12; y /= 0x12;
//   if 0<=x<*(int*)(this+0xc) && 0<=y<*(int*)(this+0x10)
//       -> ColGet(RowGet(this+0x18, x), y)
//   else "CChatGameBlock::QueryBlock: map = %u, x=%d, y =%d is invalid"
//        and 0
#include <cstdint>
#include <cstddef>
namespace msg {
class CChatGameBlock {
public:
    struct Seams {
        void* (*RowGet)(void* rows, int x);       // 140039da0
        void* (*ColGet)(void* row, int y);        // 140039e30
        void (*LogInvalid)(unsigned map, int x, int y);
    };
    void* QueryBlock(unsigned map, int x, int y, Seams& s);
    uint8_t  m_Pad0[0x0c] = {};
    int32_t  m_nWidth  = 0;                       // +0x0c
    int32_t  m_nHeight = 0;                       // +0x10
    uint8_t  m_Pad1[4] = {};
    void*    m_Rows    = nullptr;                 // +0x18
};
}
#endif
