#ifndef C_ANALYST_PROFILE_H
#define C_ANALYST_PROFILE_H
// 14001e720 — the whole tick-analyst registration table of MsgServer.
// Body, verbatim:
//   Analyst()->SetLogFile("syslog/analyst");
//   for every row: Analyst()->AddItem(id, 1, text)
// The rows below are GENERATED from the disassembly (no typing by
// hand, no invented ids): each (id, text) pair is exactly what the
// RAW passes to AddItem, in the RAW order.
namespace msg {
class CAnalystProfile {
public:
    struct SItem { int id; const char* text; };
    struct Seams {
        void* (*Analyst)();
        void (*SetLogFile)(void* a, const char* file);
        void (*AddItem)(void* a, int id, int flag, const char* text);
    };
    static void RegisterAll(Seams& s);
    static const SItem kItems[];
    static const int  kItemCount;
};
}
#endif
