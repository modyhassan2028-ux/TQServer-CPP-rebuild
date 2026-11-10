#!/usr/bin/env python3
"""Read the string a DAT_ address points at, straight out of NpcServer.exe."""
import struct, sys

EXE = '/app/co_decomp/orig_binaries/Source/NpcServer.exe'


def image():
    d = open(EXE, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    nsec = struct.unpack_from('<H', d, pe + 6)[0]
    optsz = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<Q', d, pe + 24 + 24)[0]
    secs = []
    off = pe + 24 + optsz
    for i in range(nsec):
        s = off + i * 40
        name = d[s:s + 8].rstrip(b'\0').decode('latin1')
        vsz, va, rawsz, rawptr = struct.unpack_from('<IIII', d, s + 8)
        secs.append((name, base + va, vsz, rawptr, rawsz))
    return d, secs


def read(va, maxlen=400):
    d, secs = image()
    for name, start, vsz, rawptr, rawsz in secs:
        if start <= va < start + max(vsz, rawsz):
            off = rawptr + (va - start)
            end = d.index(b'\0', off)
            return d[off:min(end, off + maxlen)]
    return None


if __name__ == '__main__':
    for a in sys.argv[1:]:
        va = int(a, 16)
        b = read(va)
        print(a, repr(b.decode('latin1')) if b is not None else 'NOT MAPPED')
