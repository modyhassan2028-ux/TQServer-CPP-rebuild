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
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/stl-global.cpp -o /tmp/npcsrv/global.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/log-stubs.cpp -o /tmp/npcsrv/logstub.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/log-getters.cpp -o /tmp/npcsrv/logget.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/container-bodies.cpp -o /tmp/npcsrv/cont.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/container-nodes.cpp -o /tmp/npcsrv/cnode.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/map-tree.cpp -o /tmp/npcsrv/maptree.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/vector-accessors.cpp -o /tmp/npcsrv/vacc.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/tree-links.cpp -o /tmp/npcsrv/tlink.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/tree-erase.cpp -o /tmp/npcsrv/terase.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/tree-erase-range.cpp -o /tmp/npcsrv/terange.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/cinstance.cpp -o /tmp/npcsrv/cinst.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/cmapmanager-instance.cpp -o /tmp/npcsrv/cminst.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/map-insert-erase.cpp -o /tmp/npcsrv/mins.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/module-singletons.cpp -o /tmp/npcsrv/msing.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/tree-insert.cpp -o /tmp/npcsrv/tins.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/src/version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp -o /tmp/npcsrv/data.o
for t in tests/npcserver_d*_test.cpp; do
    name=$(basename "$t" _test.cpp)
    g++ -std=c++17 $SAN $INC -c "$t" -o /tmp/npcsrv/$name.o
    g++ -std=c++17 $SAN /tmp/npcsrv/$name.o /tmp/npcsrv/front.o /tmp/npcsrv/stl.o /tmp/npcsrv/iter.o /tmp/npcsrv/shapes.o /tmp/npcsrv/refs.o /tmp/npcsrv/tail.o /tmp/npcsrv/global.o /tmp/npcsrv/logstub.o /tmp/npcsrv/logget.o /tmp/npcsrv/cont.o /tmp/npcsrv/cnode.o /tmp/npcsrv/maptree.o /tmp/npcsrv/vacc.o /tmp/npcsrv/tlink.o /tmp/npcsrv/terase.o /tmp/npcsrv/terange.o /tmp/npcsrv/cinst.o /tmp/npcsrv/cminst.o /tmp/npcsrv/mins.o /tmp/npcsrv/msing.o /tmp/npcsrv/tins.o /tmp/npcsrv/data.o -o /tmp/npcsrv/$name
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
