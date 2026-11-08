#!/usr/bin/env python3
"""Repair the two defects the audits found, using capstone as the authority.

The stored rows came from an earlier objdump pipeline that (a) dropped single-byte padding and
(b) recomputed rip-relative targets with its own instruction lengths. Both matter to the lift:
a dropped byte means a branch can target an address that no longer has a label, and a wrong
rip target means the body reads or writes the wrong global.

The repair never invents an instruction. Padding is re-inserted from capstone exactly as decoded,
and a rip target is replaced by instruction_address + instruction_size + displacement, which is
the definition of the addressing mode.
"""
import json
import os

import capstone

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE = 0x141721000
TEXT_OFF = 0x400

WIDTH = {1: 'BYTE', 2: 'WORD', 4: 'DWORD', 8: 'QWORD', 16: 'XMMWORD'}
PAD = ('nop', 'int3', 'xchg ax,ax', 'hlt')


def load(name):
    with open(os.path.join(BULK, name)) as fh:
        return json.load(fh)


def fmt(ins, for_lifter=True):
    """One instruction in the syntax lift.py parses."""
    ops = []
    for op in ins.operands:
        if op.type == capstone.x86.X86_OP_REG:
            ops.append(ins.reg_name(op.reg))
        elif op.type == capstone.x86.X86_OP_IMM:
            ops.append('0x%x' % (op.imm & 0xFFFFFFFFFFFFFFFF))
        elif op.type == capstone.x86.X86_OP_MEM:
            m = op.mem
            if m.base == capstone.x86.X86_REG_RIP:
                inner = 'rip@0x%x' % (ins.address + ins.size + m.disp)
            else:
                bits = []
                if m.base:
                    bits.append(ins.reg_name(m.base))
                if m.index:
                    scale = m.scale or 1
                    bits.append('%s*%d' % (ins.reg_name(m.index), scale) if scale != 1
                                else ins.reg_name(m.index))
                expr = '+'.join(bits) if bits else '0x0'
                if m.disp > 0:
                    expr += '+0x%x' % m.disp
                elif m.disp < 0:
                    expr += '-0x%x' % (-m.disp)
                inner = expr
            pre = WIDTH.get(op.size)
            ops.append(('%s PTR [%s]' % (pre, inner)) if pre else '[%s]' % inner)
        else:
            ops.append('?')
    txt = ins.mnemonic
    if ops:
        txt += ' ' + ', '.join(ops)
    return txt


def main():
    image = open(DLL, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    md.detail = True
    funcs = {x['a']: dict(x) for x in load('funcs.json')}
    for k, v in load('extra_bodies.json').items():
        v = dict(v, a=int(k, 16))
        funcs[v['a']] = v

    fixed = {}
    stats = {'inserted': 0, 'rip_fixed': 0, 'rows': 0, 'unexplained': []}
    for a in sorted(funcs):
        f = funcs[a]
        off = a - BASE + TEXT_OFF
        span = max(0, f['b'] - a)
        dec = list(md.disasm(image[off:off + span], a))
        by_addr = {ins.address: ins for ins in dec}
        text_of = dict(zip(f['addr'], f['text']))

        new_addr, new_text = [], []
        for ins in dec:
            if ins.address in text_of:
                txt = text_of[ins.address]
                if 'rip@0x' in txt:
                    want = ins.address + ins.size + ins.operands[-1].mem.disp \
                        if any(o.type == capstone.x86.X86_OP_MEM and o.mem.base == capstone.x86.X86_REG_RIP
                               for o in ins.operands) else None
                    if want is not None:
                        import re
                        txt = re.sub(r'rip@0x[0-9a-f]+', 'rip@0x%x' % want, txt)
                        if txt != text_of[ins.address]:
                            stats['rip_fixed'] += 1
            else:
                txt = fmt(ins)
                if not txt.split()[0] in PAD and txt.split()[0] not in ('nop', 'int3'):
                    stats['unexplained'].append((a, hex(ins.address), txt[:40]))
                stats['inserted'] += 1
            new_addr.append(ins.address)
            new_text.append(txt)
        # unreachable instructions cannot be reached except by a jump, and a jump lands on a
        # label: whatever sits between an unconditional transfer and the next label is data
        import re as _re
        labels = set()
        for t in new_text:
            for m in _re.finditer(r'\b(?:j\w+|call)\s+0x([0-9a-f]+)', t):
                labels.add(int(m.group(1), 16))
        keep_a, keep_t = [], []
        alive = True
        for x_a, x_t in zip(new_addr, new_text):
            if x_a in labels:
                alive = True
            if not alive:
                continue
            keep_a.append(x_a)
            keep_t.append(x_t)
            head = x_t.split()[0]
            if head in ('ret', 'jmp'):
                alive = False
        stats['pruned'] = stats.get('pruned', 0) + (len(new_addr) - len(keep_a))
        new_addr, new_text = keep_a, keep_t

        if new_addr != f['addr'] or any(new_text[i] != f['text'][i] if i < len(f['text']) else True
                                        for i in range(len(new_text))):
            fixed['0x%x' % a] = {'a': a, 'b': f['b'], 'addr': new_addr, 'text': new_text}
            stats['rows'] += 1

    json.dump(fixed, open(os.path.join(BULK, 'rows_fixed.json'), 'w'))
    print('rows rewritten:', stats['rows'], '| padding inserted:', stats['inserted'],
          '| rip targets corrected:', stats['rip_fixed'],
          '| unreachable slots pruned:', stats.get('pruned', 0))
    print('dropped instructions that are not padding:', len(stats['unexplained']))
    for r in stats['unexplained'][:8]:
        print('   0x%x at %s: %s' % r)


if __name__ == '__main__':
    main()
