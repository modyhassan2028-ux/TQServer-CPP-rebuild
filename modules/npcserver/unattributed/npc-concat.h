// `CONCATxy` and the Ghidra slice types.
//
// The listing writes value assembly as CONCATxy(high, low) where x is the width of the high part and y the width of the
// low part, in bytes. The macros below are that definition and nothing else: shift the high part into place, mask the
// low part, or them together. Nothing here decides what the value means - that stays in the body, as written.
#ifndef TQ_NPCSERVER_CONCAT_H
#define TQ_NPCSERVER_CONCAT_H

typedef signed long long int7;
typedef unsigned long long uint7;
typedef signed long long int6;
typedef unsigned long long uint6;
typedef signed long long int5;
typedef unsigned long long uint5;
typedef signed int int4;
typedef unsigned int uint4;
typedef signed int int3;
typedef unsigned int uint3;
typedef signed short int2;
typedef unsigned short uint2;
typedef signed char int1;
typedef unsigned char uint1;

#define CONCAT11(h, l) ((unsigned)(unsigned char)(h) << 8 | (unsigned)(unsigned char)(l))
#define CONCAT12(h, l) ((unsigned)(unsigned char)(h) << 16 | ((unsigned)(l) & 0xFFFFu))
#define CONCAT13(h, l) ((unsigned)(unsigned char)(h) << 24 | ((unsigned)(l) & 0xFFFFFFu))
#define CONCAT21(h, l) ((unsigned)(unsigned short)(h) << 8 | (unsigned)(unsigned char)(l))
#define CONCAT22(h, l) ((unsigned)(unsigned short)(h) << 16 | (unsigned)(unsigned short)(l))
#define CONCAT31(h, l) ((unsigned)((unsigned)(h) & 0xFFFFFFu) << 8 | (unsigned)(unsigned char)(l))
#define CONCAT44(h, l) ((unsigned long long)(unsigned)(h) << 32 | (unsigned)(l))
#define CONCAT62(h, l) ((unsigned long long)(h) << 16 | (unsigned)(unsigned short)(l))
#define CONCAT71(h, l) ((unsigned long long)(h) << 8 | (unsigned)(unsigned char)(l))
#define CONCAT17(h, l) ((unsigned long long)(unsigned char)(h) << 56 | ((unsigned long long)(l) & 0x00FFFFFFFFFFFFFFULL))

#endif  // TQ_NPCSERVER_CONCAT_H
