"""Maps the arguments of every log call inside CPerformanceInfo's record body
(0x140ba51c0..0x140ba5cd0) from the shipped binary: the format string each call
receives and the instructions that filled its value slots. Reads the binary only."""
import re, subprocess

DLL = '/app/work/orig_extract/Source/CQBase.dll'
START, STOP = 0x140ba51c0, 0x140ba5cd0
LOG_FN = 0x140ba04e0

dis = subprocess.run(['objdump', '-d', '--no-show-raw-insn',
                      f'--start-address={hex(START)}', f'--stop-address={hex(STOP)}', DLL],
                     capture_output=True, text=True).stdout
insns = []
for line in dis.split('\n'):
    m = re.match(r'^\s+([0-9a-f]+):\t(.*)$', line)
    if m:
        body = m.group(2)
        comment = body.split('#')[1].strip() if '#' in body else ''
        insns.append((int(m.group(1), 16), body.split('#')[0].strip(), comment))

def read_str(va, limit=160):
    out = subprocess.run(['objdump', '-s', f'--start-address={hex(va)}',
                          f'--stop-address={hex(va + limit)}', DLL],
                         capture_output=True, text=True).stdout
    raw = b''
    for line in out.split('\n'):
        m = re.match(r'^\s+([0-9a-f]+)\s+((?:[0-9a-f]{2,8}\s+){1,4})', line)
        if m:
            raw += b''.join(bytes.fromhex(h) for h in m.group(2).split() if len(h) % 2 == 0)
    return raw.split(b'\x00')[0].decode('latin-1')

report = ['# The record body 0x140ba51c0, call by call', '',
          'Every block below is one log call. rcx carries the object, rdx the format, then',
          'r8 and r9, then the stack slots from 0x20 up. The format text is read out of the',
          'shipped binary at the address the code loads it from.', '']
n = 0
for i, (addr, text, comment) in enumerate(insns):
    if not text.startswith('call'):
        continue
    tgt = text.split('call')[1].strip()
    if tgt != hex(LOG_FN):
        continue
    n += 1
    report.append(f'## call at {hex(addr)}')
    window = insns[max(0, i - 18):i]
    fmt_va = None
    for _, t, c in reversed(window):
        if re.match(r'lea\s+0x[0-9a-f]+\(%rip\),%rdx$', t) and c:
            fmt_va = int(c.split()[0], 16)
            break
    if fmt_va:
        report.append(f'format @ {hex(fmt_va)}: `{read_str(fmt_va)}`')
    report.append('')
    report.append('```')
    for a, t, c in window:
        report.append(f'{hex(a)}  {t}' + (f'   # {c}' if c else ''))
    report.append(f'{hex(addr)}  call {tgt}')
    report.append('```')
    report.append('')
open('Docs/PERF_RECORD_BODY.md', 'w').write('\n'.join(report) + '\n')
print('documented calls:', n)
