# Phase 2 Lab: Compiler-Generated SSE Stack Alignment

Goal: see a realistic stack-alignment failure where normal C SIMD code makes
the compiler generate `movaps`, then correct the ROP-chain alignment.

Build:

```bash
make
```

## New C Concepts

- `__m128` is one 128-bit SSE value. It can hold four 32-bit `float` values.
- `_mm_set_ps(4, 3, 2, 1)` fills those four lanes. After storing them in an
  array, `result[0]` is `1`.
- `aligned(16)` tells the compiler that `result` must begin at an address that
  is divisible by 16.
- `_mm_store_ps(result, values)` stores all four floats into `result`.
- `noinline` keeps each function separate so its entry and stack frame are easy
  to inspect in GDB.

This is normal C using SSE intrinsics. GCC translates the aligned store into
`movaps`; the source does not contain hand-written assembly.

Inspect:

```bash
file ./stack_alignment_sse
checksec ./stack_alignment_sse
nm -an ./stack_alignment_sse | grep ' win\| prepare_reward'
objdump -d -M intel ./stack_alignment_sse
ROPgadget --binary ./stack_alignment_sse | grep ': ret$'
```

## Debugging Workflow

1. Find the exact distance to saved RIP with a cyclic pattern.
2. Try returning directly to `win()` and inspect the crash in GDB.
3. Disassemble `prepare_reward` and identify the compiler-generated `movaps`.
4. At the crashing instruction, check `p/x $rsp & 0xf` and inspect the memory
   operand used by `movaps`.
5. Compare that run with a chain containing one additional plain `ret` before
   `win()`.
6. Explain why consuming one 8-byte stack slot changes the alignment.

Remember:

- The System V AMD64 ABI requires 16-byte stack alignment before a function
  call.
- A normal function therefore expects a particular alignment when it begins.
- A ROP `ret` enters a function differently from a normal `call`.
- One extra plain `ret` moves `rsp` forward by 8 bytes.

Checkpoint:

```text
bug:
offset:
what __m128 stores:
compiler-generated instruction:
crashing memory address alignment:
plain ret effect:
why the corrected run works:
```
