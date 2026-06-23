# Pwn From Scratch To Advanced

## Summary

You already know basic tooling and theory, but need the practical exploit-writing skill: binary analysis, debugging, vulnerability identification, exploit construction, and eventually hard CTF / research-style work.

Default track: **8-12 hours/week**, focused on **CTF pwn + vulnerability research foundations**, using Linux x86_64 first.

## Phase Plan

### Phase 1: Core Foundations, 3-4 weeks

Build fluency with the machine model.

- C memory model: stack, heap, pointers, structs, calling conventions
- x86_64 assembly: registers, stack frames, function calls, syscalls
- ELF basics: sections, symbols, GOT/PLT, dynamic linking
- Tools: `gdb`, `pwndbg`, `checksec`, `objdump`, `readelf`, `strace`, `ltrace`, `pwntools`

Practice:

- Rebuild simple C programs and inspect them in `gdb`
- Step through function calls, stack frames, crashes, and return addresses
- Write small `pwntools` scripts that launch binaries, send input, parse leaks

### Phase 2: Stack Exploitation, 4-6 weeks

Learn classic pwn properly instead of memorizing payloads.

- Buffer overflows
- Offset discovery with cyclic patterns
- Return address control
- Shellcode basics
- ret2win
- ret2libc
- ROP chains
- Stack canary leaks
- PIE and ASLR bypass using leaks
- NX bypass through ROP

Practice platforms:

- `pwn.college`
- `ROP Emporium`
- `pwnable.kr`
- beginner/intermediate CTF pwn challenges

Success criteria:

- You can solve simple stack challenges without a walkthrough
- You can explain why the exploit works at register/memory level
- You can write clean `pwntools` exploits from scratch

### Phase 3: Format Strings And Linking Internals, 3-4 weeks

Move beyond basic overflow patterns.

- Format string reads and writes
- GOT overwrite
- Partial overwrite
- Arbitrary read/write primitives
- Dynamic linker behavior
- libc leaks and symbol resolution
- One-gadget limitations
- RELRO levels and their impact

Practice:

- Write exploits that leak libc and compute base addresses
- Build arbitrary write primitives using `%n`
- Solve challenges with Full RELRO, PIE, NX, and canaries enabled

### Phase 4: Heap Exploitation, 8-12 weeks

This is where pwn starts becoming serious.

- `malloc` / `free` internals
- chunks, bins, tcache, fastbins, unsorted bin
- use-after-free
- double free
- heap overflow
- tcache poisoning
- safe-linking bypasses
- libc version differences
- heap leak strategies

Practice:

- `how2heap`
- heap CTF challenges by glibc version
- write small vulnerable heap programs yourself and exploit them

Success criteria:

- You can identify heap primitives from source or reversing
- You can turn UAF/double-free/overflow bugs into leaks or control
- You understand exploit strategy, not just named techniques

### Phase 5: Reversing For Pwn, 6-8 weeks

Become good at analyzing unknown binaries.

- Static analysis with Ghidra/IDA/Binary Ninja
- Recovering structs and program state
- Identifying input paths and bug surfaces
- Symbol-stripped binaries
- C++ basics when relevant
- State machines, parsers, menu programs
- Patch/diff reasoning

Practice:

- For every challenge, produce a short writeup:
  - bug
  - primitive
  - mitigation state
  - leak method
  - control method
  - final exploit chain

### Phase 6: Advanced Topics, ongoing

After the core track, rotate through advanced areas.

- seccomp escapes in CTF contexts
- SROP
- ret2dlresolve
- JOP/COP concepts
- kernel pwn basics
- browser exploitation concepts
- fuzzing with AFL++ / libFuzzer
- sanitizer-assisted bug discovery
- real-world CVE writeup reading
- exploit reliability and environment matching

## Weekly Structure

For 8-12 hours/week:

- 2 hours: reading/tool study
- 4-6 hours: hands-on challenges
- 1-2 hours: debugging failed attempts
- 1 hour: writeup/review
- optional: one CTF weekend per month

Weekly rule:

- Do not watch a full walkthrough before spending at least 90 minutes debugging.
- After solving with help, re-solve the challenge from zero the next day.
- Keep an exploit notebook with payload patterns, primitives, and mistakes.

## Tooling Setup

Use a Linux VM or native Linux.

Install:

- `gcc`, `gdb`, `python3`, `python3-pip`
- `pwntools`
- `pwndbg`
- `checksec`
- `ropper` or `ROPgadget`
- `one_gadget`
- `patchelf`
- `pwninit`
- Ghidra or Binary Ninja/IDA Free

Standard exploit template:

- start local process
- optional remote mode
- `checksec` notes
- leak parsing
- base calculation
- final payload
- interactive shell or flag read

## Test Plan / Milestones

Milestone 1:

- Solve 10 basic stack challenges
- Explain stack frame layout and RIP control clearly

Milestone 2:

- Solve 10 ret2libc/ROP challenges
- Build chains without copying payloads blindly

Milestone 3:

- Solve 8 format string challenges
- Demonstrate arbitrary read/write

Milestone 4:

- Solve 15 heap challenges across tcache/fastbin/unsorted-bin topics
- Explain glibc-version-specific behavior

Milestone 5:

- Participate in live CTFs and solve at least one pwn challenge without walkthroughs

## Assumptions

- Main architecture: Linux x86_64 first.
- Main goal: CTF pwn plus real-world research foundations.
- Time budget: 8-12 hours/week.
- We stay inside legal labs, CTFs, local binaries, and authorized research targets only.
- We start from practical exploit writing, not from generic cybersecurity theory.
