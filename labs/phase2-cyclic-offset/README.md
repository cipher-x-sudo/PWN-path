# Phase 2 Lab: Cyclic Offset Discovery

Goal: find the exact RIP offset using a cyclic pattern, then redirect execution
to `win()`.

Build:

```bash
make
```

Inspect:

```bash
file ./cyclic_offset
checksec ./cyclic_offset
nm -an ./cyclic_offset | grep ' win'
objdump -d -M intel ./cyclic_offset
```

Offset workflow:

```bash
cyclic 200
gdb ./cyclic_offset
run
info registers
x/gx $rsp
cyclic -l <value_from_stack>
```

Hint:

- If the crash happens at `ret`, `rip` may still show the `ret` instruction.
- In that case, inspect `$rsp`.
- The 8 bytes at `$rsp` are what `ret` is trying to jump to.

Payload shape:

```text
padding_from_cyclic
win
```

Checkpoint:

```text
bug:
crash value:
offset:
target:
payload shape:
```
