#!/bin/bash
# The protobuf constructor suite: 0x1417f05f0 (CMsgLeagueRobOptPB) and 0x1417f1600
# (CMsgLeagueTokenPB), against a build that includes the seam definitions the PB headers declare but no
# unit defined (msgpbseams.cpp). Six cycles, sanitizers on.
cd "$(dirname "$0")/.." || exit 1
BIN=/tmp/syndicate_pbsuite
SRC="tests/syndicate_pbctors_test.cpp
     modules/syndicate/src/msg/msgleagueroboptpb.cpp
     modules/syndicate/src/msg/msgleaguetokenpb.cpp
     modules/syndicate/src/msg/msgpbmemberdtors.cpp
     modules/syndicate/src/msg/msgseams.cpp
     modules/syndicate/src/msg/msgpbseams.cpp"
g++ -std=c++17 -I. -g -Wall -Wextra -fsanitize=address,undefined $SRC -o $BIN || exit 1
ok=1
for r in 1 2 3 4 5 6; do
  ASAN_OPTIONS=detect_leaks=0 $BIN >/tmp/pbsuite_$r.log 2>&1 || { ok=0; echo "cycle $r FAILED"; tail -3 /tmp/pbsuite_$r.log; }
done
[ $ok -eq 1 ] && echo "PBSUITE-GREEN x6: $(grep -h PBCTORS_OK /tmp/pbsuite_6.log)"
