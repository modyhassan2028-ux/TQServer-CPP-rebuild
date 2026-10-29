#include "MsgServerDlgBoot.h"

namespace msg {
namespace {
inline int32_t&  F32(void* p, size_t o) { return *(int32_t*)((char*)p + o); }
inline uint64_t& F64(void* p, size_t o) { return *(uint64_t*)((char*)p + o); }
inline uint8_t&  F8 (void* p, size_t o) { return *(uint8_t*)((char*)p + o); }
}

void OnTimerBootTimer1(void* pDlg, SBootSeams& s) {
    if (*s.reentrancy > 0) return;                    // line 111
    *s.reentrancy = *s.reentrancy + 1;
    {
        void* mgr = s.GetGlobalMgr();                 // 113
        s.MgrBootStep(mgr);                           // 114
        if (F64(pDlg, 0x1f0) != 0) s.ProcessOnce(pDlg);   // 115-117
        int st = F32(pDlg, 0x1fc);                    // 118
        if (st == 0) { F32(pDlg, 0x1fc) = 4; goto dec; }  // 119-121
        if (st != 1) goto dec;                        // the other states live elsewhere
        F32(pDlg, 0x1fc) = 3;                         // 123
        s.AddThreadHandle(pDlg, s.GetCurrentThread()); // 124-125
        s.InitStep1(pDlg);                             // 126
        {
            // 127-137: the log thread, size 0xd0, port 7
            void* mem = s.New(0xd0);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(7); thr = s.MakeLogThread(mem); }
            F64(pDlg, 0x178) = (uint64_t)thr;
            if (thr == nullptr || !s.StartLogThread()) goto dec;    // 134
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.SetLogThreadStatus(1);
            if (!s.DatabaseInit()) goto dec;                        // 138-139
        }
        {
            // 140-153: the async DB thread, inline, 0x40
            void* mem = s.New(0x40);
            void* thr = nullptr;
            if (mem != nullptr) { s.CtorAsyncDB(mem); s.SetAsyncDBVtable(mem); thr = mem; }
            F64(pDlg, 0x180) = (uint64_t)thr;
            if (thr == nullptr || !s.CreateThread(thr, "AsyncDBThread", true)) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, nullptr);                                   // 154
        }
        {
            // 155-165: port 2, 0x50
            void* mem = s.New(0x50);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(2); thr = s.MakePort2(mem); }
            F64(pDlg, 0x1c0) = (uint64_t)thr;
            if (thr == nullptr || !s.StartPort2()) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, nullptr);
        }
        {
            // 166-179: port 10, 0x50
            void* mem = s.New(0x50);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(10); thr = s.MakePort10(mem); }
            F64(pDlg, 0x1e0) = (uint64_t)thr;
            if (thr == nullptr || !s.StartVtable20(thr)) goto dec;   // 174-175
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, "Init OK.");                               // 178
            s.Log(pDlg, nullptr);                                  // 179
        }
        {
            // 181-204: the worker loop, 0x58 each, port i+0xe
            for (int i = 0; i < s.workerCount; ++i) {
                void* mem = s.New(0x58);
                void* thr = nullptr;
                if (mem != nullptr) { s.RegisterPort(i + 0xe); thr = s.MakeWorker(mem); }
                if (thr == nullptr) goto dec;                      // 191-194
                s.PushWorker((char*)pDlg + 0x188);                 // 196
                if (!s.StartVtable20(thr)) goto dec;               // 197-198
                s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            }
        }
        s.Log(pDlg, nullptr);                                      // 205
        {
            // 206-216: port 4, 0x50
            void* mem = s.New(0x50);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(4); thr = s.MakePort4(mem); }
            F64(pDlg, 0x1c8) = (uint64_t)thr;
            if (thr == nullptr || !s.StartPort4()) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, nullptr);
        }
        {
            // 217-231: ports 0xe and 1, 0x58
            void* mem = s.New(0x58);
            void* thr = nullptr;
            if (mem != nullptr) {
                s.RegisterPort(0xe);
                s.RegisterPort(1);
                thr = s.MakeCross(mem);
            }
            F64(pDlg, 0x1b8) = (uint64_t)thr;
            if (thr == nullptr || !s.StartVtable20(thr)) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, s.str3248);                                   // &DAT_1406e3248
        }
        if (F8(pDlg, 0x1d0) != 0) {                                // 232
            s.Log(pDlg, nullptr);
            void* mem = s.New(0x68);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(6); thr = s.MakePort6(mem); }
            F64(pDlg, 0x1d8) = (uint64_t)thr;
            if (thr == nullptr || !s.StartVtable20(thr)) goto dec;   // 242-244
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, s.str3248);
        }
        {
            // 250-263: port 8, 0x50
            s.Log(pDlg, nullptr);
            void* mem = s.New(0x50);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(8); thr = s.MakePort8(mem); }
            F64(pDlg, 0x1e8) = (uint64_t)thr;
            if (thr == nullptr || !s.StartPort8()) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, "Init OK.");
        }
        if (F8(pDlg, 0x220) != 0) {                                // 264
            s.Log(pDlg, nullptr);
            void* mem = s.New(0x50);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(9); thr = s.MakePort9(mem); }
            F64(pDlg, 0x228) = (uint64_t)thr;
            if (thr == nullptr || !s.StartVtable20(thr)) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, s.str3248);
        }
        if (F8(pDlg, 0x221) != 0) {                                // 282
            s.Log(pDlg, nullptr);
            void* mem = s.New(0xb0);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(0xb); thr = s.MakePort11(mem); }
            F64(pDlg, 0x238) = (uint64_t)thr;
            if (thr == nullptr || !s.StartVtable20(thr)) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, s.str31a8);
        }
        if (F8(pDlg, 0x222) != 0) {                                // 300
            s.Log(pDlg, nullptr);
            void* mem = s.New(0x8d8);
            void* thr = nullptr;
            if (mem != nullptr) { s.RegisterPort(0xd); thr = s.MakePort13(mem); }
            F64(pDlg, 0x230) = (uint64_t)thr;
            if (thr == nullptr || !s.StartVtable20(thr)) goto dec;
            s.AddThreadHandle(pDlg, s.GetThreadHandle(thr));
            s.Log(pDlg, s.str3248);
        }
        // 318-343: the resume sweep
        s.ResumeThread((void*)F64(pDlg, 0x1c0));
        s.ResumeThread((void*)F64(pDlg, 0x1e0));
        for (int i = 0; i < s.workerCount; ++i) {
            void* slot = s.WorkerAt((char*)pDlg + 0x188, i);
            s.ResumeThread(slot ? *(void**)slot : nullptr);
        }
        s.ResumeThread((void*)F64(pDlg, 0x1b8));
        s.ResumeThread((void*)F64(pDlg, 0x1c8));
        s.ResumeThread((void*)F64(pDlg, 0x1e8));
        if (F64(pDlg, 0x1d8) != 0) s.ResumeThread((void*)F64(pDlg, 0x1d8));
        if (F64(pDlg, 0x228) != 0) s.ResumeThread((void*)F64(pDlg, 0x228));
        if (F64(pDlg, 0x238) != 0) s.ResumeThread((void*)F64(pDlg, 0x238));
        if (F64(pDlg, 0x230) != 0) s.ResumeThread((void*)F64(pDlg, 0x230));
        s.Log(pDlg, s.str3160);                                        // &DAT_1406e3160
        F32(pDlg, 0x1fc) = 2;                                       // 345
        {
            void* h = s.MgrAuxHandle(s.GetGlobalMgr());              // 346-351
            if (h != nullptr) s.AddThreadHandle(pDlg, h);
        }
        {
            void* h = s.DBAuxHandle();                               // 352-357
            if (h != nullptr) s.AddThreadHandle(pDlg, h);
        }
        s.PerfInit(pDlg, "syslog/process");                          // 358
        s.ThreadTimesInit(pDlg);                                     // 360
        F32(pDlg, 0x144) = 600;                                      // 361
        F64(pDlg, 0x148) = (uint32_t)(s.TimeGet(0) / 1000);           // 362-363
        F32(pDlg, 0x14c) = 300;                                      // 364
        F64(pDlg, 0x150) = (uint32_t)(s.TimeGet(0) / 1000);           // 365-366
    }
dec:
    *s.reentrancy = *s.reentrancy - 1;                               // 878
}

} // namespace msg
