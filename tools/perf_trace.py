import re, subprocess
DLL='/app/work/orig_extract/Source/CQBase.dll'
out=subprocess.run(['objdump','-d','--no-show-raw-insn','--start-address=0x140ba51c0',
 '--stop-address=0x140ba5cd0',DLL],capture_output=True,text=True).stdout
ins=[]
for line in out.split('\n'):
    m=re.match(r'^\s+([0-9a-f]+):\t(.*)$',line)
    if m: ins.append((int(m.group(1),16), m.group(2).split('#')[0].strip()))
def norm(r):
    r=r.lstrip('%')
    if r in ('rax','rbx','rcx','rdx','rsi','rdi','rbp','rsp','r8','r9','r10','r11','r12','r13','r14','r15'):
        return r
    for full in ('rax','rbx','rcx','rdx','rsi','rdi','rbp','rsp','r8','r9','r10','r11','r12','r13','r14','r15'):
        if r in ('e'+full[1:], full+'d', full+'w', full+'b' if len(full)==3 else full+'b'):
            return full
    if r.startswith('e') and ('r'+r[1:]) in ('r8','r9'):
        return 'r'+r[1:]
    m=re.match(r'^(r1[0-5]|[89])d$',r)
    if m: return 'r'+m.group(1)
    m=re.match(r'^e(ax|bx|cx|dx|si|di|bp|sp)$',r)
    if m: return 'r'+m.group(1)
    return None
reg={}; slot={}
def v(op):
    op=op.strip()
    if op.startswith('$'): return op
    m=re.match(r'^(-?0x[0-9a-f]+)\(%rsp\)$',op)
    if m: return slot.get(m.group(1),'mem'+m.group(1))
    if op.startswith('%'):
        r=norm(op)
        return reg.get(r,r) if r else op
    return op
for addr,text in ins:
    p=text.split(None,1); op=p[0]; a=[x.strip() for x in p[1].split(',')] if len(p)>1 else []
    if op in ('mov','movsd','movss','movzx','movsxd','movsx','movups') and len(a)==2:
        src,dst=a; sval=v(src)
        r=norm(dst) if dst.startswith('%') else None
        m=re.match(r'^(-?0x[0-9a-f]+)\(%rsp\)$',dst)
        if r: reg[r]=sval
        elif m: slot[m.group(1)]=sval
    elif op=='lea' and len(a)==2:
        src,dst=a; r=norm(dst)
        m=re.match(r'^(-?0x[0-9a-f]+)\(%rsp\)$',src)
        if r:
            if m: reg[r]='&'+m.group(1)
            else: reg[r]='lea('+src+')'
    elif op=='xor' and len(a)==2 and a[0]==a[1]:
        r=norm(a[0])
        if r: reg[r]='$0'
    elif op=='call':
        tgt=p[1].strip()
        if '0x140ba04e0' in tgt:
            print(f'--- {hex(addr)}')
            print('   r8 =',v('%r8'),'| r9 =',v('%r9'))
            print('   stk:', {k:slot.get(k,'-') for k in ('0x20','0x28','0x30','0x38','0x40','0x48')})
        for r in ('rax','rcx','rdx','r8','r9','r10','r11'): reg[r]='ret' if r=='rax' else '?'
    else:
        for x in a:
            r=norm(x) if x.startswith('%') else None
            if r and r not in ('rsp','rbp'): reg[r]=op+'('+str(reg.get(r,r))+')'
