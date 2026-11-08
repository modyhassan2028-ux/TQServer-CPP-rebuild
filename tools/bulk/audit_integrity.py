#!/usr/bin/env python3
"""Check that every stored row really is one contiguous run of instructions.

A row carries an address list and a text list. For the lift to match the original, three things
have to hold, and none of them were verified before:

  1. each listed address is the start of the instruction the list claims (capstone's length at
     addr[i] equals addr[i+1] - addr[i]);
  2. the row ends where its .pdata record says it ends;
  3. the row does not swallow another function's entry, which would mean it was carved across a
     boundary and is lifting someone else's code.

Reported per address, with the failing check, so each defect can be repaired from evidence.
"""
import json
import os

import capstone

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE = 0x141721000
TEXT_OFF = 0x400


def load(name):
    with open(os.path.join(BULK, name)) as fh:
        return json.load(fh)


def main():
    image = open(DLL, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    funcs = {x['a']: dict(x, src='pdata') for x in load('funcs.json')}
    for k, v in load('extra_bodies.json').items():
        v = dict(v, a=int(k, 16), src='extra')
        funcs[v['a']] = v

    entries = sorted(funcs)
    bad_len = []
    bad_end = []
    swallowed = []
    for a in entries:
        f = funcs[a]
        addr = f['addr']
        off = a - BASE + TEXT_OFF
        # 1: arguments to the address list itself
        decoded = {}
        for ins in md.disasm(image[off:off + max(0, f['b'] - a)], a):
            decoded[ins.address] = ins.size
        for i in range(len(addr) - 1):
            step = addr[i + 1] - addr[i]
            size = decoded.get(addr[i])
            if size is None or size != step:
                bad_len.append((a, f['src'], hex(addr[i]), step, size))
                break
        # 2: the last instruction has to finish exactly at the recorded end
        last = addr[-1]
        size = decoded.get(last)
        if size is not None and last + size != f['b']:
            bad_end.append((a, f['src'], hex(last), hex(last + size), hex(f['b'])))
        # 3: an entry inside this row means it was carved across a boundary
        import bisect
        i = bisect.bisect_right(entries, a)
        if i < len(entries) and entries[i] < f['b']:
            swallowed.append((a, f['src'], hex(entries[i]), hex(f['b'])))

    print('rows:', len(entries), '| pdata:', sum(1 for f in funcs.values() if f['src'] == 'pdata'),
          '| carved/overridden:', sum(1 for f in funcs.values() if f['src'] == 'extra'))
    print('address lists that do not match the bytes:', len(bad_len))
    for r in bad_len[:6]:
        print('   row 0x%x (%s) breaks at %s: next listed step %s, decoded size %s' % r)
    print('rows whose last instruction overshoots or undershoots its end:', len(bad_end))
    for r in bad_end[:6]:
        print('   row 0x%x (%s) last %s ends %s but row end is %s' % r)
    print('rows swallowing another entry:', len(swallowed))
    for r in swallowed[:8]:
        print('   row 0x%x (%s) covers 0x%x..%s' % r)
    return 0 if not bad_len and not swallowed else 1


if __name__ == '__main__':
    raise SystemExit(main())
