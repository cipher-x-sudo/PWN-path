# Phase 2 Lab: ret2win With One Argument

Goal: redirect execution to `win(0xdeadbeef)`.

Build:

```bash
make
```

Inspect:

```bash
file ./ret2win_arg
checksec ./ret2win_arg
nm -an ./ret2win_arg | grep ' win\| gadget'
objdump -d -M intel ./ret2win_arg
```

What changes from basic ret2win:

- normal `ret2win`: overwrite RIP with `win`
- this lab: put `0xdeadbeef` into `rdi`, then jump to `win`

Payload shape:

```text
padding + pop_rdi_ret + 0xdeadbeef + win
```

Checkpoint:

```text
bug:
offset:
argument register:
gadget:
target:
payload shape:
```
