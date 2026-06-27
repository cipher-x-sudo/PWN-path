# Phase 2 Lab: Stack Alignment

Goal: diagnose a ROP chain that reaches `win()` but crashes because the stack is
not aligned, then correct the alignment with a plain `ret` gadget.

Build:

```bash
make
```

Inspect:

```bash
file ./stack_alignment
checksec ./stack_alignment
nm -an ./stack_alignment | grep ' win\| alignment_check'
objdump -d -M intel ./stack_alignment
ROPgadget --binary ./stack_alignment | grep ': ret$'
```

Debugging workflow:

1. Find the overflow offset and try returning directly to `win()`.
2. Run that payload in GDB and inspect the instruction where it crashes.
3. At `movaps`, inspect the alignment with `p/x $rsp & 0xf`.
4. Find a plain `ret` gadget and determine where it belongs in your chain.

Hints:

- The System V AMD64 ABI expects the stack to be 16-byte aligned before a
  function call.
- A plain `ret` consumes one 8-byte address from the stack.
- Your corrected chain should change alignment without setting a register.

Checkpoint:

```text
bug:
offset:
crashing instruction:
rsp alignment before fix:
plain ret effect:
corrected payload shape:
```
