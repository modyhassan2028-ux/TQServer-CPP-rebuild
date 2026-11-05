// ============================================================================
// synpboutstream.h — RAW Syndicate.dll v6159 · the two output-stream BackUp bodies.
//   0x1417e66f0  StringOutputStream::BackUp(count)
//       count < 0                     -> CHECK line 0xbc, "CHECK failed: (count) >= (0): "
//       (uint64)count > target_->size -> CHECK line 0xbd,
//                                        "CHECK failed: (count) <= (target_->size()): "
//       target_->resize(target_->size() - count)
//     The target is the std::string at self + 8 (MSVCP90 size/resize through IAT
//     0x1418231c0 / 0x1418231c8).
//   0x1417e74c0  CopyingOutputStreamAdaptor::BackUp(count)
//       count < 0                          -> CHECK line 0x165
//       buffer_used_ != buffer_size_ (+0x2c vs +0x28) -> CHECK line 0x166, two literals
//       count > buffer_used_               -> CHECK line 0x168, two literals
//       buffer_used_ -= count
//   Every CHECK reports through the protobuf log chain (0x1417e0d30 ctor / 0x1417e0990
//   append / 0x1417e0ee0 dtor / 0x1417e0da0 finish): one seam for the one-literal form and
//   one for the two-literal form, both named here so they cannot clash with the seams the
//   input-stream port already owns.
// ============================================================================
#ifndef SYNDICATE_SYNPBOUTSTREAM_H
#define SYNDICATE_SYNPBOUTSTREAM_H

#include <cstdint>

namespace tq {

// the one-literal CHECK report
extern void (*g_fnPbOutCheck1)(const char* pszFile, int32_t nLine, const char* pszText);
// the two-literal CHECK report
extern void (*g_fnPbOutCheck2)(const char* pszFile, int32_t nLine, const char* pszA,
                               const char* pszB);

void SynPbStringOutBackUp(void* pSelf, int32_t nCount);    // 0x1417e66f0
void SynPbCopyingAdaptorBackUp(void* pSelf, int32_t nCount);  // 0x1417e74c0

// the file literal both bodies hand to the log (0x141840330 / 0x141840740 / 0x1418407b0 /
// 0x141840870 are all the same string)
extern const char* const kSynPbOutFile;

}  // namespace tq

#endif  // SYNDICATE_SYNPBOUTSTREAM_H
