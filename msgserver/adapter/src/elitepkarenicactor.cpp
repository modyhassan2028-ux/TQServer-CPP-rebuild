#include "elitepkarenicactor.h"
namespace msg {
void CElitePKArenicActor::OnUserArenicHornorChange(uint32_t rank,
                                                   SElitePKArenicSeams& s) {
    void* inst = s.CurrentInstanceGet();
    if (inst == nullptr) { s.LogNullInstance(); return; }
    void* mod = s.GetModule(inst, 4);
    if (mod == nullptr) { s.LogNoInterface(); return; }
    s.OnHornorChange(mod, rank);
}
} // namespace msg
