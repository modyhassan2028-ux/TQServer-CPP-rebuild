#!/usr/bin/env python3
"""Coverage of the whole .pdata function table for Syndicate.dll v6159.

A function counts as covered when its address appears in the port sources (as a real port or
as a documented seam). The report ranks what is left, because that number, not the class
count, is what says how much work remains.
"""
import pefile, struct, glob, os, re, sys

DLL = '/app/work/orig_extract/Source/Syndicate.dll'
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
pe = pefile.PE(DLL, fast_load=True)
IB = pe.OPTIONAL_HEADER.ImageBase
secs = {s.Name.rstrip(b'\0').decode(): s for s in pe.sections}
pd = [s for n, s in secs.items() if n.startswith('.pdata')][0].get_data()
text_va = IB + secs['.text'].VirtualAddress
text_end = text_va + secs['.text'].Misc_VirtualSize

funcs = []
for o in range(0, len(pd) - 12, 12):
    st, en, ui = struct.unpack_from('<3I', pd, o)
    st += IB
    en += IB
    if text_va <= st < text_end and en > st:
        funcs.append((st, en))
funcs = sorted(set(funcs))

src = ''
for f in glob.glob(os.path.join(REPO, 'modules/**/*.cpp'), recursive=True) + \
         glob.glob(os.path.join(REPO, 'modules/**/*.h'), recursive=True):
    src += open(f, errors='ignore').read().lower()

missing = [(st, en - st) for st, en in funcs if ('%x' % st) not in src]
total_bytes = sum(en - st for st, en in funcs)
miss_bytes = sum(sz for _, sz in missing)

print('functions in .pdata : %d  (%d bytes)' % (len(funcs), total_bytes))
print('covered             : %d  (%d bytes)' % (len(funcs) - len(missing), total_bytes - miss_bytes))
print('remaining           : %d  (%d bytes)' % (len(missing), miss_bytes))
buckets = [(0, 16), (16, 64), (64, 256), (256, 1024), (1024, 4096), (4096, 1 << 30)]
print('\nremaining by size:')
for lo, hi in buckets:
    n = sum(1 for _, sz in missing if lo <= sz < hi)
    b = sum(sz for _, sz in missing if lo <= sz < hi)
    print('  %5d..%-6d : %4d funcs  %7d bytes' % (lo, hi if hi < (1 << 30) else 0, n, b))
print('\nlargest 25 remaining:')
for st, sz in sorted(missing, key=lambda x: -x[1])[:25]:
    print('  0x%x  %6d bytes' % (st, sz))
