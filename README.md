# Lexical Analyzer for C

This project implements a lexical analyzer that parses C source code and identifies tokens such as keywords, identifiers, constants, and operators. It also performs basic error detection for unbalanced braces and missing semicolons.

## Features
- Identifies **Pre-processor Directives** (lines starting with `#`).
- Recognizes **C Keywords** (e.g., `int`, `while`, `return`).
- Distinguishes between **Identifiers** and **Constants**.
- Detects **Operators** and **Special Characters**.
- **Error Detection**: Basic checks for syntax errors like missing semicolons and unbalanced braces.

## How to Run
1. Compile the analyzer:
   ```bash
   gcc lexical_analyzer.c -o lexer
   ```
2. Run it with a sample C file:
   ```bash
   ./lexer input.c
   ```

## Requirements
- GCC Compiler
- C Standard Library
