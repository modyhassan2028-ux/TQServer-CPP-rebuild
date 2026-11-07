#!/usr/bin/env python3
"""Rebuild whole functions out of the partial .pdata segments.

A quarter of the remaining rows are chunks: their last branch leaves the recorded range and lands in a
neighbouring row that is really the tail of the same routine. This sweeps the bytes of a row from its
entry up to the next row start, keeps everything up to the last `ret` that is followed only by padding,
and checks that every branch target lands inside the swept range. Only bodies that pass that check are
written to tools/bulk/extra_bodies.json, where lift.py picks them up.

    merge_ranges.py 0x14172ae00 0x14175d840 ...     rebuild these rows
    merge_ranges.py --segments                     rebuild every remaining row that needs it
"""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import extract_body as E   # noqa: E402  (disasm/normalise live there)

REPO = E.REPO
PAD = ('nop', 'int3')


def load():
    funcs = {x['a']: x for x in json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))}
    starts = sorted(funcs)
    extra_path = os.path.join(REPO, 'tools/bulk/extra_bodies.json')
    extra = json.load(open(extra_path)) if os.path.exists(extra_path) else {}
    for k, v in extra.items():
        v['a'] = int(k, 16)
        funcs[v['a']] = v
        starts.append(v['a'])
    return funcs, sorted(set(starts)), extra_path, extra


def boundary(starts, addr):
    import bisect
    i = bisect.bisect_right(starts, addr)
    return starts[i] if i < len(starts) else addr + 0x800


def sweep(addr, stops):
    """Linear sweep from the entry; it ends at the first `ret` that is followed by padding or by the
    start of a known row. Tail jumps are followed when the region runs out of code first."""
    stop = set(stops)
    keep, cursor, hops = [], addr, 0
    while True:
        if hops > 8:
            return None, 'tail-jump loop'
        hops += 1
        rows = E.normalise(E.disasm(cursor, 0x800))
        if not rows or rows[0][0] != cursor:
            return None, 'unreadable at 0x%x' % cursor
        done = False
        for i, (a, size, t) in enumerate(rows):
            op = t.split()[0]
            keep.append((a, size, t))
            if op.startswith('ret'):
                nxt = rows[i + 1] if i + 1 < len(rows) else None
                if nxt is None or nxt[2].split()[0].startswith(PAD) or nxt[0] in stop:
                    done = True
                    break
        if done:
            break
        last = keep[-1][2]
        m = re.match(r'^jmp (0x[0-9a-f]+)$', last)
        if not m:
            return None, 'ran out of code after %s' % last
        cursor = int(m.group(1), 16)
    while keep and keep[-1][2].split()[0].startswith(PAD):
        keep.pop()
    body = {'a': addr, 'b': keep[-1][0] + keep[-1][1],
            'addr': [a for a, _s, _t in keep], 'text': [t for _a, _s, t in keep]}
    # closure: pull in every region a branch reaches until nothing is missing
    for _round in range(8):
        inside = set(body['addr'])
        missing = []
        for t in body['text']:
            m = re.match(r'^j\w+ (0x[0-9a-f]+)$', t)
            if m and int(m.group(1), 16) not in inside:
                missing.append(int(m.group(1), 16))
        if not missing:
            break
        for tgt in sorted(set(missing)):
            rows = E.normalise(E.disasm(tgt, 0x800))
            if not rows or rows[0][0] != tgt:
                return None, 'branch to 0x%x cannot be read' % tgt
            add = []
            for i, (a, size, t) in enumerate(rows):
                add.append((a, size, t))
                if t.split()[0].startswith('ret'):
                    nxt = rows[i + 1] if i + 1 < len(rows) else None
                    if nxt is None or nxt[2].split()[0].startswith(PAD) or nxt[0] in stop:
                        break
            else:
                return None, 'region at 0x%x has no end' % tgt
            body['addr'] += [a for a, _s, _t in add]
            body['text'] += [t for _a, _s, t in add]
        body['b'] = max(body['b'], body['addr'][-1])
    inside = set(body['addr'])
    for t in body['text']:
        m = re.match(r'^j\w+ (0x[0-9a-f]+)$', t)
        if m and int(m.group(1), 16) not in inside:
            return None, 'branch to 0x%x outside the span' % int(m.group(1), 16)
    return body, '%d instructions (%d bytes)' % (len(body['text']), body['b'] - body['a'])


def needs_merge(row):
    own = set(row['addr'])
    for t in row['text']:
        m = re.match(r'^j\w+ (0x[0-9a-f]+)$', t)
        if m and int(m.group(1), 16) not in own:
            return True
    return False


def main():
    funcs, starts, extra_path, extra = load()
    args = sys.argv[1:]
    if args == ['--segments']:
        targets = [a for a, f in sorted(funcs.items()) if needs_merge(f)]
    else:
        targets = [int(a, 16) for a in args]
    ok = bad = 0
    for addr in targets:
        body, why = sweep(addr, starts)
        if body:
            extra['0x%x' % addr] = body
            ok += 1
            print('0x%x: %s' % (addr, why))
        else:
            bad += 1
            print('0x%x: %s' % (addr, why))
    json.dump(extra, open(extra_path, 'w'), indent=1)
    print('merged %d, refused %d, extra_bodies now %d' % (ok, bad, len(extra)))


if __name__ == '__main__':
    main()
