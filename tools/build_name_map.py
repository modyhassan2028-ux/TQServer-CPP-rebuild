#!/usr/bin/env python3
"""Recover the author's names from the Ghidra class-level dump under Docs/reference/NpcServer_Ghidra.

Emits two tables:
  Docs/FUN_NAME_MAP.tsv   address <TAB> Class::method (or FUN_<addr>) <TAB> signature
  Docs/VTABLE_SLOTS.tsv   vtable address <TAB> Class <TAB> slot <TAB> function

Run after any refresh of the reference folder.
"""
import os
import re
import sys

REF = "Docs/reference/NpcServer_Ghidra"
HDR = re.compile(r"^// ==== (\S+) @ ([0-9a-f]{9})  (.*)$")


def main() -> int:
    if not os.path.isdir(REF):
        print("no reference folder at %s" % REF)
        return 1
    names = {}
    for fn in sorted(os.listdir(REF)):
        if not fn.endswith(".cpp"):
            continue
        with open(os.path.join(REF, fn), errors="ignore") as f:
            for line in f:
                m = HDR.match(line.rstrip("\n"))
                if m:
                    names[m.group(2)] = (m.group(1), m.group(3).strip())
    with open("Docs/FUN_NAME_MAP.tsv", "w") as out:
        out.write("address\tname\tsignature\n")
        for addr in sorted(names):
            name, sig = names[addr]
            out.write("%s\t%s\t%s\n" % (addr, name, sig))

    vt_path = os.path.join(REF, "_VTABLES.txt")
    slots = []
    cls = None
    with open(vt_path, errors="ignore") as f:
        for line in f:
            line = line.rstrip("\n")
            m = re.match(r"^(\S+)::vftable @ ([0-9a-f]{9})", line)
            if m:
                cls = m.group(1)
                slots.append(("%s" % m.group(2), cls, "-", "-"))
                continue
            m = re.match(r"^\s+\+(0x[0-9a-f]+)\s+(\S+)", line)
            if m and cls:
                slots.append((None, cls, m.group(1), m.group(2)))
    with open("Docs/VTABLE_SLOTS.tsv", "w") as out:
        out.write("vtable\tclass\tslot\tfunction\n")
        vt = None
        for row in slots:
            if row[0]:
                vt = row[0]
            out.write("%s\t%s\t%s\t%s\n" % (vt, row[1], row[2], row[3]))

    named = sum(1 for n, _ in names.values() if not n.startswith("FUN_"))
    print("functions: %d (named %d, unnamed %d)" % (len(names), named, len(names) - named))
    print("vtable slots: %d" % sum(1 for r in slots if r[0] is None))
    return 0


if __name__ == "__main__":
    sys.exit(main())
