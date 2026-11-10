#!/bin/sh
# Build and run every NpcServer suite, six times each, with the sanitizers on.
set -e
cd "$(dirname "$0")/.."
SAN="-fsanitize=address,undefined -fno-omit-frame-pointer -g"
INC="-I. -Iinclude -Imodules -Imodules/npcserver/src"
mkdir -p /tmp/npcsrv
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/front-of-image.cpp -o /tmp/npcsrv/front.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/stl-internals.cpp -o /tmp/npcsrv/stl.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/stl-iterators.cpp -o /tmp/npcsrv/iter.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/stl-shapes.cpp -o /tmp/npcsrv/shapes.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/stl-refs.cpp -o /tmp/npcsrv/refs.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/stl-tail.cpp -o /tmp/npcsrv/tail.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/src/version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp -o /tmp/npcsrv/data.o
for t in tests/npcserver_d*_test.cpp; do
    name=$(basename "$t" _test.cpp)
    g++ -std=c++17 $SAN $INC -c "$t" -o /tmp/npcsrv/$name.o
    g++ -std=c++17 $SAN /tmp/npcsrv/$name.o /tmp/npcsrv/front.o /tmp/npcsrv/stl.o /tmp/npcsrv/iter.o /tmp/npcsrv/shapes.o /tmp/npcsrv/refs.o /tmp/npcsrv/tail.o /tmp/npcsrv/data.o -o /tmp/npcsrv/$name
done
cycle=1
while [ $cycle -le 6 ]; do
    for exe in /tmp/npcsrv/npcserver_d[0-9]*; do
        case "$exe" in *.o) continue;; esac
        "$exe" > /dev/null 2>&1 || { echo "cycle $cycle: $exe FAILED"; exit 1; }
    done
    cycle=$((cycle + 1))
done
echo "all NpcServer suites green, six cycles"
