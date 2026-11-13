#!/usr/bin/env python3
"""Transliterate the decompiled bodies, mechanically.

No logic is invented: each body is the listing's own text after a fixed, table-driven substitution. Three passes of
*mechanical* repair are applied, all of them recorded here rather than guessed at decode time:

 1. type names      Ghidra's spellings (`undefined8`, `longlong`, ...) become C equivalents.
 2. class names     a `Foo *` parameter whose class the unit never defines gets a `struct Foo;` forward declaration.
 3. vftable         `Foo::vftable` becomes the address the RTTI table records for `Foo`; a class with no row is left out.
 4. void promotion  a body the listing types `void` but whose callers read a value is declared to return one - the
                    same rule D201 established for the tail calls.
 5. tiers           a body whose whole call graph lives in the port is "linked" (compiled into the tested object); a
                    body that calls something still unported is "pending" - it compiles with a declaration, and is
                    parked behind TQ_TRANSLIT_PENDING until its callee lands.

A body that uses anything the tables cannot express is declined and reported, never approximated.

Sections are marked //@START <addr> / //@END so a build loop can drop one body without touching its neighbours.
"""
import re
import sys

SRC = "/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c"
OUT = "modules/npcserver/unattributed/transliterated.cpp"
VTABLE_TSV = "Docs/VTABLE_SLOTS.tsv"
DENY = "Docs/TRANSLIT_DENY.txt"

TYPES = [
    ("undefined8", "unsigned long long"),
    ("undefined4", "unsigned"),
    ("undefined2", "unsigned short"),
    ("undefined1", "unsigned char"),
    ("ulonglong", "unsigned long long"),
    ("longlong", "long long"),
    ("ulong", "unsigned long"),
    ("ushort", "unsigned short"),
    ("uchar", "unsigned char"),
    ("sbyte", "signed char"),
    ("uint", "unsigned"),
    ("byte", "unsigned char"),
    ("rsize_t", "size_t"),
    ("__uint64", "unsigned long long"),
    ("ULONG_PTR", "unsigned long long"),
]

CRT = {
    "operator_delete": ("void", "void* pPointer", "g_pfnNpcOperatorDelete(pPointer);"),
    "operator_new": ("void*", "size_t cbSize", "return g_pfnNpcOperatorNew(cbSize);"),
    "operator_delete__": ("void", "void* pPointer", "g_pfnNpcOperatorDelete(pPointer);"),
    "memmove_s": ("int", "void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc",
                  "g_pfnNpcMemmoveS(pDst, cbDst, pSrc, cbSrc); return 0;"),
    "memcpy": ("void*", "void* pDst, const void* pSrc, size_t cbSize", "return ::memcpy(pDst, pSrc, cbSize);"),
    "memset": ("void*", "void* pDst, int nValue, size_t cbSize", "return ::memset(pDst, nValue, cbSize);"),
    "strlen": ("size_t", "const char* pszText", "return ::strlen(pszText);"),
    "strcmp": ("int", "const char* pA, const char* pB", "return ::strcmp(pA, pB);"),
    "_invalid_parameter_noinfo": ("void", "void", "g_pfnNpcInvalidParameter();"),
    "__security_check_cookie": ("void", "unsigned long long nCookie", "(void)nCookie;"),
    "log_InlineLogERROR": ("void", "const void* pMsg, ...", "(void)pMsg;"),
}

REJECT = [
    "switch", "goto ", "LAB_", "code *", "unaff_", "in_stack_", "extraout_", "std::", "__thiscall",
    "__fastcall", "DAT_", "_guard_", "in_EAX", "in_RAX", "CONCAT", "SUB84", "SUB168", "ZEXT", "SEXT",
    "assert", "Ordinal_", "DWORD", "freeaddrinfo", "_open(", "_close(", "_read(", "_write(", "_lseek(", "_fstat64",
    "log_InlineLogWARNING", "log_InlineLogINFO", "TimeGet", "LPCRITICAL_SECTION",
    "type_info", "_1_1_", "undefined)", "LPCSTR", "LPVOID", "HWND", "LPCVOID", "exception", "undefined ", "LPCSTR",
    "va_list", "time_t", "FILE ", "(_locale_t)",
]

VTABLE = {}
CLASSES = set()


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


def load():
    src = open(SRC, errors="ignore").read()
    out = {}
    for part in re.split(r"\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()", src):
        part = part.split("\n// ====")[0].strip()
        m = re.match(r"([a-zA-Z_][\w \*]*?)\b(FUN_[0-9a-fA-F]{9})\((.*?)\)\s*\n\n\{\n(.*)\n\}$", part, re.S)
        if m:
            out[m.group(2)] = (m.group(1).strip(), m.group(3).strip(), m.group(4))
    return out


def map_types(text):
    for a, b in TYPES:
        text = re.sub(r"\b%s\b" % a, b, text)
    return text


def rename_params(text):
    return re.sub(r"\bparam_(\d+)\b", r"arg\1", text)


def split_args(args):
    if not args or args.strip() == "void":
        return []
    return [a.strip() for a in args.split(",")]


def signature(name, ret, args, promote):
    ret_c = map_types(ret).strip()
    m_ret = re.match(r"([A-Z]\w*) \*$", ret_c)
    if m_ret:
        CLASSES.add(m_ret.group(1))
    if promote and ret_c == "void":
        ret_c = "unsigned long long"
    if ret_c in ("", "code"):
        return None
    params = []
    for i, a in enumerate(split_args(args), 1):
        a = map_types(a).strip()
        if a == "...":
            params.append("...")
            continue
        if a.endswith("*"):
            params.append("%sarg%d" % (a, i))
            base = a.rstrip("*").strip().replace("const ", "")
            if re.fullmatch(r"[A-Z]\w*", base):
                CLASSES.add(base)
            continue
        m = re.match(r"(.+?)\s*\bparam_(\d+)$", a)
        if m:
            params.append("%s arg%d" % (m.group(1), i))
        elif re.fullmatch(r"arg%d" % i, a.replace("param_", "arg")):
            params.append("unsigned long long arg%d" % i)
        else:
            params.append(a)
    return "%s %s(%s)" % (ret_c, name, ", ".join(params) if params else "void")


def rewrite_body(body):
    body = rename_params(map_types(body))
    body = re.sub(r"\b([A-Z]\w*)::vftable\b",
                  lambda m: ("g_pNpcVtblTrans_%x" % VTABLE[normalise(m.group(1))])
                  if normalise(m.group(1)) in VTABLE else m.group(0), body)
    for name in re.findall(r"\b([A-Z]\w* *)\*", body):
        pass
    for name in re.findall(r"\(([A-Z]\w*) \*\)", body):
        CLASSES.add(name)
    for name in re.findall(r"(?m)^\s*([A-Z]\w*) \*", body):
        CLASSES.add(name)
    return body


def main():
    global VTABLE
    VTABLE = load_vtables()
    bodies = load()
    try:
        deny = set(open(DENY, errors="ignore").read().split())
    except FileNotFoundError:
        deny = set()

    import glob
    syms = {}
    try:
        for line in open("Docs/TRANSLIT_SYMS.tsv", errors="ignore"):
            f = line.rstrip("\n").split("\t")
            if len(f) == 2:
                syms.setdefault(f[0], f[1])
    except FileNotFoundError:
        pass

    declared_headers = {}
    for path in glob.glob("modules/npcserver/**/*.h", recursive=True):
        for line in open(path, errors="ignore"):
            m = re.search(r"\bFUN_(1[0-9a-f]{8})\s*\(", line)
            if m and ";" in line:
                name = "FUN_" + m.group(1)
                decl = line.split(";")[0].strip()
                decl = re.sub(r"^(extern|static)\s+", "", decl)
                declared_headers.setdefault(name, decl)

    # A callee counts as available only when an object the suite links really defines it: the symbol table of those
    # objects is the authority (tools/build_objects.sh writes it before every run).
    defined = set()
    try:
        defined = {(x if x.startswith("FUN_") else "FUN_" + x)
                   for x in open("Docs/TRANSLIT_AVAILABLE.txt", errors="ignore").read().split()}
    except FileNotFoundError:
        pass

    # a body the listing types void but whose callers read a value returns one (rule from D201).
    # Line-based: a call that fills a whole statement is a discard; anything else reads the result.
    promote = set()
    value_read = set()
    for name, (ret, args, body) in bodies.items():
        for line in body.splitlines():
            for callee in re.findall(r"\b(FUN_[0-9a-f]{9})\s*\(", line):
                if not re.match(r"\s*%s\s*\(.*\)\s*;\s*$" % callee, line):
                    value_read.add(callee)
        for line in body.splitlines():
            for callee in re.findall(r"\b(FUN_[0-9a-f]{9})\s*\(", line):
                if callee not in bodies or bodies[callee][0].strip() != "void":
                    continue
                if not re.match(r"\s*%s\s*\(.*\)\s*;\s*$" % callee, line):
                    promote.add(callee)

    candidates = []
    declined = {}
    for name in sorted(bodies):
        if name in defined or name[4:] in deny:
            continue
        ret, args, body = bodies[name]
        if name in promote and re.search(r"return\s*;", body):
            promote.discard(name)
        raw = "%s %s(%s)\n{\n%s\n}" % (ret, name, args, body)
        bad = next((t for t in REJECT if t in raw), None)
        if bad:
            declined[bad] = declined.get(bad, 0) + 1
            continue
        sig = signature(name, ret, args, name in promote)
        if sig is None:
            declined["return type"] = declined.get("return type", 0) + 1
            continue
        text = rewrite_body(body)
        byval = False
        for cls in CLASSES:
            if re.search(r"\b%s\b(?!\s*\*)" % cls, text):
                byval = True
                break
        if byval:
            declined["class used by value"] = declined.get("class used by value", 0) + 1
            continue
        if "::vftable" in text:
            declined["vftable not in table"] = declined.get("vftable not in table", 0) + 1
            continue
        callees = {c for c in re.findall(r"\b(FUN_[0-9a-f]{9})\b", text)}
        candidates.append((name, sig, text, callees))

    emitted = {c[0] for c in candidates}
    usable = {}
    for name, sig, text, callees in candidates:
        for callee in callees:
            if callee in usable:
                continue
            if callee in bodies:
                decl = signature(callee, bodies[callee][0], bodies[callee][1], callee in value_read)
                if decl is None or next((t for t in REJECT if t in decl), None):
                    usable[callee] = False
                else:
                    usable[callee] = decl
    stable = False
    while not stable:
        stable = True
        keep = []
        for name, sig, text, callees in candidates:
            bad = {c for c in callees if c not in emitted and not usable.get(c)}
            if bad:
                declined["callee has no usable declaration"] = declined.get("callee has no usable declaration", 0) + 1
                emitted.discard(name)
                stable = False
                continue
            keep.append((name, sig, text, callees))
        candidates = keep
    # a body is only linkable when its whole call graph is: pending-ness propagates up the callers
    ok = {c[0] for c in candidates}
    changed = True
    while changed:
        changed = False
        for name, sig, text, callees in candidates:
            if name not in ok:
                continue
            if any(c not in ok and c not in defined for c in callees):
                ok.discard(name)
                changed = True

    linked = []
    pending = []
    for name, sig, text, callees in candidates:
        missing = {c for c in callees if c not in ok and c not in defined}
        (pending if missing else linked).append((name, sig, text, missing))

    lines = []
    lines.append("// Mechanically transliterated from NpcServer.exe.decompiled.c by tools/transliterate.py.")
    lines.append("// Each body is the listing's own text after a fixed type substitution: no logic was added, removed or")
    lines.append("// reordered. The linked tier compiles into the tested object; the pending tier needs a callee that has")
    lines.append("// not landed yet and is built only for a syntax check until then.")
    lines.append("#include <cstddef>")
    lines.append("#include <cstdio>")
    lines.append("#include <cstring>")
    lines.append('#include "modules/npcserver/unattributed/front-of-image.h"')
    lines.append('#include "modules/npcserver/unattributed/stl-global.h"')
    lines.append("")
    lines.append("namespace tq {")
    lines.append("")
    for crt, (ret, args, body) in sorted(CRT.items()):
        lines.append("static %s %s(%s) { %s }" % (ret, crt, args, body))
    lines.append("")
    if CLASSES:
        lines.append("// Classes the listing names but this unit never defines; only ever used behind a pointer.")
        for cls in sorted(CLASSES):
            lines.append("struct %s;" % cls)
        lines.append("")
    vtables = set()
    for _, _, text, _ in [(c[0], c[1], c[2], c[3]) for c in candidates]:
        vtables.update(re.findall(r"g_pNpcVtblTrans_[0-9a-f]+", text))
    for sym in sorted(vtables):
        lines.append("const void* const %s = (const void*)0x%x;" % (sym, int(sym.rsplit("_", 1)[1], 16)))
    if vtables:
        lines.append("")
    lines.append("// Declarations first, so the call graph needs no ordering.")
    for name, sig, text, missing in linked + pending:
        lines.append(sig + ";")
    external = {}
    for name, sig, text, missing in linked + pending:
        for callee in re.findall(r"\b(FUN_[0-9a-f]{9})\b", text):
            if callee in emitted or callee in external:
                continue
            decl = declared_headers.get(callee)
            if not decl and callee in syms:
                decl = "unsigned long long %s%s" % (callee, syms[callee])
            decl = decl or usable.get(callee)
            if decl and callee not in external:
                external[callee] = decl
    for callee in list(external):
        if callee in declared_headers:
            continue
    for callee in sorted(external):
        lines.append("extern " + external[callee] + ";   // defined elsewhere in the port")
    lines.append("")
    for name, sig, text, missing in pending:
        lines.append("// pending: %s needs %s" % (name, ", ".join(sorted(missing))))
    lines.append("")
    for name, sig, text, missing in linked:
        lines.append("//@START %s" % name[4:])
        lines.append("%s {\n%s\n}" % (sig, text))
        lines.append("//@END")
        lines.append("")
    if pending:
        lines.append("#ifdef TQ_TRANSLIT_PENDING")
        lines.append("")
        for name, sig, text, missing in pending:
            lines.append("//@PENDING %s" % name[4:])
            lines.append("%s {\n%s\n}" % (sig, text))
            lines.append("")
        lines.append("#endif  // TQ_TRANSLIT_PENDING")
    lines.append("")
    lines.append("// The unit's own account of what it carries, so a suite can hold it to the report.")
    lines.append("extern const unsigned long long g_aNpcTranslitAddr[];")
    lines.append("extern const unsigned long long g_aNpcTranslitAddr[] = {")
    for name in sorted(n for n, _, _, _ in linked + pending):
        lines.append("    (unsigned long long)0x%sULL," % name[4:])
    lines.append("};")
    lines.append("extern const unsigned g_nNpcTranslitCount = %d;" % (len(linked) + len(pending)))
    lines.append("extern const unsigned g_nNpcTranslitLinked = %d;" % len(linked))
    lines.append("extern const unsigned g_nNpcTranslitPending = %d;" % len(pending))
    lines.append("")
    lines.append("}  // namespace tq")

    open(OUT, "w").write("\n".join(lines) + "\n")
    print("linked %d bodies, pending %d" % (len(linked), len(pending)))
    for k, v in sorted(declined.items(), key=lambda kv: -kv[1])[:8]:
        print("  declined: %-24s %d" % (k, v))
    return 0


if __name__ == "__main__":
    sys.exit(main())
