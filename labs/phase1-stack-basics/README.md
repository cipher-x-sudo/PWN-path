# Phase 1 Lab: Stack Frames

This lab is not an exploit challenge. It is a debugger fluency drill.

Build:

```bash
make
```

Run:

```bash
./stack_frames
```

Debug:

```bash
gdb ./stack_frames
```

Suggested GDB flow:

```gdb
set disassembly-flavor intel
break main
run
disassemble main
break inspect_me
continue
info registers
x/40gx $rsp
disassemble inspect_me
stepi
nexti
```

Questions to answer in your notes:

- Where are the arguments stored when `inspect_me` starts?
- Where is the saved return address?
- How does `$rsp` change across `call`, function prologue, and function epilogue?
- Which values are on the stack and which are in registers?

