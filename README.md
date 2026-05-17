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

Build Requirements
GCC or Clang
GNU Make
Linux environment

Tested on:

Arch Linux
Linux Mint
Zorin OS

Compilation
make

Run
./c-toolbox

Clean Build Files
make clean
Example Usage
Enter number of words:
5

1- hello
2- world
3- hell
4- example
5- hello

Example filtered output:

Found words:

1- example
2- hello
3- world
Complexity Notes
Operation	Complexity
Vector random access	O(1)
Vector push back (amortized)	O(1)
Vector remove at index	O(n)
Prefix filtering	O(n * m)
Insertion sort	O(n²)
Technical Concepts Practiced
Pointer arithmetic
Dynamic memory allocation (malloc, realloc, free)
Generic programming using void *
Manual memory management
Small String Optimization (SSO)
Stack vs heap optimization
Modular software architecture
Data structure implementation from scratch
Basic algorithmic complexity analysis
Design Goals

This project was created to deepen understanding of:

Systems programming in C
Generic container implementation
Low-level optimization techniques
Separation of concerns
Memory-safe programming practices
Software modularization
Project Purpose

This repository is part of my personal learning path focused on:

C systems programming
Data structures and algorithms
Linux development environment
Low-level software engineering
Future Improvements

Planned future additions include:

Generic hash table implementation
File input/output support
Unit testing framework
Benchmarking utilities
Iterator support for containers
CLI argument parsing
Additional sorting algorithms
What Makes This Project Different
No external libraries
Fully manual memory management
Generic reusable containers
Clean separation between layers
Focus on correctness and architecture
Built as systems programming practice rather than tutorial-style code
Author

Self-taught developer focused on:

C programming
Systems programming
Data structures and algorithms
Linux-based development

Currently building projects focused on low-level programming and software engineering fundamentals.
