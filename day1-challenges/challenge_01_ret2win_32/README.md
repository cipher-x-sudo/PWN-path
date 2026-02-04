# challenge_01_ret2win_32

32-bit ret2win. Buffer 40 bytes, then saved EBP (4), then return address (4).

- **Vuln**: `gets(buf)` in `vuln()`.
- **Win**: `win()` prints the flag.
- **Goal**: Overflow and overwrite return address with `&win`.

```bash
make
checksec ./vuln
nm ./vuln | grep win
```

Use `cyclic` / `cyclic_find` to get offset, then `payload = padding + p32(win_addr)`.
