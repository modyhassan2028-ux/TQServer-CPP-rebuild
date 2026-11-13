// CRT and lock helpers the listing calls by name, carried as seams: the bodies live in the MSVC runtime, which this
// port does not contain. Signatures are the ones the listings' call sites state (no argument, or the cookie value),
// matching the documented CRT entry points.
#ifndef TQ_NPCSERVER_CRT_SEAMS_H
#define TQ_NPCSERVER_CRT_SEAMS_H

inline void (*g_pfnNpcInvalidParameter)(void) = nullptr;
inline void (*g_pfnSecurityCheckCookie)(unsigned long long ullCookie) = nullptr;
inline void (*g_pfnNpcLock)(void) = nullptr;
inline void (*g_pfnNpcUnlock)(void) = nullptr;

inline void _invalid_parameter_noinfo(void) { if (g_pfnNpcInvalidParameter) g_pfnNpcInvalidParameter(); }
inline void __security_check_cookie(unsigned long long ullCookie) { if (g_pfnSecurityCheckCookie) g_pfnSecurityCheckCookie(ullCookie); }
inline void LOCK(void) { if (g_pfnNpcLock) g_pfnNpcLock(); }
inline void UNLOCK(void) { if (g_pfnNpcUnlock) g_pfnNpcUnlock(); }

#endif  // TQ_NPCSERVER_CRT_SEAMS_H
