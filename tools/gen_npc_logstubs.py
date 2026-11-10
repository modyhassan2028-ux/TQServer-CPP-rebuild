#!/usr/bin/env python3
"""Transcribe NpcServer.exe's fixed-argument log stubs, reading their arguments from the bytes.

IDA renders these as `log_InlineLogERROR(&DAT_x);` with a single argument, but the machine code sets up five:
the format in rcx, three more strings in rdx/r8/r9, and the source line as an immediate at [rsp+0x20]. The strings
are GBK byte sequences inside .rdata, so they are read out of the image and emitted byte-for-byte.

Only bodies whose instruction sequence is exactly
    sub rsp,0x38 / lea r9 / lea r8 / lea rdx / lea rcx / mov dword [rsp+0x20],LINE / call
are taken; every other variant is left for its own batch.
"""
import json, os, re, struct
import capstone

DECOMP = '/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c'
EXE = '/app/co_decomp/orig_binaries/Source/NpcServer.exe'
OUT_H = 'modules/npcserver/unattributed/log-stubs.h'
OUT_C = 'modules/npcserver/unattributed/log-stubs.cpp'
MANIFEST = '/tmp/npc_logstubs.json'


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
            e = DATA.index(b'\0', o)
            return DATA[o:e]
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
    s = ''.join(out)
    # a hex escape swallows following hex digits, so close it with the empty-string trick
    return '"%s"' % re.sub(r'(\\x[0-9a-f]{2})(?=[0-9a-fA-F])', r'\1""', s)


def bodies():
    src = open(DECOMP, errors='ignore').read()
    out = {}
    for part in re.split(r'\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()', src):
        part = part.split('\n// ====')[0]
        m = re.match(r'[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(', part)
        if m:
            out[m.group(1)] = part.strip()
    return out


MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)


def analyse(va):
    ins = list(MD.disasm(raw(va, 96), va))[:8]
    if len(ins) < 7:
        return None
    seq = [i.mnemonic for i in ins]
    if seq[:6] != ['sub', 'lea', 'lea', 'lea', 'lea', 'mov'] or seq[6] != 'call':
        return None
    if ins[0].op_str.replace(' ', '') != 'rsp,0x38':
        return None
    regs = [i.op_str.split(',')[0].strip() for i in ins[1:5]]
    if regs != ['r9', 'r8', 'rdx', 'rcx']:
        return None
    mem, sep, imm = ins[5].op_str.partition(',')
    if mem.replace(' ', '') != 'dwordptr[rsp+0x20]' or not imm.strip().startswith('0x'):
        return None
    strs = []
    for i in ins[1:5]:
        m = re.match(r'(\w+), \[rip \+ (0x[0-9a-f]+)\]', i.op_str)
        if not m:
            return None
        strs.append(int(m.group(2), 16) + i.address + i.size)
    vals = []
    for a in strs:
        b = rdcstr(a)
        if b is None or len(b) == 0:
            return None
        vals.append(b)
    return vals, int(imm.strip(), 16), ins[6].op_str


def defined_in_repo():
    """Bodies already written by hand elsewhere: never emit them twice."""
    out = set()
    for root, dirs, files in os.walk('modules'):
        for fn in files:
            if not fn.endswith(('.c', '.cpp')):
                continue
            if fn in ('log-stubs.cpp',):
                continue
            try:
                t = open(os.path.join(root, fn), errors='ignore').read()
            except OSError:
                continue
            out |= set('FUN_' + m for m in re.findall(r'\bFUN_([0-9a-f]{9})\b', t))
    return out


def main():
    done = set()
    if os.path.exists('/tmp/ported_addrs.txt'):
        done = set(open('/tmp/ported_addrs.txt').read().split())
    done |= defined_in_repo()
    got, skipped = {}, []
    for a, text in sorted(bodies().items()):
        if a in done or 'log_InlineLogERROR(' not in text:
            continue
        if text.count('log_InlineLogERROR') != 1:
            continue
        head = re.match(r'(void|undefined8|undefined1) FUN_', text)
        if not head:
            continue
        r = analyse(int(a[4:], 16))
        if r is None:
            skipped.append(a)
            continue
        vals, line, callop = r
        got[a] = {'ret': head.group(1), 'args': [v.decode('latin1') for v in vals], 'line': line,
                  'call': callop, 'bytes': [v.hex() for v in vals]}
    print('  fixed-argument log stubs: %d  (other log bodies left: %d)' % (len(got), len(skipped)))
    if got:
        first = sorted(got)[0]
        print('  first %s ret=%s line=%d args=%s' % (first, got[first]['ret'], got[first]['line'],
                                                     got[first]['args']))

    RET = {'void': ('void', []), 'undefined8': ('long long', ['    return 0;']),
           'undefined1': ('unsigned char', ['    return 0;'])}
    h = ['// The fixed-argument log stubs of NpcServer.exe.',
         '//',
         '// Arguments read from the machine code by tools/gen_npc_logstubs.py: the format in rcx, three more strings',
         '// in rdx/r8/r9 and the source line as an immediate at [rsp+0x20].',
         '#ifndef TQ_NPCSERVER_LOG_STUBS_H',
         '#define TQ_NPCSERVER_LOG_STUBS_H',
         '',
         'namespace tq {',
         '',
         'extern void (*g_pfnNpcInlineLogError)(const void* pFormat, ...);',
         '']
    for a in sorted(got):
        h.append('%-14s FUN_%s(void);   // line %d' % (RET[got[a]['ret']][0], a[4:], got[a]['line']))
    h += ['', 'struct NpcLogStubEntry {',
          '    const char* pszAddress;',
          '    void*       pfn;',
          '    const char* pszFile;          // rcx',
          '    const char* pszExpression;    // rdx',
          '    const char* pszKind;          // r8',
          '    const char* pszFormat;        // r9',
          '    int         nLine;',
          '    int         bReturns;   // 0 when the body is void',
          '};',
          '',
          'extern const NpcLogStubEntry g_aNpcLogStub[];',
          'extern const int g_nNpcLogStub;',
          '', '}  // namespace tq', '', '#endif']

    c = ['// Generated from NpcServer.exe by tools/gen_npc_logstubs.py.',
         '#include "modules/npcserver/unattributed/log-stubs.h"',
         '',
         'namespace tq {',
         '']
    for a in sorted(got):
        e = got[a]
        c.append('// 0x%s - log at line %d' % (a[4:], e['line']))
        c.append('%s FUN_%s(void) {' % (RET[e['ret']][0], a[4:]))
        q = [cliteral(v.encode('latin1')) for v in e['args']]
        c.append('    g_pfnNpcInlineLogError(%s, %s, %s, %s, 0x%X);' % (q[0], q[1], q[2], q[3], e['line']))
        c.extend(RET[e['ret']][1])
        c.append('}')
        c.append('')
    c.append('const NpcLogStubEntry g_aNpcLogStub[] = {')
    for a in sorted(got):
        e = got[a]
        q = [cliteral(v.encode('latin1')) for v in e['args']]
        c.append('    { "%s", (void*)&FUN_%s, %s, %s, %s, %s, 0x%X, %d },' % (
            a[4:], a[4:], q[0], q[1], q[2], q[3], e['line'], 0 if e['ret'] == 'void' else 1))
    c.append('};')
    c.append('')
    c.append('const int g_nNpcLogStub = %d;' % len(got))
    c += ['', '}  // namespace tq']

    open(OUT_H, 'w').write('\n'.join(h) + '\n')
    open(OUT_C, 'w').write('\n'.join(c) + '\n')
    json.dump({'ported': got, 'skipped': skipped}, open(MANIFEST, 'w'))


if __name__ == '__main__':
    main()
