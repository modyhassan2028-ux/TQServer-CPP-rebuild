#!/usr/bin/env python3
"""Read the CSyndicateLogic vtable slots straight from the
original binary (used since D96).

The wave-based porting of CSyndicateLogic (modules/syndicate/src/
syndicatelogic.cpp) needs the exact function address of each table
slot. Instead of trusting decompiler listings, read the .rdata
vtable directly:

    Syndicate.dll, file offset 0x113810 (VA 0x1833810) is the
    CSyndicateLogic vtable: slot i lives at 0x113810 + i*8 and
    holds the VA of that slot's function.

Method to reuse for any other class:
  1. Find 5+ consecutive known slot VAs (from already-ported
     functions) in the binary -> that locates the vtable file
     offset.
  2. Read slot addresses from the table; dump each body from the
     decompiled .c by address.

Usage:
  python3 tools/read_vtable_slots.py [start_hex end_hex]
       (slot offsets in hex without 0x; default 0..0x258)
"""
import struct
import sys

BIN = ('/app/co_decomp/orig_binaries/Source/'
       'Syndicate.dll')
VT_OFF = 0x113810

def main():
    lo = int(sys.argv[1], 16) if len(sys.argv) > 1 else 0
    hi = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x258
    data = open(BIN, 'rb').read()
    for s in range(lo // 8, hi // 8 + 1):
        v = struct.unpack_from('<Q', data, VT_OFF + s * 8)[0]
        print(f'slot +0x{s*8:03x} = 0x{v:016x}')

if __name__ == '__main__':
    main()
