#!/usr/bin/env python3
"""merge_chunks — join rows that were carved into pieces back into whole functions.

611 rows in funcs.json stop mid-flow at an address where the next row begins. A port written from
one such row silently loses the rest of the function. This tool chains those rows and writes
tools/bulk/merged_rows.json: { start: end } for every function, plus a report of anything that
still does not end on a return or a jump.

It does not invent bytes and it does not touch the disassembly. It only answers "where does the
function that starts here actually end".
"""
import json
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

IMG = '/app/work/orig_extract/Source/Syndicate.dll'
BASE, FO = 0x141721000, 0x400


def is_return(ins) -> bool:
    # int3 is the alignment fill MSVC emits after a function, so a row ending on it is finished;
    # the returns it does emit are spelled `ret`, `rep ret` and `repz ret`, all matched by name.
    m = ins.mnemonic
    return 'ret' in m or m in ('jmp', 'hlt', 'ud2', 'int3')


def main() -> int:
    img = open(IMG, 'rb').read()
    md = Cs(CS_ARCH_X86, CS_MODE_64)
    rows = {r['a']: r for r in json.load(open('tools/bulk/funcs.json'))
            if isinstance(r, dict) and 'a' in r}

    def last_ins(a, b):
        ins = list(md.disasm(img[FO + a - BASE:FO + a - BASE + (b - a)], a))
        return ins[-1] if ins else None

    merged, chained, unresolved, chunk_starts = {}, set(), [], set()
    for a in rows:
        end, seen, joins = rows[a]['b'], {a}, 0
        while True:
            li = last_ins(a, end)
            if li is None:
                unresolved.append((a, end, 'no instructions'))
                break
            if is_return(li) and li.address + li.size == end:
                break
            if end in rows and end not in seen:      # the function continues in the next row
                seen.add(end)
                chunk_starts.add(end)
                end = rows[end]['b']
                joins += 1
                chained.add(a)
                continue
            unresolved.append((a, end, 'stops on ' + li.mnemonic + ' ' + li.op_str))
            break
        merged[a] = end

    # a row that is really the tail of another row is not a function entry point
    entry_points = {a: b for a, b in merged.items() if a not in chunk_starts}
    overlap = 0
    ordered = sorted(entry_points.items())
    for i in range(1, len(ordered)):
        if ordered[i][0] < ordered[i - 1][1]:
            overlap += 1

    print('rows %d | chained into %d entry points | chunk starts dropped %d | unresolved %d'
          ' | overlapping entry spans %d'
          % (len(rows), len(entry_points), len(chunk_starts), len(unresolved), overlap))
    for u in unresolved[:15]:
        print('  unresolved 0x%x -> 0x%x  (%s)' % u)
    json.dump({('%x' % k): v for k, v in entry_points.items()},
              open('tools/bulk/merged_rows.json', 'w'), indent=0)
    json.dump(sorted('%x' % a for a in chunk_starts),
              open('tools/bulk/chunk_starts.json', 'w'), indent=0)
    return 0


if __name__ == '__main__':
    sys.exit(main())
