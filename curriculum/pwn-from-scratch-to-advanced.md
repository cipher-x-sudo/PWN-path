# Pwn From Scratch To Advanced

## Goal

Build practical exploit-writing skill: binary analysis, debugging,
vulnerability identification, exploit construction, and eventually hard CTF /
research-style work.

Default track:

- 8-12 hours per week
- Linux x86_64 first
- CTF pwn plus real-world vulnerability research foundations
- legal labs, CTF binaries, and authorized targets only

## Phase 1: Core Foundations, 3-4 Weeks

Build fluency with the machine model.

Learn:

- C memory model: stack, heap, pointers, structs, arrays, strings
- x86_64 assembly: registers, stack frames, function calls, syscalls
- ABI/calling convention: argument registers, return values, stack alignment
- ELF basics: sections, symbols, GOT/PLT, dynamic linking
- Tools: `gdb`, `pwndbg`, `checksec`, `objdump`, `readelf`, `strace`,
  `ltrace`, `pwntools`

Practice:

- Compile small C programs and inspect them in GDB.
- Step through function prologues/epilogues.
- Watch local variables, saved RBP, and saved RIP move on the stack.
- Write pwntools scripts that launch binaries, send input, and parse output.

Local lab:

- `labs/phase1-stack-basics`

Exit criteria:

- You can explain a stack frame from a GDB screenshot.
- You can identify saved return addresses and function arguments.
- You can use `objdump`, `readelf`, `nm`, and `gdb` without a walkthrough.

## Phase 2: Stack Exploitation, 4-6 Weeks

Learn classic pwn properly instead of memorizing payloads.

Learn:

- buffer overflows
- offset discovery with cyclic patterns
- return address control
- ret2win
- stack alignment during ROP
- compiler-generated SSE instructions such as `movaps`
- shellcode basics when NX is disabled
- ret2libc
- ROP chains
- stack canary leaks
- PIE and ASLR bypass with leaks
- NX bypass through ROP

Practice platforms:

- ROP Emporium
- pwn.college
- pwnable.kr
- picoCTF binary exploitation
- beginner/intermediate CTF pwn challenges

Local labs:

- `labs/phase2-ret2win`
- `labs/phase2-ret2win-arg`
- `labs/phase2-ret2win-2args`
- `labs/phase2-ret2win-3args`
- `labs/phase2-cyclic-offset`
- `labs/phase2-stack-alignment`
- `labs/phase2-stack-alignment-sse`
- `labs/phase2-ret2libc-leak`

Exit criteria:

- You can solve simple stack challenges without a walkthrough.
- You can explain why the exploit works at register/memory level.
- You can write clean pwntools exploits from scratch.

## Phase 3: Format Strings And Linking Internals, 3-4 Weeks

Move beyond basic overflow patterns.

Learn:

- format string reads
- format string writes with `%n`
- GOT overwrite when Partial RELRO permits it
- partial overwrite
- arbitrary read/write primitives
- dynamic linker behavior
- libc leaks and symbol resolution
- one-gadget limitations
- RELRO levels and their impact

Practice:

- Leak stack, binary, and libc addresses.
- Compute base addresses from leaks.
- Build arbitrary write primitives.
- Compare exploit plans under No RELRO, Partial RELRO, and Full RELRO.

Exit criteria:

- You can turn `%p` leaks into base addresses.
- You can describe when GOT overwrite is possible.
- You can avoid GOT overwrite plans when Full RELRO is enabled.

## Phase 4: Heap Exploitation, 8-12 Weeks

This is where pwn starts becoming serious.

Learn:

- `malloc` / `free` internals
- chunks, metadata, arenas
- tcache, fastbins, unsorted bin
- use-after-free
- double free
- heap overflow
- tcache poisoning
- safe-linking bypasses
- libc version differences
- heap leak strategies

Practice:

- how2heap
- heap CTF challenges grouped by glibc version
- small vulnerable heap programs you write yourself

Exit criteria:

- You can identify heap primitives from source or reversing.
- You can turn UAF/double-free/overflow bugs into leaks or control.
- You understand exploit strategy, not just named techniques.

## Phase 5: Reversing For Pwn, 6-8 Weeks

Become good at analyzing unknown binaries.

Learn:

- static analysis with Ghidra, IDA Free, or Binary Ninja
- recovering structs and program state
- identifying input paths and bug surfaces
- symbol-stripped binaries
- C++ basics when relevant
- state machines, parsers, menu programs
- patch/diff reasoning

Practice:

- For every challenge, produce a short writeup:
  - bug
  - primitive
  - mitigation state
  - leak method
  - control method
  - final exploit chain

Exit criteria:

- You can find the vulnerable path in a stripped binary.
- You can name the data structure or state machine being abused.
- You can explain your exploit without relying on source code.

## Phase 6: Advanced Topics, Ongoing

Rotate through advanced areas after the core track.

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

Exit criteria:

- You can choose advanced topics based on a target's actual constraints.
- You can read high-quality public writeups and reproduce the key technique.
- You can explain reliability limits across libc/kernel/container versions.

## Weekly Structure

For 8-12 hours/week:

- 2 hours: reading/tool study
- 4-6 hours: hands-on challenges
- 1-2 hours: debugging failed attempts
- 1 hour: writeup/review
- optional: one CTF weekend per month

Rules:

- Do not watch a full walkthrough before spending at least 90 minutes debugging.
- After solving with help, re-solve the challenge from zero the next day.
- Keep an exploit notebook with payload patterns, primitives, and mistakes.

## Milestones

Milestone 1:

- Solve 10 basic stack challenges.
- Explain stack frame layout and RIP control clearly.

Milestone 2:

- Solve 10 ret2libc/ROP challenges.
- Build chains without copying payloads blindly.

Milestone 3:

- Solve 8 format string challenges.
- Demonstrate arbitrary read/write.

Milestone 4:

- Solve 15 heap challenges across tcache/fastbin/unsorted-bin topics.
- Explain glibc-version-specific behavior.

Milestone 5:

- Participate in live CTFs.
- Solve at least one pwn challenge without walkthroughs.

## Daily Challenge Workflow

Use this flow every time:

1. Run `file ./chall`.
2. Run `checksec ./chall`.
3. Start a notes file from `templates/writeup.md`.
4. Identify input paths.
5. Trigger a crash or leak.
6. Reproduce the crash in GDB.
7. Find exact offset or primitive.
8. Choose the mitigation bypass.
9. Write a pwntools exploit.
10. Re-run from a clean terminal.
11. Record the bug, primitive, leak, control method, and final payload shape.

