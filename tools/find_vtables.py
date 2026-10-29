#!/usr/bin/env python3
"""tools/find_vtables.py — resolve a class vtable from its RTTI name.

No guessing: the chain is
  type-descriptor string ".?AV<Name>@syndicate@@"
  -> TypeDescriptor (vftable, spare, &name)
  -> Complete Object Locator (references the TD by RVA)
  -> vtable (whose [-1] slot holds the COL address)

Usage: python3 tools/find_vtables.py [Name ...]
"""
import struct
import sys

DLL = '/app/co_decomp/orig_binaries/Source/Syndicate.dll'


def load():
    data = open(DLL, 'rb').read()
    pe = struct.unpack_from('<I', data, 0x3c)[0]
    n = struct.unpack_from('<H', data, pe + 6)[0]
    opt = struct.unpack_from('<H', data, pe + 20)[0]
    base = struct.unpack_from('<Q', data, pe + 24 + 24)[0]
    secs = []
    for i in range(n):
        o = pe + 24 + opt + i * 40
        vs, va, rs, ra = struct.unpack_from('<IIII', data, o + 8)
        secs.append((va, vs, ra, rs))
    return data, base, secs


def f2v(secs, base, off):
    for va, vs, ra, rs in secs:
        if ra <= off < ra + rs:
            return base + va + (off - ra)
    return None


def v2f(secs, base, addr):
    rva = addr - base
    for va, vs, ra, rs in secs:
        if va <= rva < va + max(vs, rs):
            return ra + (rva - va)
    return None


def find_vtable(data, base, secs, name):
    i = -1
    for pat in ('.?AV%s@@' % name, '.?AV%s@syndicate@@' % name):
        i = data.find(pat.encode())
        if i >= 0:
            break
    if i < 0:
        return None, 'no type-descriptor string'
    td_str = f2v(secs, base, i)
    # TypeDescriptor: [vftable q][spare q][name ptr q] -> the name ptr == td_str
    pack = struct.pack('<Q', td_str)
    for j in range(max(0, i - 0x40), i):
        if data[j:j + 8] == pack and j % 8 == 0:
            td = f2v(secs, base, j - 0x10)
            if td is None:
                continue
            # COLs referencing this TD by 32-bit RVA
            rva_td = struct.pack('<I', td - base)
            rva_td_va = struct.pack('<Q', td)          # the v3 layout
            cols = []
            for k in range(0, len(data) - 4):
                if data[k:k + 4] == rva_td:
                    a = f2v(secs, base, k - 12)
                    if a:
                        cols.append(a)
            for col in cols:
                need = struct.pack('<Q', col)
                k = data.find(need)
                while k >= 0:
                    if k % 8 == 0:
                        vt = f2v(secs, base, k + 8)
                        if vt:
                            return vt, 'ok'
                    k = data.find(need, k + 1)
    return None, 'no COL/vtable'


def slots(data, base, secs, vt, count=12):
    out = []
    f = v2f(secs, base, vt)
    if f is None:
        return out
    for i in range(count):
        p = struct.unpack_from('<Q', data, f + i * 8)[0]
        out.append(p)
    return out


def main():
    data, base, secs = load()
    names = sys.argv[1:]
    for name in names:
        vt, note = find_vtable(data, base, secs, name)
        if vt is None:
            print('%-34s MISS (%s)' % (name, note))
            continue
        print('%-34s vtable 0x%x' % (name, vt))
        for i, p in enumerate(slots(data, base, secs, vt)):
            print('    slot%02d 0x%x' % (i, p))


if __name__ == '__main__':
    main()
