#!/usr/bin/env python3
"""find_cut_rows — classify every row in funcs.json by how it ENDS.

Why this exists: a port built on a row that stops mid-flow silently drops the rest of the
function. That already produced one wrong port (CSynManager::SetValue, which looked like it
returned early because its row ended at the first store). Two shapes matter:

  terminal  the row's last instruction is a return or an unconditional jump
  chunked   the row stops mid-flow and ANOTHER row starts exactly at that address, so the
            function lives in pieces and a faithful body has to be the concatenation
  cut       the row stops mid-flow and nothing continues it; the bytes past the end were
            never lifted

Terminal detection is deliberately strict: MSVC emits `rep ret` / `repz ret` as a return, and
the mnemonic is what carries that, not the operand string.
"""
import json
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

IMG = '/app/work/orig_extract/Source/Syndicate.dll'
BASE, FO = 0x141721000, 0x400


def main() -> int:
    img = open(IMG, 'rb').read()
    md = Cs(CS_ARCH_X86, CS_MODE_64)
    rows = {r['a']: r for r in json.load(open('tools/bulk/funcs.json'))
            if isinstance(r, dict) and 'a' in r}

    def is_return(ins) -> bool:
        m = ins.mnemonic
        return 'ret' in m or m in ('jmp', 'hlt', 'ud2')

    terminal = chunked = 0
    cut = []
    for a, r in rows.items():
        b = r['b']
        ins = list(md.disasm(img[FO + a - BASE:FO + a - BASE + (b - a)], a))
        if not ins:
            continue
        last = ins[-1]
        if last.address + last.size != b:
            cut.append([a, b, 'not-on-boundary'])
            continue
        if is_return(last):
            terminal += 1
        elif b in rows:
            chunked += 1
        else:
            cut.append([a, b, last.mnemonic + ' ' + last.op_str])

    print('rows %d | terminal %d | chunked %d | cut %d' % (len(rows), terminal, chunked, len(cut)))
    for c in cut[:20]:
        print('  cut 0x%x-0x%x  last=%s' % (c[0], c[1], c[2]))
    json.dump(cut, open('tools/bulk/cut_rows.json', 'w'), indent=0)
    json.dump({'rows': len(rows), 'terminal': terminal, 'chunked': chunked, 'cut': len(cut)},
              open('tools/bulk/cut_rows_summary.json', 'w'), indent=1)
    return 0


if __name__ == '__main__':
    sys.exit(main())
