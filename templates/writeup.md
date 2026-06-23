# Challenge Writeup

Challenge:

Source:

Date:

## Summary

One paragraph: what the binary does, where the bug is, and what the exploit does.

## Protections

```text
file:
checksec:
```

Protections enabled:

- NX:
- PIE:
- Canary:
- RELRO:
- Fortify:

## Bug

Vulnerable function/path:

Root cause:

Input constraints:

## Primitive

What the bug gives:

- [ ] RIP/EIP control
- [ ] leak
- [ ] arbitrary read
- [ ] arbitrary write
- [ ] UAF
- [ ] double free
- [ ] heap overflow

Important offsets:

```text
offset to saved return address:
leaked address:
base address:
```

## Exploit Plan

1. 
2. 
3. 

## Debugger Evidence

Important GDB commands/output:

```gdb

```

## Final Payload Shape

Do not paste giant payload dumps. Describe the structure.

```text
padding + saved registers/canary + ROP/leak/write/control
```

## Lessons

- 

