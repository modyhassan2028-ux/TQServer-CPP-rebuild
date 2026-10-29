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

// 140021f60 — walks ExtraProc.ini [Exe1..ExeCount].ExeName and terminates
// every listed process. RAW quirks kept: the basename it computes is thrown
// away (the log prints the full name), the PID source takes only the context,
// a failed OpenProcess abandons the remaining entries, and the opened handle
// is never closed.
class CExtraProc {
public:
    struct Seams {
        void*    (*IniOpen)(const char* file, const char* section);
        int      (*IniGetInt)(const char* key);
        void     (*IniSetSection)(const char* name);
        void     (*IniGetString)(char* buf, const char* key, int max);
        void     (*IniClose)();
        uint32_t (*NextPid)(uint64_t ctx);                       // 14001f4d0
        void*    (*OpenProcess)(uint32_t access, int inherit, uint32_t pid);
        int      (*TerminateProcess)(void* h, uint32_t code);
        uint32_t (*GetLastError)();
        void     (*SysLog)(const char* tag, const char* fmt,
                           const char* exe, int err);            // tq::SysLogSave
    };
    static void CloseAll(uint64_t ctx, Seams& s);
};
}
#endif
