# Phase 2 Lab: ret2libc Leak

Goal: learn the first full ret2libc shape:

```text
leak libc address -> calculate libc base -> call system("/bin/sh")
```

Build:

```bash
make
```

Inspect:

```bash
file ./ret2libc_leak
checksec ./ret2libc_leak
nm -an ./ret2libc_leak | grep ' vuln\| gadget'
objdump -d -M intel ./ret2libc_leak
readelf -r ./ret2libc_leak | grep puts
```

## New Idea

NX is enabled, so the stack is not executable. Instead of putting shellcode on
the stack, reuse libc code that is already loaded.

Useful names:

- `puts@plt`: the binary's small caller stub for `puts`.
- `puts@got`: the memory slot that holds the real libc address of `puts`.
- libc base: where libc was loaded this run.
- `system`: libc function that can run a command.
- `/bin/sh`: string inside libc that can become the first argument to `system`.

## Workflow

Stage 1 leaks one libc address:

```text
padding
pop rdi; ret
puts@got
puts@plt
vuln
```

That prints the real runtime address of `puts`, then returns to `vuln` so you
can send a second payload.

Stage 2 uses the leak:

```text
libc base = leaked puts - libc.symbols["puts"]
system = libc base + libc.symbols["system"]
binsh = libc base + next(libc.search(b"/bin/sh"))
```

Then call:

```text
system("/bin/sh")
```

You may need one extra plain `ret` before `system` for stack alignment, just
like the stack-alignment labs.

Checkpoint:

```text
bug:
offset:
first argument register:
what puts@got contains:
why puts@plt is called:
why return to vuln after leak:
libc base formula:
final call:
```
