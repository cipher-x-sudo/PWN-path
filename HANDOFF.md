# Handoff

## Goal

Guide the user from beginner pwn basics toward advanced exploit development using
short, direct explanations and local labs.

## Current State

- Branch: `main`
- Remote: `origin https://github.com/cipher-x-sudo/mypwm.git`
- Last push result: ret2win two-argument completion pushed to `origin/main`.
- Working tree should be clean after push.
- `.specstory/` is ignored and no longer tracked.
- Reminder automation created:
  - id: `practice-pwn-daily`
  - schedule: daily at 11:00 PM user local time
  - prompt: remind user to practice current pwn lab, short and direct

## Repo Setup Completed

- Added pwn learning workspace:
  - `README.md`
  - `curriculum/pwn-from-scratch-to-advanced.md`
  - `curriculum/resources.md`
  - `curriculum/weekly-tracker.md`
  - `templates/exploit.py`
  - `templates/writeup.md`
- Added labs:
  - `labs/phase1-stack-basics`
  - `labs/phase2-ret2win`
  - `labs/phase2-ret2win-arg`
  - `labs/phase2-ret2win-2args`
- Added user learning style to `AGENTS.md`:
  - keep answers short and direct
  - explain instruction by instruction
  - guide logic instead of dumping full answers

## User Progress

### Phase 1: Stack Basics

User has practiced:

- `break main`
- `run`
- `disassemble`
- `info registers`
- `x/Ngx`
- stepping with `n` / `ni`

Concepts understood:

- `rip` is current/next instruction pointer
- `rsp` is stack pointer
- `rbp` is base pointer
- function args on Linux x86_64:
  - `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`
  - extra args go on stack
- saved return address is usually at `[rbp+8]`
- locals are usually below `rbp`, like `[rbp-0x20]`
- `rax` carries function return value
- `leave` restores stack frame
- `ret` jumps to saved return address from stack

### Phase 2: ret2win

User analyzed `labs/phase2-ret2win/ret2win.c`.

Important facts:

- vulnerable function: `vuln`
- buffer: `char buf[64]`
- bug: `read(STDIN_FILENO, buf, 200)`
- buffer starts at `[rbp-0x40]`
- return address at `[rbp+8]`
- offset to RIP: `0x40 + 8 = 0x48 = 72`
- `win` address observed: `0x4011b6`

Exploit worked:

```text
72 bytes padding + p64(win)
```

Observed success output:

```text
local{ret2win_control_flow}
```

`Got EOF while reading in interactive` is expected because `win()` exits.

### Phase 2: ret2win With One Argument

Added lab: `labs/phase2-ret2win-arg`.

Important facts:

- vulnerable function: `vuln`
- buffer: `char buf[64]`
- bug: `read(STDIN_FILENO, buf, 200)`
- offset to RIP: `72`
- target: call `win(0xdeadbeef)`
- argument register on Linux x86_64: `rdi`
- included helper gadget: naked `gadget()` with `pop rdi; ret`
- user completed the lab and understood the logic:
  - overflow to saved RIP
  - return into `pop rdi; ret`
  - put `0xdeadbeef` into `rdi`
  - return into `win`

Exploit shape:

```text
72 bytes padding + pop_rdi_ret + 0xdeadbeef + win
```

Current exploit uses pwntools ROP gadget lookup:

```python
rop = ROP(elf)
pop_rdi = rop.find_gadget(["pop rdi", "ret"])[0]
```

Verified success output:

```text
local{ret2win_argument_control}
```

Observed current addresses after WSL build:

```text
pop rdi; ret = 0x4011b6
win = 0x4011bf
```

These may change if source/compiler flags change.

### Phase 2: ret2win With Two Arguments

Added lab: `labs/phase2-ret2win-2args`.

Important facts:

- vulnerable function: `vuln`
- buffer: `char buf[64]`
- bug: `read(STDIN_FILENO, buf, 200)`
- expected offset to RIP: `72`
- target: call `win(0xdeadbeef, 0xcafebabe)`
- first argument register: `rdi`
- second argument register: `rsi`
- included helper gadgets:
  - `gadget_rdi()` with `pop rdi; ret`
  - `gadget_rsi()` with `pop rsi; ret`
- user completed the lab and filled the exploit chain.

Exploit shape:

```text
72 bytes padding + pop_rdi_ret + 0xdeadbeef + pop_rsi_ret + 0xcafebabe + win
```

Current exploit uses pwntools ROP gadget lookup:

```python
pop_rdi = rop.find_gadget(["pop rdi", "ret"])[0]
pop_rsi = rop.find_gadget(["pop rsi", "ret"])[0]
```

Observed success output:

```text
local{ret2win_two_argument_control}
```

## Commands/Checks Run

```bash
make
checksec ./ret2win
nm -an ./ret2win
python3 exploit.py
wsl bash -lc 'cd /mnt/d/mypwm/labs/phase2-ret2win-arg && make clean && make && python3 exploit.py'
wsl bash -lc 'cd /mnt/d/mypwm/labs/phase2-ret2win-arg && checksec ./ret2win_arg'
wsl bash -lc 'cd /mnt/e/mypwm/labs/phase2-ret2win-2args && make clean && make'
wsl bash -lc 'cd /mnt/e/mypwm/labs/phase2-ret2win-2args && make clean && make && python3 exploit.py'
git push origin main
```

`checksec ./ret2win` showed:

- amd64
- No canary
- NX enabled
- No PIE
- Partial RELRO
- not stripped
- debug info present

`checksec ./ret2win_arg` showed:

- amd64
- No canary
- NX enabled
- No PIE
- Partial RELRO
- SHSTK enabled
- IBT enabled
- not stripped
- debug info present

## Next Steps

1. Do not require writeups for every solved lab.
2. Use quick oral/checkpoint review instead:
   - bug
   - offset
   - target address
   - why exploit works
3. Review the completed two-argument ret2win lab with the user.
   - Ask them to explain:
     - why `rdi` gets `0xdeadbeef`
     - why `rsi` gets `0xcafebabe`
     - how each `ret` moves to the next gadget/function
   - Next lab should add a third argument with `rdx`, or teach cyclic offset discovery more formally.
   - Teach 16-byte stack alignment later if a crash requires it.
4. Keep coaching style short/direct:
   - explain one instruction or idea at a time
   - ask the user to inspect values in GDB
   - avoid giving full answers before they try

## Roadmap To Elite Level

Use this as the long-term plan. No mandatory writeups for every lab. Use short
checkpoint reviews after each solve.

### Phase 2 Continued: Stack Exploitation

Goal: become comfortable controlling execution flow.

- ret2win with no args
- ret2win with 1 arg: `pop rdi; ret`
- ret2win with 2-3 args: `rdi`, `rsi`, `rdx`
- stack alignment with plain `ret`
- cyclic offset discovery
- shellcode only when NX is disabled
- ret2libc basics
- ROP chains

Checkpoint after each lab:

- Where is the bug?
- What is the offset?
- Which address is controlled?
- Which mitigation matters?
- Why does the final jump/call work?

### Phase 3: Mitigations

Goal: understand what each protection blocks and how to reason around it.

- NX: use ROP/ret2libc, not stack shellcode
- PIE: leak code pointer, calculate binary base
- ASLR: leak libc/stack/heap pointer, calculate base
- Canary: leak canary, put it back unchanged
- Partial RELRO: GOT overwrite may work
- Full RELRO: GOT overwrite blocked
- Fortify: understand when safer libc wrappers change behavior

Checkpoint:

- Run `checksec`
- Say what each mitigation changes
- Pick the correct exploit direction before coding

### Phase 4: Format Strings

Goal: turn format string bugs into leaks and writes.

- `%p`, `%lx`, `%s` leaks
- stack index discovery
- leaking canary, PIE, libc
- `%n`, `%hn`, `%hhn` writes
- GOT overwrite under Partial RELRO
- arbitrary read/write primitives

Checkpoint:

- Which argument index is controlled?
- What did the leak reveal?
- What base address was calculated?
- What write target was chosen?

### Phase 5: ret2libc And ROP

Goal: reliably call libc functions under NX.

- leak `puts`/`read`/`printf` from GOT
- calculate libc base
- find `system`
- find `/bin/sh`
- call `system("/bin/sh")`
- handle stack alignment
- use `ROP(elf)` and manual gadgets
- ret2csu for multi-register setup
- stack pivot when overflow space is small

Checkpoint:

- Which libc function was leaked?
- What is libc base?
- Which gadgets set arguments?
- Why is stack alignment needed or not needed?

### Phase 6: Heap Exploitation

Goal: understand allocator state and turn heap bugs into control.

- malloc/free basics
- chunk headers
- tcache bins
- fastbins
- unsorted bin leaks
- use-after-free
- double free
- heap overflow
- tcache poisoning
- safe-linking basics
- glibc version differences

Checkpoint:

- What heap primitive exists?
- Which chunk is corrupted/reused?
- What leak is needed?
- What target is overwritten?
- Which glibc version matters?

### Phase 7: Reversing For Pwn

Goal: solve binaries without source.

- Ghidra/IDA/Binary Ninja basics
- recover function names mentally
- identify input paths
- identify structs and arrays
- identify menu logic
- find dangerous calls
- compare decompiler output with assembly
- stripped binary workflow

Checkpoint:

- Where does input enter?
- Where is it stored?
- What bounds/checks exist?
- What primitive does the bug create?

### Phase 8: Advanced Userland Pwn

Goal: solve hard CTF-style binaries.

- SROP
- ret2dlresolve
- seccomp analysis
- ORW chains: open/read/write
- one_gadget constraints
- partial overwrites
- brute force when fork server permits it
- FILE structure basics
- advanced heap techniques from how2heap

Checkpoint:

- What restriction blocks normal shell?
- Which syscall/function path still works?
- What exact constraint must be satisfied?

### Phase 9: Fuzzing And Bug Discovery

Goal: find bugs, not only exploit given bugs.

- ASAN/UBSAN builds
- AFL++
- libFuzzer
- corpus minimization
- crash triage
- reproducer creation
- root-cause analysis

Checkpoint:

- What input caused crash?
- Is it exploitable or just a crash?
- What primitive can be extracted?

### Phase 10: Real-World Research Foundation

Goal: move from CTF patterns to research thinking.

- read CVE writeups
- reproduce old bugs locally
- diff vulnerable vs patched versions
- understand exploit reliability
- understand environment matching
- learn basic report writing
- stay inside authorized targets only

Checkpoint:

- What is the vulnerable version?
- What changed in the patch?
- What security impact exists?
- How reliable is exploitation?

### Phase 11: Kernel And Browser Intro

Goal: get exposure to elite-level domains without rushing.

- Linux kernel module basics
- kernel debugging with QEMU
- kernel UAF/overflow concepts
- SMEP/SMAP/KASLR basics
- browser engine architecture basics
- JavaScript engine bug classes
- sandboxing concepts

Checkpoint:

- What privilege boundary exists?
- What mitigation blocks the obvious path?
- What info leak/control primitive is needed?

### Phase 12: Elite Practice Loop

Goal: build speed, depth, and independence.

- play live CTFs monthly
- solve old hard pwn challenges
- re-solve solved challenges without notes
- keep a personal technique index, not full writeups
- read high-quality public writeups after trying
- build tiny vulnerable programs to test each technique
- explain each exploit in 5 direct bullets

Checkpoint format:

```text
bug:
primitive:
leak:
control:
final chain:
```
