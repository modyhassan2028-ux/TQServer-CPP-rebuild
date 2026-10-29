// 1400149a0 / 1400222e0
#include <cstdio>
#include <cstdint>
#include "timegate.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static uint32_t g_now=0,g_calls=0;
static uint32_t TG(int){ g_calls++; return g_now; }
static STimeGateSeams S{TG};
int main(){
    // not yet due: one clock read, nothing stored
    { SIntervalGate g{10, 100}; g_now=105000; g_calls=0;
      CK(IntervalElapsed(g,S)==false,"before the deadline it reports false");
      CK(g_calls==1,"the clock is read once while waiting");
      CK(g.last==100,"the stored second is untouched"); }
    // exactly due: the boundary is inclusive
    { SIntervalGate g{10, 100}; g_now=110000; g_calls=0;
      CK(IntervalElapsed(g,S)==true,"an exact boundary fires");
      CK(g.last==110 && g_calls==2,"the stored second comes from the second read"); }
    // the second read is the one stored
    { SIntervalGate g{5, 200}; g_calls=0;
      static int n=0; struct L { static uint32_t F(int){ n++; return n==1?300000u:301500u; } };
      STimeGateSeams s2{L::F};
      CK(IntervalElapsed(g,s2)==true,"firing reads the clock twice");
      CK(g.last==301,"the stored value is the SECOND read, not the first"); n=0; }
    // the interval passed as an argument
    { SIntervalGate g{0, 490}; g_now=510000; g_calls=0;
      CK(IntervalElapsedWith(g,20,S)==true,"the argument interval fires");
      CK(g.last==510,"the argument form stores the new second"); }
    { SIntervalGate g{0, 505}; g_now=510000;
      CK(IntervalElapsedWith(g,20,S)==false,"the argument interval still waits");
      CK(g.last==505,"nothing is stored while waiting"); }
    // the struct interval is ignored by the argument form
    { SIntervalGate g{9999, 600}; g_now=610000;
      CK(IntervalElapsedWith(g,5,S)==true,"the argument wins over the struct interval"); }
    // sub-second times never reach the comparison window
    { SIntervalGate g{0, 700}; g_now=700999;
      CK(IntervalElapsed(g,S)==true,"999 ms into the second still counts as that second");
      CK(g.last==700,"the second is truncated, not rounded"); }
    std::printf("TIMEGATE-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
