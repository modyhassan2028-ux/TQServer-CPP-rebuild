// msgleagueberob.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgleagueberob.h"
namespace syndicate {

// 0x1417d5710 — class vftable, sub-object dtor at +0x408, base vftable, delete
void* CMsgLeagueBeRob::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    g_fn_1417e9440((unsigned char*)self + kOffSubObject);
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

}  // namespace syndicate
