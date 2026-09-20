# iCompressor

A simple text file compressor and decompressor written in C++. It shrinks text files
using a **two-level compression** scheme and can restore them back to the original.

## How It Works (The Algorithm)

Compression is done in two passes, one after the other.

### Level 1 — Dictionary Substitution
Common English words are replaced with short codes.

- A **Trie** (`Trie_class.hpp`) is built from `dictionary.txt`. Each word maps to an index.
- The input is scanned word by word (looking ahead up to 15 characters). When a word
  is found in the Trie, it is replaced by its matching short code from `key.txt`.
- Text that is not in the dictionary is buffered and written out with a length prefix,
  so it can be told apart from the codes during decompression.
- The result of this pass is written to `coutput1.bin`.

### Level 2 — Bit Packing
The Level 1 output is packed more tightly at the bit level.

- Letters (`a`–`z`), space, `,`, `.` and `-` are mapped to numbers `1`–`30`.
- Two such characters are combined into a single 10-bit code (prefixed with `1`).
- Any other byte is stored as its raw 8 bits (prefixed with `0`).
- The bit stream is then flushed into bytes and saved as `<filename>_compressed.bin`.

**Decompression** simply reverses these two steps: Level 2 unpacks the bits into the
Level 1 form (`doutput1.bin`), then Level 1 expands the codes back into words, producing
`<filename>decompressed.txt`.

## Required Files
These must be present in the same folder when running the program:

| File | Purpose |
|------|---------|
| `dictionary.txt` | List of common words used for Level 1 substitution |
| `key.txt` | Short codes that replace the dictionary words |
| `Trie_class.hpp` | Trie data structure used for fast word lookup |
| `Logo.txt` | ASCII logo shown at startup |

## How to Build and Run

**1. Compile:**
```bash
g++ -std=c++17 -O2 iCompressor.cpp -o iCompressor.exe
```

**2. Run:**
```bash
iCompressor.exe
```

**3. Use the menu:**
- Press `1` to **compress** a file, then enter its path/name.
  → Produces `<yourfile>_compressed.bin` and prints the compression ratio.
- Press `2` to **decompress** a file, then enter its path/name.
  → Produces `<yourfile>decompressed.txt`.
- Press `3` to **exit**.

## Example
```
Press '1' to compress your file
Enter your file path or file name to compress: test.txt

	File Compressed Succesfully
	File Path: test_compressed.bin
	Text compressed by: 42%
```

> **Note:** This tool is designed for plain English text files. Best results are
> achieved on content whose words appear in `dictionary.txt`.