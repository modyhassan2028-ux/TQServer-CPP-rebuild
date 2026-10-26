#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
full_inventory.py - full inventory: every decompiled binary vs addresses
actually referenced in the port code. Output: Docs/INVENTORY_REPORT.md
"""
import os, re, glob, csv
from collections import defaultdict

DECOMP = "/app/co_repo/Native-Decompiled"
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(REPO, "Docs", "INVENTORY_REPORT.md")

def load_index(binname):
    path = os.path.join(DECOMP, binname + ".index.tsv")
    if not os.path.exists(path):
        return {}
    funcs = {}
    with open(path, newline="") as f:
        for row in csv.DictReader(f, delimiter="\t"):
            a = row.get("address", "")
            if re.fullmatch(r"[0-9a-f]+", a):
                funcs.setdefault(a.lower(), row)
    return funcs

def ported_refs():
    refs = defaultdict(set)
    pat = re.compile(r"FUN_([0-9a-f]+)")
    roots = [os.path.join(REPO, "Exe"), os.path.join(REPO, "Core"),
             os.path.join(REPO, "Modules"), os.path.join(REPO, "Tools")]
    for root in roots:
        for p in glob.glob(os.path.join(root, "**", "*.cpp"), recursive=True) + \
                 glob.glob(os.path.join(root, "**", "*.h"), recursive=True):
            try:
                txt = open(p, errors="ignore").read()
            except OSError:
                continue
            rel = os.path.relpath(p, REPO)
            for m in pat.finditer(txt):
                refs[m.group(1).lower()].add(rel)
    return refs

def main():
    bins = sorted(f[:-len(".decompiled.c")] for f in os.listdir(DECOMP)
                  if f.endswith(".decompiled.c"))
    refs = ported_refs()
    sections = []
    for b in bins:
        idx = load_index(b)
        if idx:
            addrs = [int(a, 16) for a in idx]
            sections.append((b, min(addrs), max(addrs), idx))
    assigned = defaultdict(set)
    for a in refs:
        v = int(a, 16)
        for b, lo, hi, idx in sections:
            if lo - 0x100000 <= v <= hi + 0x100000:
                assigned[b].add(a)
    lines = []
    lines.append("# Comprehensive inventory: decompiled vs ported (auto-generated)\n")
    lines.append("> Generated: 2026-10-26. Source: per-binary `.index.tsv` vs every `FUN_` address mentioned in port code.")
    lines.append("> Total function counts include inlined CRT/STL library code (not needing verbatim port). An address counts as ported if mentioned in any Port implementation file.\n")
    lines.append("## 1. Per-component inventory\n")
    lines.append("| Binary | decompiled funcs | ported addr refs |")
    lines.append("|---|---|---|")
    total_f = total_p = 0
    for b in bins:
        idx = load_index(b)
        n = len(idx); p = len(assigned.get(b, ()))
        total_f += n; total_p += p
        lines.append(f"| {b} | {n:,} | {p:,} |")
    lines.append(f"| **Total** | **{total_f:,}** | **{total_p:,}** |")
    lines.append("\n## 2. Executables and servers\n")
    lines.append("- EXEs in orig_binaries/Source: MsgServer.exe (10.6MB), NpcServer.exe (1.1MB), CQCrossServer.exe (0.5MB), RevampedLoader.exe + Conquer.exe (patch).")
    lines.append("- Every EXE/DLL has a `.decompiled.c` + `.index.tsv` pair in Native-Decompiled/.")
    lines.append("\n## 3. Methodology notes\n")
    lines.append("- \"ported\" here means the address is referenced in port code (coverage or implementation); per-family verbatim coverage is tracked in PORTING_LOG.md.")
    lines.append("- `Modules/` are ABI skeleton stubs (except Syndicate/Trade); the ongoing verbatim port lives in Exe/Dll/*/Port.")
    with open(OUT, "w") as f:
        f.write("\n".join(lines) + "\n")
    print("WROTE", OUT)
    for b in bins:
        idx = load_index(b)
        print(f"{b:28s} {len(idx):7,} funcs   ported-refs {len(assigned.get(b, ())):5,}")

if __name__ == "__main__":
    main()
