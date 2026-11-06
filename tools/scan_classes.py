#!/usr/bin/env python3
"""RTTI-accurate class/slot scanner for Syndicate.dll v6159.

Why RTTI: matching slot addresses against the port's text produced false "incomplete
classes" (a row address such as 0x141841780 was read as a vtable base, and rows shared by
several tables were counted as separate classes). Each real vtable is found by its own
CompleteObjectLocator: at vtable-8 sits a COL whose +0x0C is the TypeDescriptor RVA and
whose name is the mangled class name. Only tables that resolve to a name are reported.
"""
import pefile, struct, glob, re, sys, os

DLL = '/app/work/orig_extract/Source/Syndicate.dll'
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

pe = pefile.PE(DLL, fast_load=True)
IB = pe.OPTIONAL_HEADER.ImageBase
secs = {s.Name.rstrip(b'\0').decode(): s for s in pe.sections}
data = {n: s.get_data() for n, s in secs.items()}
TEXT_LO, TEXT_HI = IB + secs['.text'].VirtualAddress, IB + secs['.text'].VirtualAddress + secs['.text'].Misc_VirtualSize


def read(addr, n):
    for name, s in secs.items():
        lo = IB + s.VirtualAddress
        if lo <= addr < lo + s.Misc_VirtualSize:
            o = addr - lo
            return data[name][o:o + n]
    return None


def u32(addr):
    b = read(addr, 4)
    return struct.unpack('<I', b)[0] if b else None


def u64(addr):
    b = read(addr, 8)
    return struct.unpack('<Q', b)[0] if b else None


def class_name(vt):
    """vtable-8 -> COL -> TypeDescriptor -> the mangled class name"""
    loc = u64(vt - 8)              # the qword before the table holds the locator's address
    if not loc:
        return None
    # the locator is stored as a full image address here; the type descriptor inside it is
    # an RVA, so the two are resolved differently
    col = loc if loc >= IB else IB + loc
    sig = u32(col)
    if sig != 1:                   # the only signature x64 uses
        return None
    td_rva = u32(col + 0x0C)
    if not td_rva:
        return None
    td = IB + td_rva
    b = read(td + 0x10, 256)
    if not b:
        return None
    s = b.split(b'\0')[0].decode('latin1', 'replace')
    if not s.startswith('.?AV'):
        return None
    return s[4:].split('@@')[0].rstrip('@')


def vtables():
    """every address whose qword run of text pointers follows a valid locator"""
    out = []
    s = secs['.rdata']
    lo = IB + s.VirtualAddress
    blob = data['.rdata']
    for off in range(8, len(blob) - 8, 8):
        vt = lo + off
        q = struct.unpack_from('<Q', blob, off)[0]
        if not (TEXT_LO <= q < TEXT_HI):
            continue
        name = class_name(vt)
        if not name:
            continue
        slots = []
        k = off
        while k + 8 <= len(blob):
            v = struct.unpack_from('<Q', blob, k)[0]
            if TEXT_LO <= v < TEXT_HI:
                slots.append(v)
                k += 8
            else:
                break
        out.append((vt, name, slots))
    return out


def ported_text():
    t = ''
    for f in glob.glob(os.path.join(REPO, 'modules/**/*.cpp'), recursive=True) + \
             glob.glob(os.path.join(REPO, 'modules/**/*.h'), recursive=True):
        t += open(f, errors='ignore').read().lower()
    return t


def main():
    text = ported_text()
    rows = []
    for vt, name, slots in vtables():
        # a slot counts as ported only when a real `0x<addr>` marker exists. A bare '%x'
        # matched comment labels like `// ---- FUN_14173f950 ----`, which made the ledger
        # report zero incomplete tables by construction.
        miss = [s for s in slots if ('0x%x' % s) not in text]
        rows.append((len(miss), name, vt, len(slots), miss))
    rows.sort(key=lambda r: (r[0] == 0, -r[0]))
    total = len(rows)
    complete = sum(1 for r in rows if r[0] == 0)
    print('RTTI vtables: %d   complete: %d   with missing rows: %d' % (total, complete, total - complete))
    print()
    for n, name, vt, nslots, miss in rows:
        if n == 0:
            continue
        print('%-42s vt 0x%x  %2d slots, %d missing :: %s' %
              (name[:42], vt, nslots, n, ' '.join('%x' % m for m in miss)))


if __name__ == '__main__':
    main()
