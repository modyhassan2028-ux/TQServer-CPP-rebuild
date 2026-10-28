// 14003a8e0
#include "CChatGameBlock.h"
namespace msg {
void* CChatGameBlock::QueryBlock(unsigned map, int x, int y, Seams& s) {
    int cx = x / 0x12;
    int cy = y / 0x12;
    if (cx > -1 && cx < m_nWidth && cy > -1 && cy < m_nHeight) {
        void* row = s.RowGet(&m_Rows, cx);
        return s.ColGet(row, cy);
    }
    s.LogInvalid(map, x, y);
    return nullptr;
}
}
