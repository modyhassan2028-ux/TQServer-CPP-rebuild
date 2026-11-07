"""Same inputs, two implementations: the original machine code (emulated) and the ported C++."""
import json
import re
import struct
import subprocess
import sys

sys.path.insert(0, __file__.rsplit('/', 2)[0] + '/tools/emu')
from emu import Image, Machine, STACK, STACK_SIZE  # noqa: E402

SCRATCH = 0x300000000
SCRATCH_SIZE = 0x20000
MASK = (1 << 64) - 1


def splitmix(s):
    s = (s + 0x9e3779b97f4a7c15) & MASK
    z = s
    z = ((z ^ (z >> 30)) * 0xbf58476d1ce4e5b9) & MASK
    z = ((z ^ (z >> 27)) * 0x94d049bb133111eb) & MASK
    return s, z ^ (z >> 31)


def fill(s, n):
    out = bytearray()
    while len(out) < n:
        s, v = splitmix(s)
        out += struct.pack('<Q', v)
    return bytes(out[:n]), s


def run_original(img, addr):
    rows = []
    for c in range(8):
        m = Machine(img)
        m._map(SCRATCH, SCRATCH_SIZE)
        body, _ = fill((addr * 0x100 + c) & MASK, SCRATCH_SIZE)
        m.write(SCRATCH, body)
        s = addr & MASK
        args = []
        for _ in range(4):
            s, v = splitmix(s)
            args.append(SCRATCH + (v % 0x800))
        r = m.run(addr, args)
        if 'error' in r:
            rows.append((c, None, r['error']))
            continue
        import zlib
        rows.append((c, r['rax'], '%08x' % zlib.crc32(m.read(SCRATCH, SCRATCH_SIZE))))
    return rows


def main():
    img = Image('/app/work/orig_extract/Source/Syndicate.dll')
    cpp = {}
    for line in subprocess.run(['/tmp/diffcpp'], capture_output=True, text=True).stdout.split('\n'):
        p = line.split()
        if len(p) == 4:
            cpp.setdefault(p[0], []).append((int(p[1]), int(p[2], 16), p[3]))
    addrs = sorted(int(x, 16) for x in json.load(open('/tmp/nostack.json')))
    hdr = open('modules/syndicate/src/synlift.h').read() + open('modules/syndicate/src/synlift_stage.h').read()
    have = {int(m, 16) for m in re.findall(r'uint64_t SynLift_([0-9a-f]+)\(', hdr)}
    addrs = [a for a in addrs if a in have]
    bad = 0
    for a in addrs:
        key = format(a, 'x')
        orig = run_original(img, a)
        ported = cpp.get(key, [])
        for (c, rax_o, tail_o), (c2, rax_p, crc_p) in zip(orig, ported):
            if rax_o is None:
                print('EMU-FAIL %s case %d: %s' % (key, c, tail_o))
                bad += 1
                continue
            if rax_o != rax_p or tail_o != crc_p:
                print('MISMATCH %s case %d: orig rax=%x crc=%s | ported rax=%x crc=%s' % (key, c, rax_o, tail_o, rax_p, crc_p))
                bad += 1
    print('compared %d bodies, %d mismatches' % (len(addrs), bad))
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
