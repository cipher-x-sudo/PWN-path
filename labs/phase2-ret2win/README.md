# Phase 2 Lab: ret2win

This is a local beginner exploit-writing lab. The binary has a stack overflow
and a hidden `win()` function. Your job is to redirect execution to `win()`.

Build:

```bash
make
```

Inspect:

```bash
file ./ret2win
checksec ./ret2win
nm -an ./ret2win | grep ' win'
objdump -d -M intel ./ret2win
```

Exploit workflow:

1. Crash the program with a cyclic pattern.
2. Find the offset to the saved return address.
3. Find the address of `win`.
4. Send `padding + p64(win)`.
5. If the process crashes before printing the flag on some systems, add a
   single `ret` gadget before `win` for stack alignment.

Keep your solution in a copied template:

```bash
cp ../../templates/exploit.py solve.py
```

Questions to answer in your writeup:

- Which mitigations are enabled?
- Why does NX not stop this exploit?
- What exact offset reaches saved RIP?
- What address did you redirect execution to?

