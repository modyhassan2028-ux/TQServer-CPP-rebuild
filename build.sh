#!/usr/bin/env bash
# TQServer C++ rebuild — cross-build all Windows binaries with zig cc (MinGW-compatible).
# Usage: ./build.sh [path/to/zig]   (defaults to ./zig/zig if unpacked next to repo, else PATH)
set -e
cd "$(dirname "$0")"

ZIG="${1:-zig}"
[ -x "$ZIG" ] || ZIG="$(command -v zig)" || { echo "zig not found (https://ziglang.org)"; exit 1; }

CC="$ZIG c++ -target x86_64-windows-gnu -std=c++17"
INC="-Iinclude -ICore/CQBase -ICore/DB -ICore/Root -IExe/MsgServer -IExe/NpcServer -IModules/Syndicate -IModules/Trade"
WARN="-Wno-unused-parameter"
mkdir -p build

echo "[1/6] MsgServer.exe (net core + packet handlers)..."
$CC $INC $WARN Exe/MsgServer/main.cpp Exe/MsgServer/NetCore.cpp Exe/MsgServer/Account.cpp Exe/MsgServer/Npc.cpp Exe/MsgServer/MsgNpcInfo.cpp Exe/MsgServer/MySQLClient.cpp Exe/MsgServer/Dialog.cpp Core/CQBase/SHA1.cpp Exe/MsgServer/BattleSystem.cpp \
    Exe/MsgServer/DMap.cpp Exe/MsgServer/GameMap.cpp Exe/MsgServer/Guild.cpp Exe/MsgServer/MapManager.cpp Exe/MsgServer/Monster.cpp Exe/MsgServer/MonsterManager.cpp Exe/MsgServer/MsgMonster.cpp Exe/MsgServer/MsgConnect.cpp \
    Exe/MsgServer/MsgAction.cpp \
    Exe/MsgServer/MsgInteract.cpp Exe/MsgServer/MsgItem.cpp Exe/MsgServer/MsgTalk.cpp Exe/MsgServer/MsgUserAttrib.cpp \
    Exe/MsgServer/User.cpp Exe/MsgServer/UserManager.cpp Exe/MsgServer/CrossServer/CrossMsgAction.cpp \
    Core/CQBase/Msg.cpp Core/CQBase/StringPacker.cpp Core/CQBase/Timer.cpp \
    Core/DB/AsyncDBThread.cpp Core/Root/Root.cpp -lws2_32 -o build/MsgServer.exe

echo "[2/6] NpcServer.exe..."
$CC $INC $WARN Exe/NpcServer/main.cpp -o build/NpcServer.exe

echo "[3/6] Syndicate.dll..."
$CC $INC $WARN -shared Modules/Syndicate/Syndicate.cpp -o build/Syndicate.dll

echo "[4/6] Trade.dll..."
$CC $INC $WARN -shared Modules/Trade/Trade.cpp -o build/Trade.dll

echo "[5/6] CustomGM.dll..."
$CC $INC $WARN -shared Tools/CustomGM/CustomGM.cpp -o build/CustomGM.dll

echo "[6/6] ServerLoader.exe..."
$CC $INC $WARN Tools/ServerLoader/main.cpp Tools/ServerLoader/ConfigManager.cpp \
    Tools/ServerLoader/HookInjector.cpp Tools/ServerLoader/ProcessManager.cpp \
    Tools/ServerLoader/ServerLoaderGUI.cpp -lshlwapi -lcomctl32 -lgdi32 -luser32 -o build/ServerLoader.exe

echo "OK. Binaries in ./build/"
ls -la build/
