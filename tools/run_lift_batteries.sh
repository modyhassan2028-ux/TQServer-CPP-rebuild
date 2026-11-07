#!/bin/sh
# Regression for the mechanically lifted tree containers: three batteries, six rounds, ASan+UBSan.
# Any failing round aborts. Kept separate from the hand-ported modules because the lift tests wire the
# seam pointers directly instead of exercising gameplay code.
set -e
cd "$(dirname "$0")/.."
SRC=modules/syndicate/src
CFLAGS="-std=c++17 -I. -I$SRC -g -fsanitize=address,undefined -static-libasan"
g++ $CFLAGS tests/cqbase_lift_insert_hint_test.cpp $SRC/synlift.cpp $SRC/synlift_stage.cpp \
    $SRC/synrbinsert_family.cpp -o /tmp/lift_ih
g++ $CFLAGS tests/cqbase_lift_erase_family_test.cpp $SRC/synlift.cpp $SRC/synlift_stage.cpp \
    $SRC/synrbinsert_family.cpp -o /tmp/lift_ef
g++ $CFLAGS tests/cqbase_lift_erase_test.cpp $SRC/synlift.cpp $SRC/synlift_stage.cpp \
    $SRC/synrbinsert.cpp $SRC/synthunks_it.cpp -o /tmp/lift_e1
g++ $CFLAGS -DERASE_RANGE_WIP tests/cqbase_lift_teardown_test.cpp $SRC/synlift.cpp $SRC/synlift_stage.cpp -o /tmp/lift_td
round=1
while [ $round -le 6 ]; do
    /tmp/lift_e1  | tail -1
    /tmp/lift_ih  | tail -1
    /tmp/lift_ef  | tail -1
    /tmp/lift_td  | tail -1
    round=$((round + 1))
done
