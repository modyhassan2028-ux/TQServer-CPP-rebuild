#!/usr/bin/env python3
"""Extract the original CGameAction factory map from the decompiled MsgServer.exe.

FUN_1402b6710 is CGameAction::CreateAction: a switch on (actionType - 0x3ec)
that operator_news the right action class and calls its ctor. This script maps
every supported action type -> ctor function -> ctor's vftable class name,
verbatim from the decompiled C. Output: tools/gameaction/action_types.json
"""
import re, json, os, sys

DEC = "../conquer-online-v6159-decompiled/Native-Decompiled/MsgServer.exe.decompiled.c"
BASE = 0x3ec  # switch is on (type - 0x3ec)

src = open(DEC, encoding="utf-8", errors="replace").read()

def fn_body(name):
    m = re.search(r"// Function: %s @.*?\n// =+\n(.*?)(?=\n// Function:|\Z)" % re.escape(name), src, re.S)
    return m.group(1) if m else None

body = fn_body("FUN_1402b6710")
if not body:
    sys.exit("factory not found")

# main switch: case N: ... FUN_ctor(new) ... break
cases = {}
cur = None
for line in body.splitlines():
    m = re.match(r"\s*case (0x[0-9a-f]+|[0-9]+):", line)
    if m:
        cur = int(m.group(1), 0)
        continue
    m = re.search(r"plVar3 = \(longlong \*\)FUN_([0-9a-f]+)\(pvVar2\);", line)
    if m and cur is not None:
        cases.setdefault(cur, m.group(1))
# special: param_4 == 0x523
if re.search(r"param_4 == 0x523", body):
    m = re.search(r"FUN_([0-9a-f]+)\(pvVar2\);", body.split("param_4 == 0x523",1)[1][:400])
    if m: cases[0x523 - BASE] = m.group(1)

out = []
for case, ctor in sorted(cases.items()):
    cb = fn_body("FUN_" + ctor) or ""
    cls = re.search(r"(\w+)::vftable", cb)
    out.append({
        "type": BASE + case,
        "ctor": "0x" + ctor,
        "class": cls.group(1) if cls else "?",
    })

json.dump(out, open("tools/gameaction/action_types.json", "w"), indent=1)
print(f"{len(out)} action types extracted")
for e in out:
    print(f"  {e['type']:5} -> {e['class']:20} (ctor {e['ctor']})")
