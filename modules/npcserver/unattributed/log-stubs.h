// The fixed-argument log stubs of NpcServer.exe.
//
// Arguments read from the machine code by tools/gen_npc_logstubs.py: the format in rcx, three more strings
// in rdx/r8/r9 and the source line as an immediate at [rsp+0x20].
#ifndef TQ_NPCSERVER_LOG_STUBS_H
#define TQ_NPCSERVER_LOG_STUBS_H

namespace tq {

extern void (*g_pfnNpcInlineLogError)(const void* pFormat, ...);

unsigned char  FUN_14001bf80(void);   // line 35
void           FUN_14001bfc0(void);   // line 36
long long      FUN_14001c000(void);   // line 37
void           FUN_14001c040(void);   // line 38
void           FUN_14001c080(void);   // line 39
void           FUN_14001c0c0(void);   // line 40
unsigned char  FUN_14001ddb0(void);   // line 23
long long      FUN_14001ddf0(void);   // line 24
long long      FUN_14001de30(void);   // line 27
unsigned char  FUN_14001de70(void);   // line 28
unsigned char  FUN_14001deb0(void);   // line 29
long long      FUN_14001def0(void);   // line 30
long long      FUN_140021110(void);   // line 240
long long      FUN_140021150(void);   // line 241
long long      FUN_140021190(void);   // line 242
void           FUN_1400211d0(void);   // line 245
unsigned char  FUN_140021210(void);   // line 246
unsigned char  FUN_140021250(void);   // line 247
unsigned char  FUN_140021290(void);   // line 248
unsigned char  FUN_1400212d0(void);   // line 249
unsigned char  FUN_140021310(void);   // line 250
long long      FUN_140021350(void);   // line 251
void           FUN_140021390(void);   // line 252
void           FUN_1400213d0(void);   // line 253
void           FUN_140021410(void);   // line 254
unsigned char  FUN_140021450(void);   // line 255
void           FUN_140025c90(void);   // line 24
long long      FUN_140025cd0(void);   // line 27
unsigned char  FUN_140025d10(void);   // line 28
unsigned char  FUN_140025d50(void);   // line 29
unsigned char  FUN_140025d90(void);   // line 30
long long      FUN_140025dd0(void);   // line 31
long long      FUN_140025e10(void);   // line 32
void           FUN_140025e60(void);   // line 14
long long      FUN_140025ea0(void);   // line 15
long long      FUN_140025ee0(void);   // line 16
unsigned char  FUN_140025f20(void);   // line 17
unsigned char  FUN_140025f60(void);   // line 18
long long      FUN_140025fa0(void);   // line 19
long long      FUN_140025fe0(void);   // line 20
void           FUN_140026030(void);   // line 14
long long      FUN_140026070(void);   // line 15
long long      FUN_1400260b0(void);   // line 16
unsigned char  FUN_1400260f0(void);   // line 17
unsigned char  FUN_140026130(void);   // line 18
long long      FUN_140026170(void);   // line 19
long long      FUN_1400261b0(void);   // line 20
void           FUN_140034ee0(void);   // line 24
long long      FUN_140034f20(void);   // line 27
unsigned char  FUN_140034f60(void);   // line 28
unsigned char  FUN_140034fa0(void);   // line 29
unsigned char  FUN_140034fe0(void);   // line 30
long long      FUN_140035020(void);   // line 31
long long      FUN_140035060(void);   // line 32
void           FUN_1400381a0(void);   // line 14
long long      FUN_1400381e0(void);   // line 15
long long      FUN_140038220(void);   // line 16
unsigned char  FUN_140038260(void);   // line 17
unsigned char  FUN_1400382a0(void);   // line 18
long long      FUN_1400382e0(void);   // line 19
long long      FUN_140038320(void);   // line 20
void           FUN_14003c5b0(void);   // line 14
long long      FUN_14003c5f0(void);   // line 15
long long      FUN_14003c630(void);   // line 16
unsigned char  FUN_14003c670(void);   // line 17
unsigned char  FUN_14003c6b0(void);   // line 18
long long      FUN_14003c6f0(void);   // line 19
long long      FUN_14003c730(void);   // line 20
void           FUN_140048ed0(void);   // line 58
long long      FUN_1400574a0(void);   // line 23
long long      FUN_1400574e0(void);   // line 24
long long      FUN_140057520(void);   // line 25
long long      FUN_140057560(void);   // line 27
long long      FUN_1400575a0(void);   // line 28
long long      FUN_1400575e0(void);   // line 29
long long      FUN_140057620(void);   // line 30
long long      FUN_140057660(void);   // line 31
unsigned char  FUN_1400576a0(void);   // line 32
unsigned char  FUN_1400576e0(void);   // line 33
unsigned char  FUN_140057720(void);   // line 34
unsigned char  FUN_140057760(void);   // line 35
unsigned char  FUN_1400577a0(void);   // line 36
unsigned char  FUN_1400577e0(void);   // line 37
long long      FUN_140057820(void);   // line 40
void           FUN_140057860(void);   // line 42
void           FUN_1400578a0(void);   // line 43
void           FUN_1400578e0(void);   // line 44
void           FUN_140057920(void);   // line 45
long long      FUN_140057960(void);   // line 56
unsigned char  FUN_1400592f0(void);   // line 66
void           FUN_140059330(void);   // line 69
void           FUN_140059370(void);   // line 70
void           FUN_1400593b0(void);   // line 71
unsigned char  FUN_1400593f0(void);   // line 72
void           FUN_140059430(void);   // line 73
long long      FUN_140059470(void);   // line 74
void           FUN_1400594b0(void);   // line 75
void           FUN_1400594f0(void);   // line 76
unsigned char  FUN_140059530(void);   // line 77
void           FUN_140059570(void);   // line 78
void           FUN_1400595b0(void);   // line 79
void           FUN_1400595f0(void);   // line 80
long long      FUN_140059630(void);   // line 91
void           FUN_1400678e0(void);   // line 14
long long      FUN_140067920(void);   // line 15
long long      FUN_140067960(void);   // line 16
unsigned char  FUN_1400679a0(void);   // line 17
unsigned char  FUN_1400679e0(void);   // line 18
long long      FUN_140067a20(void);   // line 19
long long      FUN_140067a60(void);   // line 20
long long      FUN_14006dac0(void);   // line 64
long long      FUN_14006db00(void);   // line 65
long long      FUN_14006db40(void);   // line 66
unsigned char  FUN_14006db80(void);   // line 67
void           FUN_14006dbc0(void);   // line 70
unsigned char  FUN_14006dc00(void);   // line 71
unsigned char  FUN_14006dc40(void);   // line 73
void           FUN_14006dc80(void);   // line 75
unsigned char  FUN_14006dcc0(void);   // line 80
unsigned char  FUN_14006dd00(void);   // line 82
unsigned char  FUN_14006dd40(void);   // line 85
long long      FUN_14007f6d0(void);   // line 22
long long      FUN_14007f710(void);   // line 23
long long      FUN_14007f750(void);   // line 24
long long      FUN_14007f790(void);   // line 25
long long      FUN_14007f7d0(void);   // line 26
long long      FUN_14007f810(void);   // line 27
long long      FUN_14007f850(void);   // line 28
unsigned char  FUN_14007f890(void);   // line 29
unsigned char  FUN_14007f8d0(void);   // line 32
unsigned char  FUN_14007f910(void);   // line 33
unsigned char  FUN_14007f950(void);   // line 38
void           FUN_14007f990(void);   // line 39
unsigned char  FUN_14007f9d0(void);   // line 40

struct NpcLogStubEntry {
    const char* pszAddress;
    void*       pfn;
    const char* pszFile;          // rcx
    const char* pszExpression;    // rdx
    const char* pszKind;          // r8
    const char* pszFormat;        // r9
    int         nLine;
    int         bReturns;   // 0 when the body is void
};

extern const NpcLogStubEntry g_aNpcLogStub[];
extern const int g_nNpcLogStub;

}  // namespace tq

#endif
