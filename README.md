# Pwn From Scratch to Advanced

A hands-on learning path for Linux x86_64 binary exploitation.

This repository is for learners who want to understand *why* an exploit works—not just copy a payload. It combines a structured curriculum, small local labs, reusable pwntools templates, and a repeatable debugging workflow. The current labs begin with stack frames and progress through ret2win, ROP arguments, stack alignment, and a first ret2libc leak.

> [!IMPORTANT]
> Practice only on these local labs, CTF challenges, and systems you own or have explicit permission to test.

## Who This Is For

This path is a good fit if you:

- know basic Python and can read simple C;
- are comfortable using a Linux terminal;
- want to learn CTF pwn or build vulnerability-research foundations;
- prefer learning by debugging small programs.

You do **not** need previous exploit-development experience. The recommended pace is 8–12 hours per week, but every lab can be completed independently.

## What You Will Learn

- C memory layout, stack frames, and pointers
- x86_64 registers, calls, returns, and the System V calling convention
- ELF files, symbols, GOT/PLT, and dynamic linking
- GDB/pwndbg debugging and crash analysis
- cyclic offset discovery and saved RIP control
- ret2win and small ROP chains
- stack alignment and `movaps` crashes
- libc leaks and the basic ret2libc workflow
- later curriculum topics: format strings, heap exploitation, reversing, and advanced pwn

## Quick Start

Use native Linux, a Linux VM, or WSL2. Ubuntu or another Debian-based distribution is the easiest path because the setup commands below use `apt`.

### 1. Install the core tools

```bash
sudo apt update
sudo apt install -y build-essential gcc gdb python3 python3-pip \
  binutils file strace ltrace patchelf ruby-full git
python3 -m pip install --user pwntools ropper ROPGadget
gem install one_gadget
```

Install [pwndbg](https://github.com/pwndbg/pwndbg) for a more useful GDB interface. More tools and practice platforms are listed in [curriculum/resources.md](curriculum/resources.md).

### 2. Clone the repository

```bash
git clone https://github.com/cipher-x-sudo/PWN-path.git
cd PWN-path
```

### 3. Build and inspect the first lab

```bash
cd labs/phase1-stack-basics
make
./stack_frames
gdb ./stack_frames
```

The first lab is a debugger drill, not an exploit challenge. Follow its [lab instructions](labs/phase1-stack-basics/README.md), answer the checkpoint questions, and then continue through the labs in order.

## Learning Path

| # | Lab | Main skill |
|---:|---|---|
| 1 | [Stack Frames](labs/phase1-stack-basics/README.md) | Inspect calls, arguments, saved RBP, and saved RIP |
| 2 | [ret2win](labs/phase2-ret2win/README.md) | Redirect control flow to an existing function |
| 3 | [ret2win: One Argument](labs/phase2-ret2win-arg/README.md) | Set `rdi` with a ROP gadget |
| 4 | [ret2win: Two Arguments](labs/phase2-ret2win-2args/README.md) | Build a small multi-gadget chain |
| 5 | [ret2win: Three Arguments](labs/phase2-ret2win-3args/README.md) | Apply the x86_64 calling convention |
| 6 | [Cyclic Offset Discovery](labs/phase2-cyclic-offset/README.md) | Find the exact saved RIP offset |
| 7 | [Stack Alignment](labs/phase2-stack-alignment/README.md) | Diagnose and repair ROP alignment |
| 8 | [SSE Stack Alignment](labs/phase2-stack-alignment-sse/README.md) | Debug a compiler-generated `movaps` crash |
| 9 | [ret2libc Leak](labs/phase2-ret2libc-leak/README.md) | Leak libc, calculate its base, and reuse libc code |

The full roadmap continues beyond the labs currently included:

1. Core foundations
2. Stack exploitation
3. Format strings and linking internals
4. Heap exploitation
5. Reversing for pwn
6. Advanced topics such as SROP, ret2dlresolve, fuzzing, and kernel basics

Read [the complete curriculum](curriculum/pwn-from-scratch-to-advanced.md) for topics, practice targets, milestones, and exit criteria.

## How to Work Through a Lab

Do not start by searching for a finished exploit. Use this loop:

1. Read the lab README and build the binary with `make`.
2. Run `file`, `checksec`, `readelf`, and `objdump` to understand the target.
3. Read the source when it is provided, then confirm your understanding in assembly.
4. Reproduce the behavior or crash in GDB.
5. Identify the bug and the primitive it gives you.
6. Find the exact offset, required addresses, or leak.
7. Copy the starter template and fill in its TODOs:

   ```bash
   cp ../../templates/exploit.py solve.py
   ```

8. Test from a fresh terminal, not only inside GDB.
9. Record what changed in registers and memory using [templates/writeup.md](templates/writeup.md).

Useful first commands:

```bash
file ./chall
checksec ./chall
readelf -a ./chall
objdump -d -M intel ./chall
nm -an ./chall
gdb ./chall
```

If you are stuck, inspect the crash state before reaching for a walkthrough. A wrong payload is useful when you can explain exactly where it failed.

## Repository Structure

```text
.
├── curriculum/
│   ├── pwn-from-scratch-to-advanced.md  # Full roadmap
│   ├── resources.md                     # Tools and practice platforms
│   └── weekly-tracker.md                # Progress checklist
├── labs/                                # Buildable local exercises
├── templates/
│   ├── exploit.py                       # Reusable pwntools starter
│   └── writeup.md                       # Short solution-note template
└── README.md
```

## Track Your Progress

Use [curriculum/weekly-tracker.md](curriculum/weekly-tracker.md) to plan each week. For every completed challenge, keep a short writeup containing:

- vulnerability;
- mitigations;
- primitive;
- relevant offset or leak;
- control-flow plan;
- why the payload works;
- mistakes and debugging lessons.

A useful rule: spend at least 90 minutes debugging before reading a full walkthrough. If you solve something with help, solve it again from zero the next day.

## Contributing

Contributions that improve explanations, portability, tooling setup, or add focused learning labs are welcome.

When adding a lab:

- keep it small and focused on one main concept;
- include source, a `Makefile`, and a README with a goal, workflow, hints, and checkpoints;
- copy `templates/exploit.py` into the lab as the editable starter;
- leave clear TODOs for the learner;
- do not commit the completed exploit chain or a flag solution;
- verify that `make`, the binary, and the intended learning path work on Linux x86_64.

When reporting a problem, include your distribution, architecture, compiler version, command used, and complete error output.

## Project Status

The foundational curriculum and the first stack-exploitation lab sequence are available. Format-string, heap, reversing, and other advanced labs remain future work. See [labs/README.md](labs/README.md) for the current lab order.

## Responsible Use

Binary exploitation is dual-use knowledge. This repository is intended for education in controlled environments. Do not use these techniques against systems without explicit authorization.
