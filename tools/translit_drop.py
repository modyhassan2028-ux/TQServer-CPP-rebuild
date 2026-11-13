#!/usr/bin/env python3
"""Map compiler errors back to the marked section that owns the line and add those addresses to the deny list."""
import re, sys

path = "modules/npcserver/unattributed/transliterated.cpp"
errors = open(sys.argv[1], errors="ignore").read().splitlines()
lines = open(path, errors="ignore").read().splitlines()

owner = {}
current = None
for i, line in enumerate(lines, 1):
    m = re.match(r"//@(?:START|PENDING) (\w+)", line)
    if m:
        current = m.group(1)
    owner[i] = current
    if line.startswith("//@END"):
        current = None

deny = set(open("Docs/TRANSLIT_DENY.txt", errors="ignore").read().split())
for line in errors:
    m = re.match(r"[^:]+:(\d+):\d+: error:", line)
    if not m:
        continue
    n = int(m.group(1))
    addr = owner.get(n)
    if addr:
        deny.add(addr)
        continue
    # a declaration that will not compile costs the bodies that need it, not the whole unit
    for callee in re.findall(r"\bFUN_([0-9a-f]{9})\b", line):
        deny.add(callee)

open("Docs/TRANSLIT_DENY.txt", "w").write("\n".join(sorted(deny)) + "\n")
