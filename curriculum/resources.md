# Resources And Tooling

## Core Tooling

Install these first:

```bash
sudo apt update
sudo apt install -y build-essential gcc gdb python3 python3-pip \
  binutils file strace ltrace patchelf ruby-full
python3 -m pip install --user pwntools ropper
gem install one_gadget
```

Recommended:

- pwndbg: <https://github.com/pwndbg/pwndbg>
- Ghidra: <https://ghidra-sre.org/>
- ROPgadget: `python3 -m pip install --user ROPGadget`
- pwninit: <https://github.com/io12/pwninit>

## Practice Platforms

- ROP Emporium: <https://ropemporium.com/>
- pwn.college: <https://pwn.college/>
- pwnable.kr: <https://pwnable.kr/>
- pwnable.tw: <https://pwnable.tw/>
- picoCTF: <https://picoctf.org/>
- how2heap: <https://github.com/shellphish/how2heap>

## Reference Habits

Prefer primary or high-signal references:

- man pages for syscalls and libc functions
- glibc source when heap behavior matters
- challenge writeups only after a serious attempt
- debugger state over guesses

## Commands Worth Memorizing

```bash
file ./chall
checksec ./chall
readelf -a ./chall
objdump -d -M intel ./chall
nm -an ./chall
strings -a ./chall
strace ./chall
ltrace ./chall
```

GDB/pwndbg:

```gdb
checksec
info files
disassemble main
break *main
run
context
vmmap
cyclic 200
cyclic -l 0x6161616b
x/40gx $rsp
info registers
```

