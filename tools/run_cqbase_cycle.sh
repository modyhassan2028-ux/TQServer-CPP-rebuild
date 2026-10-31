#!/usr/bin/env bash
# The CQBase cycle: every cqbase unit test in one binary, six sanitizer passes.
cd "$(dirname "$0")/.."
set -u
OBJ=/app/co_repo/.build_cqbase
mkdir -p "$OBJ"
find "$OBJ" -name "*.o" -delete
SAN="-fsanitize=address,undefined -fno-omit-frame-pointer -g"
for f in $(find modules/cqbase/src -name "*.cpp" | sort); do
  o=$OBJ/$(echo "$f" | sed "s|/|_|g; s|\.cpp$|.o|")
  g++ -std=c++17 $SAN -I. -Iinclude -Imodules -c "$f" -o "$o" || { echo "OBJ-FAIL $f"; exit 1; }
done
LIST=$(ls tests/cqbase_d*_test.cpp | sort -V)
MAIN=$OBJ/cycle_main.cpp; : > "$MAIN"; NAMES=""
for f in $LIST; do
  n=$(basename "$f" _test.cpp); NAMES="$NAMES $n"
  g++ -std=c++17 $SAN -I. -Iinclude -Imodules -Dmain=${n}_main -c "$f" -o $OBJ/t_$n.o || { echo "TEST-OBJ-FAIL $n"; exit 1; }
  echo "int ${n}_main();" >> "$MAIN"
done
echo "int main(){int rc=0;" >> "$MAIN"
for n in $NAMES; do echo "  rc += (${n}_main() != 0);" >> "$MAIN"; done
echo "  return rc; }" >> "$MAIN"
g++ -std=c++17 $SAN "$MAIN" $OBJ/t_*.o $OBJ/modules_*.o -o $OBJ/cycle_bin || { echo "LINK-FAIL"; exit 1; }
N=$(echo $NAMES | wc -w)
for pass in 1 2 3 4 5 6; do
  OUT=$(ASAN_OPTIONS=detect_leaks=1 $OBJ/cycle_bin 2>&1); RC=$?
  if [ $RC -ne 0 ]; then echo "CYCLE-FAIL pass=$pass rc=$RC"; echo "$OUT" | tail -20; exit 1; fi
done
echo "CQBAE-CYCLE-6X-GREEN: $N units"
