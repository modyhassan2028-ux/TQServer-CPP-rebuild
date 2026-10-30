#!/usr/bin/env bash
# One consolidated flower cycle: every flower unit test is linked into a single
# binary (each test's main renamed) and that binary runs six times, so a batch
# costs one build instead of one build per unit.
cd "$(dirname "$0")/.."
set -u
OBJ=/app/co_repo/.build_flower
mkdir -p "$OBJ"
find "$OBJ" -name "*.o" -delete
for f in modules/analyst/src/*.cpp modules/title/src/*.cpp modules/training/src/*.cpp modules/peerage/src/*.cpp modules/syndicate/src/*.cpp modules/syndicate/src/msg/*.cpp modules/flower/src/*.cpp modules/flower/src/msg/*.cpp; do
  base=$(basename "$f" .cpp); dir=$(basename "$(dirname "$(dirname "$f")")")
  [ "$base" = "$dir" ] && continue
  o=$OBJ/$(echo "$f" | sed "s|/|_|g; s|\.cpp$|.o|")
  g++ -std=c++17 -I. -Iinclude -Imodules -c "$f" -o "$o" || { echo "OBJ-FAIL $f"; exit 1; }
done
LIST=$(ls tests/flower_d*_test.cpp | sort -V)
MAIN=$OBJ/cycle_main.cpp; : > "$MAIN"
NAMES=""
for f in $LIST; do
  n=$(basename "$f" _test.cpp)
  NAMES="$NAMES $n"
  g++ -std=c++17 -I. -Iinclude -Imodules -Dmain=${n}_main -c "$f" -o $OBJ/t_$n.o || { echo "TEST-OBJ-FAIL $n"; exit 1; }
  echo "int ${n}_main();" >> "$MAIN"
done
echo "int main(){int rc=0;" >> "$MAIN"
for n in $NAMES; do echo "  rc += (${n}_main() != 0);" >> "$MAIN"; done
echo "  return rc; }" >> "$MAIN"
g++ -std=c++17 "$MAIN" $OBJ/t_*.o $OBJ/modules_*.o -o $OBJ/cycle_bin || { echo "LINK-FAIL"; exit 1; }
N=$(echo $NAMES | wc -w)
for pass in 1 2 3 4 5 6; do
  OUT=$($OBJ/cycle_bin 2>&1); RC=$?
  if [ $RC -ne 0 ]; then echo "CYCLE-FAIL pass=$pass rc=$RC"; echo "$OUT" | tail -20; exit 1; fi
done
echo "CYCLE-6X-GREEN: $N flower units in one binary"
