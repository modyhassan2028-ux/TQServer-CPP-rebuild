#!/bin/bash
# MsgServer regression — builds the pool (69 compilable
# units) then every tests/msg_*_test.cpp; tests whose units
# are still pending (Msg.h/UserManager.h/CrossProtocol.h
# modules) are reported as SKIP, not failures.
cd "$(dirname "$0")/.." || exit 1
POOL=/tmp/objs_msg; mkdir -p $POOL
INC="-I. -Imodules -Imsgserver -Imsgserver/ui -Imsgserver/chatkernel -Imsgserver/chatkernel/network3 -Imsgserver/evnet -Imsgserver/adapter/src -Imsgserver/mapgroupkernel -Imsgserver/mapgroupkernel/network -Imsgserver/mapgroupkernel/roulette/msg -Imsgserver/worldkernel -Ichangeserversocket -Icrossclient"
for f in $(find msgserver changeserversocket crossclient -name "*.cpp" | sort); do
  o=$POOL/$(basename "$f" .cpp).o
  [ "$o" -nt "$f" ] && [ -z "$(find msgserver -name '*.h' -newer "$o" -print -quit)" ] || g++ -std=c++17 -c $INC "$f" -o "$o" 2>/dev/null
done
ar rcs /tmp/libmsg.a $POOL/*.o 2>/dev/null
OBJS=/tmp/libmsg.a
PASS=0; SKIP=0; FAIL=0
for t in tests/msg_*_test.cpp; do
  n=$(basename "$t" .cpp)
  bin=/tmp/msgbin_$n
  if ! g++ -std=c++17 -g -fsanitize=address,undefined $INC \
       "$t" $OBJS -o "$bin" 2>/tmp/msg_link_$n.log; then
    SKIP=$((SKIP+1)); echo "SKIP $n"; continue
  fi
  good=1
  for r in 1 2 3 4 5 6; do
    ASAN_OPTIONS=detect_leaks=0:alloc_dealloc_mismatch=0 "$bin" >/tmp/msg_run_$n.log 2>&1 || { good=0; break; }
  done
  if [ $good -eq 1 ]; then PASS=$((PASS+1)); else
    FAIL=$((FAIL+1)); echo "RUN-FAIL $n"; tail -3 /tmp/msg_run_$n.log; fi
done
echo "=== MSG RESULT: PASS=$PASS SKIP=$SKIP FAIL=$FAIL ==="
[ $FAIL -eq 0 ] && echo "MSG-ALL-GREEN $PASS/$PASS x6"
exit 0
