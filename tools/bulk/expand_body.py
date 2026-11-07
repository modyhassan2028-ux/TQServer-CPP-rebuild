#!/usr/bin/env python3
"""Grow a .pdata row into the whole function by following its branches.

A row sometimes stops at the first `ret` while a conditional branch jumps past it into the rest of the
function. Lifting that row alone silently drops an arm, so before lifting we walk the control flow from the
entry and keep every block reachable inside the function's own code (stopping at `ret`, `jmp` out, and calls).
"""
import json
import re
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


def expand_by_rows(entry, funcs, rows):
    """Complete a row whose code runs past its own .pdata range.

    Proven on 0x141740e80: the row ends on a non-terminator (`cmp`), the `je` inside it targets a block that
    lives in a later row, and the real function only ends at a `ret`. So keep appending the row that holds the
    missing branch target, or the next contiguous row while the body does not terminate yet.
    """
    body = {'a': entry, 'b': max(funcs[entry]['addr']),
            'addr': list(funcs[entry]['addr']), 'text': list(funcs[entry]['text'])}
    for _ in range(12):
        inside = set(body['addr'])
        nxt = None
        for ins in body['text']:
            m = re.match(r'^(j\w+) (0x[0-9a-f]+)$', ins)
            if m and m.group(1) != 'jmp' and int(m.group(2), 16) not in inside:
                t = int(m.group(2), 16)
                nxt = next((r for r in rows if r <= t), None)
                break
        if nxt is None:
            last = body['text'][-1]
            if last.startswith('ret') or last.startswith('jmp'):
                return body
            end = max(body['addr']) + 6
            cand = [r for r in rows if r >= end]
            if not cand:
                return body
            nxt = cand[0]
        if nxt in inside:
            return body
        body['addr'] += list(funcs[nxt]['addr'])
        body['text'] += list(funcs[nxt]['text'])
        body['b'] = max(body['addr'])
    return body


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


def still_leaves(body):
    inside = set(body['addr'])
    for ins in body['text']:
        m = re.match(r'^(j\w+) (0x[0-9a-f]+)$', ins)
        if m and m.group(1) != 'jmp' and int(m.group(2), 16) not in inside:
            return True
    return False


def main():
    adds = [int(x, 16) for x in open(os.path.join(REPO, 'tools/bulk/truncated_rows.txt')).read().split()]
    funcs = {x['a']: x for x in json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))}
    table = sorted(funcs)
    extra = json.load(open(os.path.join(REPO, 'tools/bulk/extra_bodies.json')))
    # never replace an overlay body that is already longer (the merge_ranges work owns those), and never
    # write a body that still has a branch leaving it: a half body is worse than a refused one.
    extra = dict(extra)
    grown = 0
    for a in adds:
        old = funcs.get(a)
        new = expand_by_rows(a, funcs, table)
        have = extra.get(hex(a))
        best = len(have['text']) if have and have.get('text') else 0
        if old and len(new['text']) <= max(len(old['text']), best):
            continue
        if still_leaves(new):
            print('0x%x: still leaves its range after completion, left as is' % a)
            continue
        extra[hex(a)] = new
        grown += 1
        print('0x%x: %d -> %d instructions' % (a, len(old['text']) if old else 0, len(new['text'])))
    json.dump(extra, open(os.path.join(REPO, 'tools/bulk/extra_bodies.json'), 'w'), indent=0)
    print('grown %d of %d rows' % (grown, len(adds)))


if __name__ == '__main__':
    main()
