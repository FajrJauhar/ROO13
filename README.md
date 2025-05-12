# 🔐 ROOT13 - Custom File Encryptor with Secure Editing

ROOT13 is a terminal-based encryption tool written in C that provides a ROT13-inspired encryption for `.txt` files, including secure file editing via the `nano` editor. It is especially useful when you want to protect and modify sensitive data without exposing plaintext on disk.

---

## ✨ Features

- 🔁 **ROOT13 Custom Encryption:**
  - ROT13 for letters (a-z, A-Z)
  - Modulo-shifted digits (0-9)
  - Special characters converted to unique tokens (e.g., `@` ➝ `A3`)

- 🧠 **Password Validation (optional):**
  - Ensure only authorized users can decrypt or edit files.

- 📝 **Nano Editor Integration:**
  - Opens decrypted content in `nano`
  - Automatically re-encrypts after editing

- 🧾 **Menu-Driven UI:**
  - Intuitive options for encrypting, decrypting, and editing

---

## 🚀 How It Works

### 🔣 Encryption Logic

| Character Type | Example Input | Example Output |
|----------------|---------------|----------------|
| Lowercase      | `a`           | `n`            |
| Uppercase      | `B`           | `O`            |
| Digit          | `5`           | `8`            |
| Special        | `@`           | `A3`           |

### 🧰 Menu Options


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
