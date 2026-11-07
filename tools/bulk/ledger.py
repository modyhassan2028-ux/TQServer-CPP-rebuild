#!/usr/bin/env python3
"""The porting ledger: a row counts as ported only when a module really defines it.

A body is counted when one of these holds:

  1. a function whose *name* carries the address is declared or defined -- `SynRbInsert_141727e60(`,
     `SynLift_141728290(`. Function-pointer seams (`g_fn...`) are skipped: those name a callee, and the
     callee may well not be ported.
  2. a `// 0x<addr>` header line (dashes/spacing allowed) that is followed within two lines by a
     definition -- the convention used by the hand-written modules.
  3. a `0x<addr>` on a code line that also carries a '(' .
  4. the address is listed in a tools/bulk/manifest_*.json, i.e. a generated family recorded it.

Anything else (prose mentions, "see FUN_<addr>" notes) is not a port. The result is written to
tools/bulk/ported.json so the same set can be reused by the generators.
"""
import glob
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def main():
    funcs = {x['a']: x for x in json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))}
    routines = json.load(open(os.path.join(REPO, 'tools/bulk/routines.json')))
    paths = glob.glob(os.path.join(REPO, 'modules/**/*.cpp'), recursive=True) + \
        glob.glob(os.path.join(REPO, 'modules/**/*.h'), recursive=True)
    # staged work-in-progress is not ported until its battery is green
    paths = [p for p in paths if os.path.basename(p) not in ('synlift_stage.cpp', 'synlift_stage.h')]

    defs = set()
    for p in paths:
        L = [l.rstrip('\n') for l in open(p, errors='ignore')]
        text = '\n'.join(L).lower()
        for m in re.finditer(r'\b([a-z]\w*)_([0-9a-f]{6,})\s*\(', text):
            if m.group(1).startswith('g_fn'):
                continue
            a = int(m.group(2), 16)
            if a in funcs:
                defs.add(a)
        for i, ln in enumerate(L):
            s, low = ln.strip(), ln.lower()
            m = re.match(r'^//\s*[-=\s]*0x([0-9a-f]{6,})\b', low)
            if m:
                a = int(m.group(1), 16)
                if a in funcs and '(' in ' '.join(x.strip() for x in L[i + 1:i + 3]):
                    defs.add(a)
            elif not s.startswith('//'):
                for mm in re.finditer(r'0x([0-9a-f]{6,})', low):
                    a = int(mm.group(1), 16)
                    if a in funcs and '(' in s:
                        defs.add(a)
    for p in glob.glob(os.path.join(REPO, 'tools/bulk/manifest_*.json')):
        try:
            for h in json.load(open(p)):
                if isinstance(h, dict) and 'a' in h:
                    defs.add(h['a'])
        except Exception:
            pass

    # a row that was only a .pdata segment is counted at the length of the whole function that
    # tools/bulk/merge_ranges.py rebuilt from it, otherwise the ledger would price 121 instructions as 34
    extra_path = os.path.join(REPO, 'tools/bulk/extra_bodies.json')
    if os.path.exists(extra_path):
        for k, v in json.load(open(extra_path)).items():
            a = int(k, 16)
            if a in funcs and len(v['text']) > len(funcs[a]['text']):
                funcs[a] = {'a': a, 'b': v['b'], 'addr': v['addr'], 'text': v['text']}

    defs &= set(funcs)
    json.dump(sorted(defs), open(os.path.join(REPO, 'tools/bulk/ported.json'), 'w'))
    total_ins = sum(len(x['text']) for x in funcs.values())
    done = sum(1 for r in routines if all(a in defs for a in r['rows']))
    ins = sum(len(funcs[a]['text']) for a in defs)
    # Instruction-address coverage: rows overlap (fragments nested in bigger functions), so summing
    # their lengths double-counts. Counting each address once is the only honest denominator.
    def addrs_of(a):
        ad = funcs[a].get('addr') or [a]
        return [ad] if isinstance(ad, int) else list(ad)
    universe = set()
    for a in funcs:
        universe.update(addrs_of(a))
    covered = set()
    for a in defs:
        covered.update(addrs_of(a))
    print('rows %d/%d | routines %d/%d (%.1f%%) | instructions %d/%d (%.1f%%) | code covered %d/%d (%.1f%%)'
          % (len(defs), len(funcs), done, len(routines), 100.0 * done / len(routines),
             ins, total_ins, 100.0 * ins / total_ins,
             len(covered), len(universe), 100.0 * len(covered) / len(universe)))


if __name__ == '__main__':
    main()
