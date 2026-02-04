# challenge_03_buffer_32

32-bit. `read(0, buf, 0x100)` into buf[56]. Win: `print_flag()`.

Find offset with cyclic, then payload = padding + p32(print_flag).
