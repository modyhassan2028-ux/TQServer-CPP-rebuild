// synrbinsert.cpp — the two seams used by the transcription of 0x141727e60.
#include "synrbinsert.h"

namespace tq {

void* (*g_fnRB_141726e10)(void*, void*, void*, void*, const uint32_t*, uint8_t) = nullptr;
void (*g_fnRB_1417f3154)() = nullptr;

}  // namespace tq
