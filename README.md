# TQServer (C++ Rebuild)

C++ rebuild of the Conquer Online **TQ server** family (v6159 era). This project was started by another developer (a Visual Studio skeleton with Copilot); it is being completed here.

> Reference material: the full 60,000-function decompilation of the original `MsgServer.exe` is available in [conquer-online-v6159-decompiled](https://github.com/modyhassan2028-ux/conquer-online-v6159-decompiled) and is used as the specification when porting real systems.

## Build

**Option A — Visual Studio (Windows):** open `TQServer.sln`, build x64 Debug/Release.

**Option B — cross-build from Linux/macOS with [zig](https://ziglang.org/download/) (produces real Windows .exe/.dll):**

```bash
./build.sh /path/to/zig   # or have zig on PATH
```

Outputs in `build/`:

| Binary | What it is |
|---|---|
| `MsgServer.exe` | Game message server — **real winsock network core**: listens on port 5816 (configurable via argv), per-client threads, 2-byte `MsgHead` framing (`length`,`type`), packet dispatch |
| `NpcServer.exe` | NPC server skeleton |
| `Syndicate.dll`, `Trade.dll` | Game-system modules |
| `CustomGM.dll` | GM tool DLL (named-pipe command server, targets original MsgServer.exe addresses) |
| `ServerLoader.exe` | Server loader/monitor GUI |

## Current status (honest)

**Working:**
- Full solution builds cleanly (C++17) to Windows binaries.
- MsgServer: real socket listener, client accept/recv loops, packet framing, dispatch table (1001/1004).
- Login v1: MsgConnect (1001) creates the player session, registers in CUserManager, pushes attributes (1017: life/level/money/CPs) and a welcome message (1004). Auth is accepted as-is (real SRP6/AccountServer flow is on the roadmap).

**Implemented as stubs (porting from the decompiled reference is the roadmap):**
- Real account validation (AccountServer/SRP6), account DB (MySQL via `Core/DB`), character creation
- Map/NPC/monster world loading from the original data files
- Battle, item, attribute, guild/syndicate systems (classes exist with placeholder formulas)
- NpcServer is a placeholder main only

**Roadmap order (matching the original's architecture):**
1. Login handshake + AccountServer connection (reference: decompiled `AccountServer` C# + MsgServer login path)
2. Map group + map data loading (`.dmap` etc.)
3. ~~Monster spawn/AI~~ **done (v1)**: built-in spawn table, AI thread (2s ticks, roam + leash + respawn), MsgMonsterInfo 20001 / MsgMonsterJump 20002 extracted from the decompiled Create functions, monsters spawn to clients on login and broadcast movement to the map
4. ~~Monster spawn/AI~~ done. ~~Battle v1~~ done: MsgInteract (1022, 40B) from the decompiled Create, melee damage vs monsters, strike broadcast to map, kill rewards (money/CPs) and ~16s respawn.
5. Item/inventory system (1009), user attributes (1017), action/movement (1010) done
5. Chat channels (1004) beyond echo, guild, trade, team, quest systems

## Layout

```
Core/           CQBase (Msg base, StringPacker, Timer), DB (AsyncDBThread), Root
Exe/MsgServer   game server (net core + packet handlers)
Exe/NpcServer   NPC server (skeleton)
Modules/        Syndicate, Trade (DLLs)
Tools/          CustomGM.dll, ServerLoader.exe
include/        shared headers (Network/MsgHead.h, ...)
Config/         ini files (game port 5816, Blowfish key, ...)
```

## Legal

Conquer Online © TQ Digital. This repo may receive DMCA takedowns; keep that in mind.
