# Memory Management Simulator  
## Design & Implementation Document

---

## 1. Overview

This project implements a **user-space memory management simulator** that models core operating system concepts including:

- Dynamic physical memory allocation
- External fragmentation
- Multilevel CPU cache behavior

The simulator is **not an operating system**, but a faithful simulation using well-defined data structures and algorithms, following the given project specification.

---
## Command Interface

The simulator provides a CLI-based interface to interact with memory and cache simulation.

Supported commands:
- init <size>        : Initialize physical memory
- malloc <size>      : Allocate a memory block
- free <block_id>    : Free an allocated block
- print              : Display memory layout
- stats              : Display memory statistics
- exit               : Exit simulator

## 2. Project Structure

The project follows a modular structure with clear separation of concerns:

mem_sim/
├── src/
│ ├── allocator/
│ │ └── memory_allocator.cpp
│ ├── cache/
│ │ └── cache.cpp
│ └── main.cpp
├── include/
│ ├── allocator/
│ │ └── allocator.h
│ └── cache/
│ └── cache.h
├── docs/
│ └── design.md
└── readme.md


Each subsystem is implemented independently and integrated at the driver level (`main.cpp`).

---
## Demonstration

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/e3e9a9de-9fa8-45fc-9fef-7c59f7e42b93" />
[Screencast from 2026-01-08 00-13-42.webm](https://github.com/user-attachments/assets/9d9ca01a-3f1b-41ea-891f-6882452ac405)

---
## 3. Physical Memory Simulation

Physical memory is simulated as a **contiguous address space** using a **linked list of memory blocks**.

Each memory block contains:
- `start`: starting address
- `size`: size of the block
- `free`: allocation status
- `id`: allocation identifier
- `next`: pointer to the next block

This representation allows dynamic splitting and merging of memory blocks.

---

## 4. Memory Allocation Strategies

The simulator supports the following allocation strategies:

### First Fit
Selects the first free block large enough to satisfy the request.

### Best Fit
Selects the smallest free block that can satisfy the request.

### Worst Fit
Selects the largest available free block.

### Block Splitting
If a free block is larger than the requested size, it is split into:
- an allocated block
- a remaining free block

### Deallocation and Coalescing
When a block is freed, adjacent free blocks are merged to reduce external fragmentation.

---

## 5. Fragmentation Metrics

The simulator reports:
- Total memory
- Used memory
- External fragmentation

External fragmentation is calculated as:

External Fragmentation = 1 − (largest_free_block / total_free_memory)


Internal fragmentation is not explicitly tracked because variable-sized allocation is used.

---

## 6. Cache Simulation

A **two-level cache hierarchy** is simulated:

- L1 Cache
- L2 Cache

Each cache level is configurable by:
- Cache size
- Block size
- Associativity

Caches are implemented as **set-associative caches**.

---

## 7. Cache Replacement Policy

The simulator implements the **FIFO (First-In First-Out)** replacement policy.

- Each cache line stores an insertion timestamp
- Timestamps are updated only on insertion
- Cache hits do not modify timestamps
- Eviction removes the oldest inserted cache line

---

## 8. Cache Access Flow

Cache accesses follow the hierarchy:

1. L1 cache lookup
2. On L1 miss, L2 cache lookup
3. On L2 miss, data is fetched from memory
4. Blocks are inserted upward (L2 → L1)

This behavior is implemented without tight coupling between cache levels.

---

## 9. Integration Between Components

The allocator and cache are implemented as **independent modules**.

Integration occurs in `main.cpp`, where:
- the allocator returns a physical address
- the cache is accessed using that address

Example integration flow:

```cpp
int addr = malloc_sim(size);
access_add(addr);
```
---

## 10. Command Line Interface (CLI)

The simulator provides an **interactive command-line interface** that allows users to test different memory allocation strategies and observe memory behavior dynamically.

### Supported Commands

- `init <size>`  
  Initializes physical memory with the specified size.

- `malloc <size>`  
  Allocates a memory block of the given size using the currently selected allocation strategy.

- `free <id>`  
  Frees the memory block corresponding to the given allocation ID and performs block coalescing.

- `set first | best | worst`  
  Sets the memory allocation strategy:
  - `first` → First Fit
  - `best` → Best Fit
  - `worst` → Worst Fit

- `print`  
  Displays the current memory layout, showing allocated and free blocks with their address ranges.

- `stats`  
  Displays memory usage statistics and external fragmentation.

- `exit`  
  Terminates the simulator.

### Example CLI Session

init 1024
set first
malloc 100
malloc 200
free 1
print
stats
exit


---

## 11. Cache Statistics

Each cache level (L1 and L2) maintains the following statistics:

- Number of cache hits
- Number of cache misses
- Cache hit ratio

The cache hit ratio is calculated as:

Hit Ratio = hits / (hits + misses)


These statistics allow observation of cache effectiveness and comparison of access behavior across cache levels.


---

## 13. Conclusion

This project implements a minimal yet accurate simulation of key operating system memory management concepts, including:

- Dynamic memory allocation using multiple strategies
- External fragmentation handling
- Multilevel cache simulation with FIFO replacement
- Modular system design with driver-based integration

The simulator adheres to the required project specifications and provides a clear, extensible foundation for further enhancements.
