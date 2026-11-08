#!/usr/bin/env python3
"""print a lifted body without the frame boilerplate"""
import re
import sys

SRC = 'modules/syndicate/src/synlift.cpp'
text = open(SRC).read()


def body(addr):
    i = text.find('uint64_t SynLift_%x(' % addr)
    if i < 0:
        return None
    j = text.index('{', i)
    depth = 0
    for k in range(j, len(text)):
        if text[k] == '{':
            depth += 1
        elif text[k] == '}':
            depth -= 1
            if depth == 0:
                return text[i:k + 1]
    return None


SKIP = ('if (ml_hit)', 'uint64_t rax = 0', 'uint64_t rcx = rcxA', 'bool f_zf',
        'uint8_t xmm0', 'alignas(16)', 'uint64_t rsp =', 'if (ml_entry_rsp)',
        '#define ML_CALL', '#undef', 'return rax;')

for a in sys.argv[1:]:
    b = body(int(a, 16))
    print('=== 0x%s' % a)
    if not b:
        print('   no body')
        continue
    for line in b.splitlines()[1:-1]:
        if line.strip() and not any(s in line for s in SKIP):
            print(line)
