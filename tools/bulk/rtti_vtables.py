#!/usr/bin/env python3
"""Resolve each class the DLL names to its vtable and its slots.

MSVC x64 lays the chain out as: type descriptor (name preceded by two words) -> complete object
locator (holds the descriptor's RVA) -> vtable, whose first word points back at the locator. Every
step is read out of the image, so the slot list for a class is the file's own statement about that
class, not an inference from call shapes.
"""
import json
import os
import re
import struct

BULK = os.path.dirname(os.path.abspath(__file__))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
BASE = 0x141870000  # image base of the PE (from the optional header)
SECTIONS = [('.text', 0x400, 0x10100e, 0x141721000), ('.rdata', 0x101600, 0x6067d, 0x141823000),
            ('.data', 0x161e00, 0x2e00, 0x141884000), ('.pdata', 0x164c00, 0x1df40, 0x141888000)]


def main():
    image = open(DLL, 'rb').read()
    # image base from the optional header (PE32+)
    pe = struct.unpack_from('<I', image, 0x3C)[0]
    image_base = struct.unpack_from('<Q', image, pe + 0x18 + 0x18)[0]

    def to_va(off):
        for _, fo, size, va in SECTIONS:
            if fo <= off < fo + size:
                return va + (off - fo)
        return None

    def to_off(va):
        for _, fo, size, base in SECTIONS:
            if base <= va < base + size:
                return fo + (va - base)
        return None

    rdata_off, rdata_size = 0x101600, 0x6067d
    blob = image[rdata_off:rdata_off + rdata_size]

    # every complete object locator in .rdata: signature 1, six 32-bit fields, the last an RVA of itself
    locators = {}
    for i in range(0, rdata_size - 24, 4):
        sig, off, cd, td, chd, self_rva = struct.unpack_from('<IIIIII', blob, i)
        if sig != 1:
            continue
        here = 0x141823000 + i
        if self_rva != here - image_base:
            continue
        locators[td] = (here, chd)

    out = {}
    for m in re.finditer(rb'\.\?A[VU][0-9A-Za-z_@?$.]{2,200}\x00', image):
        raw = m.group(0)[:-1].decode('ascii', 'ignore')
        parts = [p for p in raw[4:].split('@') if p]
        if not parts:
            continue
        cls = parts[0]
        name_va = to_va(m.start())
        desc_va = name_va - 0x10
        loc = locators.get(desc_va - image_base)
        if not loc:
            continue
        col_va = loc[0]
        # the vtable's word before slot 0 is the locator pointer, so find where that value is stored
        vtable = None
        for k2 in range(0, rdata_size - 8, 8):
            if struct.unpack_from('<Q', blob, k2)[0] == col_va:
                vtable = 0x141823000 + k2 + 8
                break
        if vtable is None:
            continue
        off = to_off(vtable)
        if off is None:
            continue
        slots = []
        for j in range(0, 0x400, 8):
            v = struct.unpack_from('<Q', image, off + j)[0]
            if 0x141721000 <= v < 0x141823000:
                slots.append(v)
            else:
                break
        if slots:
            out.setdefault(cls, {'vtable': '0x%x' % vtable, 'slots': ['0x%x' % s for s in slots]})

    json.dump(out, open(os.path.join(BULK, 'class_vtables.json'), 'w'), indent=1, sort_keys=True)
    total_slots = sum(len(v['slots']) for v in out.values())
    print('classes with a resolved vtable:', len(out), '| vtable slots:', total_slots)
    for cls in sorted(out)[:8]:
        print('   %-28s %d slots' % (cls, len(out[cls]['slots'])))


if __name__ == '__main__':
    main()
