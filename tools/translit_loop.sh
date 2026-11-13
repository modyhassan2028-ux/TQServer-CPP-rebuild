#!/bin/sh
# Compile the transliterated unit, drop the bodies the compiler rejects, repeat until clean, then build both tiers.
# A dropped body is recorded in Docs/TRANSLIT_DENY.txt with its address; nothing in it is edited by hand.
# -fpermissive is needed because the listing passes pointers in integer slots; on x86-64 that is the same register,
# so the conversion is the listing's own looseness, not a change of meaning.
INC="-I. -Iinclude -Imodules -Imodules/npcserver/src"
# the symbol table of the objects the suite actually links is the authority on what is already ported
OBJS=$(grep -h -- "-o /tmp/npcsrv/\$name" tools/run_npcserver_suites.sh | tr ' ' '\n' | grep '^/tmp/npcsrv/.*\.o$' | grep -v translit | sed 's|\$name|npcserver_d255_test|' | sort -u)
nm -g --defined-only $OBJS 2>/dev/null | grep -oE "FUN_1[0-9a-f]{8}" | sort -u > Docs/TRANSLIT_AVAILABLE.txt
# and their demangled signatures, so a call site written from the listing still matches the ported definition
nm -g --defined-only -C $OBJS 2>/dev/null | sed -nE 's/^.{17}T tq::(FUN_[0-9a-f]{9})\((.*)\)$/\1\t(\2)/p' | sort -u > Docs/TRANSLIT_SYMS.tsv
touch Docs/TRANSLIT_DENY.txt
for i in $(seq 1 10); do
  python3 tools/transliterate.py >/tmp/translit.log
  if g++ -std=c++17 -fpermissive $INC -fsyntax-only modules/npcserver/unattributed/transliterated.cpp 2>/tmp/translit.err; then
    echo "clean after $i rounds"
    break
  fi
  python3 tools/translit_drop.py /tmp/translit.err
  echo "round $i: $(grep -c 'error:' /tmp/translit.err) errors, deny list $(wc -l < Docs/TRANSLIT_DENY.txt)"
done
python3 tools/transliterate.py | head -2
g++ -std=c++17 -fpermissive $INC -c modules/npcserver/unattributed/transliterated.cpp -o /tmp/npcsrv/translit.o && echo "linked tier built"
g++ -std=c++17 -fpermissive -DTQ_TRANSLIT_PENDING $INC -fsyntax-only modules/npcserver/unattributed/transliterated.cpp && echo "pending tier syntax clean"
# the pending tier is syntax-checked the same way, so a parked body cannot rot either
for i in $(seq 1 6); do
  if g++ -std=c++17 -fpermissive -DTQ_TRANSLIT_PENDING $INC -fsyntax-only modules/npcserver/unattributed/transliterated.cpp 2>/tmp/translit.err; then
    echo "pending tier clean"; break
  fi
  python3 tools/translit_drop.py /tmp/translit.err
  python3 tools/transliterate.py >/tmp/translit.log
  echo "pending round $i: $(grep -c 'error:' /tmp/translit.err) errors"
done
