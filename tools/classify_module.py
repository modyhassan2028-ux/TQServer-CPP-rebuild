#!/usr/bin/env python3
"""Sort every function of a decompiled module into the buckets that decide the work:
   thunk (one tail call), accessor (one read/write), lib (STL/CRT only), real logic.
   Usage: classify_module.py <module base name> [--list real]"""
import re, sys, collections

def sections(path):
    src = open(path, errors='ignore').read()
    marks = [(m.start(), m.group(1), m.group(2)) for m in
             re.finditer(r'// Function: (\S+) @ ([0-9a-f]{6,10})\n', src)]
    marks.append((len(src), 'END', '0'))
    for i in range(len(marks) - 1):
        yield marks[i][1], marks[i][2], src[marks[i][0]:marks[i + 1][0]]

def sizes(path):
    d = {}
    for l in open(path, errors='ignore'):
        p = l.rstrip('\n').split('\t')
        if len(p) >= 4 and p[2].isdigit():
            d[p[1]] = int(p[2])
    return d

LIB = ('std::', '_invalid_parameter', 'operator_new', '_CxxThrowException',
       '__security_check_cookie', 'memmove', 'memset', 'memcpy', 'strlen')

def classify(body):
    code = [l.strip() for l in body.split('\n')[1:] if l.strip() and not l.startswith('//')]
    text = ' '.join(code)
    if not code: return 'thunk'
    # only declarations left, no statements
    if len(code) <= 2 and len(text) < 200: return 'thunk'
    nomem = re.sub(r'FUN_[0-9a-f]+', 'C', re.sub(r'\b(puVar|piVar|plVar|uVar|iVar|local|auStack|param)\w*\d*', 'V', text))
    if 'std::' in text: return 'lib'
    if any(k in text for k in LIB) and 'FUN_' not in text: return 'lib'
    # one tail call with arguments passed through, nothing else
    if len(code) <= 3 and re.fullmatch(r'(V = )?C\((V(,V)*)?\); return( V)?;', nomem.replace(' ', ' ')): return 'thunk'
    # pure accessor: return a field of the first argument, or write one
    if len(code) == 1 and re.match(r'return ', code[0]) and not re.search(r'[*+\-&|^<>]=', code[0]): return 'accessor'
    if len(code) <= 2 and re.match(r'\*\(?\w*\*?\)?\(?V \+ 0x', text) and 'return ;' in text: return 'accessor'
    return 'real'

def main():
    base = sys.argv[1]
    what = sys.argv[2] if len(sys.argv) > 2 else ''
    d = sizes(base + '.index.tsv')
    buckets = collections.Counter(); byts = collections.Counter(); real = []
    for name, addr, body in sections(base + '.decompiled.c'):
        k = classify(body)
        buckets[k] += 1; byts[k] += d.get(addr, 0)
        if k == 'real': real.append((d.get(addr, 0), name, addr))
    total = sum(buckets.values()) or 1
    print(f'{base}: {total} functions, {sum(d.values())} bytes')
    for k, n in buckets.most_common():
        print(f'  {k:9s} {n:6d}  {100*n/total:5.1f}%  {byts[k]:8d} bytes')
    if what == 'real':
        real.sort(reverse=True)
        for s, n, a in real[:40]: print(f'   {s:6d}  {n} @ {a}')

main()
