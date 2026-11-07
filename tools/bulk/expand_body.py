#!/usr/bin/env python3
"""Grow a .pdata row into the whole function by following its branches.

A row sometimes stops at the first `ret` while a conditional branch jumps past it into the rest of the
function. Lifting that row alone silently drops an arm, so before lifting we walk the control flow from the
entry and keep every block reachable inside the function's own code (stopping at `ret`, `jmp` out, and calls).
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from extract_body import disasm, normalise  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
WINDOW = 0x400


def next_row(entry, table):
    for a in table:
        if a > entry:
            return a
    return entry + WINDOW


def expand(entry, limit=None):
    rows = disasm(entry, WINDOW)
    if limit is not None:
        # a branch can point at a neighbouring function; never walk past the next indexed row
        rows = [r for r in rows if r[0] < limit]
    by_addr = {a: (size, text) for a, size, text in rows}
    order = [a for a, _, _ in rows]
    seen = set()
    work = [entry]
    while work:
        a = work.pop()
        while a in by_addr and a not in seen:
            seen.add(a)
            size, text = by_addr[a]
            if text.startswith('ret') or text.startswith('repz ret'):
                break
            if text.startswith('jmp') and '0x' in text:
                # a tail jump leaves this function
                parts = text.split()
                if len(parts) == 2 and parts[1].startswith('0x'):
                    t = int(parts[1], 16)
                    if t in by_addr and t > a:
                        work.append(t)
                break
            if text.startswith('j'):
                parts = text.split()
                if len(parts) == 2 and parts[1].startswith('0x'):
                    work.append(int(parts[1], 16))
            a = a + size
    keep = sorted(seen)
    body = [by_addr[a][1] for a in keep]
    return {'a': entry, 'addr': keep,
            'text': [t for _a, _s, t in normalise([(a, by_addr[a][0], by_addr[a][1]) for a in keep])]}


def main():
    adds = [int(x, 16) for x in open(os.path.join(REPO, 'tools/bulk/truncated_rows.txt')).read().split()]
    funcs = {x['a']: x for x in json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))}
    table = sorted(funcs)
    extra = json.load(open(os.path.join(REPO, 'tools/bulk/extra_bodies.json')))
    extra = {k: v for k, v in extra.items() if k not in {hex(a) for a in adds}}
    grown = 0
    for a in adds:
        old = funcs.get(a)
        new = expand(a, next_row(a, table))
        if old and len(new['text']) <= len(old['text']):
            continue
        extra[hex(a)] = new
        grown += 1
        print('0x%x: %d -> %d instructions' % (a, len(old['text']) if old else 0, len(new['text'])))
    json.dump(extra, open(os.path.join(REPO, 'tools/bulk/extra_bodies.json'), 'w'), indent=0)
    print('grown %d of %d rows' % (grown, len(adds)))


if __name__ == '__main__':
    main()
