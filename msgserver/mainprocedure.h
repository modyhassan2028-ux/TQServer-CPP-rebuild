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
        // 14001f070 additions
        bool (*Query)(void* a, int id, uint64_t* v1, uint64_t* v2, int* vi);
        void (*Flush)(void* a);
    };

    // the counters 14001f070 fills (0x140975968..0x1409759a8)
    struct SStats {
        uint32_t f968, f96c;      // the low/high pair written by ids 0x45 / 0x43
        uint32_t f970, f974;      // ids 0x40 / 0x41
        uint64_t f978, f980;      // id 0x45 / 0x43 second and third out
        uint64_t f988, f990;
        int32_t  f998, f99c;      // id 0x46 accumulates into the low dword
        uint64_t f9a0;            // tick counter, incremented once per call
        uint64_t f9a8;            // sum of the 8 id queries
    };
    // 14001f070 — registers the log file, refills every counter and bumps the
    // tick counter. The accumulator is not cleared between the eight queries,
    // exactly like the RAW.
    static void LoadStats(SStats& st, Seams& s);
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
