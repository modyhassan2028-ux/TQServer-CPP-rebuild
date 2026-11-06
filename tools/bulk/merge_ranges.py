#!/usr/bin/env python3
"""Reassemble whole routines out of the .pdata rows.

Some rows begin after a routine's prologue, so `classify_remaining.py` flags them. Those rows are pieces of
one bigger routine: walking the rows in address order, a piece is followed by more pieces until a row that is
self-contained and ends at a `ret`/`jmp`. This merges such runs into the routine they belong to and reports
the real remaining routines, with contiguity checked so a merge is never assumed across a gap.
"""
import json, sys

sys.path.insert(0, 'tools/bulk')
from classify_remaining import classify


def main():
    funcs = json.load(open('tools/bulk/funcs.json'))
    funcs.sort(key=lambda f: f['a'])
    rows = [(f, classify(f)) for f in funcs]
    groups, cur = [], None
    for f, miss in rows:
        if cur is None:
            cur = {'start': f['a'], 'rowids': [f['a']], 'text': list(f['text']),
                   'addr': list(f['addr']), 'gap': False}
        else:
            if f['a'] != cur['lastb']:      # not adjacent: this row starts its own routine
                groups.append(cur)
                cur = {'start': f['a'], 'rowids': [f['a']], 'text': list(f['text']),
                       'addr': list(f['addr']), 'gap': False, 'lastb': f['b']}
                ends = f['text'][-1] if f['text'] else ''
                if not miss and (ends == 'ret' or ends.startswith('jmp') or ends.startswith('rex.W jmp')):
                    groups.append(cur); cur = None
                continue
            cur['rowids'].append(f['a']); cur['text'] += f['text']; cur['addr'] += f['addr']
        cur['lastb'] = f['b']
        ends = f['text'][-1] if f['text'] else ''
        if not miss and (ends == 'ret' or ends.startswith('rex.W jmp') or ends.startswith('jmp')):
            groups.append(cur); cur = None
    if cur:
        groups.append(cur)
    multi = [g for g in groups if len(g['rowids']) > 1]
    print('rows %d -> routines %d   (multi-row routines %d, merged rows %d)'
          % (len(rows), len(groups), len(multi), sum(len(g['rowids']) for g in multi)))
    print('routines with an address gap: %d' % sum(1 for g in groups if g['gap']))
    print('instruction volume of routines: %d' % sum(len(g['text']) for g in groups))
    sizes = sorted((len(g['text']) for g in groups), reverse=True)
    print('largest 8 routines by instructions:', sizes[:8])
    json.dump([{'start': g['start'], 'rows': g['rowids'], 'insns': len(g['text']), 'gap': g['gap']}
               for g in groups], open('tools/bulk/routines.json', 'w'))


if __name__ == '__main__':
    main()
