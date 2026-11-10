#!/usr/bin/env python3
"""Guard the NpcServer tree: every folder must be a real nesting level of one of the 50 paths the binary embeds.

The list in Docs/NPCSERVER_PATHS.md is extracted from the image, so it is the only authority. A folder that is not
a prefix of a listed path is invented; a listed path without a file is scaffolding that has to be created.
"""
import os, re, sys

ROOT = 'modules/npcserver/src'
DOC = 'Docs/NPCSERVER_PATHS.md'


def listed():
    out = []
    for line in open(DOC, encoding='utf-8'):
        m = re.match(r'\|\s*`([^`]+)`', line)
        if m:
            out.append(m.group(1))
    return out


def main():
    paths = listed()
    missing = [p for p in paths if not os.path.exists(os.path.join(ROOT, p))]
    on_disk = set()
    for root, dirs, _ in os.walk(ROOT):
        for d in dirs:
            on_disk.add(os.path.relpath(os.path.join(root, d), ROOT).replace(os.sep, '/'))
    prefixes = set()
    for p in paths:
        parts = p.split('/')
        for i in range(1, len(parts)):
            prefixes.add('/'.join(parts[:i]))
    stray = sorted(on_disk - prefixes)
    # a folder name that itself contains a separator cannot exist, but a name that merely looks like one can
    for d in sorted(on_disk):
        if '/' in os.path.basename(d):
            stray.append(d + '  (separator inside a single name)')
    print('paths listed: %d, present: %d' % (len(paths), len(paths) - len(missing)))
    for p in missing:
        print('  missing: %s' % p)
    for d in stray:
        print('  invented: %s' % d)
    return 1 if (missing or stray) else 0


if __name__ == '__main__':
    sys.exit(main())
