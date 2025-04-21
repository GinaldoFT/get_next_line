<p align="center">
  <img src="https://raw.githubusercontent.com/GinaldoFT/GinaldoFT/main/42covers/cover-get_next_line.png" alt="get_next_line cover" />
</p>

# 📄 get_next_line

`get_next_line` is a function that reads and returns one line at a time from a file descriptor.  
This project is part of the 42 school curriculum and focuses on low-level file I/O, memory management, and the use of static variables.

<p align="center">
  <img src="https://raw.githubusercontent.com/GinaldoFT/GinaldoFT/main/42Badges/get_next_linee.png" width="100" alt="get_next_line badge"/>
</p>

---

## 🧠 Project Objective

The objective of `get_next_line` is to implement a function that:

- Reads from a file descriptor using a buffer of fixed size
- Returns a full line, ending with `\n` (if present)
- Handles incomplete reads and buffers properly
- Manages memory and leftover data between function calls using a `static` variable
