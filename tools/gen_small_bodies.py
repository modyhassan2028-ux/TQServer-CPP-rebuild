#!/usr/bin/env python3
"""Generate the cluster's mechanically safe bodies.

Only shapes that can be transcribed without a judgement call are accepted. Each generated body keeps the original
expression in the comment above it, and the manifest carries the shape so a suite can drive every entry. A shape that
does not match exactly is skipped, so a batch can never contain a guess.

Families (all verbatim):
  single expression : field get, deref get, module-base get, zero, identity, pointer add, size getter, compare, range
  guarded           : guarded field get
  write             : field store, pointer store
  iterator          : compare (two flavours), assign
  object            : vtable store, refcount destructing destructor, log-and-clear
  copy              : forward move in two decompiler spellings (A and B)
"""
import re
import sys

SRC = "/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c"
VTABLE_TSV = "Docs/VTABLE_SLOTS.tsv"

CTYPE = {
    "undefined8": "unsigned long long", "undefined4": "unsigned", "undefined2": "unsigned short",
    "undefined1": "unsigned char", "longlong": "long long", "uint": "unsigned", "int": "int",
    "ushort": "unsigned short", "short": "short", "byte": "unsigned char", "char": "char",
}
SIZE = {"undefined8": 8, "undefined4": 4, "undefined2": 2, "undefined1": 1, "longlong": 8,
        "uint": 4, "int": 4, "ushort": 2, "short": 2, "byte": 1, "char": 1}
VTYPE = {8: "unsigned long long", 4: "unsigned", 2: "unsigned short", 1: "unsigned char"}
VTABLE = {}


def normalise(name):
    name = name.replace("class_", "").replace("struct_", "").replace("enum_", "").replace("union_", "")
    name = name.replace(" ", "")
    while "_>" in name:
        name = name.replace("_>", ">")
    return name


def load_vtables():
    out = {}
    try:
        lines = open(VTABLE_TSV, errors="ignore").read().splitlines()[1:]
    except FileNotFoundError:
        return out
    for line in lines:
        f = line.split("\t")
        if len(f) >= 3 and f[0] and f[1]:
            out.setdefault(normalise(f[1]), int(f[0], 16))
    return out


def load_bodies():
    src = open(SRC, errors="ignore").read()
    out = {}
    for part in re.split(r"\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()", src):
        part = part.split("\n// ====")[0]
        m = re.match(r"[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(", part)
        if m:
            out[m.group(1)] = part.strip()
    return out


def defined_bodies():
    """addresses the port already defines, so a batch never re-emits one"""
    import glob
    out = set()
    for path in glob.glob("modules/npcserver/**/*") + glob.glob("modules/npcserver/**/**/*", recursive=True):
        if not (path.endswith(".cpp") or path.endswith(".h")):
            continue
        if path.endswith("small-bodies.cpp") or path.endswith("small-bodies.h"):
            continue   # our own output, rewritten below
        for line in open(path, errors="ignore"):
            m = re.match(r"^[A-Za-z_][\w \*]*?\bFUN_(1[0-9a-f]{8})\s*\(", line)
            if m:
                out.add("FUN_" + m.group(1))
    return out


T = "|".join(CTYPE)


def classify(body):
    m = re.search(r"\{\n(.*)\n\}", body, re.S)
    if not m:
        return None
    b = re.sub(r"\s+", " ", m.group(1).strip())

    # ---- single expressions -------------------------------------------------
    p = re.fullmatch(r"return \*\((%s) \*\)\(param_1 \+ (0x[0-9a-f]+)\);" % T, b)
    if p:
        return ("get-offset", SIZE[p.group(1)], int(p.group(2), 16), None)

    p = re.fullmatch(r"return \*\((%s) \*\)\*param_1;" % T, b)
    if p:
        return ("get-deref", SIZE[p.group(1)], 0, None)

    p = re.fullmatch(r"return \*\((%s) \*\)\(DAT_1401045b8 \+ (0x[0-9a-f]+)\);" % T, b)
    if p:
        return ("get-base", SIZE[p.group(1)], int(p.group(2), 16), None)

    if b == "return 0;":
        return ("zero", 8, 0, None)

    if b == "return param_1;":
        return ("identity", 8, 0, None)

    if b == "return *param_1;":
        return ("deref-get", 8, 0, None)

    if b == "return;":
        return ("noop", 0, 0, None)

    p = re.fullmatch(r"return param_1 \+ (0x[0-9a-f]+);", b)
    if p:
        return ("ptr-add", 8, int(p.group(1), 16), None)

    p = re.fullmatch(r"return \*\(longlong \*\)\(param_1 \+ (0x[0-9a-f]+)\) - "
                     r"\*\(longlong \*\)\(param_1 \+ (0x[0-9a-f]+)\) >> (\d);", b)
    if p:
        return ("size-getter", int(p.group(3)), int(p.group(1), 16), int(p.group(2), 16))

    p = re.fullmatch(r"return \*param_1 (==|!=) \*param_2;", b)
    if p:
        return ("compare", 8, 0, 0 if p.group(1) == "==" else 1)

    p = re.fullmatch(r"return param_1 - (0x[0-9a-f]+)U? < (\d+);", b)
    if p:
        return ("range", 4, int(p.group(1), 16), int(p.group(2)))

    # ---- guarded ------------------------------------------------------------
    p = re.fullmatch(r"if \(param_1 == 0\) \{ return 0; \} return \*\((%s) \*\)\(param_1 \+ (0x[0-9a-f]+)\);" % T, b)
    if p:
        return ("get-offset-guard", SIZE[p.group(1)], int(p.group(2), 16), None)

    # ---- writes -------------------------------------------------------------
    p = re.fullmatch(r"\*param_1 = param_2; return;", b)
    if p:
        return ("set-deref", 8, 0, None)

    p = re.fullmatch(r"\*\((undefined8|undefined4|undefined2|undefined1) \*\)\(param_1 \+ (0x[0-9a-f]+)\) = "
                     r"\((?:undefined8|undefined4|undefined2|undefined1)\)param_2; return;", b)
    if p:
        return ("set-offset", SIZE[p.group(1)], int(p.group(2), 16), None)

    # ---- iterators ----------------------------------------------------------
    p = re.fullmatch(r"if \(\(\*param_1 == 0\) \|\| \(\*param_1 != \*param_2\)\) \{ _invalid_parameter_noinfo\(\); \} "
                     r"return param_1\[1\] (==|!=) param_2\[1\];", b)
    if p:
        return ("iter-cmp", 8, 0, 0 if p.group(1) == "==" else 1)

    p = re.fullmatch(r"\*param_1 = 0; param_1\[1\] = param_2; if \(param_3 == \(undefined8 \*\)0x0\) \{ "
                     r"_invalid_parameter_noinfo\(\); \} \*param_1 = \*param_3; return param_1;", b)
    if p:
        return ("iter-assign", 8, 0, None)

    # ---- objects ------------------------------------------------------------
    p = re.fullmatch(r"\*param_1 = (\S+?)::vftable; return;", b)
    if p:
        addr = VTABLE.get(normalise(p.group(1)), 0)
        return ("vtable-set", 8, addr, None) if addr else None

    p = re.fullmatch(r"\*param_1 = (\S+?)::vftable; if \(\(param_2 & 1\) != 0\) \{ operator_delete\(param_1\); \} "
                     r"return param_1;", b)
    if p:
        addr = VTABLE.get(normalise(p.group(1)), 0)
        return ("refcount-dtor", 8, addr, None) if addr else None

    p = re.fullmatch(r"log_InlineLogERROR\(&DAT_1400be0b0\); \*param_2 = 0; param_2\[1\] = 0; return param_2;", b)
    if p:
        return ("log-clear-iter", 8, 0, None)

    # ---- the forward move, spelled two ways in the listing -------------------
    p = re.fullmatch(r"longlong lVar1; void \*_Dst; lVar1 = param_2 - \(longlong\)param_1 >> (\d); "
                     r"_Dst = \(void \*\)\(param_3 \+ lVar1 \* -(\d)\); if \(0 < lVar1\) \{ "
                     r"memmove_s\(_Dst,lVar1 \* (\d),param_1,lVar1 \* (\d)\); \} return _Dst;", b)
    if p:
        return ("move-a", int(p.group(3)), int(p.group(1)), None)

    p = re.fullmatch(r"rsize_t _DstSize; longlong lVar1; lVar1 = \*\(longlong \*\)\(param_2 \+ (0x[0-9a-f]+|\d+)\) - "
                     r"\(longlong\)\*\(void \*\*\)\(param_1 \+ (0x[0-9a-f]+|\d+)\) >> (\d+); "
                     r"_DstSize = lVar1 \* (\d+); if \(lVar1 != 0\) \{ "
                     r"memmove_s\(param_3,_DstSize,\*\(void \*\*\)\(param_1 \+ (0x[0-9a-f]+|\d+)\),_DstSize\); \} "
                     r"return \(void \*\)\(_DstSize \+ \(longlong\)param_3\);", b)
    if p:
        offA, offB, shift, size, offC = (int(p.group(i), 0) for i in range(1, 6))
        if not (offB == offC and size == 1 << shift):
            return None
        return ("move-b", size, offA, offB)

    # the third spelling: the same forward move written through a byte count, parameter-shifted by one
    p = re.fullmatch(r"rsize_t _DstSize; longlong lVar1; lVar1 = param_(\d) - \(longlong\)param_(\d) >> (\d); "
                     r"_DstSize = lVar1 \* (\d); if \(0 < lVar1\) \{ "
                     r"memmove_s\(param_(\d),_DstSize,param_(\d),_DstSize\); \} "
                     r"return \(void \*\)\(_DstSize \+ \(longlong\)param_(\d)\);", b)
    if p:
        q, pidx, shift, size, dst, src, ret = (int(p.group(i)) for i in range(1, 8))
        if not (q == pidx + 1 and src == pidx and dst == q + 1 and ret == dst and size == 1 << shift):
            return None
        return ("move-c", size, pidx, pidx - 1)

    return None


def emit_cpp(rows):
    out = ['// Generated by tools/gen_small_bodies.py from NpcServer.exe.decompiled.c.',
           '// Every body below is one shape the generator recognises verbatim; the original expression is kept in the',
           '// comment above it. Anything else belongs to a hand-written batch.',
           '#include "modules/npcserver/unattributed/small-bodies.h"',
           '#include "modules/npcserver/unattributed/front-of-image.h"',
           '#include "modules/npcserver/unattributed/module-singletons.h"',
           '#include "modules/npcserver/unattributed/stl-global.h"',
           '', 'namespace tq {', '']

    seen = set()
    for addr, kind, size, off, extra, text in rows:
        if kind in ("vtable-set", "refcount-dtor") and off not in seen:
            seen.add(off)
            out.append("// %s" % text)
            out.append("const void* const g_pNpcVtblGen_%x = (const void*)0x%x;" % (off, off))
            out.append("")
    out.append("")

    for addr, kind, size, off, extra, text in rows:
        out.append("// %s - %s   [%s]" % (addr, kind, text))
        ctype = VTYPE.get(size, "unsigned long long")
        if kind == "get-offset":
            out.append("unsigned long long FUN_%s(long long pObject) { return *(%s*)((char*)pObject + 0x%x); }"
                       % (addr, ctype, off))
        elif kind == "get-offset-guard":
            out.append("unsigned long long FUN_%s(long long pObject) {\n"
                       "    if (pObject == 0) {\n"
                       "        return 0;\n"
                       "    }\n"
                       "    return *(%s*)((char*)pObject + 0x%x);\n"
                       "}" % (addr, ctype, off))
        elif kind == "get-deref":
            out.append("unsigned long long FUN_%s(long long* pObject) { return *(%s*)*pObject; }" % (addr, ctype))
        elif kind == "get-base":
            out.append("unsigned long long FUN_%s(void) { return *(%s*)((char*)g_pNpcModuleBase_1401045b8 + 0x%x); }"
                       % (addr, ctype, off))
        elif kind == "zero":
            out.append("unsigned long long FUN_%s(void) { return 0; }" % addr)
        elif kind == "identity":
            out.append("unsigned long long FUN_%s(unsigned long long nValue) { return nValue; }" % addr)
        elif kind == "deref-get":
            out.append("unsigned long long FUN_%s(unsigned long long* pValue) { return *pValue; }" % addr)
        elif kind == "ptr-add":
            out.append("unsigned long long FUN_%s(unsigned long long nValue) { return nValue + 0x%x; }" % (addr, off))
        elif kind == "size-getter":
            out.append("long long FUN_%s(long long pObject) { return *(long long*)((char*)pObject + 0x%x) - "
                       "*(long long*)((char*)pObject + 0x%x) >> %d; }" % (addr, off, extra, size))
        elif kind == "compare":
            op = "==" if extra == 0 else "!="
            out.append("bool FUN_%s(long long* pA, long long* pB) { return *pA %s *pB; }" % (addr, op))
        elif kind == "range":
            out.append("bool FUN_%s(int nValue) { return (unsigned)nValue - 0x%xU < %d; }" % (addr, off, extra))
        elif kind == "set-deref":
            out.append("void FUN_%s(long long* pObject, long long nValue) { *pObject = nValue; }" % addr)
        elif kind == "set-offset":
            out.append("void FUN_%s(long long pObject, unsigned long long nValue) { *(%s*)((char*)pObject + 0x%x) = "
                       "(%s)nValue; }" % (addr, ctype, off, ctype))
        elif kind == "noop":
            out.append("void FUN_%s(void) { return; }" % addr)
        elif kind == "iter-cmp":
            op = "==" if extra == 0 else "!="
            out.append("bool FUN_%s(long long* pA, long long* pB) {\n"
                       "    if ((pA[0] == 0) || (pA[0] != pB[0])) {\n"
                       "        g_pfnNpcInvalidParameter();\n"
                       "    }\n"
                       "    return pA[1] %s pB[1];\n"
                       "}" % (addr, op))
        elif kind == "iter-assign":
            out.append("unsigned long long* FUN_%s(unsigned long long* pOut, unsigned long long nOwner, "
                       "unsigned long long* pSrc) {\n"
                       "    pOut[0] = 0;\n"
                       "    pOut[1] = nOwner;\n"
                       "    if (pSrc == 0) {\n"
                       "        g_pfnNpcInvalidParameter();\n"
                       "    }\n"
                       "    pOut[0] = pSrc[0];\n"
                       "    return pOut;\n"
                       "}" % addr)
        elif kind == "vtable-set":
            out.append("void FUN_%s(long long pThis) { *(const void**)pThis = g_pNpcVtblGen_%x; }" % (addr, off))
        elif kind == "refcount-dtor":
            out.append("long long* FUN_%s(long long* pThis, unsigned long long nFlags) {\n"
                       "    *(const void**)pThis = g_pNpcVtblGen_%x;\n"
                       "    if ((nFlags & 1) != 0) {\n"
                       "        g_pfnNpcOperatorDelete(pThis);\n"
                       "    }\n"
                       "    return pThis;\n"
                       "}" % (addr, off))
        elif kind == "log-clear-iter":
            out.append("unsigned long long* FUN_%s(long long pArg, unsigned long long* pOut) {\n"
                       "    g_pfnNpcInlineLogError((const void*)0x1400be0b0);\n"
                       "    pOut[0] = 0;\n"
                       "    pOut[1] = 0;\n"
                       "    return pOut;\n"
                       "}" % addr)
        elif kind == "move-a":
            out.append("void* FUN_%s(void* pFirst, long long nLast, long long pDst) {\n"
                       "    long long nCount = nLast - (long long)pFirst >> %d;\n"
                       "    void* pDstEnd = (void*)(pDst + nCount * -%d);\n"
                       "    if (0 < nCount) {\n"
                       "        g_pfnNpcMemmoveS(pDstEnd, (size_t)(nCount * %d), pFirst, (size_t)(nCount * %d));\n"
                       "    }\n"
                       "    return pDstEnd;\n"
                       "}" % (addr, off, size, size, size))
        elif kind == "move-c":
            nLead = off
            leads = "".join("long long pLead%d, " % (i + 1) for i in range(nLead - 1))
            out.append("void* FUN_%s(%svoid* pFirst, long long nLast, void* pDst) {\n"
                       "    long long nCount = nLast - (long long)pFirst >> %d;\n"
                       "    size_t cbBytes = (size_t)(nCount * %d);\n"
                       "    if (0 < nCount) {\n"
                       "        g_pfnNpcMemmoveS(pDst, cbBytes, pFirst, cbBytes);\n"
                       "    }\n"
                       "    return (void*)(cbBytes + (long long)pDst);\n"
                       "}" % (addr, leads, size.bit_length() - 1, size))
        elif kind == "move-b":
            offA = off
            offB = extra
            out.append("void* FUN_%s(long long pObjectA, long long pObjectB, void* pDst) {\n"
                       "    long long nCount = *(long long*)(pObjectB + 0x%x) - (long long)*(void**)(pObjectA + 0x%x) >> %d;\n"
                       "    size_t cbBytes = (size_t)(nCount * %d);\n"
                       "    if (nCount != 0) {\n"
                       "        g_pfnNpcMemmoveS(pDst, cbBytes, *(void**)(pObjectA + 0x%x), cbBytes);\n"
                       "    }\n"
                       "    return (void*)(cbBytes + (long long)pDst);\n"
                       "}" % (addr, offA, offB, size, size, offB))
        out.append("")
    out.append("const NpcSmallBodyEntry g_aNpcSmallBody[] = {")
    for addr, kind, size, off, extra, text in rows:
        extra_txt = "0" if extra is None else str(extra)
        out.append('    { "%s", "%s", %d, 0x%x, %s, (void*)&FUN_%s },'
                   % (addr, kind, size, off, extra_txt, addr))
    out.append("};")
    out.append("")
    out.append("const int g_nNpcSmallBody = %d;" % len(rows))
    out.append("")
    out.append("}  // namespace tq")
    return "\n".join(out) + "\n"


def main():
    global VTABLE
    VTABLE = load_vtables()
    bodies = load_bodies()
    defined = defined_bodies()
    rows = []
    for name, body in sorted(bodies.items()):
        if name in defined:
            continue
        if body.count("\n") + 1 > 16:
            continue
        shape = classify(body)
        if not shape:
            continue
        kind, size, off, extra = shape
        m = re.search(r"\{\n(.*)\n\}", body, re.S)
        text = re.sub(r"\s+", " ", m.group(1).strip())
        rows.append((name[4:], kind, size, off, extra, text))

    open("modules/npcserver/unattributed/small-bodies.h", "w").write("""// The small bodies of the cluster, generated by tools/gen_small_bodies.py.
//
// One shape per body, transcribed verbatim; the manifest carries the shape so a suite can drive every entry.
#ifndef TQ_NPCSERVER_SMALL_BODIES_H
#define TQ_NPCSERVER_SMALL_BODIES_H

namespace tq {

struct NpcSmallBodyEntry {
    const char* pszAddress;
    const char* pszKind;
    int         nSize;      // the width the body reads or writes, or the element size of a forward move
    long long   nOffset;    // the field the body reaches, the range base, or the vtable address
    long long   nExtra;     // the comparison kind, the range width, or a second field
    void*       pfn;
};

extern const NpcSmallBodyEntry g_aNpcSmallBody[];
extern const int g_nNpcSmallBody;

}  // namespace tq

#endif
""")
    open("modules/npcserver/unattributed/small-bodies.cpp", "w").write(emit_cpp(rows))

    kinds = {}
    for r in rows:
        kinds[r[1]] = kinds.get(r[1], 0) + 1
    print("generated %d bodies" % len(rows))
    for k, v in sorted(kinds.items(), key=lambda kv: -kv[1]):
        print("  %-18s %d" % (k, v))
    return 0


if __name__ == "__main__":
    sys.exit(main())
