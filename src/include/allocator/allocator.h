#ifndef ALLOCATOR_H
#define ALLOCATOR_H

struct Block;

void init_memory(int n);
int malloc_sim(int s);
bool free_sim(int id);
void print_memory();
void show_stats();

#endif
