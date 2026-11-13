"""Cut the `_DAT_` blobs out of the image, byte for byte.

Ghidra writes `_DAT_<addr>` for data it found but has no symbol for.  The image has the bytes, so the port keeps them
rather than describing them: each symbol becomes a byte array whose contents are exactly what sits at that address,
and the bodies keep passing `&_DAT_x` the way the listing does.  Nothing interprets the blob.
"""
import glob, re, struct, sys

EXE = "/app/co_decomp/orig_binaries/Source/NpcServer.exe"
SIZE = 32  # four pointers: the widest use in this listing is a ThrowInfo/RTTI blob


def sections(d):
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    nsec = struct.unpack_from("<H", d, pe + 6)[0]
    opt = struct.unpack_from("<H", d, pe + 20)[0]
    base = struct.unpack_from("<Q", d, pe + 24 + 24)[0]
    out, sec = [], pe + 24 + opt
    for i in range(nsec):
        o = sec + i * 40
        vsz, va, rsz, ptr = struct.unpack_from("<IIII", d, o + 8)
        out.append((va, vsz, ptr, rsz))
    return base, out


def main():
    d = open(EXE, "rb").read()
    base, secs = sections(d)
    addrs = set()
    for p in glob.glob("Docs/reference/NpcServer_Ghidra/**/*.c*", recursive=True):
        addrs.update(re.findall(r"_DAT_([0-9a-f]{9})\b", open(p, errors="ignore").read()))
    lines_h = ["// Blobs the listing spells `_DAT_<addr>`; bytes cut from NpcServer.exe at that address.",
               "#ifndef TQ_NPCSERVER_UNDERSCORE_DATA_H", "#define TQ_NPCSERVER_UNDERSCORE_DATA_H", ""]
    lines_c = ["#include \"npc-underscore-data.h\"", ""]
    for a in sorted(addrs):
        addr = int(a, 16)
        rva = addr - base
        blob = None
        for va, vsz, ptr, rsz in secs:
            if va <= rva < va + max(vsz, rsz):
                off = ptr + (rva - va)
                blob = d[off:off + SIZE]
                break
        if not blob or len(blob) < SIZE:
            print("skip %s" % a, file=sys.stderr)
            continue
        lines_h.append("extern \"C\" const unsigned char _DAT_%s[%d];" % (a, SIZE))
        lines_c.append("extern \"C\" const unsigned char _DAT_%s[%d] = {%s};"
                       % (a, SIZE, ", ".join("0x%02x" % b for b in blob)))
    lines_h.append("")
    lines_h.append("#endif  // TQ_NPCSERVER_UNDERSCORE_DATA_H")
    open("modules/npcserver/unattributed/npc-underscore-data.h", "w").write("\n".join(lines_h) + "\n")
    open("modules/npcserver/unattributed/npc-underscore-data.cpp", "w").write("\n".join(lines_c) + "\n")
    print("wrote %d blobs" % len(addrs))


if __name__ == "__main__":
    main()
