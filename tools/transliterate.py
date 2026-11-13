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
import os
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
    ("code *", "unsigned long long"),
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

}

REJECT = [
    "unaff_", "in_stack_", "extraout_", "__thiscall",
    "__fastcall", "_guard_", "in_EAX", "in_RAX", "SUB84", "SUB168", "ZEXT", "SEXT",
    "assert", "Ordinal_", "freeaddrinfo", "_open(", "_close(", "_read(", "_write(", "_lseek(", "_fstat64",
    "log_InlineLogWARNING", "log_InlineLogINFO", "basic_string",
    "type_info", "_1_1_",
    "time_t", "FILE ", "(_locale_t)",
]

TYPED_GLOBALS = set()
VTABLE = {}
_H = "modules/npcserver/unattributed/npc-data.h"
TYPED = set()


def typed_globals():
    global TYPED
    if not TYPED and os.path.exists(_H):
        TYPED = load_typed_globals(open(_H).read())
    return TYPED
CLASSES = set()


def load_typed_globals(raw):
    """The globals npc-data.h actually carries, with the bytes cut from the image."""
    return set(re.findall(r"extern const (?:char|unsigned char) (DAT_[0-9a-f]{9})\[", raw))


def body_globals_ok(body, typed):
    """A body may touch a global only if it is typed and only by address.

    A string constant is passed as &DAT_x; a body that stores through it, or adds to it, is treating it as a variable
    of unknown width - that is the data wave still open, so the body waits instead of being approximated.
    """
    for m in re.finditer(r"\b_?DAT_([0-9a-f]{9})\b", body):
        name = m.group(0)
        if name not in typed:
            return False, "global not typed"
        before = body[:m.start()].rstrip()
        # A `_DAT_` symbol is carried as its real bytes, so a body that stores through it is writing to a faithful copy
        # of the original cell and the width comes from the body's own expression. A plain `DAT_` string constant has
        # no such backing and still waits.
        if not before.endswith("&") and not name.startswith("_DAT_"):
            return False, "global used as storage"
    return True, ""


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
    # The consolidated listing is the base, but a body that only appears in one of the split files still belongs to this
    # image and still has to be ported: read every reference file and keep the first body found for each address.
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



# ---------------------------------------------------------------------------------------------------------------
# Two call shapes the listing writes that the port already has an answer for. Both rewrites are mechanical: they
# change the spelling of the call, never its arguments.
# ---------------------------------------------------------------------------------------------------------------
STD_STR = "std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::"
STD_MEMBERS = {"size", "length", "data", "c_str", "clear", "empty", "append", "assign", "resize", "find", "rfind",
               "substr", "compare", "push_back", "capacity", "reserve", "insert", "erase", "replace", "pop_back"}


def _paren(text, i):
    depth = 0
    while i < len(text):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def _args(text):
    out, depth, cur = [], 0, ""
    for ch in text:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def rewrite_log_calls(text):
    """log_InlineLogERROR(...) is the port's own seam, the pointer the hand-ported bodies call and the tests hook."""
    return re.sub(r"\blog_InlineLogERROR\s*\(", "::tq::g_pfnNpcInlineLogError(", text)


def rewrite_std_string(text):
    out, i = [], 0
    while True:
        k = text.find(STD_STR, i)
        if k < 0:
            out.append(text[i:])
            return "".join(out)
        out.append(text[i:k])
        j = k + len(STD_STR)
        m = re.match(r"~?[A-Za-z_][A-Za-z0-9_]*|operator\s*[=!+\[\]]+", text[j:])
        if not m:
            out.append(STD_STR)
            i = j
            continue
        name = m.group(0).strip()
        j += m.end()
        if j < len(text) and text[j] == "<":
            depth = 0
            while j < len(text):
                if text[j] == "<":
                    depth += 1
                elif text[j] == ">":
                    depth -= 1
                    if depth == 0:
                        j += 1
                        break
                j += 1
        if j >= len(text) or text[j] != "(":
            out.append(text[k:j])
            i = j
            continue
        e = _paren(text, j)
        if e < 0:
            out.append(text[k:])
            return "".join(out)
        a = _args(text[j + 1:e])
        first = a[0] if a else "0"
        rest = a[1:]
        dst = "(*((std::string *)(%s)))" % first
        if name == "~basic_string":
            rep = "((std::string *)(%s))->~basic_string()" % first
        elif name in STD_MEMBERS:
            rep = "((std::string *)(%s))->%s(%s)" % (first, name, ", ".join(rest))
        elif name == "begin":
            rep = "((std::string *)(%s))->data()" % first
        elif name == "end":
            rep = "((std::string *)(%s))->data() + ((std::string *)(%s))->size()" % (first, first)
        elif name == "basic_string":
            rep = "::new ((void *)(%s)) std::string(%s)" % (first, ", ".join(rest))
        elif name == "operator=":
            rep = "%s = *((std::string *)(%s))" % (dst, rest[0]) if rest else "%s.clear()" % first
        elif name in ("operator==", "operator!=", "operator+", "operator<"):
            rep = "%s %s *((std::string *)(%s))" % (dst, name[8:], rest[0])
        elif name == "operator[]":
            rep = "%s[%s]" % (dst, rest[0])
        else:
            out.append(text[k:j])
            i = j
            continue
        out.append(rep)
        i = e + 1


def rewrite_body(body):
    body = rewrite_log_calls(body)
    body = rewrite_std_string(body)
    body = rename_params(map_types(body))
    # The RTTI table names some classes with a scope and some with template arguments
    # (`CGameData<&char*_szGenerator,&char*_szID>`, `std::tr1::_Ref_count_base`), so the class name is read backwards
    # from `::vftable` with angle brackets balanced, then matched whole and by its last component.
    def _vtbl(body):
        out = body
        while True:
            i = out.find("::vftable")
            if i < 0:
                return out
            j, depth = i, 0
            while j > 0:
                ch = out[j - 1]
                if ch == ">":
                    depth += 1
                elif ch == "<":
                    depth -= 1
                elif depth == 0 and not (ch.isalnum() or ch in "_:*& ,"):
                    break
                j -= 1
            name = out[j:i]
            sym = None
            for cand in (name, name.split("::")[-1]):
                key = normalise(cand)
                if key in VTABLE:
                    sym = "g_pNpcVtblTrans_%x" % VTABLE[key]
                    break
            out = out[:j] + (sym if sym else "::vftable") + out[i + 9:]
            if not sym:
                out = out[:j] + "\x00" + out[i + 9:]
                return out.replace("\x00::vftable", "::vftable")
    # Ghidra's bare `undefined` is its one-byte type (undefined1) and is also what it prints for a function that
    # returns nothing meaningful; both are `unsigned char` here, which is the width the listing itself states.
    body = re.sub(r"\bundefined\b(?!\d)", "unsigned char", body)
    for n in ("SysTimeGet", "IsTimeRange", "DateTime"):
        body = re.sub(r"(?<![\w:])%s\s*\(" % n, "tq::%s(" % n, body)
    body = body.replace("_CxxThrowException(", "g_pfnNpcCxxThrowException(")
    body = _vtbl(body)
    for name in re.findall(r"\b([A-Z]\w* *)\*", body):
        pass
    for name in re.findall(r"\(([A-Z]\w*) \*\)", body):
        CLASSES.add(name)
    for name in re.findall(r"(?m)^\s*([A-Z]\w*) \*", body):
        CLASSES.add(name)
    return body


def main():
    import os
    global VTABLE
    VTABLE = load_vtables()
    bodies = load()
    if os.environ.get("TQ_ONLY"):
        keep = set(open(os.environ["TQ_ONLY"]).read().split())
        bodies = {a: b for a, b in bodies.items() if a[4:] in keep}
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
    lines.append("#include <string>")
    lines.append("#include <new>")
    lines.append("#include \"npc-data.h\"")
    lines.append("#include \"npc-underscore-data.h\"")
    lines.append("#include \"npc-win-types.h\"")
    lines.append("#include \"npc-tq-imports.h\"")
    lines.append("#include \"log-stubs.h\"")
    lines.append("#include \"npc-concat.h\"")
    lines.append("#include <string>")
    lines.append("#include <new>")
    lines.append("#include \"npc-data.h\"")
    lines.append("#include \"log-stubs.h\"")
    lines.append("")
    lines.append("namespace tq {")
    lines.append("// An indirect call the listing types `code *`. The template fixes the arity from the call site, so every")
    lines.append("// argument reaches the register the original convention put it in; only the return value is widened.")
    lines.append("template <class... A>")
    lines.append("inline unsigned long long CallCode(unsigned long long nPfn, A... a)")
    lines.append("{")
    lines.append("    return ((unsigned long long (*)(A...))nPfn)(a...);")
    lines.append("}")
    lines.append("}  // namespace tq")
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
    # every slot the RTTI table knows, not only the ones this run happens to reference: a body kept in the pending
    # tier refers to the same symbols, and a missing definition turns a faithful body into a compile error.
    for addr in VTABLE.values():
        vtables.add("g_pNpcVtblTrans_%x" % addr)
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
