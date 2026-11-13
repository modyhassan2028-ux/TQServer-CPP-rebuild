"""Cut every `DAT_<addr>` the listing still needs out of the image, byte for byte.

A `DAT_` symbol is data the port has not named. Rather than describe it, the bytes are taken from `NpcServer.exe` at
that exact address and declared as an array, so a body that passes the address, indexes it, or stores through it is
working with the original contents. Symbols the port already declares are left alone.
"""
import glob, re, struct

EXE = "/app/co_decomp/orig_binaries/Source/NpcServer.exe"
SIZE = 32
HDR = "modules/npcserver/unattributed/npc-underscore-data.h"
CPP = "modules/npcserver/unattributed/npc-underscore-data.cpp"


def sections(d):
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    opt = struct.unpack_from("<H", d, pe + 20)[0]
    base = struct.unpack_from("<Q", d, pe + 24 + 24)[0]
    sec = pe + 24 + opt
    out = []
    for i in range(n):
        o = sec + i * 40
        vsz, va, rsz, ptr = struct.unpack_from("<IIII", d, o + 8)
        out.append((va, vsz, ptr, rsz))
    return base, out


def main():
    d = open(EXE, "rb").read()
    base, secs = sections(d)

    def cut(addr):
        rva = addr - base
        for va, vsz, ptr, rsz in secs:
            if va <= rva < va + max(vsz, rsz):
                return d[ptr + (rva - va):ptr + (rva - va) + SIZE]
        return None

    needed = set()
    for p in glob.glob("Docs/reference/NpcServer_Ghidra/*.c*"):
        needed |= set(re.findall(r"\b(DAT_[0-9a-f]{9})\b", open(p, errors="ignore").read()))
    declared = set()
    for p in glob.glob("modules/npcserver/**/*.h", recursive=True) + glob.glob("modules/npcserver/**/*.cpp", recursive=True):
        declared |= set(re.findall(r"\b(DAT_[0-9a-f]{9})\b", open(p, errors="ignore").read()))
    missing = sorted(needed - declared)

    hdr = open(HDR).read().splitlines()
    cpp = open(CPP).read().splitlines()
    added = []
    for sym in missing:
        blob = cut(int(sym[4:], 16))
        if not blob or len(blob) < SIZE:
            continue
        hdr.insert(-2, "extern unsigned char %s[%d];" % (sym, SIZE))
        cpp.append("unsigned char %s[%d] = {%s};" % (sym, SIZE, ", ".join("0x%02x" % b for b in blob)))
        added.append(sym)
    open(HDR, "w").write("\n".join(hdr) + "\n")
    open(CPP, "w").write("\n".join(cpp) + "\n")
    print("referenced:", len(needed), "already carried:", len(needed & declared), "new blobs:", len(added))


if __name__ == "__main__":
    main()
