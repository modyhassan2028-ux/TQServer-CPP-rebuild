#!/usr/bin/env python3
"""Attribute each NpcServer.exe body to the source path the binary itself carries.

Method (evidence only):
  1. the .rdata strings that look like source paths are read from the image and their VAs computed
     from the section headers objdump prints;
  2. every `lea 0x..(%rip)` whose resolved address is one of those strings marks the body that
     loads it, so that body belongs to that path;
  3. bodies are ordered by address, and a body takes the path of the nearest reference at or before
     it. Bodies before the first reference are reported as unattributed rather than guessed.
"""
import re, subprocess, sys, bisect

BIN = '/app/co_decomp/orig_binaries/Source/NpcServer.exe'
DIS = '/tmp/npc_full.txt'

def sections():
    out = subprocess.run(['objdump', '-h', BIN], capture_output=True, text=True).stdout
    secs = []
    for line in out.splitlines():
        m = re.match(r'\s*\d+\s+(\.\S+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)', line)
        if m:
            secs.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16), int(m.group(5), 16)))
    return secs

def strings():
    secs = sections()
    data = open(BIN, 'rb').read()
    found = {}
    for name, size, va, off in secs:
        blob = data[off:off + size]
        for m in re.finditer(rb'[A-Za-z0-9_\\/\.\-]{4,140}\.(?:cpp|h|cc|cxx)\x00', blob):
            s = m.group(0)[:-1].decode('ascii', 'ignore').replace('\\', '/')
            if ':' in s: s = s.split(':', 1)[1]
            found[va + m.start()] = s.lstrip('/')
    return found

def main():
    paths = strings()
    refs = []
    for line in open(DIS):
        m = re.match(r'\s+([0-9a-f]+):\tlea\s+.*?#\s*0x([0-9a-f]+)', line)
        if m:
            tgt = int(m.group(2), 16)
            if tgt in paths:
                refs.append((int(m.group(1), 16), paths[tgt]))
    refs.sort()
    print('path strings: %d | lea references: %d' % (len(paths), len(refs)))
    seen = []
    for addr, p in refs:
        if not seen or seen[-1][1] != p:
            seen.append((addr, p))
    cur = None
    for addr, p in seen:
        if p != cur:
            print('  from 0x%x : %s' % (addr, p))
            cur = p
    print('\nfirst reference at 0x%x' % (seen[0][0] if seen else 0))

main()
