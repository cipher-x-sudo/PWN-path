# challenge_02_ret2win_64

64-bit ret2win. Buffer 40 bytes, then saved RBP (8), then return address (8).

- **Vuln**: `gets(buf)` in `vuln()`.
- **Win**: `win()` prints the flag.
- **Goal**: Overflow and overwrite return address with `&win`. Use `p64(win_addr)`.

```bash
make
checksec ./vuln
nm ./vuln | grep win
```
