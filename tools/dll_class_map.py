#!/usr/bin/env python3
"""tools/dll_class_map.py — build the full RTTI class map of any original DLL.

Chain (no guessing — every address is read out of the binary):
  name string ".?AV<Class>@<ns>@@"  -> TypeDescriptor (name ptr at +0x10)
  -> Complete Object Locator (TD RVA at +0x0c)
  -> vtable (the qword just before slot 0 is the COL address)

Usage: python3 tools/dll_class_map.py <dll-path> [out-json] [out-md]
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
            return bool(ch & 0x20000000)      # IMAGE_SCN_MEM_EXECUTE
    return False


def name_strings(d, base, secs):
    out = []
    i = d.find(b'.?AV')
    while i >= 0:
        if i == 0 or d[i - 1] == 0:
            j = d.find(b'@@', i)
            if j > 0:
                s = d[i:j + 2]
                if all(32 < c < 127 for c in s):
                    va = f2v(secs, base, i)
                    if va:
                        out.append((va, s.decode('ascii')))
        i = d.find(b'.?AV', i + 1)
    return out


def main():
    path = sys.argv[1]
    out_json = sys.argv[2] if len(sys.argv) > 2 else None
    out_md = sys.argv[3] if len(sys.argv) > 3 else None
    d, base, secs = load(path)
    res = {}
    for va, s in name_strings(d, base, secs):
        name = s[4:].replace('@@', '').replace('@', '::')
        # TypeDescriptor: { vftable, spare, &name }
        pack = struct.pack('<Q', va)
        td = None
        for j in range(0, len(d) - 8):
            pass
        # index the name-pointer occurrences
        idx = []
        k = d.find(pack)
        while k >= 0:
            idx.append(k)
            k = d.find(pack, k + 1)
        best = None
        for k in idx:
            tdv = f2v(secs, base, k - 0x10)
            if tdv is None:
                continue
            rva = tdv - base
            col = struct.pack('<I', rva)
            c = d.find(col)
            while c >= 0:
                colv = f2v(secs, base, c - 12)
                if colv is not None:
                    p = struct.pack('<Q', colv)
                    v = d.find(p)
                    while v >= 0:
                        vt = f2v(secs, base, v + 8)
                        if vt is not None:
                            best = (tdv, colv, vt, v + 8)
                            break
                        v = d.find(p, v + 1)
                if best:
                    break
                c = d.find(col, c + 1)
            if best:
                break
        if not best:
            continue
        tdv, colv, vt, vt_off = best
        fns = []
        for i in range(32):
            raw = struct.unpack_from('<Q', d, vt_off + i * 8)[0]
            if not in_text(secs, base, raw):
                break
            fns.append('0x%x' % raw)
        res['0x%x' % vt] = {'name': name, 'td': '0x%x' % tdv,
                            'col': '0x%x' % colv, 'fns': fns}
    if out_json:
        json.dump(res, open(out_json, 'w'), indent=1, sort_keys=True)
    if out_md:
        with open(out_md, 'w') as f:
            f.write('# %s — RTTI class map\n\n' % path.split('/')[-1])
            f.write('| vtable | class | slots |\n|---|---|---|\n')
            for vt, v in sorted(res.items()):
                f.write('| `%s` | `%s` | %d |\n' % (vt, v['name'],
                                                    len(v['fns'])))
    print('classes: %d' % len(res))
    for vt, v in sorted(res.items())[:40]:
        print(vt, v['name'], v['fns'])


main()
