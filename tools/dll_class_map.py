#!/usr/bin/env python3
"""tools/dll_class_map.py — full RTTI class map of any original binary.

Same chain as find_vtables.py, applied to every ".?AV<Class>@<ns>@@" string:
  name string -> TypeDescriptor (name ptr right before it)
  -> Complete Object Locator (32-bit TD RVA at +0x0c)
  -> vtable (the qword just before slot 0 holds the COL VA)

Usage: python3 tools/dll_class_map.py <binary> [out.json] [out.md]
"""
import json
import struct
import sys


def load(path):
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3C)[0]
    n = struct.unpack_from('<H', d, pe + 6)[0]
    opt = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<Q', d, pe + 24 + 24)[0]
    secs = []
    for i in range(n):
        o = pe + 24 + opt + i * 40
        vs, va, rs, ra = struct.unpack_from('<IIII', d, o + 8)
        ch = struct.unpack_from('<I', d, o + 36)[0]
        secs.append((va, vs, ra, rs, ch))
    return d, base, secs


def f2v(secs, base, off):
    for va, vs, ra, rs, ch in secs:
        if ra <= off < ra + max(rs, vs):
            return base + va + (off - ra)
    return None


def v2f(secs, base, addr):
    rva = addr - base
    for va, vs, ra, rs, ch in secs:
        if va <= rva < va + max(vs, rs):
            return ra + (rva - va)
    return None


def in_text(secs, base, addr):
    rva = addr - base
    for va, vs, ra, rs, ch in secs:
        if va <= rva < va + max(vs, rs):
            return bool(ch & 0x20000000)
    return False


def resolve(d, base, secs, i, td_str):
    pack = struct.pack('<Q', td_str)
    for j in range(max(0, i - 0x40), i):
        if d[j:j + 8] != pack or j % 8 != 0:
            continue
        td = f2v(secs, base, j - 0x10)
        if td is None:
            continue
        rva_td = struct.pack('<I', td - base)
        k = d.find(rva_td)
        while k >= 0:
            col = f2v(secs, base, k - 12)
            if col is not None:
                need = struct.pack('<Q', col)
                m = d.find(need)
                while m >= 0:
                    if m % 8 == 0:
                        vt = f2v(secs, base, m + 8)
                        if vt is not None:
                            return vt, td, col
                    m = d.find(need, m + 1)
            k = d.find(rva_td, k + 1)
    return None, None, None


def main():
    path = sys.argv[1]
    out_json = sys.argv[2] if len(sys.argv) > 2 else None
    out_md = sys.argv[3] if len(sys.argv) > 3 else None
    d, base, secs = load(path)
    res = {}
    seen = set()
    i = d.find(b'.?AV')
    while i >= 0:
        if i == 0 or d[i - 1] == 0:
            e = d.find(b'@@', i)
            if e > 0:
                s = d[i:e + 2]
                if all(32 < c < 127 for c in s):
                    name = s[4:].decode('ascii')[:-2].replace('@', '::')
                    td_str = f2v(secs, base, i)
                    if td_str and name not in seen:
                        vt, td, col = resolve(d, base, secs, i, td_str)
                        if vt is not None:
                            seen.add(name)
                            off = v2f(secs, base, vt)
                            fns = []
                            for k in range(32):
                                raw = struct.unpack_from('<Q', d, off + k * 8)[0]
                                if not in_text(secs, base, raw):
                                    break
                                fns.append('0x%x' % raw)
                            res['0x%x' % vt] = {'name': name,
                                                'td': '0x%x' % td,
                                                'col': '0x%x' % col,
                                                'fns': fns}
        i = d.find(b'.?AV', i + 1)
    if out_json:
        json.dump(res, open(out_json, 'w'), indent=1, sort_keys=True)
    if out_md:
        with open(out_md, 'w') as f:
            f.write('# %s — RTTI class map\n\n' % path.split('/')[-1])
            f.write('| vtable | class | slots |\n|---|---|---|\n')
            for vt, v in sorted(res.items()):
                f.write('| `%s` | `%s` | %d |\n'
                        % (vt, v['name'], len(v['fns'])))
    print('%s: classes %d' % (path.split('/')[-1], len(res)))
    for vt, v in sorted(res.items())[:12]:
        print(' ', vt, v['name'], len(v['fns']))


if __name__ == '__main__':
    main()
