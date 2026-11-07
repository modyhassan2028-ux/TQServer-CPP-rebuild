#!/usr/bin/env python3
"""Extend a row so a forward branch target lands inside it, with contamination guards.

Only used for rows whose branch target sits outside their .pdata range: the cold block the
branch reaches belongs to the same routine but was not indexed. The range is cut at the first
`ret` at or after the target, and refused outright if it would swallow the start of any body
that is already ported, or if the existing row is longer than the expansion.
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import extract_body  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BULK = os.path.join(REPO, 'tools/bulk')


def load(name):
    p = os.path.join(BULK, name)
    return json.load(open(p)) if os.path.exists(p) else {}


def main():
    extra = load('extra_bodies.json')
    funcs = {x['a']: x for x in json.load(open(os.path.join(BULK, 'funcs.json')))}
    ported = {int(a) for a in json.load(open(os.path.join(BULK, 'ported.json')))}
    for pair in sys.argv[1:]:
        start_s, target_s = pair.split(':')
        start, target = int(start_s, 16), int(target_s, 16)
        if target <= start:
            print('0x%x: target behind the row, refused' % start)
            continue
        rows = extract_body.normalise(extract_body.disasm(start, (target - start) + 0x60))
        if not rows or rows[0][0] != start:
            print('0x%x: could not read' % start)
            continue
        keep = []
        for a2, size2, t2 in rows:
            op2 = t2.split()[0]
            if op2 == 'int3' or op2.startswith('nop'):
                if keep:
                    break
                continue
            keep.append((a2, size2, t2))
            if a2 >= target and op2.startswith('ret'):
                break
        body = {'a': start, 'b': keep[-1][0] + keep[-1][1],
                'addr': [a2 for a2, _, _ in keep], 'text': [t2 for _, _, t2 in keep]} if keep else None
        if not body:
            print('0x%x: could not read' % start)
            continue
        if not (body['a'] <= target < body['b']):
            print('0x%x: expansion stops before 0x%x, refused' % (start, target))
            continue
        clash = [a for a in ported if start < a < body['b']]
        if clash:
            print('0x%x: would swallow 0x%x, refused' % (start, min(clash)))
            continue
        old = extra.get('0x%x' % start) or funcs.get(start) or {}
        if len(old.get('text') or []) >= len(body['text']):
            print('0x%x: existing body is longer, kept' % start)
            continue
        extra['0x%x' % start] = body
        print('0x%x: %d -> %d instructions' % (start, len(old.get('text') or []), len(body['text'])))
    json.dump(extra, open(os.path.join(BULK, 'extra_bodies.json'), 'w'), indent=1)


if __name__ == '__main__':
    main()
