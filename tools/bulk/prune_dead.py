#!/usr/bin/env python3
"""Drop instructions that no path can reach, so a jump table embedded in a body stops
looking like code.

Inside a function a switch is laid out as `jmp QWORD PTR [reg*8+table]` followed by the
table itself. Linear disassembly decodes those table bytes as instructions (`ins`, or a
store to an impossible displacement), and the lifter then refuses the whole row. Anything
between an unconditional transfer and the next branch target inside the row is unreachable:
the only way in is a jump, and that lands on a label. Those bytes are data, and the row's
text is rewritten without them. Already ported rows are left untouched.
"""
import json
import os
import re
import sys

BULK = os.path.dirname(os.path.abspath(__file__))
TERMINAL = ('ret', 'jmp', 'repz', 'rep')


def load(name):
    with open(os.path.join(BULK, name)) as fh:
        return json.load(fh)


def prune(body):
    addr, text = body['addr'], body['text']
    label = set()
    for t in text:
        for m in re.finditer(r'\b(?:call|j\w+)\s+0x([0-9a-f]+)', t):
            label.add(int(m.group(1), 16))
    keep_a, keep_t = [], []
    alive = True
    for a, t in zip(addr, text):
        if a in label:
            alive = True
        if not alive:
            continue
        keep_a.append(a)
        keep_t.append(t)
        if t.split()[0] in TERMINAL:
            alive = False
    return {'a': body['a'], 'b': body['b'], 'addr': keep_a, 'text': keep_t}


def main():
    extra = load('extra_bodies.json')
    funcs = {x['a']: x for x in load('funcs.json')}
    ported = {int(a) for a in load('ported.json')}
    dropped = 0
    for a in sorted(funcs):
        if a in ported:
            continue
        body = extra.get('0x%x' % a) or funcs[a]
        before = len(body['text'])
        cut = prune(body)
        after = len(cut['text'])
        if after < before:
            dropped += before - after
            if '%x' % a in [k.lstrip('0x') for k in extra] or '0x%x' % a in extra:
                extra['0x%x' % a] = cut
            else:
                extra.setdefault('0x%x' % a, cut)
    json.dump(extra, open(os.path.join(BULK, 'extra_bodies.json'), 'w'), indent=1)
    print('pruned %d unreachable instruction slots into %d rewritten rows' % (dropped, len(extra)))


if __name__ == '__main__':
    main()
