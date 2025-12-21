#ifndef CACHE_H
#define CACHE_H

#include <vector>

struct Cache_line {
    bool valid;
    int tag;
    int time;
};

class Cache {
public:
    Cache(int cs, int bs, int assoc);

    bool access(int address);
    void insert(int address);
    void print_stats();

private:
    int cache_size;
    int block_size;
    int associativity;

    int num_sets;
    int global_time;

    int hits;
    int misses;

    std::vector<std::vector<Cache_line>> sets;

    int get_set_i(int address);
    int get_tag(int address);
};

void access_add(int address);

#endif
