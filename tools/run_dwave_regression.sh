#!/usr/bin/env bash
# TQServer rebuild — Wave-1 DLL unit regression (D1..D20), 6 passes.
# Builds all port objects then compiles+runs each unit test against them.
cd "$(dirname "$0")/.."
set -u
TESTS="analyst_d1 analyst_d2 title_d3 title_d4 title_d5 title_d6 title_d7 title_d8 title_d9 title_d10 title_d11 title_d12 training_d13 training_d14 training_d15 training_d16 peerage_d17 peerage_d18 peerage_d19 peerage_d20 peerage_d21 peerage_d22 peerage_d23 peerage_d24 peerage_d25 syndicate_d26 syndicate_d27 syndicate_d28 syndicate_d29"
OBJ=/tmp/objs_wave; rm -f $OBJ/*.o; mkdir -p $OBJ
for f in Exe/Dll/Analyst/Port/*.cpp Exe/Dll/Title/Port/*.cpp Exe/Dll/Training/Port/*.cpp Exe/Dll/Peerage/Port/*.cpp Exe/Dll/Syndicate/Port/*.cpp; do
  g++ -std=c++17 -I. -c "$f" -o $OBJ/$(basename $f .cpp).o || { echo "OBJ-FAIL $f"; exit 1; }
done
FAIL=0
for pass in 1 2 3 4 5 6; do
  for t in $TESTS; do
    g++ -std=c++17 -I. tests/${t}_test.cpp $OBJ/*.o -o /tmp/reg_bin 2>/tmp/reg_err.txt
    [ $? -ne 0 ] && { echo "BUILD-FAIL $t"; head -3 /tmp/reg_err.txt; FAIL=1; break 2; }
    OUT=$(/tmp/reg_bin 2>&1); RC=$?
    N=$(echo $t | sed 's/[a-z]*_d//')
    if [ $RC -ne 0 ] || ! echo "$OUT" | grep -qiE "(ANALYST|TITLE|TRAINING|PEERAGE|SYNDICATE)-D${N}-OK"; then
      echo "RUN-FAIL $t (pass=$pass rc=$RC)"; echo "$OUT" | head -3; FAIL=1; break 2
    fi
  done
done
[ $FAIL -eq 0 ] && echo "ALL-6X-GREEN: 29/29"
exit $FAIL
