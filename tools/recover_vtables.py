#!/usr/bin/env python3
"""tools/recover_vtables.py — vtable recovery for binaries built WITHOUT RTTI.

The Syndicate trick (RTTI) does not exist in the small modules (Flower, ...),
so classes are recovered structurally:
  1. every aligned run of >=3 pointers into .text is a vtable candidate
  2. slot 0 must be a dtor: its body writes the candidate's own address back to
     [rcx] before testing the delete bit
  3. report the vtable, its slot count and the slot0 address

Usage: python3 tools/recover_vtables.py <dll> [out.md]
"""
import struct
import sys

import capstone


def load(path):
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3C)[0]
    n = struct.unpack_from('<H', d, pe + 6)[0]
    opt = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<Q', d, pe + 24 + 24)[0]
    secs = []
    for i in range(n):
        o = pe + 24 + opt + i * 40
        name = d[o - 8:o].rstrip(b'\0').decode('ascii', 'ignore')
        vs, va, rs, ra = struct.unpack_from('<IIII', d, o + 8)
        ch = struct.unpack_from('<I', d, o + 36)[0]
        secs.append((name, va, vs, ra, rs, ch))
    return d, base, secs


def v2f(secs, base, addr):
    rva = addr - base
    for name, va, vs, ra, rs, ch in secs:
        if va <= rva < va + max(vs, rs):
            return ra + (rva - va)
    return None


def f2v(secs, base, off):
    for name, va, vs, ra, rs, ch in secs:
        if ra <= off < ra + max(rs, vs):
            return base + va + (off - ra)
    return None


def is_text(secs, base, addr, exec_only=True):
    rva = addr - base
    for name, va, vs, ra, rs, ch in secs:
        if va <= rva < va + max(vs, rs):
            return bool(ch & 0x20000000) if exec_only else True
    return False


def writes_self(fn_off, fn_va, d, target_va):
    """does the first ~0x40 bytes of fn load target_va into a register?"""
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    code = d[fn_off:fn_off + 0x40]
    for ins in md.disasm(code, fn_va):
        if ins.mnemonic == 'lea' and 'rip' in ins.op_str:
            try:
                disp = int(ins.op_str.split('rip + ')[1].split(']')[0], 16)
            except Exception:
                continue
            if ins.address + ins.size + disp == target_va:
                return True
        if ins.mnemonic in ('ret', 'jmp', 'int3'):
            break
    return False


def main():
    path = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else None
    d, base, secs = load(path)
    rows = []
    seen = set()
    for name, va, vs, ra, rs, ch in secs:
        if ch & 0x20000000:
            continue
        for off in range(ra, ra + max(rs, vs) - 24, 8):
            if off in seen:
                continue
            ptrs = []
            p = off
            while True:
                v = struct.unpack_from('<Q', d, p)[0]
                if not is_text(secs, base, v):
                    break
                ptrs.append(v)
                p += 8
                if len(ptrs) > 260:
                    break
            if len(ptrs) < 3:
                continue
            vt = f2v(secs, base, off)
            fn_off = v2f(secs, base, ptrs[0])
            if vt is None or fn_off is None:
                continue
            if not writes_self(fn_off, ptrs[0], d, vt):
                continue
            for q in range(off, off + len(ptrs) * 8, 8):
                seen.add(q)
            rows.append((vt, ptrs[0], len(ptrs), ptrs))
    lines = ['# %s — recovered vtables (no RTTI)' % path.split('/')[-1], '',
             '| vtable | dtor | slots |', '|---|---|---|']
    for vt, dtor, n, ptrs in sorted(rows):
        lines.append('| `0x%x` | `0x%x` | %d |' % (vt, dtor, n))
    txt = '\n'.join(lines) + '\n'
    if out:
        open(out, 'w').write(txt)
    print('%s: vtables %d' % (path.split('/')[-1], len(rows)))
    for vt, dtor, n, ptrs in sorted(rows)[:15]:
        print('  0x%x  dtor 0x%x  slots %d' % (vt, dtor, n))


if __name__ == '__main__':
    main()
