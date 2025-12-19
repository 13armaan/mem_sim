# Memory Management Simulator (C++)

## Overview

This project implements a **command-line memory management simulator** that models how an operating system manages **physical memory allocation and deallocation**.  
It simulates dynamic memory allocation using a **linked-list–based block allocator** and supports multiple allocation strategies.

The goal of the project is **not** to build a real OS allocator, but to accurately **simulate allocator behavior**, fragmentation, and allocation strategies using well-defined data structures and algorithms.

---

## Features

### 1. Physical Memory Simulation
- Simulates a contiguous block of physical memory of user-defined size.
- Memory is represented as a linked list of blocks.
- Each block maintains:
  - Start address (offset)
  - Size
  - Allocation status (free / used)
  - Block ID

---

### 2. Allocation Strategies

The simulator supports **three classic dynamic memory allocation strategies**:

- **First Fit**  
  Allocates the first free block large enough to satisfy the request.

- **Best Fit**  
  Allocates the smallest free block that can satisfy the request.

- **Worst Fit**  
  Allocates the largest available free block.

The allocation strategy can be changed at runtime via CLI commands.

---

### 3. Block Splitting
- When a free block is larger than the requested size, it is **split** into:
  - One allocated block
  - One smaller free block
- This mimics real allocator behavior and reduces internal fragmentation.

---

### 4. Deallocation and Coalescing
- Blocks can be freed using their block ID.
- After deallocation, **adjacent free blocks are automatically merged (coalesced)**.
- This reduces external fragmentation over time.

---

### 5. Fragmentation Statistics

The simulator computes and reports:

- Total memory
- Used memory
- External fragmentation

**External Fragmentation Definition:**


This metric measures how scattered free memory is, even when sufficient total memory exists.

---

### 6. Command-Line Interface (CLI)

The simulator is fully interactive and controlled via a simple CLI.

#### Supported Commands

| Command | Description |
|------|------------|
| `init <size>` | Initialize physical memory |
| `malloc <size>` | Allocate memory |
| `free <id>` | Free a block by ID |
| `set <first|best|worst>` | Set allocation strategy |
| `print` | Display memory layout |
| `stats` | Show memory statistics |
| `exit` | Exit the simulator |

---

## Example Session

scrnshot


---

## Implementation Details

- Language: **C++**
- Data structure: **Singly linked list**
- Allocation complexity:
  - First Fit: `O(n)`
  - Best Fit: `O(n)`
  - Worst Fit: `O(n)`
- Coalescing complexity: `O(n)`



---

## Design Decisions

- Implemented in a **single source file** to focus on allocator correctness and clarity.
- Logic is cleanly separated into:
  - Allocation
  - Deallocation
  - Coalescing
  - Statistics
  - CLI handling
- No external libraries or OS-specific calls are used.

---




## Build & Run

### Compile
```bash
g++ memsim.cpp -o memsim

screenshot
