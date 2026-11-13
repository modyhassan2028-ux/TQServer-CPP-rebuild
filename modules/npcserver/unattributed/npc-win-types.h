// The handful of Windows SDK types this listing names. Everything here is the documented definition from the Windows
// headers; nothing is sized by judgement. Types that would need a layout (CRITICAL_SECTION and friends) are forward
// declared only, because a pointer to one is all the listing ever declares.
#ifndef TQ_NPCSERVER_WIN_TYPES_H
#define TQ_NPCSERVER_WIN_TYPES_H

typedef unsigned long DWORD;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef void* HANDLE;
typedef void* HWND;
typedef __builtin_va_list va_list;           // same typedef the compiler already made, re-stated so the listing can name it

struct CRITICAL_SECTION;
typedef CRITICAL_SECTION* LPCRITICAL_SECTION;

#endif  // TQ_NPCSERVER_WIN_TYPES_H
