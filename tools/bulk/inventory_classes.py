#!/usr/bin/env python3
"""List the classes the DLL actually declares, from its own type descriptors.

MSVC writes an RTTI type descriptor per polymorphic class: a vftable pointer, a spare word and a
mangled name. Names start with `.?AV` (class) or `.?AU` (struct). Reading them out of `.rdata` is the
only inventory that cannot be invented: a name is there because the linker put it there.

The output is the denominator the hand port should be measured against.
"""
import json
import os
import re
import struct

BULK = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(BULK))
DLL = '/app/work/orig_extract/Source/Syndicate.dll'
RDATA_VA, RDATA_SIZE, RDATA_OFF = 0x141823000, 0x6067d, 0x101600


def main():
    image = open(DLL, 'rb').read()
    blob = image[RDATA_OFF:RDATA_OFF + RDATA_SIZE]
    names = {}
    for m in re.finditer(rb'\.\?A[VU][0-9A-Za-z_@?$.]{2,200}\x00', blob):
        raw = m.group(0)[:-1].decode('ascii', 'ignore')
        # .?AVClassName@@  ->  ClassName ; nested and namespace forms keep their '@' parts
        body = raw[4:]
        parts = [p for p in body.split('@') if p]
        if not parts:
            continue
        cls = parts[0]
        names[cls] = RDATA_VA + m.start()

    # which of them the hand-written tree already declares
    hand = ''
    files = []
    for root, d, fs in os.walk(os.path.join(REPO, 'modules')):
        for n in fs:
            if not n.endswith(('.h', '.cpp')):
                continue
            if n.startswith(('synlift', 'synthunks', 'synrbinsert_family')):
                continue
            files.append(os.path.join(root, n))
            hand += open(os.path.join(root, n), errors='ignore').read()
    have = [c for c in names if re.search(r'\b(class|struct)\s+%s\b' % re.escape(c), hand)]

    print('classes with RTTI in the DLL:', len(names))
    print('declared in the hand-written tree:', len(have), '| not declared:', len(names) - len(have))
    json.dump(sorted(names), open(os.path.join(BULK, 'classes_dll.json'), 'w'), indent=1)
    json.dump(sorted(have), open(os.path.join(BULK, 'classes_ported.json'), 'w'), indent=1)
    print('sample of the ones still missing:', sorted(set(names) - set(have))[:8])


if __name__ == '__main__':
    main()
