#!/usr/bin/env python3
"""Classify the bodies the port has not covered yet.

The .pdata index contains ranges that are not always whole functions: some rows begin in the middle of a
routine, after its prologue, so rbx/rbp/rsi/rdi/r12-r15 are already live. Such a row cannot be ported as a
standalone function. This script flags them so the remaining-work count is honest.

A callee-saved register counts as established when the body pushes it, spills it to memory in its first
three instructions (the prologue save), or simply writes it before reading it.
"""
import json, re, glob, collections, os

CALLE = {'rbx', 'rbp', 'rsi', 'rdi', 'r12', 'r13', 'r14', 'r15'}
JUNK = re.compile(r'^(call|jmp|ret|nop|int3|xchg|jb|jbe|je|jne|ja|jae|jge|jg|jl|jle|js|jns|rep|movaps|movdqa)\b')


def classify(body):
    text = body['text']
    est = set()
    for i, ins in enumerate(text[:3]):
        m = re.match(r'^push (r\w+)$', ins)
        if m:
            est.add(m.group(1))
        m = re.match(r'^mov (?:QWORD|DWORD) PTR \[[^\]]*\],(r\w+)$', ins)
        if m:
            est.add(m.group(1))          # the prologue spills instead of pushing
    missing = set()
    for ins in text:
        m = re.match(r'^(\w+)\s+(.*)$', ins)
        if not m:
            continue
        op, rest = m.group(1), m.group(2)
        if JUNK.match(ins):
            continue
        parts = [p.strip() for p in rest.split(',')]
        srcs = parts if op in ('cmp', 'test', 'push') else parts[1:]
        for s in srcs:
            for r in re.findall(r'\b(r[a-z0-9]+)\b', s):
                if r in CALLE and r not in est:
                    missing.add(r)
        d = re.match(r'^(r[a-z0-9]+)$', parts[0])
        if d:
            est.add(d.group(1))
    return sorted(missing)


def main():
    funcs = json.load(open('tools/bulk/funcs.json'))
    low = ''
    for p in glob.glob('modules/**/*.cpp', recursive=True) + glob.glob('modules/**/*.h', recursive=True):
        low += open(p, errors='ignore').read().lower()
    rem = [f for f in funcs if ('0x%x' % f['a']) not in low]
    whole, frag = [], []
    for f in rem:
        (frag if classify(f) else whole).append((f, classify(f)))
    print('remaining %d  |  whole bodies %d  |  mid-function rows %d'
          % (len(rem), len(whole), len(frag)))
    print('mid-function rows by the registers they inherit:')
    for k, v in collections.Counter(tuple(m) for _, m in frag).most_common(8):
        print('   %4d x  %s' % (v, ', '.join(k)))
    print('instruction volume: whole %d  mid %d'
          % (sum(len(f['text']) for f, _ in whole), sum(len(f['text']) for f, _ in frag)))
    json.dump({'whole': [f['a'] for f, _ in whole], 'mid': {hex(f['a']): m for f, m in frag}},
              open('tools/bulk/remaining.json', 'w'))


if __name__ == '__main__':
    main()
