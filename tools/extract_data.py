#!/usr/bin/env python3
"""Cut every DAT_ global the listing names out of the original image, byte for byte.

The image is the authority: a global the bodies pass as &DAT_x is a string, a ThrowInfo, a table - and the only honest
way to give it a value is to read it. Sizes come from the same evidence harvest_data.py uses for widths, and from the
string itself. A global that cannot be sized that way is reported and left undefined.
"""
import glob, re, struct, sys

IMG = "/app/co_decomp/orig_binaries/Source/NpcServer.exe"

def sections():
    data = open(IMG, "rb").read()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    optsz = struct.unpack_from("<H", data, pe + 0x14)[0]
    base = struct.unpack_from("<Q", data, pe + 0x18 + 24)[0]
    secs = []
    off = pe + 0x18 + optsz
    for i in range(nsec):
        va, vsz, rsz, rptr = struct.unpack_from("<IIII", data, off + i * 40 + 12 - 4)
        secs.append((va, vsz, rsz, rptr))
    return data, base, secs

def read(data, base, secs, va, n):
    rva = va - base
    for sva, vsz, rsz, rptr in secs:
        if sva <= rva < sva + max(vsz, rsz):
            fo = rptr + (rva - sva)
            return data[fo:fo + n]
    return b""

def main():
    data, base, secs = sections()
    widths = {}
    for line in open("Docs/NPC_DATA_WIDTHS.tsv"):
        f = line.rstrip("\n").split("\t")
        if len(f) >= 2 and f[1].isdigit():
            widths[f[0]] = int(f[1])
    used = set()
    for path in glob.glob("Docs/reference/NpcServer_Ghidra/**/*.c*", recursive=True):
        for m in re.finditer(r"\bDAT_([0-9a-f]{9})\b", open(path, errors="ignore").read()):
            used.add("DAT_" + m.group(1))

    out_h = ["// Globals cut out of the original image (tools/extract_data.py). Values are the image's own bytes.",
             "#pragma once", "", "namespace tq {", ""]
    out_c = ["#include \"npc-data.h\"", "", "namespace tq {", ""]
    strings = other = unsized = 0
    missing = []
    for name in sorted(used):
        va = int(name[4:], 16)
        blob = read(data, base, secs, va, 256)
        if not blob:
            missing.append(name)
            continue
        nul = blob.find(b"\x00")
        # a string is a run of bytes with no control character in it (high bytes included: this server logs in Korean),
        # terminated by a NUL inside a plausible length
        printable = nul > 0 and all(b >= 0x20 or b in (9, 10, 13) for b in blob[:nul])
        if printable and nul <= 512:
            chunk = read(data, base, secs, va, nul + 1)
            bytes_txt = ", ".join("(char)0x%02x" % b for b in chunk)
            out_c.append("extern const char %s[%d] = { %s };" % (name, nul + 1, bytes_txt))
            out_h.append("extern const char %s[%d];" % (name, nul + 1))
            strings += 1
            continue
        size = widths.get(name, 0)
        if not size:
            unsized += 1
            continue
        chunk = read(data, base, secs, va, size)
        bytes_txt = ", ".join("0x%02x" % b for b in chunk)
        out_c.append("extern const unsigned char %s[%d] = { %s };" % (name, size, bytes_txt))
        out_h.append("extern const unsigned char %s[%d];" % (name, size))
        other += 1
    out_h += ["", "}  // namespace tq", ""]
    out_c += ["", "}  // namespace tq", ""]
    open("modules/npcserver/unattributed/npc-data.h", "w").write("\n".join(out_h))
    open("modules/npcserver/unattributed/npc-data.cpp", "w").write("\n".join(out_c))
    print("strings %d, fixed-width %d, unsized %d, unreadable %d, of %d named"
          % (strings, other, unsized, len(missing), len(used)))

if __name__ == "__main__":
    main()
