"""Run a function out of the original Syndicate.dll in an emulator.

The point is to get an oracle that is independent of the lifter: the same inputs go into the
original machine code and into the ported C++, and the results have to match. Nothing here
interprets what the function means, so it can check any body without a hand-written test.
"""
import struct
import sys
import zlib

from unicorn import (Uc, UcError, UC_ARCH_X86, UC_MODE_64, UC_HOOK_MEM_FETCH_UNMAPPED,
                     UC_HOOK_MEM_READ_UNMAPPED, UC_HOOK_MEM_WRITE_UNMAPPED, UC_HOOK_CODE)
from unicorn.x86_const import (UC_X86_REG_RAX, UC_X86_REG_RBX, UC_X86_REG_RCX, UC_X86_REG_RDX,
                               UC_X86_REG_RSI, UC_X86_REG_RDI, UC_X86_REG_RBP, UC_X86_REG_RSP,
                               UC_X86_REG_R8, UC_X86_REG_R9, UC_X86_REG_R10, UC_X86_REG_R11,
                               UC_X86_REG_R12, UC_X86_REG_R13, UC_X86_REG_R14, UC_X86_REG_R15,
                               UC_X86_REG_RIP, UC_X86_REG_EFLAGS)

REGS = {'rax': UC_X86_REG_RAX, 'rbx': UC_X86_REG_RBX, 'rcx': UC_X86_REG_RCX, 'rdx': UC_X86_REG_RDX,
        'rsi': UC_X86_REG_RSI, 'rdi': UC_X86_REG_RDI, 'rbp': UC_X86_REG_RBP,
        'r8': UC_X86_REG_R8, 'r9': UC_X86_REG_R9, 'r10': UC_X86_REG_R10, 'r11': UC_X86_REG_R11,
        'r12': UC_X86_REG_R12, 'r13': UC_X86_REG_R13, 'r14': UC_X86_REG_R14, 'r15': UC_X86_REG_R15}

STACK = 0x200000000
STACK_SIZE = 0x40000
RET_MAGIC = 0x1ee7c0de


class Image:
    def __init__(self, path):
        data = open(path, 'rb').read()
        e_lfanew = struct.unpack_from('<I', data, 0x3c)[0]
        assert data[e_lfanew:e_lfanew + 4] == b'PE\0\0', 'not a PE'
        coff = e_lfanew + 4
        nsec, = struct.unpack_from('<H', data, coff + 2)
        opt_size, = struct.unpack_from('<H', data, coff + 16)
        opt = coff + 20
        magic, = struct.unpack_from('<H', data, opt)
        assert magic == 0x20b, 'expects PE32+'
        self.base, = struct.unpack_from('<Q', data, opt + 0x18)
        self.size_of_image, = struct.unpack_from('<I', data, opt + 0x38)
        self.sections = []
        sec = opt + opt_size
        for i in range(nsec):
            off = sec + 40 * i
            name = data[off:off + 8].rstrip(b'\0').decode('latin1')
            vsize, va, rawsize, rawptr = struct.unpack_from('<IIII', data, off + 8)
            self.sections.append({'name': name, 'va': va, 'vsize': vsize,
                                  'rawsize': rawsize, 'rawptr': rawptr,
                                  'bytes': data[rawptr:rawptr + rawsize] if rawsize else b'',
                                  'exec': bool(struct.unpack_from('<I', data, off + 36)[0] & 0x20000000)})
        self.data = data

    def section(self, name):
        for s in self.sections:
            if s['name'] == name:
                return s
        return None


def page(x):
    return x & ~0xfff


class Machine:
    """One emulated call at a time, with import thunks served by a Python stub."""

    def __init__(self, image, stub_value=0, keep_globals=True):
        self.img = image
        self.uc = Uc(UC_ARCH_X86, UC_MODE_64)
        self.mapped = []
        for s in image.sections:
            if not s['vsize']:
                continue
            base = image.base + s['va']
            size = (max(s['vsize'], len(s['bytes'])) + 0xfff) & ~0xfff
            if not keep_globals and s['name'] != '.text':
                continue
            self._map(base, size)
            if s['bytes']:
                self.uc.mem_write(base, s['bytes'])
        self._map(STACK, STACK_SIZE)
        self.stub_value = stub_value
        self.calls = []
        self.uc.hook_add(UC_HOOK_MEM_FETCH_UNMAPPED, self._unmapped_fetch)
        self.uc.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED, self._unmapped_access)
        self.uc.hook_add(UC_HOOK_CODE, self._code)

    def _map(self, base, size):
        b = page(base)
        end = (base + size + 0xfff) & ~0xfff
        self.uc.mem_map(b, end - b)
        self.mapped.append((b, end))

    def _in_text(self, addr):
        for s in self.img.sections:
            if s['exec']:
                lo = self.img.base + s['va']
                if lo <= addr < lo + max(s['vsize'], len(s['bytes'])):
                    return True
        return False

    def _unmapped_access(self, uc, access, address, size, value, user):
        # the original runs with a heap and initialized globals; here any page the body touches is
        # satisfied with zeros so the call can finish. Both sides of a comparison see the same zeros,
        # so this stays an honest oracle for the code path being checked.
        for a in {address & ~0xfff, (address + max(size, 1) - 1) & ~0xfff}:
            try:
                uc.mem_map(a, 0x1000)
            except UcError:
                # already covered (an access can straddle into a mapped page) - retry and let it fault
                # again if it is genuinely unreadable
                continue
        return True

    def _code(self, uc, address, size, user):
        self.insns += 1

    def _unmapped_fetch(self, uc, access, address, size, value, user):
        # an import thunk jumped outside the image: behave like a stub that returns
        try:
            rsp = uc.reg_read(UC_X86_REG_RSP)
            ret, = struct.unpack('<Q', uc.mem_read(rsp, 8))
        except UcError:
            return False
        self.calls.append(address)
        uc.reg_write(UC_X86_REG_RAX, self.stub_value)
        uc.mem_write(uc.reg_read(UC_X86_REG_RSP), struct.pack('<Q', RET_MAGIC))
        uc.reg_write(UC_X86_REG_RIP, RET_MAGIC)
        return True

    def run(self, addr, args, stack_args=(), steps=2000000):
        uc = self.uc
        self.insns = 0
        rsp = STACK + STACK_SIZE - 0x800
        uc.mem_write(rsp, struct.pack('<Q', RET_MAGIC))
        for i, v in enumerate(stack_args):
            uc.mem_write(rsp + 8 * (i + 1), struct.pack('<Q', v & 0xffffffffffffffff))
        for name, v in zip(('rcx', 'rdx', 'r8', 'r9'), args):
            uc.reg_write(REGS[name], v & 0xffffffffffffffff)
        uc.reg_write(UC_X86_REG_RSP, rsp)
        uc.reg_write(UC_X86_REG_RIP, addr)
        try:
            uc.emu_start(addr, RET_MAGIC, count=steps)
        except UcError as e:
            return {'error': str(e), 'insns': self.insns, 'calls': len(self.calls)}
        out = {'insns': self.insns, 'calls': len(self.calls),
               'rip': uc.reg_read(UC_X86_REG_RIP)}
        for name, reg in REGS.items():
            out[name] = uc.reg_read(reg)
        out['eflags'] = uc.reg_read(UC_X86_REG_EFLAGS)
        return out

    def read(self, addr, size):
        return bytes(self.uc.mem_read(addr, size))

    def write(self, addr, data):
        self.uc.mem_write(addr, data)

    def digest(self, regions):
        h = zlib.crc32(b'')
        for base, size in regions:
            h = zlib.crc32(self.read(base, size), h)
        return h


if __name__ == '__main__':
    img = Image(sys.argv[1])
    print('image base', hex(img.base), 'sections',
          [(s['name'], hex(s['va']), s['vsize'], 'x' if s['exec'] else '') for s in img.sections][:8])
