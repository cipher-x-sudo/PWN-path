from pwn import *
context.terminal = ["tmux", "splitw", "-h"]
elf = context.binary = ELF("./main_patched")
rop = ROP(elf)
libc = elf.libc
# libc = ELF("./libc.so.6")
# LEAVE_RET = rop.find_gadget(['leave', 'ret'])[0]
# POP_RDI = rop.find_gadget(['pop rdi', 'ret'])[0]
# POP_RBP = rop.find_gadget(['pop rbp', 'ret'])[0]
# RET = rop.find_gadget(['ret'])[0]

p = remote(sys.argv[1], int(sys.argv[2])
    ) if args.REMOTE else process(["./ld-linux-x86-64.so.2", "--library-path", ".", "./main_patched"], aslr=True)

if args.GDB: gdb.attach(p, """
    brva 0x469b0
    """)

encode = lambda e: e if type(e) == bytes else str(e).encode()
hexleak = lambda l: int(l[:-1] if l[-1] == '\n' else l, 16)
fixleak = lambda l: unpack(l[:-1].ljust(8, b"\x00"))
sl  = lambda d: p.sendline(d)
sa  = lambda m, d: p.sendafter(m, d)
sla = lambda m, d: p.sendlineafter(m, d)
s   = lambda d: p.send(d)
ra  = lambda: p.recvall()
ru  = lambda d: p.recvuntil(d)
rl  = lambda: p.recvline()
rla = lambda m: p.recvlineafter(m)
delta = lambda x, y: (0xffffffffffffffff - x) + y
