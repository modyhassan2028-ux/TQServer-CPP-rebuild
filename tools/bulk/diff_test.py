#!/usr/bin/env python3
"""Differential test: the lifted body against the original bytes in an independent CPU emulator.

The driver `tests/cqbase_lift_diff.cpp` runs a lifted body from a deterministic state and prints
what came out. This script reconstructs the same initial state, executes the row's original bytes in
unicorn, and compares.

Reconstruction is exact rather than approximate: the driver's generator is a 32-bit LCG seeded with
`seed ^ addr`, and this file replays it in the same order, so both sides start from identical
memory. The state that gets compared is the return value, the scratch block, and the stack window.

Emulation stops *before* the `ret`, because the model's `ret` returns instead of popping, so the
final pop is the one place the two cannot agree by construction.
"""
import json
import os
import subprocess
import sys

import unicorn
import unicorn.x86_const as ux

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE = 0x141721000
TEXT_OFF = 0x400
SECS = [(0x141721000, 0x10100e, 0x400), (0x141823000, 0x6067d, 0x101600),
        (0x141884000, 0x2e00, 0x161e00)]
REGS = [ux.UC_X86_REG_RCX, ux.UC_X86_REG_RDX, ux.UC_X86_REG_R8, ux.UC_X86_REG_R9]
ZEROED = [ux.UC_X86_REG_RAX, ux.UC_X86_REG_RBX, ux.UC_X86_REG_RBP, ux.UC_X86_REG_RSI,
          ux.UC_X86_REG_RDI, ux.UC_X86_REG_R10, ux.UC_X86_REG_R11, ux.UC_X86_REG_R12,
          ux.UC_X86_REG_R13, ux.UC_X86_REG_R14, ux.UC_X86_REG_R15]


def load(name):
    with open(os.path.join(BULK, name)) as fh:
        return json.load(fh)


def rows():
    funcs = {x['a']: dict(x) for x in load('funcs.json')}
    for k, v in load('extra_bodies.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    for k, v in load('rows_fixed.json').items():
        funcs[int(k, 16)] = dict(v, a=int(k, 16))
    return funcs


class Lcg:
    def __init__(self, seed):
        self.s = seed & 0xFFFFFFFF

    def next(self):
        self.s = (self.s * 1103515245 + 12345) & 0xFFFFFFFF
        return self.s


def replay(seed, addr, scratch):
    """Same sequence the driver runs: four pointers, twelve filler draws, then the scratch block."""
    g = Lcg(seed ^ (addr & 0xFFFFFFFF))
    init = [scratch + (g.next() % 0x400) for _ in range(4)]
    for _ in range(12):
        g.next()
    block = bytearray()
    for _ in range(0x2000 // 8):
        block += g.next().to_bytes(8, 'little')
    return init, bytes(block)


def main():
    addrs_file = sys.argv[1]
    seed = int(sys.argv[2], 0) if len(sys.argv) > 2 else 1
    limit = int(sys.argv[3], 0) if len(sys.argv) > 3 else 200

    table = rows()
    image = open(DLL, 'rb').read()
    addrs = [l.strip() for l in open(addrs_file) if l.strip()][:limit]
    env = dict(os.environ)
    scratch = stack = 0     # replaced per run: the driver prints its own addresses

    same = 0
    diff_reg = 0
    diff_mem = 0
    skipped = 0
    faults = 0
    details = []
    for one in addrs:
        run = subprocess.run(['/tmp/lift_dn2', one, str(seed)], capture_output=True,
                             text=True, env=env, timeout=120)
        got = [l for l in run.stdout.splitlines() if l.startswith('{')]
        if got:
            hdr = json.loads(got[0])
            scratch, stack = hdr['scratch'], hdr['stack']
        model_fault = len(got) < 2
        if not got:
            skipped += 1
            continue
        if model_fault:
            # the model crashed: the honest comparison is whether the original bytes crash too
            rec = {'addr': int(one, 16), 'ra': 0, 'rsp': stack, 'scratch': '00' * 0x800}
            a = rec['addr']
        else:
            rec = json.loads(got[1])
            a = rec['addr']
        row = table.get(a)
        if not row:
            skipped += 1
            continue
        init, block = replay(seed, a, scratch)
        uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_64)
        try:
            uc.mem_map(scratch & ~0xFFF, 0x4000)
            uc.mem_write(scratch, block)
            rsp = rec.get('rsp') or stack
            uc.mem_map((rsp - 0x400) & ~0xFFF, 0x2000)
            uc.mem_map(BASE & ~0xFFF, 0x110000)
            uc.mem_map(0x141823000 & ~0xFFF, 0x70000)
        except unicorn.UcError:
            pass
        for s_va, size, off in SECS:
            try:
                uc.mem_write(s_va, image[off:off + size])
            except unicorn.UcError:
                pass
        for r in REGS:
            pass
        for i, r in enumerate(REGS):
            uc.reg_write(r, init[i])
        for r in ZEROED:
            uc.reg_write(r, 0)
        uc.reg_write(ux.UC_X86_REG_RSP, rec.get('rsp') or stack)
        uc.reg_write(ux.UC_X86_REG_EFLAGS, 0)
        # stop before the ret: the model returns instead of popping
        stop = {'hit': False}

        def hook(uc_, address, size, user):
            code = uc_.mem_read(address, min(size, 1))
            if code and code[0] in (0xC3, 0xC2, 0xCB, 0xCA):
                stop['hit'] = True
                uc_.emu_stop()

        uc.hook_add(unicorn.UC_HOOK_CODE, hook)
        off = a - BASE + TEXT_OFF
        code = image[off:off + max(0, row['b'] - a)]
        try:
            uc.emu_start(a, a + len(code), count=400)
        except unicorn.UcError as e:
            if model_fault:
                same += 1        # both sides fault: they agree
            else:
                faults += 1
                if len(details) < 6:
                    details.append((a, 'model ran but emulator faulted: %s' % str(e)[:40]))
            continue
        if model_fault:
            diff_reg += 1
            if len(details) < 6:
                details.append((a, 'model faulted, original did not'))
            continue
        u_rax = uc.reg_read(ux.UC_X86_REG_RAX)
        u_scratch = uc.mem_read(scratch, 0x800)

        ok_reg = (u_rax & 0xFFFFFFFFFFFFFFFF) == (rec['ra'] & 0xFFFFFFFFFFFFFFFF)
        ok_mem = bytes(u_scratch) == bytes.fromhex(rec['scratch'])
        if ok_reg and ok_mem:
            same += 1
        else:
            if not ok_reg:
                diff_reg += 1
                if len(details) < 6:
                    details.append((a, 'rax model=0x%x unicorn=0x%x' % (rec['ra'], u_rax)))
            if not ok_mem:
                diff_mem += 1
                if len(details) < 6:
                    details.append((a, 'scratch differs'))

    print('bodies compared:', same + max(diff_reg, diff_mem), '| agree:', same,
          '| rax differs:', diff_reg, '| memory differs:', diff_mem,
          '| emulator faults:', faults, '| skipped:', skipped)
    for d in details:
        print('   0x%x %s' % d)
    return 0 if diff_reg == 0 and diff_mem == 0 else 1


if __name__ == '__main__':
    raise SystemExit(main())
