# Phase 2 Lab: ret2win With Three Arguments

Goal: redirect execution to:

```c
win(0xdeadbeef, 0xcafebabe, 0x13371337)
```

Build:

```bash
make
```

Inspect:

```bash
file ./ret2win_3args
checksec ./ret2win_3args
nm -an ./ret2win_3args | grep ' win\| gadget'
objdump -d -M intel ./ret2win_3args
```

What changes from the two-argument lab:

- first argument goes in `rdi`
- second argument goes in `rsi`
- third argument goes in `rdx`
- you need one gadget for each register

Payload shape:

```text
padding
pop rdi; ret
0xdeadbeef
pop rsi; ret
0xcafebabe
pop rdx; ret
0x13371337
win
```

Checkpoint:

```text
bug:
offset:
first argument register:
second argument register:
third argument register:
gadgets:
target:
payload shape:
```
