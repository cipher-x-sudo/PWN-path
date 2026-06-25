# Phase 2 Lab: ret2win With Two Arguments

Goal: redirect execution to:

```c
win(0xdeadbeef, 0xcafebabe)
```

Build:

```bash
make
```

Inspect:

```bash
file ./ret2win_2args
checksec ./ret2win_2args
nm -an ./ret2win_2args | grep ' win\| gadget'
objdump -d -M intel ./ret2win_2args
```

What changes from the one-argument lab:

- first argument goes in `rdi`
- second argument goes in `rsi`
- you need one gadget for each register

Payload shape:

```text
padding
pop rdi; ret
0xdeadbeef
pop rsi; ret
0xcafebabe
win
```

Checkpoint:

```text
bug:
offset:
first argument register:
second argument register:
gadgets:
target:
payload shape:
```
