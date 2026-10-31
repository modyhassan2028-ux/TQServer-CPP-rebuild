# modules/cqbase

CQBase.dll (v6159) lives here.

The original layout is flat under `src`. The path strings the DLL itself carries
(the log calls embed `__FILE__`) name these files:

```
modules\cqbase\src\basecode.cpp
modules\cqbase\src\basefunc.cpp
modules\cqbase\src\common.cpp
modules\cqbase\src\ini.cpp
modules\cqbase\src\inifile.cpp
modules\cqbase\src\inimgr.cpp
modules\cqbase\src\logkernel.cpp
modules\cqbase\src\myheap.cpp
modules\cqbase\src\performanceinfo.cpp
modules\cqbase\src\stringmanager.cpp
modules\cqbase\src\terrainobjinfomgr.cpp
modules\cqbase\src\threadtimesinfo.cpp
```

so this port keeps every file directly in `src`, no deeper folders:

| port file | what it holds | original bodies |
|---|---|---|
| `src/cmsg.h`, `src/cmsg.cpp` | `tq::CMsg`, `tq::MsgHead` | 0x140b8xxxx |
| `src/ctimer.h`, `src/ctimer.cpp` | `TimeGet`, `tq::CTimer`, `tq::CTimerMS` | 0x140b82df0.. |
| `src/cstrpacker.h`, `src/cstrpacker.cpp` | `tq::CStringPacker` | 0x140bb0b00.. |
| `src/csync.h`, `src/csync.cpp` | the locking primitives | 0x140ba0060.. |
| `src/basefunc.h`, `src/basefunc.cpp` | `basefunc.cpp` helpers | 0x140b82fb0.. |

A file that the port has not reached yet is still listed above with its original
name, so the target tree is known exactly.
