#!/usr/bin/env bash
# TQServer rebuild — the full D-series DLL unit regression (D1..D65), 6 passes.
# Builds all port objects then compiles+runs each unit test against them.
cd "$(dirname "$0")/.."
set -u
TESTS="analyst_d1 analyst_d2 title_d3 title_d4 title_d5 title_d6 title_d7 title_d8 title_d9 title_d10 title_d11 title_d12 training_d13 training_d14 training_d15 training_d16 peerage_d17 peerage_d18 peerage_d19 peerage_d20 peerage_d21 peerage_d22 peerage_d23 peerage_d24 peerage_d25 syndicate_d26 syndicate_d27 syndicate_d28 syndicate_d29 syndicate_d30 syndicate_d31 syndicate_d32 syndicate_d33 syndicate_d34 syndicate_d35 syndicate_d36 syndicate_d36b syndicate_d36c syndicate_d36d syndicate_d37 syndicate_d38 syndicate_d39 syndicate_d40 syndicate_d41 syndicate_d42 syndicate_d43 syndicate_d44 syndicate_d45 syndicate_d46 syndicate_d47 syndicate_d48 syndicate_d49 syndicate_d50 syndicate_d51 syndicate_d52 syndicate_d53 syndicate_d54 syndicate_d55a syndicate_d55b syndicate_d56 syndicate_d57 syndicate_d58 syndicate_d59 syndicate_d60 syndicate_d61 syndicate_d62 syndicate_d63 syndicate_d64 syndicate_d65 syndicate_d66 syndicate_d67 syndicate_d68 syndicate_d69 syndicate_d70 syndicate_d71 syndicate_d72 syndicate_d73 syndicate_d74 syndicate_d75 syndicate_d76 syndicate_d77 syndicate_d78 syndicate_d79 syndicate_d80 syndicate_d81 syndicate_d82 syndicate_d83 syndicate_d84 syndicate_d85 syndicate_d86 syndicate_d87 syndicate_d88 syndicate_d89 syndicate_d90 syndicate_d92 syndicate_d93 syndicate_d94 syndicate_d95 syndicate_d96 syndicate_d97 syndicate_d98 syndicate_d99 syndicate_d100 syndicate_d101 syndicate_d102 syndicate_d103 syndicate_d104 syndicate_d105 syndicate_d106 syndicate_d107 syndicate_d108 syndicate_d109"
OBJ=/tmp/objs_wave; rm -f $OBJ/*.o; mkdir -p $OBJ
# the d55a unit includes its port .cpp inline (to
# reach the static sort internals) -> links with
# NO port objects
for f in modules/analyst/src/*.cpp modules/title/src/*.cpp modules/training/src/*.cpp modules/peerage/src/*.cpp modules/syndicate/src/*.cpp; do
  # the module-entry skeletons (modules/<mod>/src/<mod>.cpp, the
  # original module files) are separate DLL builds — excluded
  base=$(basename $f .cpp); dir=$(basename $(dirname $(dirname $f)))
  [ "$base" = "$dir" ] && continue
  g++ -std=c++17 -I. -Iinclude -Imodules -c "$f" -o $OBJ/$base.o || { echo "OBJ-FAIL $f"; exit 1; }
done
FAIL=0
for pass in 1 2 3 4 5 6; do
  for t in $TESTS; do
    if [ "$t" = "syndicate_d55a" ]; then
      g++ -std=c++17 -I. -Iinclude -Imodules tests/${t}_test.cpp -o /tmp/reg_bin 2>/tmp/reg_err.txt
    else
      g++ -std=c++17 -I. tests/${t}_test.cpp $OBJ/*.o -o /tmp/reg_bin 2>/tmp/reg_err.txt
    fi
    [ $? -ne 0 ] && { echo "BUILD-FAIL $t"; head -3 /tmp/reg_err.txt; FAIL=1; break 2; }
    OUT=$(/tmp/reg_bin 2>&1); RC=$?
    N=$(echo $t | sed 's/[a-z]*_d//')
    if [ $RC -ne 0 ] || ! echo "$OUT" | grep -qE "[-_]OK"; then
      echo "RUN-FAIL $t (pass=$pass rc=$RC)"; echo "$OUT" | head -3; FAIL=1; break 2
    fi
  done
done
[ $FAIL -eq 0 ] && echo "ALL-6X-GREEN: $(echo $TESTS | wc -w)/$(echo $TESTS | wc -w)"
exit $FAIL
