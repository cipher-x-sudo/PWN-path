# 4-Week Pwn Learning Plan

Structured curriculum for binary exploitation from scratch: **theory + lab** each day, with in-depth focus on **bypassing protections** (NX, PIE, ASLR, canary, RELRO, Fortify) using pwntools, GDB, and pwndbg.

---

## Daily Structure (Every Day)

Each day has **theory + lab** together, then your own challenges:

| Phase | What you do |
|-------|-------------|
| **Theory + lab** | Learn the day’s concept (read/skim notes or a short guide). Then do **2 guided challenges** with the theory — step-by-step so you know exactly what to do (offset, leak, payload, GDB). |
| **Your work** | **8 challenges** on your own. Same topic and protections as the day; you apply the same ideas without a full walkthrough. |

So every day: **2 guided (with theory) + 8 on your own = 10 challenges total.**

---

## Protections: What They Are and How You Bypass Them

Before each challenge run **checksec** and decide which protections are on and which bypass to use.

- **NX**: Stack/heap non-exec → bypass with **ROP** (ret2win, ret2libc, gadgets); if NX off use shellcode.
- **PIE**: Binary at random base → **leak** a code address (format string, partial read), then `base = leak - offset`, set `ELF.address`.
- **ASLR**: Libc/stack/heap randomized → **leak** libc (e.g. via GOT/puts), get libc base; use LibcSearcher or one_gadget.
- **Stack Canary**: Cookie above return address → **leak** canary (format string or partial read) and put it back in payload; or **brute** only if fork and low entropy.
- **RELRO Full**: GOT read-only → do **not** overwrite GOT; use ROP, one_gadget, or overwrite hooks (`__malloc_hook`, `__free_hook`).
- **RELRO Partial**: GOT writable → **GOT overwrite**: overwrite GOT with libc function (e.g. system) or shellcode, then trigger that plt call.
- **FORTIFY**: Extra checks on printf/memcpy → **avoid** format-string on fortified; use overflow, UAF, or non-fortified paths.

**Habit**: checksec → list protections → choose bypass(es) → build exploit.

---

## Tools You’ll Use Every Day

- **pwntools**: `cyclic`/`cyclic_find`, `ELF`, `ELF.address` (after PIE leak), `process`/`remote`, `pack`/`unpack`, `ROP`, `LibcSearcher`, `context`, `log`
- **GDB + pwndbg**: checksec, `vmmap` (PIE/ASLR bases), breakpoints, stack inspection (canary layout), `disass`, gadget search

**Daily habit**: checksec → identify protections and bypass plan → full pwntools exploit → verify in GDB/pwndbg. Every exploit should demonstrate a clear bypass.

---

## Week 1: Foundations and First Bypasses

**Goal**: Stack layout, buffer overflows, and in-depth bypass of NX (when off), canary, and RELRO/format string. Every challenge: run checksec and name the protection(s) you bypass.

| Day | Topic | Protection bypass focus | 2 guided challenges (with theory) | 8 your work |
|-----|------|-------------------------|-----------------------------------|-------------|
| 1 | **Stack layout & ret2win** | No NX or trivial overflow; ret2win | Do 2 ret2win (e.g. ROP Emporium 32-bit + 64-bit) with a theory doc that walks through offset, win addr, payload | 8 ret2win-style from ROP Emporium, picoCTF, pwnable.kr |
| 2 | **ret2win (variants)** | Same; 32 vs 64-bit, calling convention | 2 challenges with theory on conventions and `context.binary` | 8 variants (fd, bof, other ret2win) |
| 3 | **Simple shellcode** | NX disabled: shellcode on stack | 2 with theory on when NX is off, `shellcraft`, EIP/RIP | 8 shellcode-on-stack challenges |
| 4 | **GDB/pwndbg for bypasses** | Use GDB to verify canary, ret addr, layout | 2 challenges with theory: breakpoints, vmmap, stack inspection | 8 same-type challenges, debug-first |
| 5 | **Stack canary bypass** | Canary: leak or brute; restore in payload | 2 with theory on leaking canary and restoring it | 8 canary bypass challenges |
| 6 | **Format string (read)** | PIE/ASLR/canary: leak via format string | 2 with theory on %p, reading stack, using leak | 8 format-string read challenges |
| 7 | **Format string (write)** | Arbitrary write: GOT, ret addr, hook | 2 with theory on %n, FmtStr, one-byte writes | 8 format-string write challenges |

**Week 1 deliverable**: You can overflow a buffer, find offset with `cyclic`, and bypass (1) no-NX with shellcode or ret2win, (2) canary by leak/brute and restore, (3) PIE/ASLR/canary by format-string leak, (4) Partial RELRO by format-string write. All exploits in pwntools; all debugging in GDB/pwndbg.

---

## Week 2: NX Bypass (ROP) and Multi-Protection

**Goal**: Bypass NX reliably with ROP; combine PIE + ASLR + canary + NX in one exploit (leak → bases → ROP). Full RELRO: no GOT; use ret2libc/one_gadget.

| Day | Topic | Protection bypass focus | 2 guided challenges (with theory) | 8 your work |
|-----|------|-------------------------|-----------------------------------|-------------|
| 1–2 | **ROP basics (NX bypass)** | NX: ret2libc or ret2win | 2 with theory on ROP(binary), rop.call(), ret2libc | 8 ROP Emporium split / ret2libc style |
| 3 | **ROP (no useful functions)** | NX: gadget chains | 2 with theory on ropper, ROPgadget, building chain | 8 badchars/fluff-style |
| 4 | **Stack pivot** | NX + limited overflow: ROP on fake stack | 2 with theory on leave/ret, xchg, add rsp | 8 pivot-style |
| 5 | **ret2csu** | NX + need 3 args: __libc_csu_init | 2 with theory on universal gadgets | 8 64-bit CTF challenges |
| 6 | **Canary + NX + PIE/ASLR** | Multiple: leak all, then ROP | 2 with theory on leak canary/PIE/libc, restore, ROP | 8 multi-leak + ROP |
| 7 | **Full workflow (all protections)** | Checksec-driven; Full RELRO → ROP/hooks | 2 with full recon → leak → ROP walkthrough | 8 harder stack challenges |

**Week 2 deliverable**: You can bypass NX with ROP (ret2libc, gadgets, ret2csu, stack pivot) and bypass PIE + ASLR + canary in one exploit. You know when Full RELRO blocks GOT overwrite and use ROP/hooks instead.

---

## Week 3: Heap and Bypassing Protections via Heap

**Goal**: Heap layout and primitives (UAF, double-free, tcache); bypass ASLR/NX via heap (hooks or GOT when Partial RELRO; one_gadget when Full RELRO).

| Day | Topic | Protection bypass focus | 2 guided challenges (with theory) | 8 your work |
|-----|------|-------------------------|-----------------------------------|-------------|
| 1 | **Heap layout (GDB)** | Chunks, main_arena, bins | 2 with theory on malloc/free traces in pwndbg | 8 heap recon / easy UAF |
| 2 | **Use-after-free (UAF)** | Overwrite vtable or function ptr | 2 with theory on free-then-use, overlapping allocs | 8 UAF challenges |
| 3 | **Double free / fastbin** | Overwrite fd; alloc at target | 2 with theory on fastbin double-free | 8 fastbin challenges |
| 4 | **Unlink or heap overflow** | Corrupt chunk headers; safe linking | 2 with theory (optional) or heap overflow | 8 unlink/overflow |
| 5 | **tcache (modern)** | tcache poisoning; alloc at arbitrary addr | 2 with theory on tcache, __free_hook | 8 tcache challenges |
| 6 | **House of X (one)** | One House-of for arbitrary write | 2 with theory on chosen technique | 8 House-of style |
| 7 | **Heap + one_gadget / ROP** | Full RELRO: overwrite hooks | 2 with theory on hook overwrite, one_gadget | 8 heap + one_gadget |

**Week 3 deliverable**: You can bypass ASLR via heap (libc leak, alloc near hooks), bypass Full RELRO by overwriting hooks, and bypass NX by redirecting to one_gadget or system. Debug heap in GDB/pwndbg; use tcache/fastbin for arbitrary write.

---

## Week 4: All Protections Combined and Edge Cases

**Goal**: Every challenge: checksec, list protections, choose bypass. Practice partial overwrite and brute when leaks are limited. Optional: seccomp/sandbox bypass.

| Day | Topic | Protection bypass focus | 2 guided challenges (with theory) | 8 your work |
|-----|------|-------------------------|-----------------------------------|-------------|
| 1–2 | **Mixed stack + heap** | All: NX, PIE, ASLR, canary, RELRO, FORTIFY | 2 with theory: checksec → plan → exploit | 8 mixed from backlog, picoCTF, pwnable.kr |
| 3 | **Partial overwrite & brute** | ASLR with few leaks; partial overwrite or brute | 2 with theory on partial overwrite, brute when fork | 8 ASLR partial/brute |
| 4 | **Sandbox / seccomp (optional)** | ROP to open/read/write; no execve | 2 with theory on seccomp dump, allowed syscalls | 8 sandbox bypass or more userland |
| 5 | **Speed run** | Bypass plan from checksec before coding | Re-do 2 with timed plan → exploit | 8 from your solved list, fast |
| 6 | **Writeups (bypass-centric)** | Document checksec and each bypass | 2 challenges with full writeup (theory + bypass) | 8 more or write 3 full writeups |
| 7 | **Capstone** | Every step names protection bypassed | 2 harder or multi-step with full walkthrough | 8 harder / one mini-CTF binary |

**Week 4 deliverable**: You can open any pwn, run checksec, list every protection and exact bypass (leak what, overwrite what, ROP/hook/GOT), then produce an exploit and verify in GDB/pwndbg. You understand partial overwrite and brute when leaks are limited.

---

## Where to Get Challenges

- **ROP Emporium**: ret2win, split, callme, write4, badchars, fluff, pivot (32/64).
- **pwnable.kr**: fd, collision, bof, passcode, random, input, leg, mistake, shellshock, uaf, memcpy, asm, unlink, etc.
- **picoCTF**: Binary Exploitation, easy → medium.
- **pwnable.tw**: start, orw; then harder.
- **how2heap**: Run every example in GDB (for theory/lab, not counted as “challenges”).
- **Past CTFs**: “pwn writeup [year]” and pick binaries that match the week’s topic.

Use these to pick your **2 guided** (from writeups or day-specific theory docs) and your **8** each day.

---

## Daily Routine (Repeat for 28 Days)

1. **Theory**: Read the day’s concept (e.g. stack + ret2win, canary bypass, ROP, heap).
2. **Lab (2 guided)**: Do 2 challenges with theory — follow a short guide or writeup so you know exactly what to do (checksec, offset, leak, payload, GDB).
3. **Your work (8)**: Do 8 challenges on your own on the same topic. For each:
   - Run `checksec`; list which protections are on.
   - In GDB/pwndbg: find crash, offset, bypass strategy.
   - Write a full pwntools exploit and get flag/shell.
   - If stuck 20–30 min, use writeups only then.
4. **End of day**: Note for each challenge which protections were on and which bypass you used; note one GDB or pwntools trick.

By the end you’ll have strong muscle memory for exploit writing, pwntools, GDB, and pwndbg, and an in-depth grasp of bypassing NX, PIE, ASLR, canary, RELRO, and FORTIFY in stack and heap pwn.
