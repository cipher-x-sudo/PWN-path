# Day 1 Challenges — Stack & ret2win

C source challenges for Day 1. Each challenge lives in its own folder with `main.c` and a `Makefile` that compiles with **no PIE** and **no stack canary** (suitable for ret2win).

## Build all

```bash
make          # or: make all
```

All 10 challenges are built as **64-bit** (no `gcc-multilib` needed). Folder names like `challenge_01_ret2win_32` are kept for reference; the binaries are 64-bit. A linker warning about `gets` being dangerous is expected and harmless.

## Protections (intended for Day 1)

Each Makefile compiles with:

- `-fno-stack-protector` — no stack canary
- `-no-pie` — fixed base address (so you can use addresses from `nm` / `objdump`)
- `-z noexecstack` — NX on (we jump to existing code, not shellcode)
- `-O0` — no optimization (easier to debug)
- 32-bit: `-m32`; 64-bit: default

So: **overflow → overwrite return address with win() → flag.**

## Challenge list

All binaries are **64-bit** (use `p64()` for return address). Folder names with `_32` are legacy; they build as 64-bit.

| # | Folder | Vuln | Win function |
|---|--------|------|--------------|
| 1 | challenge_01_ret2win_32 | gets(buf) | win() |
| 2 | challenge_02_ret2win_64 | gets(buf) | win() |
| 3 | challenge_03_buffer_32 | read() no null | print_flag() |
| 4 | challenge_04_buffer_64 | read() no null | print_flag() |
| 5 | challenge_05_gets_32 | gets(), different size | get_flag() |
| 6 | challenge_06_gets_64 | gets() | get_flag() |
| 7 | challenge_07_read_32 | read(0, buf, 0x200) | win() |
| 8 | challenge_08_read_64 | read(0, buf, 0x200) | win() |
| 9 | challenge_09_crackme_32 | gets() | reveal_flag() |
| 10 | challenge_10_crackme_64 | gets() | reveal_flag() |

## Solve flow

1. `checksec ./binary`
2. `cyclic 200` → run binary, crash → `cyclic_find(<value>)` for offset
3. `nm ./binary | grep -i win` or `elf.symbols['win']` in pwntools
4. Payload: `padding + p32(win)` or `p64(win)`
5. Get the flag (or "you win" message).

Flags are fake for local practice; replace with your own in the C source if you want.
