// ===== Path-A wave 8a: monitor cmd
// layer VERBATIM (raw-verified) =====
#include "MsgStatusMonitorCmd.h"
#include <cstring>
#include <cstdlib>

namespace msg {

SMSCmdSeams g_MSCmdSeams = {};
uint8_t* g_pStatusMonitor = nullptr;
uint32_t g_ResetDbState = 0;

static void InvalidParam_() {
    if (g_MSCmdSeams.InvalidParam)
        g_MSCmdSeams.InvalidParam();
    else std::abort();
}

// ===== M: ORIGINAL ctor (140029ff0)
uint8_t* MonitorCtor(uint8_t* p,
                     void* mainTh) {
    SMSCmdSeams& s = g_MSCmdSeams;
    MQ(p, 0x00) = (uint64_t)mainTh;
    MD(p, 0x08) = 0;
    MD(p, 0x0c) = 0;
    void* proxy = s.New(8);
    if (proxy) *(uint64_t*)proxy =
        (uint64_t)(p + 0x10);
    MQ(p, 0x10) = (uint64_t)proxy;
    MON_FIRST(p) = 0;
    MON_LAST(p) = 0;
    MON_CAP(p) = 0;
    s.InitCS(p + 0x40);
    MQ(p, 0x68) = 0;
    return p;
}

// ===== M: ORIGINAL create (14002a480)
int MonitorCreate(void* mainTh) {
    SMSCmdSeams& s = g_MSCmdSeams;
    if (g_pStatusMonitor != nullptr)
        return 1;
    void* pv = s.New(0x70);
    if (pv == nullptr) {
        g_pStatusMonitor = nullptr;
    }
    else {
        g_pStatusMonitor =
            MonitorCtor((uint8_t*)pv, mainTh);
    }
    if (g_pStatusMonitor == nullptr) {
        s.LogErrorFmt("\xa1\xef%s(%s)\xa1\xef"
                      " in %s, %d");
        return 0;
    }
    return 1;
}

// ===== M: ORIGINAL dtor (14002a510)
void MonitorDtor(uint8_t* m, uint32_t f) {
    SMSCmdSeams& s = g_MSCmdSeams;
    s.DelCS(m + 0x40);
    if (MQ(m, 0x68) != 0)
        s.CloseHandle(MQ(m, 0x68));
    if (MON_FIRST(m) != 0)
        s.Del((void*)MON_FIRST(m));
    MON_FIRST(m) = 0;
    MON_LAST(m) = 0;
    MON_CAP(m) = 0;
    s.Del((void*)MON_PROXY(m));
    if (f & 1) s.Del(m);
}

// ===== M: ORIGINAL shutdown
// (14002ad90)
void MonitorShutdown() {
    if (g_pStatusMonitor != 0) {
        MonitorDtor(g_pStatusMonitor, 1);
        g_pStatusMonitor = nullptr;
    }
}

// ===== M: ORIGINAL vec-alloc
// (140029150): overflow check +
// new(count*8)
static void* VecAlloc(uint8_t* cont,
                      uint64_t count) {
    SMSCmdSeams& s = g_MSCmdSeams;
    // raw: (UINT64_MAX / count) < 8
    if (count != 0 &&
        (0xffffffffffffffffULL / count)
            < 8) {
        if (s.ThrowBadAlloc)
            s.ThrowBadAlloc();
        InvalidParam_();
    }
    return s.New((size_t)(count * 8));
}

// ===== M: ORIGINAL insert_n
// (14002a1d0) VERBATIM — the three
// raw branches: grow / close-to-end /
// shift-tail-out =====
static void VecInsertN(uint8_t* cont,
        uint64_t iter, uint64_t count,
        uint64_t val) {
    SMSCmdSeams& s = g_MSCmdSeams;
    uint64_t first = MQ(cont, 0x18);
    uint64_t capSize =
        first ? (MQ(cont, 0x28) - first) / 8
              : 0;
    uint64_t last = MQ(cont, 0x20);
    if (count == 0) return;
    uint64_t oldSize = (last - first) / 8;
    if (0x1fffffffffffffffULL - oldSize
            < count) {
        // raw: FUN_140028ab0
        // (length_error -> terminate)
        InvalidParam_();
    }
    uint64_t newSize = count + oldSize;
    if (capSize < newSize) {
        // ---- branch 1: grow (1.5x)
        uint64_t newCap =
            capSize + (capSize >> 1);
        if (capSize >
            0x1fffffffffffffffULL -
                (capSize >> 1)) {
            newCap = 0;
        }
        if (newCap < newSize)
            newCap = newSize;
        uint8_t* dst = (uint8_t*)VecAlloc(
            cont + 0x10, newCap);
        uint64_t before =
            (iter - first) / 8;
        uint64_t* w = (uint64_t*)dst +
            before;
        for (uint64_t i = 0; i < count;
             i++) { *w = val; w++; }
        uint64_t lead = (iter - first)/8;
        if (lead != 0)
            std::memmove(dst, (void*)first,
                (size_t)(lead << 3));
        uint64_t tail = (last - iter) / 8;
        if (tail != 0)
            std::memmove(dst + (before +
                count) * 8, (void*)iter,
                (size_t)(tail << 3));
        uint64_t oldFirst = first;
        uint64_t oldLast = last;
        if (oldFirst != 0)
            s.Del((void*)oldFirst);
        MQ(cont, 0x28) = (uint64_t)dst +
            newCap * 8;
        MQ(cont, 0x20) = (uint64_t)dst +
            (count + (oldLast -
             oldFirst) / 8) * 8;
        MQ(cont, 0x18) = (uint64_t)dst;
        return;
    }
    if (count < (last - iter) / 8) {
        // ---- branch 3 (raw 3rd):
        // shift tail out. raw: fb0
        // (cont, last-count*8, last,
        // last) copies the tail
        // `count` elems to oldLast;
        // then 140029780(iter, last-
        // count*8, last) moves the
        // middle to end at oldLast;
        // then fill [iter, iter+count)
        uint64_t oldLast = last;
        uint64_t tailBytes = count * 8;
        std::memmove((void*)oldLast,
            (void*)(oldLast - tailBytes),
            (size_t)tailBytes);
        MQ(cont, 0x20) = oldLast +
            tailBytes;
        uint64_t midN = (oldLast -
            tailBytes - iter) / 8;
        std::memmove(
            (void*)(oldLast - midN * 8),
            (void*)iter,
            (size_t)(midN * 8));
        for (uint64_t i = 0; i < count;
             i++) {
            *(uint64_t*)(iter + i * 8) =
                val;
        }
        return;
    }
    // ---- branch 2 (raw 2nd): close
    // to end — shift [iter, last) up
    // by count, fill below
    uint64_t oldLast = last;
    std::memmove(
        (void*)(iter + count * 8),
        (void*)iter,
        (size_t)(oldLast - iter));
    uint64_t tailN = (oldLast - iter)/8;
    uint64_t* w2 = (uint64_t*)oldLast;
    for (uint64_t i = count - tailN;
         i != 0; i--) { *w2 = val; w2++; }
    MQ(cont, 0x20) = oldLast + count*8;
    for (uint64_t* p = (uint64_t*)iter;
         p != (uint64_t*)oldLast; p++) {
        *p = val;
    }
}

// ===== M: ORIGINAL insert_n
// (14002a1d0) VERBATIM =====
// cont = monitor+0x10; iterpair
// param_2 = {iter, end}; count;
// val = *param_4
static void VecInsertN(uint8_t* cont,
        uint64_t iter, uint64_t end,
        uint64_t count, uint64_t val) {
    SMSCmdSeams& s = g_MSCmdSeams;
    uint64_t first = MQ(cont, 0x18);
    uint64_t capSize =
        first ? (MQ(cont, 0x28) - first) / 8
              : 0;
    uint64_t oldSize = 0;
    if (count != 0) {
        oldSize =
            (MQ(cont, 0x20) - first) / 8;
        if (0x1fffffffffffffffULL -
                oldSize < count) {
            // raw: FUN_140028ab0 (throw
            // length_error -> terminate)
            InvalidParam_();
        }
        uint64_t newSize = count + oldSize;
        if (capSize < newSize) {
            uint64_t newCap =
                capSize + (capSize >> 1);
            if (capSize >
                0x1fffffffffffffffULL -
                    (capSize >> 1)) {
                newCap = 0;   // raw: skip
            }
            if (newCap < newSize)
                newCap = newSize;
            uint8_t* dst =
                (uint8_t*)VecAlloc(
                    cont + 0x10, newCap);
            uint64_t before =
                (iter - first) / 8;
            uint64_t* w =
                (uint64_t*)(dst +
                    before * 8);
            for (uint64_t i = 0;
                 i < count; i++) {
                *w = val; w++;
            }
            uint64_t lead =
                (iter - first) / 8;
            if (lead != 0) {
                std::memmove(dst,
                    (void*)first,
                    (size_t)(lead << 3));
            }
            uint64_t tail =
                (MQ(cont, 0x20) - iter) / 8;
            if (tail != 0) {
                std::memmove(
                    dst + (before + count)*8,
                    (void*)iter,
                    (size_t)(tail << 3));
            }
            uint64_t oldFirst = first;
            uint64_t oldLast =
                MQ(cont, 0x20);
            if (oldFirst != 0)
                s.Del((void*)oldFirst);
            MQ(cont, 0x28) =
                (uint64_t)dst + newCap*8;
            MQ(cont, 0x20) =
                (uint64_t)dst +
                (count + (oldLast - oldFirst)/8)*8;
            MQ(cont, 0x18) = (uint64_t)dst;
            return;
        }
        if ((MQ(cont, 0x20) - iter)/8 <
                count) {
            // back-insert with move
            uint64_t tail =
                (MQ(cont, 0x20) - iter)/8;
            // raw: FUN_140029fb0 move
            // tail down by count
            std::memmove(
                (void*)(iter + count*8),
                (void*)iter,
                (size_t)(tail * 8));
            uint64_t* w =
                (uint64_t*)MQ(cont, 0x20);
            // raw: fill the appended
            // count slots then fill
            // [iter, iter+count)
            uint64_t i2 =
                count - ((MQ(cont, 0x20) - iter)/8);
            for (; i2 != 0; i2--) {
                *w = val; w++;
            }
            MQ(cont, 0x20) +=
                count * 8;
            uint64_t upto = MQ(cont, 0x20) -
                count * 8;
            for (uint64_t* p2 =
                     (uint64_t*)iter;
                 p2 != (uint64_t*)upto;
                 p2++) {
                *p2 = val;
            }
            return;
        }
        // front-fit: move [iter, end)
        // back, write val at iter
        uint64_t lead =
            (iter - first) / 8;
        uint64_t moveCnt =
            (MQ(cont, 0x20) - iter)/8 - 0;
        // raw: FUN_140029fb0(lead-...)
        // then move [iter..) forward
        uint64_t src = iter;
        std::memmove((void*)(iter + count*8),
                     (void*)src,
                     (size_t)(moveCnt * 8));
        // hmm: raw moves (last - iter)
        // elements starting at iter
        for (uint64_t i = 0; i < count;
             i++) {
            *(uint64_t*)(iter + i*8) = val;
        }
        MQ(cont, 0x20) = MQ(cont, 0x20) +
            count * 8;
        return;
    }
}

// ===== M: ORIGINAL insert
// (14002ac60): append at end
static void VecInsertAtEnd(
        uint8_t* cont, uint64_t val) {
    uint64_t first = MQ(cont, 0x18);
    if ((MQ(cont, 0x20) - first) & ~7ULL) {
        if (MQ(cont, 0x20) < first)
            InvalidParam_();
    }
    // raw debug pair check: proxy
    if (MON_PROXY(cont - 0x10) == 0)
        InvalidParam_();
    VecInsertN(cont, MQ(cont, 0x20), 1,
               val);
}

// ===== M: ORIGINAL push (14002ae40)
void VecPush(uint8_t* cont, uint8_t* c) {
    uint64_t first = MQ(cont, 0x18);
    uint64_t capSize =
        first ? (MQ(cont, 0x28) - first)/8
              : 0;
    uint64_t last = MQ(cont, 0x20);
    if ((last - first)/8 < capSize) {
        *(uint64_t*)last = *(uint64_t*)c;
        MQ(cont, 0x20) = last + 8;
        return;
    }
    VecInsertAtEnd(cont,
                   *(uint64_t*)c);
}

// ===== M: ORIGINAL clear
// (14002a0e0)
void VecClear(uint8_t* cont) {
    uint64_t first = MQ(cont, 0x18);
    uint64_t last = MQ(cont, 0x20);
    if (last < first) InvalidParam_();
    // proxy self-check (always true)
    if (MON_PROXY(cont - 0x10) == 0)
        InvalidParam_();
    // raw: _Src IS param_1[4] so the
    // memmove size computes to ZERO
    // -> only last is recomputed
    if (first != last) {
        MQ(cont, 0x20) = first;
    }
}

// ===== M: ORIGINAL handler
// (14002aef0) VERBATIM =====
static int StrIcmpEq(const char* a,
                     const char* b) {
    // _stricmp
    while (*a && *b) {
        char ca = *a, cb = *b;
        if (ca >= 'A' && ca <= 'Z')
            ca += 32;
        if (cb >= 'A' && cb <= 'Z')
            cb += 32;
        if (ca != cb) return 0;
        a++; b++;
    }
    // raw compares full match
    return (*a | *b) == 0;
}

void MonitorHandleCmd(uint8_t* m,
                      uint8_t* c) {
    SMSCmdSeams& s = g_MSCmdSeams;
    if (m == nullptr) {
        s.LogErrorFmt("\xa1\xef%s(%s)\xa1\xef"
                      " in %s, %d");
        return;
    }
    int len = (int)*(int32_t*)(c + 8);
    if (len < 3) return;
    char* buf = (char*)(c + 0xc);
    if (buf[len - 2] != '\r' ||
        buf[len - 1] != '\n') {
        if (len < 0x1f) return;
        *(int32_t*)(c + 8) = 0;
        return;
    }
    bool bReply = false;   // [rsp+0x40]
    uint64_t sock =
        *(uint64_t*)(c + 0x00);
    if (StrIcmpEq(buf,
                  "get_run_info\r\n")) {
        int64_t crash0 =
            *s.CrashTimeGet();
        bool bWasEmpty = false;
        s.EnterCS(m + 0x40);
        if (((MON_LAST(m) -
              MON_FIRST(m)) &
             ~7ULL) == 0) {
            bWasEmpty = true;
            VecPush(m + 0x10, c);
        }
        else {
            // debug checks raw:
            uint64_t first =
                MON_FIRST(m);
            uint64_t last =
                MON_LAST(m);
            if (last < first)
                InvalidParam_();
            uint64_t it = first;
            while (it != last &&
                   *(uint64_t*)it !=
                       sock) {
                it += 8;
            }
            if (it == last) {
                VecPush(m + 0x10, c);
            }
        }
        s.LeaveCS(m + 0x40);
        if (crash0 == 0) {
            if (bWasEmpty) {
                if (MD(m, 0x0c) != 0) {
                    MD(m, 0x0c) = 0;
                    MD(m, 0x08) = 0;
                }
                MD(m, 0x08) = 2;
                uint32_t t = s.TimeGet();
                // raw: /1000 via magic mul
                MD(m, 0x0c) =
                    (uint32_t)(((uint64_t)
                        t * 0x10624dd3ULL)
                        >> 38);
            }
        }
        else {
            s.BuildAndSend(m);
        }
        if (bReply) {
            uint32_t sent = 0;
            s.WSASend(sock, 4,
                (const uint8_t*)"OK\r\n",
                &sent);
        }
        *(int32_t*)(c + 8) = 0;
        return;
    }
    if (StrIcmpEq(buf,
                  "close_server\r\n")) {
        if (MQ(m, 0x00) == 0) {
            *(int32_t*)(c + 8) = 0;
            return;   // no reply
        }
        s.SetCloseFlag(
            (void*)MQ(m, 0x00), 3);
        bReply = true;
    }
    else if (StrIcmpEq(buf,
                "reset_crash_state\r\n")) {
        int64_t* p = s.CrashTimeGet();
        if (*p != 0) {
            p = s.CrashTimeGet();
            // raw: xchg [p], 0
            __atomic_exchange_n(
                p, (int64_t)0,
                __ATOMIC_SEQ_CST);
        }
        bReply = true;
    }
    else if (StrIcmpEq(buf,
            "reset_dbserver_state\r\n")) {
        if (g_ResetDbState != 0) {
            __atomic_exchange_n(
                &g_ResetDbState,
                (uint32_t)0,
                __ATOMIC_SEQ_CST);
        }
        bReply = true;
    }
    else {
        uint32_t sent = 0;
        s.WSASend(sock, 2,
            (const uint8_t*)"\r\n",
            &sent);
        *(int32_t*)(c + 8) = 0;
        return;
    }
    // the known-command reply
    if (bReply) {
        uint32_t sent = 0;
        s.WSASend(sock, 4,
            (const uint8_t*)"OK\r\n",
            &sent);
    }
    *(int32_t*)(c + 8) = 0;
}

// ===== M: ORIGINAL timer-check
// (14002adc0)
void MonitorTimerCheck(uint8_t* m) {
    SMSCmdSeams& s = g_MSCmdSeams;
    if (m == nullptr) {
        s.LogErrorFmt("\xa1\xef%s(%s)\xa1\xef"
                      " in %s, %d");
        return;
    }
    if (MD(m, 0x0c) != 0) {
        uint32_t now = s.TimeGet();
        if ((uint32_t)(MD(m, 0x0c) +
                MD(m, 0x08)) <= now / 1000) {
            MD(m, 0x0c) = 0;
            MD(m, 0x08) = 0;
            s.BuildAndSend(m);
        }
    }
}

} // namespace msg
