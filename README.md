Small String Optimization (SSO) string library implemented in ANSI C.

C Toolbox

Lightweight C library implementing generic data structures and string utilities, built with focus on memory management, modular design, and low-level programming practice. It includes: -A generic dynamic vector (void*) -A String implementation with Small String Optimization (SSO) -A small CLI application for text processing and filtering

Features

Generic Vector (core/vector) -Type-agnostic container using void* -Dynamic resizing with exponential growth -Constant-time random access -Memory-safe push/pop/remove operations -Generic sorting via comparator function

String with SSO (core/string) -Small String Optimization (inline buffer for short strings) -Automatic transition to heap allocation when needed -Case-insensitive comparison support -Efficient append and copy operations -Zero-dependency design

Text Processing CLI (app/) -Interactive console program -Word filtering by: -Maximum length -Exact length
-Prefix matching -Duplicate prevention -Sorting using insertion sort

core/ vector/ Generic dynamic array implementation string/ SSO string implementation

logic/ filters Word filtering algorithms sort Sorting algorithms

app/ cli User interaction layer main Entry point

Build Requirements -GCC or Clang -Make -Linux environment (tested on Linux distributions)

Compile make

Run ./c-toolbox

Clean build make clean

Design Goals This project was built to practice and demonstrate: -Manual memory management in C -Implementation of generic data structures -Separation of concerns (core / logic / application layers) -Low-level string optimization techniques -Algorithm implementation without STL or external libraries

Example Usage Enter number of words 5

1- hello 2- world 3- hell 4- example 5- hello

Output (filter + sort example) Found words: hello world example

Key Technical Concepts -Pointer arithmetic -Dynamic memory allocation (malloc, realloc, free) -Generic programming using void* -Stack vs heap string optimization (SSO) -Time complexity awareness (sorting and filtering operations)

Project Purpose This project is part of my learning path in: -C systems programming -Data structures implementation from scratch -Memory-safe programming practices -Preparing for junior-level software development roles

Author Self-taught developer focused on: -C programming -Systems programming fundamentals -Data structures and algorithms -Linux environment development

Future Improvements -Hash table implementation (planned) -File input/output processing -Performance benchmarking tools -Unit testing framework -CLI argument parsing

What makes this project stand out -No external libraries -Fully manual memory management -Clean separation of layers (core / logic / app) -Real-world usage of generic structures in C -Focus on correctness over shortcuts
