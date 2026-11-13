"""Disassemble the bodies the port still owes, straight out of the image.

The listing gives C with widths washed out (`undefined`, `extraout_`, `SUB84`); the instruction stream has the real
widths. This writes that stream down so the next pass reads evidence instead of guessing: one block per function,
`addr  bytes  mnemonic operands`, from the function entry to the next known entry.
"""
import re, glob, struct, sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

EXE = "/app/co_decomp/orig_binaries/Source/NpcServer.exe"
OUT = "Docs/disasm/remaining.txt"


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

    def read(addr, n):
        rva = addr - base
        for va, vsz, ptr, rsz in secs:
            if va <= rva < va + max(vsz, rsz):
                o = ptr + (rva - va)
                return d[o:o + n]
        return None

    bodies = {}
    for p in glob.glob("Docs/reference/NpcServer_Ghidra/**/*.c*", recursive=True):
        for b in re.split(r"(?m)^// ==== ", open(p, errors="ignore").read()):
            m = re.search(r"FUN_(1[0-9a-f]{8})", b)
            if m:
                bodies.setdefault(m.group(1), b)
    defs = set()
    for p in glob.glob("modules/npcserver/**/*.cpp", recursive=True):
        for line in open(p, errors="ignore"):
            x = re.match(r"^[A-Za-z_][\w \*]*?\bFUN_(1[0-9a-f]{8})\s*\(", line)
            if x:
                defs.add(x.group(1))
    addrs = sorted(int(a, 16) for a in bodies)
    left = [a for a in addrs if ("%09x" % a) not in defs]
    nxt = {}
    for i, a in enumerate(addrs):
        nxt[a] = addrs[i + 1] if i + 1 < len(addrs) else a + 0x400

    md = Cs(CS_ARCH_X86, CS_MODE_64)
    md.detail = False
    out = ["# Disassembly of the %d bodies the port still owes, cut from NpcServer.exe" % len(left),
           "# addr        bytes                      instruction", ""]
    for a in left:
        code = read(a, min(nxt[a] - a, 0x400))
        if not code:
            continue
        out.append("// ==== FUN_%09x @ %09x" % (a, a))
        for ins in md.disasm(code, a):
            out.append("%09x  %-24s %s %s" % (ins.address, ins.bytes.hex(), ins.mnemonic, ins.op_str))
        out.append("")
    open(OUT, "w").write("\n".join(out) + "\n")
    print("wrote", OUT, len(left), "functions")


if __name__ == "__main__":
    main()
