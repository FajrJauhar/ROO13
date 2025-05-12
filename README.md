
If `Decrypt & Edit` is chosen:
- The file is decrypted and stored in a temporary file.
- It is opened in `nano` for editing.
- After editing, the updated file is re-encrypted.

---

## 🔧 Requirements

- Linux terminal with:
  - `nano`
  - `gcc` or compatible C compiler
- Basic knowledge of using CLI tools

---

## 📁 Example Usage

```bash
$ gcc root13.c -o root13
$ ./root13

1. Encrypt File
2. Decrypt & Edit
3. Exit

Enter your choice: 2
Enter file name: secret_note.txt
> [nano editor opens]
> [After editing, file is re-encrypted]
