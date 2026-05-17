# C-Toolbox
## Generic Data Structures and SSO String Library in ANSI C

Lightweight systems programming project written in ANSI C, focused on low-level memory management, generic programming techniques, and modular software architecture.

This project includes:

- A generic dynamic vector implementation using `void *`
- A custom String library with Small String Optimization (SSO)
- A modular CLI application for text filtering and processing

---

# Features

## Generic Vector (`core/vector`)

- Type-agnostic container using `void *`
- Dynamic resizing with exponential growth strategy
- Constant-time random access
- Memory-safe push/pop/remove operations
- Generic sorting through comparator functions
- Manual memory management without external libraries

---

## String Library with Small String Optimization (`core/string`)

- Inline storage for short strings (SSO)
- Automatic transition to heap allocation when capacity is exceeded
- Case-insensitive string comparison
- Efficient append and cloning operations
- Zero-dependency implementation
- Stack vs heap optimization strategy

---

## Text Processing CLI (`app/`)

Interactive console application capable of:

- Filtering words by:
  - Maximum length
  - Exact length
  - Prefix matching
- Duplicate prevention
- Sorting using insertion sort
- Dynamic list creation using generic containers

---

# Project Structure

```text
C-Toolbox/
│
├── core/
│   ├── vector/
│   │   ├── vector.c
│   │   └── vector.h
│   │
│   └── string/
│       ├── string_sso.c
│       └── string_sso.h
│
├── logic/
│   ├── filters.c
│   ├── filters.h
│   ├── sort.c
│   └── sort.h
│
├── app/
│   ├── cli.c
│   ├── cli.h
│   └── main.c
│
├── build/
├── Makefile
└── README.md
