#!/usr/bin/env python3
"""How much of the binary is actually in the port.

Total   - every function the decompiled listing carries.
Defined - bodies the port defines (a FUN_ definition in modules/npcserver/**/*.cpp).
Manifest- bodies reachable from a suite manifest.
"""
import glob
import re

SRC = "/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c"


def main():
    total = sum(1 for line in open(SRC, errors="ignore") if line.startswith("// Function: "))
    defined = set()
    for path in glob.glob("modules/npcserver/**/*.cpp", recursive=True):
        for line in open(path, errors="ignore"):
            m = re.match(r"^[A-Za-z_][\w \*]*\bFUN_(1[0-9a-f]{8})\s*\(", line)
            if m:
                defined.add(m.group(1))
            m = re.match(r"^\s*\*?\s*FUN_(1[0-9a-f]{8})\s*\(", line)
            if m:
                defined.add(m.group(1))
    manifest = set()
    for path in glob.glob("modules/npcserver/**/*.cpp", recursive=True):
        for m in re.finditer(r'"\s*(1[0-9a-f]{8})\s*",\s*"', open(path, errors="ignore").read()):
            manifest.add(m.group(1))
    print("total functions : %d" % total)
    print("defined bodies  : %d  (%.1f%%)" % (len(defined), 100.0 * len(defined) / total))
    print("manifest entries: %d" % len(manifest))
    print("remaining       : %d" % (total - len(defined)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
