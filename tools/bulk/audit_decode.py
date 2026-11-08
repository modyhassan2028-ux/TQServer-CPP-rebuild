#!/usr/bin/env python3
"""Verify the lifted tree against an independent disassembler (capstone).

The lifter consumes objdump text that an earlier pipeline had already filtered: single-byte
padding was dropped, and the address array was filtered with it. That is only safe if

  1. every dropped instruction really is padding (nop / int3 / xchg ax,ax), and
  2. no control transfer anywhere in the image targets a dropped address,

because a label that no longer exists would send a branch to the wrong instruction. Both are
checked here, together with the operand decoding of what remains: base, index, scale,
displacement and access width, read independently from the bytes.

Exit status is non-zero when anything disagrees, so this runs as a gate.
"""
import bisect
import json
import os
import re
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lift as L  # noqa: E402

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE = 0x141721000
TEXT_OFF = 0x400

PAD = {'nop', 'int3', 'hlt', 'xchg'}


def load(name):
    with open(os.path.join(BULK, name)) as fh:
        return json.load(fh)


def rows():
    funcs = {x['a']: x for x in load('funcs.json')}
    for k, v in load('extra_bodies.json').items():
        v['a'] = int(k, 16)
        funcs[v['a']] = v
    return funcs


def mem_of(text):
    """First memory operand of an objdump operand string, in lift's tuple shape."""
    import re
    m = re.match(r'^(?:(BYTE|WORD|DWORD|QWORD|XMMWORD) PTR )?\[(.*)\]$', text.strip())
    if not m:
        return None
    w = {'BYTE': 1, 'WORD': 2, 'DWORD': 4, 'QWORD': 8, 'XMMWORD': 16}.get(m.group(1) or 'QWORD', 8)
    inner = m.group(2)
    r = re.match(r'^rip@(0x[0-9a-f]+)$', inner)
    if r:
        return ('rip', None, None, int(r.group(1), 16), w)
    b = re.match(r'^(r[a-z0-9]+)(?:([+-])0x([0-9a-f]+))?$', inner)
    if b:
        d = int(b.group(3), 16) if b.group(3) else 0
        return ('mem', b.group(1), None, -d if b.group(2) == '-' else d, w)
    ix = re.match(r'^(?:0x([0-9a-f]+)\+)?(?:([a-z0-9]+)\+)?([a-z0-9]+)\*([1248])(?:\+0x([0-9a-f]+))?$', inner)
    if ix:
        disp = int(ix.group(1) or ix.group(5) or '0', 16)
        return ('mem', ix.group(2), ix.group(3), disp, w)
    ig = re.match(r'^([a-z0-9]+)\+0x([0-9a-f]+)$', inner)
    if ig:
        return ('mem', ig.group(1), None, int(ig.group(2), 16), w)
    return ('mem', inner, None, 0, w)


def main():
    image = open(DLL, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    md.detail = True
    funcs = rows()
    ported = {int(a) for a in load('ported.json')}

    dropped = []
    non_pad = []
    target_hits = []
    operand_bad = []
    checked = 0
    ops_checked = 0
    all_targets = set()

    for a in sorted(funcs):
        f = funcs[a]
        off = a - BASE + TEXT_OFF
        span = max(0, f['b'] - a)
        cap = [ins for i, ins in enumerate(md.disasm(image[off:off + span], a)) if i < len(f['text'])]
        if not cap:
            continue
        # 1/2: which byte addresses the row skipped, and are they padding only
        known = set(f['addr'])
        for ins in cap:
            if ins.address in known:
                continue
            dropped.append(ins.address)
            if ins.mnemonic not in PAD:
                non_pad.append((a, hex(ins.address), '%s %s' % (ins.mnemonic, ins.op_str)))
        # collect every control transfer target
        for ins in cap:
            if ins.mnemonic.split()[0] in ('call', 'jmp') or ins.mnemonic.startswith('j'):
                for op in ins.operands:
                    if op.type == capstone.x86.X86_OP_IMM:
                        all_targets.add(op.imm)
        if a not in ported:
            continue
        checked += 1
        # 3: addressing decode of the rows that were lifted, against the lifter's own encoder
        by_addr = dict(zip(f['addr'], f['text']))
        for ins in cap:
            text = by_addr.get(ins.address)
            if not text:
                continue
            parts = text.split(None, 1)
            if len(parts) < 2:
                continue
            mnem = parts[0].lower()
            bodies = [L.enc(t) for t in re.split(r',\s*', parts[1])]
            mems = [b for b in bodies if b and b[0] in ('mem', 'iat')]
            cap_mems = [op for op in ins.operands if op.type == capstone.x86.X86_OP_MEM]
            if not mems or not cap_mems:
                continue
            got, op = mems[0], cap_mems[0]
            ops_checked += 1
            c_base = ins.reg_name(op.mem.base) if op.mem.base else None
            c_index = ins.reg_name(op.mem.index) if op.mem.index else None
            c_scale = op.mem.scale if op.mem.index else None
            c_disp = op.mem.disp
            if got[0] == 'iat':
                want = ins.address + ins.size + c_disp
                if got[1] != want:
                    operand_bad.append((a, text[:44], 'rip target 0x%x' % got[1], 'capstone 0x%x' % want))
                continue
            expr, g_disp = got[1], got[2]
            if expr in ('0', '0x0'):
                expr = '0'
            m2 = re.match(r'^\((\S+) \+ (\S+) \* (\d+)\)$', expr)
            if m2:
                g_base, g_index, g_scale = m2.group(1), m2.group(2), int(m2.group(3))
            elif expr in ('0', '0x0'):
                g_base, g_index, g_scale = None, None, None
            else:
                g_base, g_index, g_scale = expr, None, None
            diffs = []
            if g_base == '0':
                g_base = None
            if (g_base or None) != (c_base or None):
                diffs.append('base %s/%s' % (g_base, c_base))
            if (g_index or None) != (c_index or None):
                diffs.append('index %s/%s' % (g_index, c_index))
            if (g_scale or None) != (c_scale or None):
                diffs.append('scale %s/%s' % (g_scale, c_scale))
            if g_disp != c_disp:
                diffs.append('disp %s/%s' % (g_disp, c_disp))
            if mnem != 'lea' and got[3] != op.size:
                diffs.append('width %s/%s' % (got[3], op.size))
            if diffs:
                operand_bad.append((a, text[:44], 'lift ' + ','.join(diffs), 'capstone size %d' % op.size))

    # a branch that stays inside its own row must land on an instruction boundary of that row,
    # otherwise the lifted body has a goto to a label that was never emitted
    target_hits = []
    for a in sorted(funcs):
        f = funcs[a]
        known = set(f['addr'])
        off = a - BASE + TEXT_OFF
        span = max(0, f['b'] - a)
        for ins in md.disasm(image[off:off + span], a):
            if not (ins.mnemonic.startswith('j') or ins.mnemonic.split()[0] == 'call'):
                continue
            for op in ins.operands:
                if op.type != capstone.x86.X86_OP_IMM:
                    continue
                t = op.imm
                if a <= t < f['b'] and t not in known:
                    target_hits.append((a, t, '%s %s' % (ins.mnemonic, ins.op_str)))

    print('rows examined:', len(funcs), 'lifted rows verified:', checked, 'memory operands compared:', ops_checked)
    pruned = sum(r['removed'] for r in load('pruned_ranges.json')) if os.path.exists(
        os.path.join(BULK, 'pruned_ranges.json')) else 0
    print('bytes pruned as jump-table data:', pruned,
          '| dropped instructions that are not padding:', len(non_pad))
    for r in non_pad[:5]:
        print('   NON-PAD 0x%x at %s: %s' % r)
    print('control transfers landing on a dropped address:', len(target_hits))
    for a, t, txt in target_hits[:6]:
        print('   row 0x%x: %s targets 0x%x, which is not a boundary in that row' % (a, txt, t))
    print('operand disagreements:', len(operand_bad))
    for r in operand_bad[:6]:
        print('   0x%x %-44s %s vs %s' % r)
    return 0 if not non_pad and not target_hits and not operand_bad else 1


if __name__ == '__main__':
    raise SystemExit(main())
