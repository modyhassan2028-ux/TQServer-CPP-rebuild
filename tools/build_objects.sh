#!/bin/sh
# Compile every object the suite links (the transliterated unit excluded), so the symbol table is current.
set -e
INC="-I. -Iinclude -Imodules -Imodules/npcserver/src"

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
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/cinstancemgr.cpp -o /tmp/npcsrv/cim.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/unattributed/small-bodies.cpp -o /tmp/npcsrv/small.o
g++ -std=c++17 $SAN $INC -c modules/npcserver/src/version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp -o /tmp/npcsrv/data.o
    g++ -std=c++17 $SAN $INC -c "$t" -o /tmp/npcsrv/$name.o
