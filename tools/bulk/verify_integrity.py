"""Flag ported bodies whose control flow leaves the row they were lifted from.

A conditional branch to an address outside the .pdata row means the row is only one arm of a bigger
function: lifting it on its own drops the other arm, and the body can claim instructions it never
implemented. 0x141740e80 was exactly that, and the differential harness caught the difference.

Usage: python3 tools/bulk/verify_integrity.py
Exits non-zero when a body in the shipped module is truncated, so it can gate a batch.
"""
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
funcs = {x['a']: x for x in json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))}
ported = set(json.load(open(os.path.join(REPO, 'tools/bulk/ported.json'))))
known = set()
path = os.path.join(REPO, 'tools/bulk/truncated_rows.txt')
if os.path.exists(path):
    known = {int(x, 16) for x in open(path).read().split()}

bad = []
for a in sorted(ported):
    f = funcs.get(a)
    if not f or not f.get('addr'):
        continue
    addrs = f['addr']
    inside = set(addrs)
    lo, hi = min(addrs), max(addrs)
    for ins in f['text']:
        m = re.match(r'^(j\w+) (0x[0-9a-f]+)$', ins)
        if not m or m.group(1) == 'jmp':
            continue
        t = int(m.group(2), 16)
        if t not in inside and not lo <= t <= hi:
            bad.append(a)
            break

print('ported bodies: %d | truncated rows: %d (%d already listed)' % (len(ported), len(bad), len(set(bad) & known)))
for a in bad[:20]:
    if a not in known:
        print('  new: 0x%x' % a)
new = [a for a in bad if a not in known]
sys.exit(1 if new else 0)
