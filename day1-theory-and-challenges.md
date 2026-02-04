# Day 1: Stack Layout & ret2win — Theory, Lab (2 Guided), and 8 On Your Own

**Structure**: Learn the theory below, then do **2 guided challenges** with the theory (so you know what to do). After that, do **8 challenges on your own** using the same ideas.

---

## Part 1 — Theory & Concepts (Learn This First)

### 1. The stack and the return address

- **Stack**: grows downward in memory; each function gets a **stack frame** (local variables, saved base pointer, **saved return address**).
- When a function is **called**, the address of the next instruction (where to return) is pushed on the stack. When the function does **ret**, the CPU jumps to that saved address.
- **Buffer overflow**: if you write past the end of a buffer (e.g. `gets`, unbounded `read` into a fixed-size array), you can overwrite:
  - other locals
  - saved base pointer
  - **saved return address** ← this is what we abuse.

If you overwrite the return address with an address **you choose**, when the function returns it will jump to **your** address instead of the real caller. That’s the core of “hijacking control flow.”

### 2. What “ret2win” means

- The binary has a “win” function (e.g. `win()`, `get_flag()`, `print_flag()`) that you’re *not* supposed to reach in normal use.
- **ret2win** = **ret**urn **2** (to) **win**: overflow the buffer so the **saved return address** is replaced with the **address of the win function**. When the vulnerable function returns, execution goes to `win()` and you get the flag.
- No shellcode, no ROP chain yet — just one address overwrite. This works when:
  - NX is **off** (stack executable) or we’re not running code on the stack, we’re just jumping to existing code;
  - There’s no stack canary (or we’re not dealing with it yet);
  - We know the address of the win function (no PIE, or we’ll leak later).

So Day 1 is: **overflow → overwrite return address with `&win` → get flag.**

### 3. checksec and “no protections” for Day 1

Run on the binary:

```bash
checksec ./binary
# or: pwn checksec ./binary
# or: rabin2 -I ./binary
```

For Day 1 you want challenges where:

- **NX**: often disabled (so we’re not forced to ROP yet), or we’re only jumping to existing code (ret2win).
- **PIE**: disabled so the binary is at a **fixed base**; we can use addresses like `0x8048xxx` (32-bit) or `0x401xxx` (64-bit) from `objdump`/IDA/Ghidra.
- **Canary**: disabled so one overflow is enough to reach the return address.
- **RELRO**: doesn’t matter yet for simple ret2win.

So “trivial overflow” + “no canary” + “no PIE” (and often “no NX”) = classic ret2win setup.

### 4. Finding the overflow offset (cyclic pattern)

We need to know **how many bytes** until we start overwriting the **return address**.

- **cyclic (pattern)**:
  - Generate a unique pattern: `cyclic 200` (or `pwn cyclic 200`).
  - Send it as input; the program crashes. Note the **fault address** or the **value** that was used as return address (e.g. in GDB: `info registers eip` or `rip`).
  - **cyclic_find**: `cyclic_find(0x6161616e)` or `cyclic_find(b'naaa')` (the 4 bytes that landed in the return slot) gives the **offset** in bytes from the start of your input to the first byte of the return address.
- So: `payload = b"A" * offset + p32(win_addr)` (32-bit) or `p64(win_addr)` (64-bit).

### 5. Finding the win function address

- **From symbols** (if not stripped):
  ```bash
  objdump -d ./binary | grep -i win
  nm ./binary | grep win
  ```
- **In pwntools**:
  ```python
  from pwn import *
  e = ELF('./binary')
  win = e.symbols['win']   # or e.symbols['get_flag'] etc.
  ```
- Or in GDB: `print win` or `x win`.

### 6. 32-bit vs 64-bit and calling convention (for later)

- **32-bit (x86)**: args on stack; return address is 4 bytes; use `p32(addr)`.
- **64-bit (x86_64)**: first args in `rdi`, `rsi`, `rdx`, …; return address is 8 bytes; use `p64(addr)`. For **plain ret2win** (no args), we only overwrite the return address with the win function address; no need to set registers yet.

### 7. GDB/pwndbg basics for Day 1

- Run: `gdb ./binary` or use pwndbg.
- Set breakpoint: `b *main`, `b *vuln`, or `b *0x8048xxx`.
- Run: `r`, with input: `r < input.txt` or `run <<< "$(cyclic 200)"`.
- After crash: `info registers` (eip/rip = where it tried to jump), `x/20wx $esp` (stack), `x/x $esp` (value at top of stack = our overwritten return address).
- Find offset: crash with cyclic, then `cyclic_find(value_at_ret_slot)` in Python.

### 8. pwntools script skeleton (Day 1)

```python
from pwn import *

context.binary = elf = ELF('./binary')
win = elf.symbols['win']   # or exact address if stripped

# Local
p = process('./binary')
# Remote (when needed)
# p = remote('host', port)

offset = 40   # from cyclic_find

payload = flat(
    b'A' * offset,
    p32(win) if context.bits == 32 else p64(win)
)

p.sendline(payload)
p.interactive()
```

---

## Part 2 — 2 Guided Challenges (Do These With the Theory)

Do these **right after** the theory, step-by-step, so you know exactly what to do.

| # | Guided challenge | What to do (with theory) |
|---|-------------------|---------------------------|
| 1 | **ret2win (x86)** — ROP Emporium 32-bit | 1) Download binary, `checksec`. 2) `cyclic 200` → run in GDB → crash → `cyclic_find(eip_value)`. 3) `objdump -d \| grep win` or `ELF.symbols['win']`. 4) Payload = `b'A'*offset + p32(win)`. 5) Run exploit, get flag. |
| 2 | **ret2win (x64)** — ROP Emporium 64-bit | Same steps; use `p64(win)` and 8-byte offset. Notice the offset is different from 32-bit. |

After these two you should be clear on: checksec → cyclic/cyclic_find → win address → payload → exploit.

---

## Part 3 — 8 Challenges On Your Own

Do these **after** the 2 guided challenges. No full walkthrough; use the same flow (checksec, offset, win, payload).

| # | Challenge idea | Source | What you practice |
|---|----------------|--------|--------------------|
| 1 | Buffer overflow 0 | picoCTF | Simple overflow, ret2win |
| 2 | Buffer overflow 1 | picoCTF | Same, different buffer size |
| 3 | fd | pwnable.kr | Overflow or control flow to win |
| 4 | bof | pwnable.kr | Classic overflow → win/flag |
| 5 | Local ret2win | Any CTF warmup / writeup | Full exploit: process(), payload |
| 6 | Custom crackme | Your own C: gets(buf), win() | Compile -fno-stack-protector -no-pie |
| 7 | ret2win 32 + 64 in one script | ROP Emporium both | context.binary, context.bits, flat() |
| 8 | Another ret2win | ROP Emporium or past CTF | Same idea; second binary |

---

## Part 4 — Day 1 Checklist

Before moving to Day 2, you should be able to:

- [ ] Explain: stack frame, saved return address, and how overflow hijacks it.
- [ ] Explain: what “ret2win” means and when it works (no canary, known win address).
- [ ] Run `checksec` and say which protections are on/off.
- [ ] Use `cyclic` and `cyclic_find` to get the exact offset to the return address.
- [ ] Find the win function address (ELF.symbols, objdump, nm, GDB).
- [ ] Write a pwntools exploit that sends `padding + p32/p64(win)` and gets the flag.
- [ ] In GDB/pwndbg: run with payload, see crash at your chosen address, inspect stack.

Once this is solid, you’re ready for Day 2 (ret2win variants, 32 vs 64-bit, calling conventions).

**Summary**: Theory → 2 guided (ret2win 32 + 64) → 8 on your own = 10 total for Day 1.
