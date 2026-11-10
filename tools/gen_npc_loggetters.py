#!/usr/bin/env python3
"""Transcribe the member getters that log when the member is still null.

Body shape, exactly (six bodies, offsets 8 / 0x10 / 0x18 / 0x20):

    v = *(long long*)(pThis + OFF); if (v == 0) { log(...); v = 0; } return v;

The log arguments are read out of the bytes around the call, not from the decompiler's rendering.
"""
import json, os, re, struct
import capstone

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
EXE = '/app/co_decomp/orig_binaries/Source/NpcServer.exe'
OUT_H = 'modules/npcserver/unattributed/log-getters.h'
OUT_C = 'modules/npcserver/unattributed/log-getters.cpp'
MANIFEST = '/tmp/npc_loggetters.json'

BODY = re.compile(r'^longlong FUN_[0-9a-f]{9}\(longlong param_1\) \{ longlong lVar1; '
                  r'lVar1 = \*\(longlong \*\)\(param_1 \+ (0x[0-9a-f]+|\d+)\); if \(lVar1 == 0\) \{ '
                  r'log_InlineLogERROR\(&DAT_1400be0b0\); lVar1 = 0; \} return lVar1; \}$')


def image():
    d = open(EXE, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    nsec = struct.unpack_from('<H', d, pe + 6)[0]
    optsz = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<Q', d, pe + 24 + 24)[0]
    secs = []
    off = pe + 24 + optsz
    for i in range(nsec):
        s = off + i * 40
        name = d[s:s + 8].rstrip(b'\0').decode('latin1')
        vsz, va, rawsz, rawptr = struct.unpack_from('<IIII', d, s + 8)
        secs.append((name, base + va, vsz, rawptr, rawsz))
    return d, secs


DATA, SECS = image()


def raw(va, n):
    for name, start, vsz, rawptr, rawsz in SECS:
        if start <= va < start + max(vsz, rawsz):
            o = rawptr + (va - start)
            return DATA[o:o + n]
    return b''


def rdcstr(va):
    for name, start, vsz, rawptr, rawsz in SECS:
        if start <= va < start + max(vsz, rawsz):
            o = rawptr + (va - start)
            return DATA[o:DATA.index(b'\0', o)]
    return None


def cliteral(b):
    out = []
    for ch in b:
        if ch == 0x22:
            out.append('\\"')
        elif ch == 0x5c:
            out.append('\\\\')
        elif 0x20 <= ch < 0x7f:
            out.append(chr(ch))
        else:
            out.append('\\x%02x' % ch)
    return '"%s"' % re.sub(r'(\\x[0-9a-f]{2})(?=[0-9a-fA-F])', r'\1""', ''.join(out))


MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)


def logcall(va):
    """Find the five-argument log call anywhere in the body and return its arguments."""
    ins = list(MD.disasm(raw(va, 200), va))
    for i in range(len(ins) - 6):
        win = ins[i:i + 6]
        if [x.mnemonic for x in win] != ['lea', 'lea', 'lea', 'lea', 'mov', 'call']:
            continue
        if [x.op_str.split(',')[0].strip() for x in win[:4]] != ['r9', 'r8', 'rdx', 'rcx']:
            continue
        mem, _, imm = win[4].op_str.partition(',')
        if mem.replace(' ', '') != 'dwordptr[rsp+0x20]':
            continue
        vals = []
        ok = True
        for x in win[:4]:
            m = re.match(r'\w+, \[rip \+ (0x[0-9a-f]+)\]', x.op_str)
            if not m:
                ok = False
                break
            b = rdcstr(int(m.group(1), 16) + x.address + x.size)
            if not b:
                ok = False
                break
            vals.append(b)
        if ok:
            return vals, int(imm.strip(), 16)
    return None


def bodies():
    src = open(DECOMP, errors='ignore').read()
    out = {}
    for part in re.split(r'\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()', src):
        part = part.split('\n// ====')[0]
        m = re.match(r'[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(', part)
        if m:
            out[m.group(1)] = re.sub(r'\s+', ' ', part).strip()
    return out


def repo_defined():
    out = set()
    for root, dirs, files in os.walk('modules'):
        for fn in files:
            if fn.endswith(('.c', '.cpp')) and fn != 'log-getters.cpp':
                t = open(os.path.join(root, fn), errors='ignore').read()
                out |= set(re.findall(r'\bFUN_([0-9a-f]{9})\b', t))
    return out


def main():
    done = set(open('/tmp/ported_addrs.txt').read().split()) if os.path.exists('/tmp/ported_addrs.txt') else set()
    blocked = repo_defined()
    got, skipped = {}, []
    for a, text in sorted(bodies().items()):
        m = BODY.match(text)
        if not m or a in done or a[4:] in blocked:
            continue
        r = logcall(int(a[4:], 16))
        if r is None:
            skipped.append(a)
            continue
        got[a] = {'offset': int(m.group(1), 16), 'args': [v.decode('latin1') for v in r[0]], 'line': r[1]}

    print('  member getters: %d  (unreadable: %d)' % (len(got), len(skipped)))
    for a in sorted(got):
        print('   %s  +0x%x  line %d' % (a, got[a]['offset'], got[a]['line']))

    h = ['// The member getters that log while their member is still null.',
         '//',
         '// Arguments read out of the machine code by tools/gen_npc_loggetters.py.',
         '#ifndef TQ_NPCSERVER_LOG_GETTERS_H',
         '#define TQ_NPCSERVER_LOG_GETTERS_H',
         '',
         'namespace tq {',
         '',
         'extern void (*g_pfnNpcInlineLogError)(const void* pFile, ...);',
         '']
    for a in sorted(got):
        h.append('long long FUN_%s(long long pThis);   // member at +0x%x' % (a[4:], got[a]['offset']))
    h += ['', 'struct NpcLogGetterEntry {',
          '    const char* pszAddress;',
          '    void*       pfn;',
          '    long long   nOffset;',
          '    const char* pszFile;',
          '    const char* pszExpression;',
          '    const char* pszKind;',
          '    const char* pszFormat;',
          '    int         nLine;',
          '};',
          '',
          'extern const NpcLogGetterEntry g_aNpcLogGetter[];',
          'extern const int g_nNpcLogGetter;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe by tools/gen_npc_loggetters.py.',
         '#include "modules/npcserver/unattributed/log-getters.h"',
         '',
         'namespace tq {',
         '']
    for a in sorted(got):
        e = got[a]
        q = [cliteral(v.encode('latin1')) for v in e['args']]
        c.append('// 0x%s - member at +0x%x, log at line %d' % (a[4:], e['offset'], e['line']))
        c.append('long long FUN_%s(long long pThis) {' % a[4:])
        c.append('    long long nValue = *(long long*)(pThis + 0x%X);' % e['offset'])
        c.append('    if (nValue == 0) {')
        c.append('        g_pfnNpcInlineLogError(%s, %s, %s, %s, 0x%X);' % (q[0], q[1], q[2], q[3], e['line']))
        c.append('        nValue = 0;')
        c.append('    }')
        c.append('    return nValue;')
        c.append('}')
        c.append('')
    c.append('const NpcLogGetterEntry g_aNpcLogGetter[] = {')
    for a in sorted(got):
        e = got[a]
        q = [cliteral(v.encode('latin1')) for v in e['args']]
        c.append('    { "%s", (void*)&FUN_%s, 0x%X, %s, %s, %s, %s, 0x%X },' % (
            a[4:], a[4:], e['offset'], q[0], q[1], q[2], q[3], e['line']))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcLogGetter = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': got, 'skipped': skipped}, open(MANIFEST, 'w'))


if __name__ == '__main__':
    main()
