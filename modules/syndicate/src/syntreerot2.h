// ============================================================================
// syntreerot2.h — RAW Syndicate.dll v6159 · the rotations of the third map kind (nil byte at
//   +0x21) and of the second id-kind copy (nil at +0x29). The two bodies differ from the
//   first pair only in that byte, and that byte decides whether a child's parent is written
//   at all, so each kind keeps its own entry point.
// ============================================================================
#ifndef SYNDICATE_SYNTREEROT2_H
#define SYNDICATE_SYNTREEROT2_H

namespace tq {

void SynTreeRotateLeft28(void* pMap, void* pNode);    // 0x1417c71f0, nil +0x21
void SynTreeRotateRight28(void* pMap, void* pNode);   // 0x1417c7250, nil +0x21
void SynTreeRotateLeftIdB(void* pMap, void* pNode);   // 0x1417c6100, nil +0x29
void SynTreeRotateRightIdB(void* pMap, void* pNode);  // 0x1417c6170, nil +0x29

}  // namespace tq

#endif  // SYNDICATE_SYNTREEROT2_H
