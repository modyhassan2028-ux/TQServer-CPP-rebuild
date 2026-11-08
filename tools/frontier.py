#!/usr/bin/env python3
"""Frontier: addresses that ported bodies mention but no ported body satisfies.

A body exists if some file defines `Slot_<addr>` or the lifted `SynLift_<addr>(`. Anything else that
appears as a `0x14xxxxxxx` mention inside modules/ is a callee nobody has transcribed yet.
"""
import re, sys, pathlib, subprocess

ROOT = pathlib.Path(__file__).resolve().parent.parent
MODS = ROOT / 'modules'
ADDR = re.compile(r'0x(141[0-9a-f]{6})\b')
DEF_SLOT = re.compile(r'\bSlot_(141[0-9a-f]{6})\b\s*\([^;]*\)\s*\{')
DEF_LIFT = re.compile(r'\bSynLift_(141[0-9a-f]{6})\s*\(uint64_t')

def scan():
    defined, mentioned = set(), {}
    for p in MODS.rglob('*.cpp'):
        text = p.read_text(errors='ignore')
        for m in DEF_SLOT.finditer(text): defined.add(m.group(1))
        for m in DEF_LIFT.finditer(text): defined.add(m.group(1))
        for m in ADDR.finditer(text):
            mentioned.setdefault(m.group(1), set()).add(p.name)
    return defined, mentioned

def main():
    defined, mentioned = scan()
    open_ = {a: f for a, f in mentioned.items() if a not in defined}
    with open(ROOT / 'Docs' / 'FRONTIER.txt', 'w') as fh:
        for a in sorted(open_):
            fh.write('%s  %s\n' % (a, ', '.join(sorted(open_[a]))))
    print('bodies: %d   mentioned: %d   open: %d' % (len(defined), len(mentioned), len(open_)))
    print('list -> Docs/FRONTIER.txt')

if __name__ == '__main__':
    main()
