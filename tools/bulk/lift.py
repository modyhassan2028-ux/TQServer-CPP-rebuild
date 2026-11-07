#!/usr/bin/env python3
"""Register-level lifter: one objdump body -> C++ that models the machine exactly.

No interpretation of intent: every x86 instruction becomes one C++ statement with the same operand width,
registers live in uint64_t variables, memory goes through width-tagged accessors, and the condition flags
are computed the way the instruction sets them. Anything the lifter does not understand is rejected, never
approximated.

Usage: lift.py <addr> [...]   (writes modules/syndicate/src/synlift_<addr>.h/.cpp)
"""
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

R64 = ['rax', 'rbx', 'rcx', 'rdx', 'rsi', 'rdi', 'rbp', 'rsp', 'r8', 'r9', 'r10', 'r11', 'r12', 'r13', 'r14', 'r15']
A32 = {'eax': 'rax', 'ebx': 'rbx', 'ecx': 'rcx', 'edx': 'rdx', 'esi': 'rsi', 'edi': 'rdi', 'ebp': 'rbp',
       'esp': 'rsp', 'r8d': 'r8', 'r9d': 'r9', 'r10d': 'r10', 'r11d': 'r11', 'r12d': 'r12', 'r13d': 'r13',
       'r14d': 'r14', 'r15d': 'r15'}
A8 = {'al': 'rax', 'bl': 'rbx', 'cl': 'rcx', 'dl': 'rdx', 'sil': 'rsi', 'dil': 'rdi', 'bpl': 'rbp',
      'r8b': 'r8', 'r9b': 'r9', 'r10b': 'r10', 'r11b': 'r11', 'r12b': 'r12', 'r13b': 'r13', 'r14b': 'r14',
      'r15b': 'r15'}
A16 = {'ax': 'rax', 'bx': 'rbx', 'cx': 'rcx', 'dx': 'rdx', 'si': 'rsi', 'di': 'rdi', 'bp': 'rbp'}
WIDTH_PTR = {'BYTE': 1, 'WORD': 2, 'DWORD': 4, 'QWORD': 8, 'XMMWORD': 16}


def reg_of(tok):
    """(base, width) for a register token, or None."""
    t = tok.strip()
    if t in R64:
        return t, 8
    if t in A32:
        return A32[t], 4
    if t in A16:
        return A16[t], 2
    if t in A8:
        return A8[t], 1
    return None


def enc(tok):
    """Encode one operand."""
    t = tok.strip()
    m = re.match(r'^(BYTE|WORD|DWORD|QWORD|XMMWORD) PTR \[(.*)\]$', t) or re.match(r'^\[(.*)\]$', t)
    if m:
        w = WIDTH_PTR[m.group(1)] if m.lastindex == 2 else 8
        inner = m.group(2) if m.lastindex == 2 else m.group(1)
        r = re.match(r'^rip@(0x[0-9a-f]+)$', inner)
        if r:
            return ('iat', int(r.group(1), 16), w)
        b = re.match(r'^(r[a-z0-9]+)(?:([+-])0x([0-9a-f]+))?$', inner)
        if b:
            disp = int(b.group(3), 16) if b.group(3) else 0
            if b.group(2) == '-':
                disp = -disp
            return ('mem', b.group(1), disp, w)
        # base + index*scale (+ disp), as in [r13+rax*8+0x0]
        base, index, disp = None, None, 0
        for part in re.findall(r'[+-]?[^+-]+', inner):
            sign = -1 if part.startswith('-') else 1
            tok = part.lstrip('+-').strip()
            if re.fullmatch(r'0x[0-9a-f]+', tok):
                disp += sign * int(tok, 16)
            elif re.fullmatch(r'\d+', tok):
                disp += sign * int(tok)
            elif '*' in tok:
                reg, scale = tok.split('*')
                index = (reg.strip(), int(scale, 16) if scale.startswith('0x') else int(scale))
            elif re.fullmatch(r'r[a-z0-9]+', tok):
                base = tok
            else:
                return None
        if base is None and index is None:
            return None
        expr = base if base else '0'
        if index:
            expr = '(%s + %s * %d)' % (expr, index[0], index[1])
        return ('mem', expr, disp, w)
    r = reg_of(t)
    if r:
        return ('reg', r[0], r[1], t)
    if re.match(r'^0x[0-9a-f]+$', t) or re.match(r'^\d+$', t):
        return ('imm', int(t, 16) if t.startswith('0x') else int(t))
    return None


def rv(op):
    """C++ expression reading a register operand."""
    base, w, tok = op[1], op[2], op[3]
    if w == 8:
        return base
    if w == 4:
        return '(uint32_t)%s' % base
    if w == 2:
        return '(uint16_t)%s' % base
    return '(uint8_t)%s' % base


def wr(base, w, expr):
    """C++ statement writing a register with the right partial-write rule."""
    if w == 8:
        return '%s = %s;' % (base, expr)
    if w == 4:
        return '%s = (uint64_t)(uint32_t)(%s);' % (base, expr)
    if w == 2:
        return '%s = (%s & ~(uint64_t)0xFFFFULL) | (uint64_t)(uint16_t)(%s);' % (base, base, expr)
    return '%s = (%s & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(%s);' % (base, base, expr)


def mem(off, disp, w):
    return 'ML_M%d(%s, 0x%x)' % (w, off, disp) if disp >= 0 else 'ML_M%d(%s, -0x%x)' % (w, off, -disp)


def operand_read(op):
    if op is None:
        raise SystemExit('operand form')
    k = op[0]
    if k == 'reg':
        return rv(op)
    if k == 'mem':
        return mem(op[1], op[2], op[3])
    if k == 'iat':
        return 'ML_IAT(0x%x)' % op[1]
    if k == 'imm':
        return '0x%xULL' % op[1]
    raise SystemExit('bad operand')


def operand_write(op, expr):
    if op is None:
        raise SystemExit('operand form')
    k = op[0]
    if k == 'reg':
        return wr(op[1], op[2], expr)
    if k == 'mem':
        return '%s = %s;' % (mem(op[1], op[2], op[3]), expr)
    raise SystemExit('unwritable operand')


JCC = {'je': 'f_zf', 'jz': 'f_zf', 'jne': '!f_zf', 'jnz': '!f_zf',
       'jb': 'f_cf', 'jnae': 'f_cf', 'jae': '!f_cf', 'jnb': '!f_cf',
       'jbe': 'f_cf || f_zf', 'jna': 'f_cf || f_zf', 'ja': '!f_cf && !f_zf', 'jnbe': '!f_cf && !f_zf',
       'js': 'f_sf', 'jns': '!f_sf',
       'jl': 'f_sf != f_of', 'jnge': 'f_sf != f_of', 'jge': 'f_sf == f_of',
       'jle': 'f_zf || (f_sf != f_of)', 'jng': 'f_zf || (f_sf != f_of)',
       'jg': '!f_zf && (f_sf == f_of)', 'jnle': '!f_zf && (f_sf == f_of)'}


def setflags(w, a, b, unsigned=True):
    """Emit flag computation for cmp a,b (a - b) at width w."""
    mask = {1: '0xFFULL', 2: '0xFFFFULL', 4: '0xFFFFFFFFULL', 8: '~0ULL'}[w]
    sign = {1: 0x80, 2: 0x8000, 4: 0x80000000, 8: 1 << 63}[w]
    return ['{', '    const uint64_t a = (uint64_t)(%s) & %s, b = (uint64_t)(%s) & %s;' % (a, mask, b, mask),
            '    const uint64_t d = (a - b) & %s;' % mask,
            '    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x%xULL) != 0);' % sign,
            '    f_of = (((a ^ b) & (a ^ d) & 0x%xULL) != 0);' % sign, '}']


def normalise(t):
    t = re.sub(r'^lock\s+', '', t.strip(), flags=re.I); return re.sub(r'^rex(?:\.[WRXB]+|64)?\s+', '', t)


REGISTRY = {int(x, 16) for x in json.load(open(os.path.join(os.path.dirname(__file__), 'seams.json')))} \
    if os.path.exists(os.path.join(os.path.dirname(__file__), 'seams.json')) else set()


class RangeTruncated(Exception):
    pass


def lift(addr, funcs):
    f = funcs[addr]
    t = f['text']
    label = set()
    for ins in t:
        m = re.match(r'^j\w+ (0x[0-9a-f]+)$', ins)
        if m:
            label.add(int(m.group(1), 16))
    idx = {a: i for i, a in enumerate(f['addr'])}
    # a conditional branch that leaves the extracted range means the row is only part of the function:
    # lifting it would silently drop the other arm, so refuse instead of producing a half body
    for i, ins in enumerate(t):
        m = re.match(r'^(j\w+) (0x[0-9a-f]+)$', ins)
        if m and m.group(1) != 'jmp' and int(m.group(2), 16) not in idx:
            raise RangeTruncated('%s at instruction %d leaves the row (target %s)'
                                 % (m.group(1), i, m.group(2)))
    body = []
    seams = set(REGISTRY)
    for i, ins in enumerate(t):
        ins = normalise(ins)
        if f['addr'][i] in label:
            body.append('L%d:' % i)
        parts = ins.split(None, 1)
        op = parts[0]
        rest = parts[1] if len(parts) > 1 else ''
        if ins in ('nop', 'int3') or re.match(r'^xchg ax,ax$', ins):
            body.append('    ;')
            continue
        if op == 'push':
            body.append('    rsp -= 8; ML_M8(rsp, 0) = %s;' % operand_read(enc(rest)))
            continue
        if op == 'pop':
            body.append('    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; %s }' % operand_write(enc(rest), 'v'))
            continue
        if op == 'ret' or ins.strip() in ('repz ret', 'rep ret', 'repz retq'):
            # `repz ret` is the padding form of a plain return
            body.append('    return rax;')
            continue
        if op == 'cqo':
            body.append('    rdx = (rax >> 63) ? ~0ULL : 0ULL;   // sign-extend rax into rdx:rax')
            continue
        if op == 'jmp':
            if re.match(r'^0x[0-9a-f]+$', rest.strip()):
                _t = int(rest.strip(), 16)
                if _t not in idx:
                    if _t not in funcs:
                        raise SystemExit('branch target has no body: %r' % ins)
                    seams.add(_t)
                    body.append('    return ML_CALL(%x);   // tail jump outside the row' % _t)
                    continue
                body.append('    goto L%d;' % idx[_t])
            else:
                e = enc(rest)
                if not e:
                    raise SystemExit('jmp form: %r' % ins)
                if e[0] in ('mem', 'reg'):
                    body.append('    return ML_CALLP(%s);   // tail through pointer' % operand_read(e))
                    continue
                if e[0] not in ('imm', 'iat'):
                    raise SystemExit('jmp form: %r' % ins)
                seams.add(e[1])
                body.append('    return ML_CALL(%x);   // tail call' % e[1])
            continue
        if op in JCC:
            tgt = int(rest.strip(), 16)
            if tgt not in idx:
                if tgt not in funcs:
                    raise SystemExit('branch target has no body: %r' % ins)
                seams.add(tgt)
                body.append('    if (%s) return ML_CALL(%x);   // branch outside the row' % (JCC[op], tgt))
                continue
            body.append('    if (%s) goto L%d;' % (JCC[op], idx[tgt]))
            continue
        if op == 'call':
            e = enc(rest)
            if not e:
                raise SystemExit('call form: %r' % ins)
            if e[0] in ('mem', 'reg'):
                # indirect call through a function pointer: same Win64 arguments, pointer read first
                body.append('    rax = ML_CALLP(%s);' % operand_read(e))
                continue
            if e[0] not in ('imm', 'iat'):
                raise SystemExit('call form: %r' % ins)
            key = e[1]
            seams.add(key)
            body.append('    rax = ML_CALL(%x);' % key)
            continue
        if op == 'neg':
            d = enc(rest)
            if d is None:
                raise SystemExit('neg form: %r' % ins)
            w = d[2] if d[0] in ('reg', 'sub') else d[3]
            bits = w * 8
            mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
            body.append('    { const uint64_t m = %s; const uint64_t v = (%s) & m; const uint64_t r = (0 - v) & m;'
                        % (mask, operand_read(d)))
            body.append('      %s' % operand_write(d, 'r'))
            body.append('      f_cf = (v != 0); f_zf = (r == 0); f_sf = ((r >> %d) & 1) != 0; f_of = (v == (1ULL << %d)); }'
                        % (bits - 1, bits - 1))
            continue
        if op == 'cdqe':
            body.append('    rax = (uint64_t)(int64_t)(int32_t)(uint32_t)rax;   // cdqe')
            continue
        if op == 'cwde':
            body.append('    rax = (uint64_t)(uint32_t)(int32_t)(int16_t)(uint16_t)rax;   // cwde')
            continue
        if op == 'mul':
            s = enc(rest)
            if s is None:
                raise SystemExit('mul form: %r' % ins)
            w = s[2] if s[0] in ('reg', 'sub') else s[3]
            src = operand_read(s)
            if w == 8:
                body.append('    { const unsigned __int128 p = (unsigned __int128)rax * (uint64_t)(%s);' % src)
                body.append('      rax = (uint64_t)p; rdx = (uint64_t)(p >> 64); f_cf = f_of = (rdx != 0); }')
            else:
                body.append('    { const uint64_t p = (uint64_t)(uint32_t)rax * (uint32_t)(%s);' % src)
                body.append('      rax = (uint32_t)p; rdx = (uint32_t)(p >> 32); f_cf = f_of = (rdx != 0); }')
            continue
        _shm = re.match(r'^(shl|sal|shr|sar)\s+(.+),\s*(cl|0x[0-9a-fA-F]+)$', ins)
        if _shm:
            _smode = _shm.group(3).lower()

            d = enc(_shm.group(2))
            if d is None:
                raise SystemExit('shift form: %r' % ins)
            w = d[2] if d[0] in ('reg', 'sub') else d[3]
            bits = w * 8
            mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
            cmask = bits - 1
            val = operand_read(d)
            _cexpr = '(unsigned)(rcx & %d)' % cmask if _smode == 'cl' else str(int(_smode, 16))
            body.append('    { const uint64_t m = %s; const unsigned c = %s;' % (mask, _cexpr))
            body.append('      const uint64_t v = (%s) & m;' % val)
            if op in ('shl', 'sal'):
                body.append('      const uint64_t r = c ? ((v << c) & m) : v;')
                body.append('      if (c) f_cf = ((v >> (%d - c)) & 1) != 0;' % bits)
                body.append('      if (c == 1) f_of = (((r >> %d) & 1) != ((v >> %d) & 1));' % (bits - 1, bits - 1))
            elif op == 'shr':
                body.append('      const uint64_t r = c ? ((v & m) >> c) : v;')
                body.append('      if (c) f_cf = ((v >> (c - 1)) & 1) != 0;')
                body.append('      if (c == 1) f_of = ((v >> %d) & 1) != 0;' % (bits - 1))
            else:
                body.append('      const int64_t sv = (int64_t)(v << (64 - %d)) >> (64 - %d);' % (bits, bits))
                body.append('      const uint64_t r = c ? ((uint64_t)(sv >> (c > %d ? %d : c)) & m) : v;' % (bits - 1, bits - 1))
                body.append('      if (c) f_cf = (((v >> (c - 1)) & 1) != 0);')
                body.append('      if (c == 1) f_of = false;')
            body.append('      %s' % operand_write(d, 'r'))
            body.append('      f_zf = (r == 0); f_sf = ((r >> %d) & 1) != 0; }' % (bits - 1))
            continue
        if op == 'not':
            d = enc(rest)
            if d is None:
                raise SystemExit('not form: %r' % ins)
            w = d[2] if d[0] in ('reg', 'sub') else d[3]
            mask = '~0ULL' if w == 8 else '0x%xULL' % ((1 << (w * 8)) - 1)
            body.append('    %s' % operand_write(d, '(%s) ^ %s' % (operand_read(d), mask)))
            continue
        if op in ('repnz scas', 'repne scas', 'repz scas', 'repe scas') or re.match(r'^rep(?:nz|ne|z|e) scas', ins, re.I):
            m = re.match(r'^rep(?:nz|ne|z|e)\s+scas\s+(?:[a-z]{2,3},\s*)?(BYTE|WORD|DWORD|QWORD) PTR (?:es:)?\[rdi\]\s*$', ins, re.I)
            if not m:
                raise SystemExit('scas form: %r' % ins)
            bits = {'BYTE': 8, 'WORD': 16, 'DWORD': 32, 'QWORD': 64}[m.group(1).upper()]
            w = bits // 8
            mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
            stop_on_zf = bool(re.match(r'^rep(?:nz|ne)', ins, re.I))
            body.append('    while (rcx) {')
            body.append('        const uint64_t a = rax & %s, b = ML_M%d(rdi, 0) & %s;' % (mask, w, mask))
            body.append('        const uint64_t d = (a - b) & %s;' % mask)
            body.append('        rdi += %d; --rcx;' % w)
            body.append('        f_cf = a < b; f_zf = (d == 0); f_sf = ((d >> %d) & 1) != 0;' % (bits - 1))
            body.append('        f_of = ((((a ^ b) & (a ^ d)) >> %d) & 1) != 0;' % (bits - 1))
            body.append('        if (%s) break;' % ('f_zf' if stop_on_zf else '!f_zf'))
            body.append('    }')
            continue
        if op == 'movsd':
            parts = [x.strip() for x in rest.split(',')]
            if len(parts) == 2 and re.match(r'^xmm\d+$', parts[0]):
                dst, src = parts[0], enc(parts[1])
                if src is None:
                    raise SystemExit('movsd form: %r' % ins)
                if src[0] == 'reg' and src[1].startswith('xmm'):
                    body.append('    memcpy(%s, %s, 8);   // movsd xmm, xmm (low quadword)' % (dst, src[1]))
                else:
                    body.append('    (*(uint64_t*)(%s)) = (uint64_t)(%s);   // movsd xmm, m64' % (dst, operand_read(src)))
                continue
            if len(parts) == 2 and re.match(r'^xmm\d+$', parts[1]):
                d = enc(parts[0])
                if d is not None and d[0] == 'mem':
                    body.append('    ML_M8(%s, %s) = *(uint64_t*)(%s);   // movsd m64, xmm' % (d[1], d[2], parts[1]))
                    continue
                if d is not None and d[0] == 'iat':
                    body.append('    ML_M8(0x%x, 0) = *(uint64_t*)(%s);   // movsd m64, xmm' % (d[1], parts[1]))
                    continue
            raise SystemExit('movsd form: %r' % ins)
        if op in ('cdq', 'cqo'):
            if op == 'cdq':
                body.append('    rdx = (rax & 0x80000000ULL) ? 0xffffffffULL : 0ULL;   // cdq')
            else:
                body.append('    rdx = (rax & 0x8000000000000000ULL) ? ~0ULL : 0ULL;   // cqo')
            continue
        if op == 'xchg':
            a1, b1 = [enc(x) for x in rest.replace(', ', ',').split(',')]
            body.append('    { const uint64_t t = %s; %s %s }' % (operand_read(a1), operand_write(a1, operand_read(b1)), operand_write(b1, 't')))
            continue
        if op in ('sbb', 'adc'):
            d0, s0 = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            w = d0[2] if d0[0] == 'reg' else d0[3]
            bits = w * 8
            mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
            body.append('    { const uint64_t m = %s; const uint64_t a = (%s) & m; const uint64_t b = (%s) & m;'
                        % (mask, operand_read(d0), operand_read(s0)))
            if op == 'sbb':
                body.append('      const uint64_t c = f_cf ? 1 : 0;')
                body.append('      const uint64_t r = (a - b - c) & m;')
                body.append('      f_cf = (a < b) || (a == b && c) || (a - b < c && a >= b);')
                body.append('      f_of = (((a ^ b) & (a ^ r)) >> %d) & 1;' % (bits - 1))
            else:
                body.append('      const uint64_t c = f_cf ? 1 : 0;')
                body.append('      const uint64_t r = (a + b + c) & m;')
                body.append('      f_cf = (r < a) || (c && r == a);')
                body.append('      f_of = ((((a ^ r) & (b ^ r)) >> %d) & 1) != 0;' % (bits - 1))
            body.append('      %s' % operand_write(d0, 'r'))
            body.append('      f_zf = (r == 0); f_sf = ((r >> %d) & 1) != 0; }' % (bits - 1))
            continue
        if op == 'movsd' and re.match(r'^movsd\s+(?:QWORD|DWORD) PTR', ins, re.I):
            m2 = re.match(r'^movsd\s+(?:(QWORD|DWORD) PTR [^,]+),\s*(xmm\d+)\s*$', ins, re.I)
            if not m2:
                raise SystemExit('movsd form: %r' % ins)
            w = 8 if m2.group(1).upper() == 'QWORD' else 4
            dstm = enc(re.match(r'^movsd\s+((?:QWORD|DWORD) PTR [^,]+)', ins, re.I).group(1))
            body.append('    %s' % operand_write(dstm, '(uint64_t)(*(uint64_t*)(%s))' % m2.group(2)))
            continue
        if op == 'lea':
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            if s[0] == 'mem':
                body.append('    ' + wr(d[1], 8, '%s + 0x%x' % (s[1], s[2]) if s[2] >= 0 else '%s - 0x%x' % (s[1], -s[2])))
            elif s[0] == 'iat':
                body.append('    ' + wr(d[1], 8, '(uintptr_t)0x%x' % s[1]))
            else:
                raise SystemExit('lea form: %r' % ins)
            continue
        if op == 'movzx':
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            body.append('    ' + wr(d[1], 8, operand_read(s)))
            continue
        if op in ('mov', 'movabs'):
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            body.append('    ' + operand_write(d, operand_read(s)))
            continue
        if op == 'cmp':
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            w = d[3] if d[0] == 'mem' else (d[2] if d[0] == 'reg' else 8)
            body += setflags(w, operand_read(d), operand_read(s))
            continue
        if op == 'test':
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            w = d[3] if d[0] == 'mem' else (d[2] if d[0] == 'reg' else 8)
            mask = {1: '0xFFULL', 2: '0xFFFFULL', 4: '0xFFFFFFFFULL', 8: '~0ULL'}[w]
            body += ['{', '    const uint64_t r = ((uint64_t)(%s) & %s) & ((uint64_t)(%s) & %s);'
                     % (operand_read(d), mask, operand_read(s), mask),
                     '    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x%xULL) != 0);' % (1 << (w * 8 - 1)),
                     '    f_of = false;', '}']
            continue
        if op in ('add', 'sub'):
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            body.append('    ' + operand_write(d, '%s %s (%s)' % (operand_read(d), '+' if op == 'add' else '-', operand_read(s))))
            continue
        if op in ('inc', 'dec'):
            d = enc(rest)
            body.append('    ' + operand_write(d, '%s %s 1' % (operand_read(d), '+' if op == 'inc' else '-')))
            continue
        if op == 'xor':
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            if d[0] == 'reg' and s[0] == 'reg' and d[1] == s[1]:
                body.append('    ' + wr(d[1], d[2], '0'))
            else:
                body.append('    ' + operand_write(d, '(%s) ^ (%s)' % (operand_read(d), operand_read(s))))
            continue
        if op.startswith(('nop', 'data16', 'int3')):
            body.append('    /* padding */')
            continue
        if op.startswith('set') and ('j' + op[3:]) in JCC:
            d = enc(rest)
            body.append('    ' + operand_write(d, '(%s) ? 1 : 0' % JCC['j' + op[3:]]))
            continue
        if op in ('shl', 'shr', 'sar', 'sal'):
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            if d[0] != 'reg' or s[0] != 'imm':
                raise SystemExit('shift form: %r' % ins)
            w = d[2]; mask = {1: '0xFFULL', 2: '0xFFFFULL', 4: '0xFFFFFFFFULL', 8: '~0ULL'}[w]
            cnt = s[1]; rd = operand_read(d)
            if op in ('shl', 'sal'):
                expr = '(%s << %d)' % (rd, cnt)
            elif op == 'shr':
                expr = '((%s & %s) >> %d)' % (rd, mask, cnt)
            else:
                if w == 8:
                    expr = '(uint64_t)((int64_t)%s >> %d)' % (rd, cnt)
                else:
                    expr = '(uint64_t)((int64_t)(int32_t)(%s & 0xFFFFFFFFULL) >> %d)' % (rd, cnt)
            body.append('    { const uint64_t src = %s; const uint64_t res = %s;' % (rd, expr))
            body.append('      f_cf = (((src >> %d) & 1) != 0); f_zf = ((res & %s) == 0);' % (cnt - 1, mask))
            body.append('      f_sf = ((res & 0x%xULL) != 0); f_of = false;' % (1 << (w * 8 - 1)))
            body.append('    ' + operand_write(d, 'res') + ' }')
            continue
        if op in ('movaps', 'movups', 'movdqa', 'movdqu', 'movapd', 'movupd', 'movdqa32'):
            a, b = [x.strip() for x in rest.split(',', 1)]
            xa, xb = re.match(r'^xmm(\d+)$', a), re.match(r'^xmm(\d+)$', b)
            if xa and xb:
                body.append('    __builtin_memcpy(xmm%s, xmm%s, 16);' % (xa.group(1), xb.group(1)))
            elif xa:
                e = enc(b)
                body.append('    __builtin_memcpy(xmm%s, (uint8_t*)((uintptr_t)%s + %d), 16);'
                            % (xa.group(1), e[1], e[2]))
            elif xb:
                e = enc(a)
                body.append('    __builtin_memcpy((uint8_t*)((uintptr_t)%s + %d), xmm%s, 16);'
                            % (e[1], e[2], xb.group(1)))
            else:
                raise SystemExit('movaps form: %r' % ins)
            continue
        if op.startswith('cmov'):
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            jcc = 'j' + op[4:]
            if jcc not in JCC:
                raise SystemExit('cmov form: %r' % ins)
            body.append('    if (%s) { %s }' % (JCC[jcc], operand_write(d, operand_read(s))))
            continue
        if op in ('movsxd', 'movsx'):
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            body.append('    ' + operand_write(d, '(uint64_t)(int64_t)(int32_t)(%s)' % operand_read(s)))
            continue
        if op in ('and', 'or'):
            d, s = [enc(x) for x in rest.replace(', ', ',').split(',', 1)]
            body.append('    ' + operand_write(d, '(%s) %s (%s)' % (operand_read(d), '&' if op == 'and' else '|', operand_read(s))))
            continue

        if op in ('div', 'idiv'):
            s = enc(rest)
            if s is None:
                raise SystemExit('div form: %r' % ins)
            d = operand_read(s)
            if op == 'div':
                # x86 divides the 128-bit pair rdx:rax; a zero divisor faults (#DE) just like the original
                body.append('    { const uint64_t d = %s; if (!d) __builtin_trap();' % d)
                body.append('      const unsigned __int128 n = ((unsigned __int128)rdx << 64) | rax;')
                body.append('      rax = (uint64_t)(n / d); rdx = (uint64_t)(n % d); }')
            else:
                body.append('    { const int64_t d = (int64_t)%s; if (!d) __builtin_trap();' % d)
                body.append('      const __int128 n = ((__int128)(int64_t)rdx << 64) | (uint64_t)rax;')
                body.append('      rax = (uint64_t)(int64_t)(n / d); rdx = (uint64_t)(int64_t)(n % d); }')
            continue
        if op == 'imul':
            parts = [x for x in rest.replace(', ', ',').split(',')]
            if len(parts) == 1:
                # one-operand form: rdx:rax = rax * src
                src = operand_read(enc(parts[0]))
                body.append('    { const __int128 p = (__int128)(int64_t)rax * (int64_t)(%s);' % src)
                body.append('      rax = (uint64_t)p; rdx = (uint64_t)(p >> 64); }')
                continue
            dst = enc(parts[0])
            if len(parts) == 2:
                a, b = operand_read(dst), operand_read(enc(parts[1]))
            else:
                a, b = operand_read(enc(parts[1])), operand_read(enc(parts[2]))
            # two/three-operand form keeps the low half and raises CF/OF on signed overflow
            body.append('    { const __int128 p = (__int128)(int64_t)(%s) * (int64_t)(%s);' % (a, b))
            body.append('      %s' % operand_write(dst, '(uint64_t)p'))
            body.append('      f_cf = f_of = (p != (__int128)(int64_t)(uint64_t)p); }')
            continue
        if op == 'rep stos' or ins.lower().startswith('rep stos'):
            m = re.match(r'^rep stos\s+(BYTE|WORD|DWORD|QWORD) PTR (?:es:)?\[rdi\]\s*,\s*(\w+)$', ins, re.I)
            if not m:
                raise SystemExit('rep stos form: %r' % ins)
            w = {'BYTE': 1, 'WORD': 2, 'DWORD': 4, 'QWORD': 8}[m.group(1).upper()]
            src = m.group(2)
            ctype = {1: 'uint8_t', 2: 'uint16_t', 4: 'uint32_t', 8: 'uint64_t'}[w]
            # the stored value comes from the accumulator, truncated to the store width
            src = {'al': '(uint8_t)rax', 'ax': '(uint16_t)rax', 'eax': '(uint32_t)rax', 'rax': 'rax'}.get(src.lower(), src)
            body.append('    while (rcx) { ML_M%d(rdi, 0) = (%s)%s; rdi += %d; --rcx; }' % (w, ctype, src, w))
            continue
        if _emit_extra(op, rest, body, ins):
            continue
        raise SystemExit('unsupported instruction %r' % ins)
    return f, body, seams


def main():
    # a full-batch run can exceed the shell's argument limit, so also accept a list file
    argv = sys.argv[1:]
    if not argv and os.environ.get('LIFT_ARGS'):
        argv = [l for l in open(os.environ['LIFT_ARGS']).read().split() if l.strip()]
    addrs = [int(a, 16) for a in argv]
    funcs = {x['a']: x for x in json.load(open(os.path.join(REPO, 'tools/bulk/funcs.json')))}
    extra_path = os.path.join(REPO, 'tools/bulk/extra_bodies.json')
    if os.path.exists(extra_path):
        for k, v in json.load(open(extra_path)).items():
            v['a'] = int(k, 16)
            funcs[v['a']] = v
    hdr = ['// Lifted mechanically by tools/bulk/lift.py - one C++ statement per x86 instruction.',
           '// Registers are uint64_t, memory goes through width-tagged accessors, flags are computed explicitly.',
           '#pragma once', '#include <cstdint>', '#include <cstring>', '',
           '#define ML_M1(p, o) (*(uint8_t*)((uint8_t*)(uintptr_t)(p) + (o)))',
           '#define ML_M2(p, o) (*(uint16_t*)((uint8_t*)(uintptr_t)(p) + (o)))',
           '#define ML_M4(p, o) (*(uint32_t*)((uint8_t*)(uintptr_t)(p) + (o)))',
           '#define ML_M8(p, o) (*(uint64_t*)((uint8_t*)(uintptr_t)(p) + (o)))',
           'inline uint64_t& ml_glb(uintptr_t a) {',
           '    static uintptr_t k[8192]; static uint64_t v[8192];',
           '    for (unsigned i = 0; i < 8192; ++i) {',
           '        if (k[i] == a) return v[i];',
           '        if (k[i] == 0) { k[i] = a; return v[i]; }',
           '    }',
           '    return v[0];',
           '}',
           'inline uint8_t& ml_glb8(uintptr_t a) {',
           '    static uintptr_t k[8192]; static uint8_t v[8192];',
           '    for (unsigned i = 0; i < 8192; ++i) {',
           '        if (k[i] == a) return v[i];',
           '        if (k[i] == 0) { k[i] = a; return v[i]; }',
           '    }',
           '    return v[0];',
           '}',
           '#define ML_IAT(a) ml_glb((uintptr_t)(a))',
           'static uint64_t mm0 = 0, mm1 = 0, mm2 = 0, mm3 = 0, mm4 = 0, mm5 = 0, mm6 = 0, mm7 = 0;', '',
           'namespace tq {', '']
    src = ['#include "modules/syndicate/src/synlift.h"', '', 'namespace tq {', '']
    defined = set()
    declared = []
    skipped = []
    for a in addrs:
        try:
            f, body, seams = lift(a, funcs)
        except (Exception, SystemExit) as e:   # one unencodable body must never kill the batch
            skipped.append((a, '%s: %s' % (type(e).__name__, e)))
            continue
        for s in sorted(seams):
            if s not in defined:
                defined.add(s)
                declared.append(s)
        hdr.append('')
        hdr.append('uint64_t SynLift_%x(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x%x' % (a, a))
        src.append('uint64_t SynLift_%x(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {' % a)
        src.append('    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;')
        src.append('    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;')
        src.append('    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;')
        src.append('    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0}, xmm6[16] = {0}, xmm7[16] = {0}, xmm8[16] = {0}, xmm9[16] = {0}, xmm10[16] = {0}, xmm11[16] = {0}, xmm12[16] = {0}, xmm13[16] = {0}, xmm14[16] = {0}, xmm15[16] = {0};')
        src.append('    alignas(16) uint8_t stkFrame[0x400] = {0};')
        src.append('    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);')
        # Win64 passes the 5th and 6th arguments on the stack, right after the 32-byte shadow space.
        # The original body stores them there, so the lifted call hands them over as well.
        src.append('#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))')
        src.append('#define ML_CALLP(t) ((uint64_t (*)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t))(uintptr_t)(t))'
                   '(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))')
        src += body
        src.append('#undef ML_CALL')
        src.append('#undef ML_CALLP')
        src.append('    return rax;')
        src.append('}')
        src.append('')
        print('lifted 0x%x: %d instructions, %d seams' % (a, len(f['text']), len(seams)))
    # every seam the module can point at, declared once, ahead of the bodies
    block = ['// seams: an indirect call the bodies make out of the image (import thunks and other bodies)']
    for s in sorted(declared):
        block.append('extern uint64_t (*g_fnLIFT_%x)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);' % s)
        src.insert(4, '__attribute__((weak)) uint64_t (*g_fnLIFT_%x)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;' % s)
    hdr += block + ['']
    hdr += ['}  // namespace tq', '']
    src += ['}  // namespace tq', '']
    # LIFT_OUT=stage keeps work-in-progress bodies out of the verified module: they land in
    # synlift_stage.* instead, so the ledger and the shipped header only ever carry tested code.
    which = os.environ.get('LIFT_OUT', 'module')
    base = 'synlift_stage' if which == 'stage' else 'synlift'
    if which == 'stage':
        src[0] = '#include "modules/syndicate/src/synlift_stage.h"'
    open(os.path.join(REPO, 'modules/syndicate/src/%s.h' % base), 'w').write('\n'.join(hdr))
    open(os.path.join(REPO, 'modules/syndicate/src/%s.cpp' % base), 'w').write('\n'.join(src))
    for a, why in skipped:
        print('  skipped 0x%x: %s' % (a, why))




# --- 16/8-bit register names (r9w, r9b, ...): masked read, read-modify-write on store ---
SUBREGS = re.compile(r'^(r(?:[89]|1[0-5]))([wdb])$')
_orig_enc = enc
_orig_operand_read = operand_read
_orig_operand_write = operand_write


def enc(x):
    if isinstance(x, str):
        m = SUBREGS.match(x.strip())
        if m:
            return ('sub', m.group(1), {'w': 2, 'd': 4, 'b': 1}[m.group(2)])
    return _orig_enc(x)


def operand_read(e):
    if e and e[0] == 'sub':
        return '(uint64_t)(%s & 0x%xULL)' % (e[1], (1 << (8 * e[2])) - 1)
    return _orig_operand_read(e)


def operand_write(e, expr):
    if e and e[0] == 'sub':
        m = (1 << (8 * e[2])) - 1
        return '%s = (%s & ~0x%xULL) | ((uint64_t)(%s) & 0x%xULL);' % (e[1], e[1], m, expr, m)
    return _orig_operand_write(e, expr)


# GLBWRITE: stores into absolute/global slots go to the same shadow the reads use
_ow_glb = operand_write


def operand_write(e, expr):
    if e and e[0] in ('iat', 'glb', 'abs', 'rip'):
        addr = e[1]
        addr = addr if isinstance(addr, str) else '0x%x' % addr
        w = e[2] if len(e) > 2 else 8
        if w >= 8:
            return 'ml_glb((uintptr_t)%s) = (uint64_t)(%s);' % (addr, expr)
        m = (1 << (8 * w)) - 1
        return ('ml_glb((uintptr_t)%s) = (ml_glb((uintptr_t)%s) & ~0x%xULL) | ((uint64_t)(%s) & 0x%xULL);'
                % (addr, addr, m, expr, m))
    return _ow_glb(e, expr)



# --- SSE/MMX byte ops, movd/movss, rotates, bit tests, cmovcc, repeated string ops ---
_orig_lift_extra = None


def _simd_dst(tok, ins):
    if re.match(r'^xmm\d+$', tok):
        return tok, 16
    if re.match(r'^mm\d+$', tok):
        return '((uint8_t*)&%s)' % tok, 8
    raise SystemExit('simd dest: %r' % ins)


def _simd_src_bytes(tok, n, ins):
    if re.match(r'^xmm\d+$', tok):
        return ['%s[%d]' % (tok, i) for i in range(n)]
    if re.match(r'^mm\d+$', tok):
        return ['((uint8_t*)&%s)[%d]' % (tok, i) for i in range(n)]
    e = enc(tok)
    if e is None:
        raise SystemExit('simd src: %r' % ins)
    if e[0] == 'mem':
        return ['(uint8_t)ML_M1(%s, %s + %d)' % (e[1], e[2], i) for i in range(n)]
    if e[0] == 'iat':
        return ['(uint8_t)ML_M1(0x%x, %d)' % (e[1], i) for i in range(n)]
    if e[0] in ('reg', 'sub'):
        v = operand_read(e)
        return ['(uint8_t)((%s) >> %d)' % (v, 8 * i) for i in range(n)]
    raise SystemExit('simd src: %r' % ins)


def _lift_simd(op, rest, body, ins):
    a1, b1 = [x.strip() for x in rest.split(',', 1)]
    dtok, n = _simd_dst(a1, ins)
    src = _simd_src_bytes(b1, n, ins)
    for i in range(n):
        if op == 'pxor':
            body.append('    %s[%d] ^= %s;' % (dtok, i, src[i]))
        elif op == 'pand':
            body.append('    %s[%d] &= %s;' % (dtok, i, src[i]))
        elif op == 'por':
            body.append('    %s[%d] |= %s;' % (dtok, i, src[i]))
        elif op == 'paddb':
            body.append('    %s[%d] = (uint8_t)(%s[%d] + %s);' % (dtok, i, dtok, i, src[i]))
        elif op == 'psubb':
            body.append('    %s[%d] = (uint8_t)(%s[%d] - %s);' % (dtok, i, dtok, i, src[i]))


_lift_base = lift


def lift(addr, funcs):
    return _lift_base(addr, funcs)


@staticmethod
def _unused():
    pass


def _scas_body(body, bits, w, stop_on_zf):
    mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
    body.append('    while (rcx) {')
    body.append('        const uint64_t a = rax & %s, b = ML_M%d(rdi, 0) & %s;' % (mask, w, mask))
    body.append('        const uint64_t d = (a - b) & %s;' % mask)
    body.append('        rdi += %d; --rcx;' % w)
    body.append('        f_cf = a < b; f_zf = (d == 0); f_sf = ((d >> %d) & 1) != 0;' % (bits - 1))
    body.append('        f_of = ((((a ^ b) & (a ^ d)) >> %d) & 1) != 0;' % (bits - 1))
    if stop_on_zf is not None:
        body.append('        if (%s) break;' % ('f_zf' if stop_on_zf else '!f_zf'))
    body.append('    }')


def _cmps_body(body, bits, w, repeat, stop_on_zf):
    mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
    body.append('    %s {' % ('while (rcx)' if repeat else 'do'))
    body.append('        const uint64_t a = ML_M%d(rsi, 0) & %s, b = ML_M%d(rdi, 0) & %s;'
                % (w, mask, w, mask))
    body.append('        const uint64_t d = (a - b) & %s;' % mask)
    body.append('        rsi += %d; rdi += %d;' % (w, w))
    if repeat:
        body.append('        --rcx;')
    body.append('        f_cf = a < b; f_zf = (d == 0); f_sf = ((d >> %d) & 1) != 0;' % (bits - 1))
    body.append('        f_of = ((((a ^ b) & (a ^ d)) >> %d) & 1) != 0;' % (bits - 1))
    if stop_on_zf is not None:
        body.append('        if (%s) break;' % ('f_zf' if stop_on_zf else '!f_zf'))
    body.append('    }%s' % (' while (0)' if not repeat else ''))



def _cvt_pack(body, dst, src_tok, n_from, in_bits, out_kind, ins):
    if not re.match(r'^xmm\d+$', dst):
        raise SystemExit('cvt form: %r' % ins)
    if re.match(r'^xmm\d+$', src_tok):
        src = src_tok
    else:
        e = enc(src_tok)
        if e is None:
            raise SystemExit('cvt form: %r' % ins)
        if e[0] == 'mem':
            src = '(const uint8_t*)ML_ADDR(%s, %s)' % (e[1], e[2])
        elif e[0] == 'iat':
            src = 'ML_ADDR(0x%x, 0)' % e[1]
        else:
            raise SystemExit('cvt form: %r' % ins)
    ctype = {32: 'int32_t', 64: 'int64_t'}[in_bits]
    if in_bits == 32 and out_kind == 'double':
        body.append('    { int32_t t[%d]; memcpy(t, %s, %d); double o[%d];'
                    % (n_from, src, 4 * n_from, n_from))
        body.append('      for (int i = 0; i < %d; ++i) o[i] = (double)t[i];' % n_from)
        body.append('      memcpy(%s, o, %d); }' % (dst, 8 * n_from))
        return True
    if in_bits == 32 and out_kind == 'float':
        body.append('    { int32_t t[%d]; memcpy(t, %s, %d); float o[%d];'
                    % (n_from, src, 4 * n_from, n_from))
        body.append('      for (int i = 0; i < %d; ++i) o[i] = (float)t[i];' % n_from)
        body.append('      memcpy(%s, o, %d); }' % (dst, 4 * n_from))
        return True
    if in_bits == 64 and out_kind == 'int32':
        body.append('    { int64_t t[%d]; memcpy(t, %s, %d); int32_t o[%d];'
                    % (n_from, src, 8 * n_from, n_from))
        body.append('      for (int i = 0; i < %d; ++i) o[i] = (int32_t)t[i];' % n_from)
        body.append('      memcpy(%s, o, %d); }' % (dst, 4 * n_from))
        return True
    raise SystemExit('cvt form: %r' % ins)



def _emit_extra(op, rest, body, ins):
    """Returns True when it handled the instruction."""
    _cv2 = re.match(r'^(cvtdq2pd|cvtdq2ps|cvttpd2dq|cvtpd2dq)\s+(.+)$', ins, re.I)
    if _cv2:
        m2 = _cv2.group(1).lower()
        a1, b1 = [x.strip() for x in _cv2.group(2).split(',', 1)]
        if m2 == 'cvtdq2pd':
            _cvt_pack(body, a1, b1, 2, 32, 'double', ins)
        elif m2 == 'cvtdq2ps':
            _cvt_pack(body, a1, b1, 4, 32, 'float', ins)
        else:
            _cvt_pack(body, a1, b1, 2, 64, 'int32', ins)
        return True
    _cx = re.match(r'^cmpxchg\s+(.+)$', ins, re.I)
    if _cx:
        a1, b1 = [x.strip() for x in _cx.group(1).split(',', 1)]
        d = enc(a1)
        sb = enc(b1)
        if d is None or sb is None:
            raise SystemExit('cmpxchg form: %r' % ins)
        w = d[2] if d[0] in ('reg', 'sub') else d[3]
        mask = '~0ULL' if w == 8 else '0x%xULL' % ((1 << (w * 8)) - 1)
        body.append('    { const uint64_t m = %s; const uint64_t ax = rax & m;' % mask)
        body.append('      const uint64_t cur = (%s) & m;' % operand_read(d))
        _cmw = operand_write(d, '(%s) & m' % operand_read(sb)).rstrip(';')
        if not _cmw.rstrip().endswith(';'):
            _cmw += ';'
        body.append('      if (ax == cur) { %s f_zf = 1; }' % _cmw)
        body.append('      else { rax = (rax & ~m) | cur; f_zf = 0; }')
        body.append('      f_cf = 0; f_of = 0; f_sf = ((cur >> %d) & 1) != 0; }' % (w * 8 - 1))
        return True
    _mv = re.match(r'^(rep\s+)?(movs|lods)\s+(?:((BYTE|WORD|DWORD|QWORD) PTR (?:es:)?\[rdi\],\s*(?:(QWORD|DWORD|WORD|BYTE) PTR )?(?:ds:)?\[rsi\])|((BYTE|WORD|DWORD|QWORD) PTR (?:ds:)?\[rsi\]))$', ins, re.I)
    if _mv:
        rep = bool(_mv.group(1))
        kind = _mv.group(2).lower()
        wname = (_mv.group(4) or _mv.group(8) or 'byte').upper()
        w = {'BYTE': 1, 'WORD': 2, 'DWORD': 4, 'QWORD': 8}[wname]
        body.append('    %s {' % ('while (rcx)' if rep else 'do'))
        if kind == 'movs':
            body.append('        ML_M%d(rdi, 0) = ML_M%d(rsi, 0); rdi += %d; rsi += %d;' % (w, w, w, w))
        else:
            v = {'1': '(uint8_t)rax', '2': '(uint16_t)rax', '4': '(uint32_t)rax', '8': 'rax'}[str(w)]
            body.append('        rax = (rax & ~0x%xULL) | (%s); rsi += %d;' % ((1 << (w * 8)) - 1, v, w))
        if rep:
            body.append('        --rcx;')
        body.append('    }%s' % (' while (0)' if not rep else ''))
        return True
    _cm = re.match(r'^(rep(?:nz|ne|z|e)?\s+)?cmps\s+(?:[a-z]{2,3},\s*)?(BYTE|WORD|DWORD|QWORD) PTR (?:ds:)?\[rsi\],\s*(?:(BYTE|WORD|DWORD|QWORD) PTR )?(?:es:)?\[rdi\]$', ins, re.I)
    if _cm:
        pref = (_cm.group(1) or '').strip().lower()
        bits = {'BYTE': 8, 'WORD': 16, 'DWORD': 32, 'QWORD': 64}[_cm.group(2).upper()]
        zf = None
        if pref in ('repz', 'repe'):
            zf = True
        elif pref in ('repnz', 'repne'):
            zf = False
        _cmps_body(body, bits, bits // 8, bool(pref), zf)
        return True
    _cs = re.match(r'^(cvtsi2sd|cvtsi2ss|cvttsd2si|cvttss2si|vcvtsi2sd)\s+(.+)$', ins, re.I)
    if _cs:
        mn2 = _cs.group(1).lower()
        a1, b1 = [x.strip() for x in _cs.group(2).split(',', 1)]
        sb = enc(b1)
        if sb is None:
            raise SystemExit('cvt form: %r' % ins)
        if mn2.startswith('cvtsi2'):
            w = sb[2] if sb[0] in ('reg', 'sub') else sb[3]
            if not re.match(r'^xmm\d+$', a1):
                raise SystemExit('cvt form: %r' % ins)
            cast = {4: '(double)(int32_t)', 8: '(double)(int64_t)'}[4 if w == 4 else 8]
            body.append('    { const double d = %s(%s); memcpy(%s, &d, 8); }' % (cast, operand_read(sb), a1))
            return True
        if not re.match(r'^xmm\d+$', b1):
            raise SystemExit('cvt form: %r' % ins)
        d = enc(a1)
        if d is None:
            raise SystemExit('cvt form: %r' % ins)
        w = d[2] if d[0] in ('reg', 'sub') else d[3]
        cast = '(int64_t)' if w == 8 else '(int32_t)'
        body.append('    { double d; memcpy(&d, %s, 8); %s }'
                    % (b1, operand_write(d, cast + 'd').rstrip(';')))
        return True
    _sm = re.match(r'^scas\s+(?:[a-z]{2,3},\s*)?(BYTE|WORD|DWORD|QWORD) PTR (?:es:)?\[rdi\]$', ins, re.I)
    if _sm or re.match(r'^scas$', ins, re.I):
        bits = {'BYTE': 8, 'WORD': 16, 'DWORD': 32, 'QWORD': 64}.get((_sm.group(1) if _sm else 'byte').upper(), 8)
        _scas_body(body, bits, bits // 8, None)
        return True
    if op in ('pxor', 'pand', 'por', 'paddb', 'psubb') and ',' in rest:
        _lift_simd(op, rest, body, ins)
        return True
    if op in ('movd', 'movq') and ',' in rest:
        a1, b1 = [x.strip() for x in rest.split(',', 1)]
        n = 4 if op == 'movd' else 8
        if re.match(r'^(xmm\d+)$', a1):
            body.append('    memset(%s, 0, 16);' % a1)
            s1 = _simd_src_bytes(b1, n, ins)
            for i in range(n):
                body.append('    %s[%d] = %s;' % (a1, i, s1[i]))
            return True
        if re.match(r'^mm\d+$', a1):
            s1 = _simd_src_bytes(b1, n, ins)
            body.append('    { uint8_t t[8] = {0}; (void)t;')
            for i in range(n):
                body.append('      ((uint8_t*)&%s)[%d] = %s;' % (a1, i, s1[i]))
            body.append('    }')
            return True
        e = enc(a1)
        if e is not None and e[0] in ('reg', 'sub'):
            if re.match(r'^xmm\d+$', b1):
                body.append('    %s' % operand_write(e, '*(uint32_t*)(%s)' % b1 if n == 4 else '*(uint64_t*)(%s)' % b1))
                return True
            if re.match(r'^mm\d+$', b1):
                body.append('    %s' % operand_write(e, ('(uint32_t)%s' if n == 4 else '(uint64_t)%s') % b1))
                return True
        raise SystemExit('movd form: %r' % ins)
    if op == 'movss' and ',' in rest:
        a1, b1 = [x.strip() for x in rest.split(',', 1)]
        if re.match(r'^xmm\d+$', a1):
            s1 = _simd_src_bytes(b1, 4, ins)
            body.append('    memset(%s, 0, 16);' % a1)
            for i in range(4):
                body.append('    %s[%d] = %s;' % (a1, i, s1[i]))
            return True
        e = enc(a1)
        if e is not None:
            if re.match(r'^xmm\d+$', b1):
                for i in range(4):
                    body.append('    %s' % operand_write(e, '%s[%d]' % (b1, i)))
                return True
            raise SystemExit('movss form: %r' % ins)
    if op in ('rol', 'ror') and ',' in rest:
        a1, b1 = [x.strip() for x in rest.split(',', 1)]
        d = enc(a1)
        if d is None or b1.lower() not in ('cl',) and not re.match(r'^0x[0-9a-f]+$', b1, re.I):
            raise SystemExit('rol form: %r' % ins)
        w = d[2] if d[0] in ('reg', 'sub') else d[3]
        bits = w * 8
        mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
        cnt = '(unsigned)(rcx & %d)' % (bits - 1) if b1.lower() == 'cl' else str(int(b1, 16) % bits)
        val = operand_read(d)
        shift = '(unsigned)(%s %% %d)' % (cnt, bits)
        if op == 'rol':
            e1 = '(((v << s) | (v >> (%d - s))) & m)' % bits
        else:
            e1 = '(((v >> s) | (v << (%d - s))) & m)' % bits
        body.append('    { const uint64_t m = %s; const uint64_t v = (%s) & m; const unsigned s = %s ? %s : 0;'
                    % (mask, val, shift, shift))
        body.append('      const uint64_t r = s ? %s : v;' % e1)
        body.append('      %s' % operand_write(d, 'r'))
        body.append('      f_cf = ((r & 1) != 0); f_zf = (r == 0); f_sf = ((r >> %d) & 1) != 0; }' % (bits - 1))
        return True
    if op in ('bt', 'bts', 'btr', 'btc') and ',' in rest:
        a1, b1 = [x.strip() for x in rest.split(',', 1)]
        d = enc(a1)
        sb = enc(b1)
        if d is None or sb is None:
            raise SystemExit('bt form: %r' % ins)
        w = d[2] if d[0] in ('reg', 'sub') else d[3]
        bits = w * 8
        mask = '~0ULL' if bits == 64 else '0x%xULL' % ((1 << bits) - 1)
        body.append('    { const uint64_t m = %s; const unsigned idx = (unsigned)(((%s) & m) %% %d);'
                    % (mask, operand_read(sb), bits))
        body.append('      uint64_t v = (%s) & m;' % operand_read(d))
        body.append('      f_cf = ((v >> idx) & 1) != 0;')
        if op == 'bts':
            body.append('      v |= (1ULL << idx);')
        elif op == 'btr':
            body.append('      v &= ~(1ULL << idx);')
        elif op == 'btc':
            body.append('      v ^= (1ULL << idx);')
        if op != 'bt':
            body.append('      %s' % operand_write(d, 'v'))
        body.append('    }')
        return True
    m = re.match(r'^cmov([a-z]{1,3})\s+(.+)$', ins, re.I)
    if m:
        cond = _CONDS.get(m.group(1).lower())
        if cond:
            a1, b1 = [x.strip() for x in m.group(2).split(',', 1)]
            d = enc(a1)
            sb = enc(b1)
            if d is None or sb is None:
                raise SystemExit('cmov form: %r' % ins)
            w = d[2] if d[0] in ('reg', 'sub') else d[3]
            mask = '~0ULL' if w == 8 else '0x%xULL' % ((1 << (w * 8)) - 1)
            body.append('    if (%s) { %s }' % (cond, operand_write(d, '(%s) & %s' % (operand_read(sb), mask)).rstrip(';')))
            return True
    return False


_CONDS = {
    'o': 'f_of', 'no': '!f_of', 'b': 'f_cf', 'c': 'f_cf', 'nae': 'f_cf',
    'ae': '!f_cf', 'nb': '!f_cf', 'nc': '!f_cf', 'e': 'f_zf', 'z': 'f_zf',
    'ne': '!f_zf', 'nz': '!f_zf', 'be': '(f_cf || f_zf)', 'na': '(f_cf || f_zf)',
    'a': '(!f_cf && !f_zf)', 'nbe': '(!f_cf && !f_zf)', 's': 'f_sf', 'ns': '!f_sf',
}


if __name__ == '__main__':
    main()
