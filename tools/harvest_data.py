#!/usr/bin/env python3
"""Decide the width of every DAT_ global from how the listing itself uses it.

No value is invented here: a global's size is the widest access the decompiler wrote anywhere in the image
(`*(undefined8 *)(DAT_x + 4)`, `DAT_x = 0x...`, `*(code **)(DAT_x)` ...). Everything else stays unknown and is
reported, so the bodies that need it keep waiting instead of being approximated.
"""
import glob, re, sys

WIDTH_OF = {"undefined8": 8, "longlong": 8, "ulonglong": 8, "uint64": 8, "int64": 8, "double": 8, "code": 8,
            "undefined4": 4, "uint": 4, "int": 4, "float": 4, "DWORD": 4, "BOOL": 4,
            "undefined2": 2, "ushort": 2, "short": 2, "WORD": 2,
            "undefined": 1, "char": 1, "byte": 1, "uchar": 1, "undefined1": 1}

WIDTHS = [
    (re.compile(r"\*(?:undefined8|longlong|ulonglong|uint64|int64|double)\s*\*"), 8),
    (re.compile(r"\*(?:code\s*\*\*?)\s*\)"), 8),
    (re.compile(r"\*\s*\(?\s*(?:longlong|ulonglong|code)\s*\*"), 8),
    (re.compile(r"\*(?:undefined4|uint|int|float|DWORD)\s*\*"), 4),
    (re.compile(r"\*(?:undefined2|ushort|short|WORD)\s*\*"), 2),
    (re.compile(r"\*(?:undefined|char|byte|uchar|BOOL)\s*\*"), 1),
]

def main():
    widths = {}          # name -> (size, evidence function)
    conflicts = {}
    for path in sorted(glob.glob("Docs/reference/NpcServer_Ghidra/**/*.c*", recursive=True)):
        text = open(path, errors="ignore").read()
        for block in re.split(r"(?m)^// ==== ", text):
            m = re.search(r"@\s*([0-9a-f]{6,10})", block.split("\n", 1)[0] + "\n" + (block.split("\n")[1] if "\n" in block else ""))
            fn = m.group(1) if m else "?"
            for line in block.splitlines():
                for dm in re.finditer(r"\bDAT_([0-9a-f]{9})\b", line):
                    name = "DAT_" + dm.group(1)
                    # only a cast applied straight to the name says anything: *(undefined4 *)(DAT_x + 8)
                    before = line[:dm.start()]
                    size = 0
                    cm = None
                    for rx, w in ((r"\*\s*\(\s*([A-Za-z0-9_ ]+?)\s*\*\s*\)\s*\(?\s*$", 0),):
                        cm = re.search(rx, before)
                    if cm:
                        t = cm.group(1).strip()
                        size = WIDTH_OF.get(t, 0)
                    if size == 0:
                        am = re.search(r"\b([A-Za-z0-9_ ]+?)\s*\*\s*$", before)
                        if am:
                            size = WIDTH_OF.get(am.group(1).strip().split()[-1], 0)
                    if size:
                        prev = widths.get(name)
                        if prev is None:
                            widths[name] = (size, fn)
                        elif size > prev[0]:
                            conflicts.setdefault(name, set()).add(prev[0])
                            widths[name] = (size, fn)
    with open("Docs/NPC_DATA_WIDTHS.tsv", "w") as f:
        f.write("name\tsize\tevidence\n")
        for name in sorted(widths):
            size, fn = widths[name]
            mixed = ""
            if name in conflicts:
                mixed = " (also seen at %s)" % ", ".join(str(x) for x in sorted(conflicts[name]))
            f.write("%s\t%d\t0x%s%s\n" % (name, size, fn, mixed))
    print("resolved %d globals, %d with mixed-width evidence" % (len(widths), len(conflicts)))

if __name__ == "__main__":
    main()
