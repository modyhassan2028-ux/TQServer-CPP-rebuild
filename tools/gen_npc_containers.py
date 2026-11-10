#!/usr/bin/env python3
"""Transcribe the container/interface small bodies around NpcManager (0x140024000..0x140027000).

Four shapes, each matched on its exact text and then verified against the bytes for the vtable address:

  vtable-set          *pThis = X::vftable;
  vtable-dtor         *pThis = X::vftable; if (pFlag & 1) operator_delete(pThis); return pThis;
  vtable-release      if (pThis) (**(*pThis))(pThis, 1); return 0;
  iter-compare        if (*pA == 0 || *pA != *pB) _invalid_parameter_noinfo(); return <expr>;
"""
import json, os, re, struct
import capstone

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
EXE = '/app/co_decomp/orig_binaries/Source/NpcServer.exe'
OUT_H = 'modules/npcserver/unattributed/container-bodies.h'
OUT_C = 'modules/npcserver/unattributed/container-bodies.cpp'
MANIFEST = '/tmp/npc_containers.json'
LO, HI = 0x140024000, 0x140027000


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
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)


def raw(va, n):
    for name, start, vsz, rawptr, rawsz in SECS:
        if start <= va < start + max(vsz, rawsz):
            o = rawptr + (va - start)
            return DATA[o:o + n]
    return b''


def vtable_store(va):
    """The address a vtable-set body stores first: lea rax,[rip+X] / mov [rcx],rax - or a direct mov [rcx],imm."""
    pending = None
    for i in MD.disasm(raw(va, 32), va):
        if i.mnemonic == 'lea':
            m = re.match(r'rax, \[rip \+ (0x[0-9a-f]+)\]', i.op_str)
            if m:
                pending = int(m.group(1), 16) + i.address + i.size
                continue
        if i.mnemonic == 'mov':
            if re.match(r'qword ptr \[rcx\], rax$', i.op_str) and pending is not None:
                return pending
            m = re.match(r'qword ptr \[rcx\], (0x[0-9a-f]+)$', i.op_str)
            if m:
                return int(m.group(1), 16)
            if re.match(r'qword ptr \[rcx\], r', i.op_str):
                return None
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


VT_NAME = re.compile(r'([A-Za-z_][\w:<>,\s]*?)::vftable')


def symbol_of(name):
    return 'g_pNpcVtbl' + re.sub(r'[^A-Za-z0-9]', '', name)


def repo_defined():
    out = set()
    for root, dirs, files in os.walk('modules'):
        for fn in files:
            if fn.endswith(('.c', '.cpp')) and fn != 'container-bodies.cpp':
                t = open(os.path.join(root, fn), errors='ignore').read()
                out |= set(re.findall(r'\bFUN_([0-9a-f]{9})\b', t))
    return out


P_SET = re.compile(r'^void FUN_[0-9a-f]{9}\(undefined8 \*param_1\) \{ \*param_1 = (.+?)::vftable; return; \}$')
P_DTOR = re.compile(r'^undefined8 \* FUN_[0-9a-f]{9}\(undefined8 \*param_1,byte param_2\) \{ \*param_1 = (.+?)::vftable; '
                    r'if \(\(param_2 & 1\) != 0\) \{ operator_delete\(param_1\); \} return param_1; \}$')
P_REL = re.compile(r'^undefined8 FUN_[0-9a-f]{9}\(undefined8 \*param_1\) \{ if \(param_1 != \(undefined8 \*\)0x0\) \{ '
                   r'\(\*\*\(code \*\*\)\*param_1\)\(param_1,1\); \} return 0; \}$')
P_CMP = re.compile(r'^(bool|longlong) FUN_[0-9a-f]{9}\(longlong \*param_1,longlong \*param_2\) \{ '
                   r'if \(\(\*param_1 == 0\) \|\| \(\*param_1 != \*param_2\)\) \{ _invalid_parameter_noinfo\(\); \} '
                   r'return (.+?); \}$')
P_ADDR = re.compile(r'^longlong FUN_[0-9a-f]{9}\(longlong param_1\) \{ return param_1 \+ (0x[0-9a-f]+|\d+); \}$')


def main():
    done = set(open('/tmp/ported_addrs.txt').read().split()) if os.path.exists('/tmp/ported_addrs.txt') else set()
    blocked = repo_defined()
    got, vtabs = {}, {}
    for a, text in sorted(bodies().items()):
        va = int(a[4:], 16)
        if not (LO <= va < HI) or a in done or a[4:] in blocked:
            continue
        m1, m2, m3, m4, m5 = P_SET.match(text), P_DTOR.match(text), P_REL.match(text), P_CMP.match(text), P_ADDR.match(text)
        if m1 or m2:
            vname = (m1 or m2).group(1)
            addr = vtable_store(va)
            if addr is None:
                continue
            sym = symbol_of(vname)
            if sym in vtabs and vtabs[sym] != addr:
                continue                                  # two different tables under one name: leave it alone
            vtabs[sym] = addr
            got[a] = {'kind': 'vtable-set' if m1 else 'vtable-dtor', 'vtable': vname, 'symbol': sym, 'addr': addr}
        elif m3:
            got[a] = {'kind': 'vtable-release'}
        elif m4:
            expr = m4.group(2).replace('param_1', 'pA').replace('param_2', 'pB')
            got[a] = {'kind': 'iter-compare', 'ret': m4.group(1), 'expr': expr}
        elif m5:
            got[a] = {'kind': 'member-address', 'offset': int(m5.group(1), 16)}

    kinds = {}
    for a, e in got.items():
        kinds.setdefault(e['kind'], []).append(a)
    for k in sorted(kinds):
        print('  %-15s %2d  first=%s' % (k, len(kinds[k]), kinds[k][0]))
    print('  distinct vtables: %d' % len(vtabs))

    h = ['// The container/interface bodies around NpcManager, transcribed from NpcServer.exe.',
         '//',
         '// Generated by tools/gen_npc_containers.py; each vtable address was read back out of the store instruction.',
         '#ifndef TQ_NPCSERVER_CONTAINER_BODIES_H',
         '#define TQ_NPCSERVER_CONTAINER_BODIES_H',
         '',
         '#include <cstddef>',
         '',
         'namespace tq {',
         '',
         'extern void (*g_pfnNpcInvalidParameter)(void);',
         'extern void* (*g_pfnNpcOperatorDelete)(void* p);',
         '']
    for sym in sorted(vtabs):
        h.append('extern const void* const %s;' % sym)
    h.append('')
    for a in sorted(got):
        e = got[a]
        if e['kind'] == 'vtable-set':
            h.append('void      FUN_%s(void* pThis);              // %s' % (a[4:], e['vtable']))
        elif e['kind'] == 'vtable-dtor':
            h.append('void*     FUN_%s(void* pThis, unsigned char bFree);   // %s' % (a[4:], e['vtable']))
        elif e['kind'] == 'vtable-release':
            h.append('long long FUN_%s(void* pThis);' % a[4:])
        elif e['kind'] == 'iter-compare':
            h.append('%-9s FUN_%s(long long* pA, long long* pB);' % ('bool' if e['ret'] == 'bool' else 'long long', a[4:]))
        else:
            h.append('long long FUN_%s(long long pThis);           // +0x%x' % (a[4:], e['offset']))
    h += ['', 'struct NpcContainerEntry {',
          '    const char* pszAddress;',
          '    const char* pszKind;',
          '    void*       pfn;',
          '    const char* pszVtable;',
          '    long long   nValue;',
          '};',
          '',
          'extern const NpcContainerEntry g_aNpcContainer[];',
          'extern const int g_nNpcContainer;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe by tools/gen_npc_containers.py.',
         '#include "modules/npcserver/unattributed/container-bodies.h"',
         '',
         'namespace tq {',
         '']
    for sym in sorted(vtabs):
        c.append('// %s read from the image' % sym)
        c.append('const void* const %s = (const void*)0x%X;' % (sym, vtabs[sym]))
        c.append('')
    for a in sorted(got):
        e = got[a]
        c.append('// 0x%s - %s' % (a[4:], e['kind']))
        if e['kind'] == 'vtable-set':
            c += ['void FUN_%s(void* pThis) {' % a[4:],
                  '    *(const void**)pThis = %s;' % e['symbol'],
                  '    return;', '}']
        elif e['kind'] == 'vtable-dtor':
            c += ['void* FUN_%s(void* pThis, unsigned char bFree) {' % a[4:],
                  '    *(const void**)pThis = %s;' % e['symbol'],
                  '    if ((bFree & 1) != 0) {',
                  '        g_pfnNpcOperatorDelete(pThis);',
                  '    }',
                  '    return pThis;', '}']
        elif e['kind'] == 'vtable-release':
            c += ['long long FUN_%s(void* pThis) {' % a[4:],
                  '    if (pThis != nullptr) {',
                  '        (*(void (**)(void*, int))(*(void**)pThis))(pThis, 1);',
                  '    }',
                  '    return 0;', '}']
        elif e['kind'] == 'iter-compare':
            c += ['%s FUN_%s(long long* pA, long long* pB) {' % ('bool' if e['ret'] == 'bool' else 'long long', a[4:]),
                  '    if ((pA[0] == 0) || (pA[0] != pB[0])) {',
                  '        g_pfnNpcInvalidParameter();',
                  '    }',
                  '    return %s;' % e['expr'], '}']
        else:
            c += ['long long FUN_%s(long long pThis) {' % a[4:],
                  '    return pThis + 0x%X;' % e['offset'], '}']
        c.append('')
    c.append('const NpcContainerEntry g_aNpcContainer[] = {')
    for a in sorted(got):
        e = got[a]
        c.append('    { "%s", "%s", (void*)&FUN_%s, %s, %d },' % (
            a[4:], e['kind'], a[4:], ('"%s"' % e['vtable']) if 'vtable' in e else 'nullptr',
            e.get('offset', 0)))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcContainer = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': got, 'vtables': vtabs}, open(MANIFEST, 'w'))


if __name__ == '__main__':
    main()
