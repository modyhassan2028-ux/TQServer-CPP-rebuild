#!/usr/bin/env bash
# TQServer C++ rebuild — cross-build all Windows binaries with zig cc (MinGW-compatible).
# Usage: ./build.sh [path/to/zig]   (defaults to ./zig/zig if unpacked next to repo, else PATH)
set -e
cd "$(dirname "$0")"

ZIG="${1:-zig}"
[ -x "$ZIG" ] || ZIG="$(command -v zig)" || { echo "zig not found (https://ziglang.org)"; exit 1; }

CC="$ZIG c++ -target x86_64-windows-gnu -std=c++17"
INC="-I. -Iinclude -ICore/CQBase -ICore/DB -ICore/Root -IExe/MsgServer -IExe/NpcServer -IModules/Syndicate -IModules/Trade"
WARN="-Wno-unused-parameter"
mkdir -p build

echo "[1/8] MsgServer.exe (net core + packet handlers)..."
mkdir -p build/luaobj
for f in vendor/lua/*.c; do
    $ZIG cc -target x86_64-windows-gnu -O2 -Ivendor/lua -c "$f" -o "build/luaobj/$(basename ${f%.c}).o" || exit 1
done
ar rcs build/liblua.a build/luaobj/*.o
$CC $INC $WARN -Ivendor/lua -IExe/CQCrossServer \
    Exe/MsgServer/*.cpp Exe/MsgServer/LuaScript/LuaVM.cpp Exe/MsgServer/Activity/ActivityManager.cpp \
    Exe/MsgServer/CrossServer/*.cpp Core/CQBase/*.cpp Core/DB/*.cpp Core/Root/*.cpp \
    build/liblua.a -lws2_32 -o build/MsgServer.exe

echo "[2/8] CQCrossServer.exe (cross hub)..."
$CC $INC $WARN -IExe/CQCrossServer Exe/CQCrossServer/main.cpp Exe/CQCrossServer/CrossKernel.cpp \
    -lws2_32 -o build/CQCrossServer.exe

# renumber handled below

echo "[3/8] game-system module DLLs (original Modules/ ABI)..."
mkdir -p build/Modules
python3 tools/modules/gen_module_skeletons.py >/dev/null
while IFS='|' read -r FOLDER NAME DLLNAME; do
    $CC $INC $WARN -shared -fPIC "Modules/$FOLDER/$NAME.cpp" -o "build/Modules/$DLLNAME" || exit 1
done < <(python3 -c "
import json
for m in json.load(open('tools/modules/abi.json')):
    print(m['folder'], m['name'], m['dll'], sep='|')")

echo "[4/8] NpcServer.exe..."
$CC $INC $WARN Exe/NpcServer/main.cpp -o build/NpcServer.exe

echo "[5/8] Syndicate.dll..."
$CC $INC $WARN -shared Modules/Syndicate/Syndicate.cpp -o build/Syndicate.dll

echo "[6/8] Trade.dll..."
$CC $INC $WARN -shared Modules/Trade/Trade.cpp -o build/Trade.dll

echo "[7/8] CustomGM.dll..."
$CC $INC $WARN -shared Tools/CustomGM/CustomGM.cpp -o build/CustomGM.dll

echo "[8/8] ServerLoader.exe..."
$CC $INC $WARN Tools/ServerLoader/main.cpp Tools/ServerLoader/ConfigManager.cpp \
    Tools/ServerLoader/HookInjector.cpp Tools/ServerLoader/ProcessManager.cpp \
    Tools/ServerLoader/ServerLoaderGUI.cpp -lshlwapi -lcomctl32 -lgdi32 -luser32 -o build/ServerLoader.exe

echo "OK. Binaries in ./build/"
ls -la build/
