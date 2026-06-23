# Pwn From Scratch To Advanced

This repo is a practical binary exploitation learning workspace for Linux x86_64.
It is built for CTF pwn and vulnerability-research fundamentals, with an 8-12
hour/week pace.

Work only on local labs, CTF challenges, and systems where you have explicit
authorization.

## Start Here

1. Read [curriculum/pwn-from-scratch-to-advanced.md](curriculum/pwn-from-scratch-to-advanced.md).
2. Install the tools listed in [curriculum/resources.md](curriculum/resources.md).
3. Copy [templates/exploit.py](templates/exploit.py) for each challenge.
4. Track progress in [curriculum/weekly-tracker.md](curriculum/weekly-tracker.md).
5. Write a short note after each solved challenge using [templates/writeup.md](templates/writeup.md).

## Local Labs

The `labs/` directory contains small local binaries for practicing analysis and
exploit-writing basics.

```bash
cd labs/phase1-stack-basics
make
./stack_frames

cd ../phase2-ret2win
make
checksec ./ret2win
```

The labs are intentionally simple. The point is to learn the workflow:

- inspect mitigations
- read the source when available
- disassemble the binary
- crash it under GDB
- find the offset
- build a pwntools exploit
- explain the exploit at register and memory level

## Repository Layout

```text
curriculum/      Long-form learning path, resources, and trackers
labs/            Small local practice binaries
templates/       Reusable exploit and writeup templates
```

## Baseline Workflow

For every pwn challenge:

1. Run `file` and `checksec`.
2. Identify architecture, protections, and input paths.
3. Reproduce the crash locally.
4. Find the primitive: overflow, leak, arbitrary read/write, UAF, etc.
5. Convert the primitive into control: RIP control, ROP, GOT write, hook write,
   stack pivot, or another challenge-appropriate path.
6. Write a clean exploit in pwntools.
7. Re-run the exploit from a fresh terminal.
8. Write down what changed in memory and why the payload worked.

