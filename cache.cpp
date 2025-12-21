#include<bits/stdc++.h>
using namespace std;

struct Cache_line{
    bool valid;
    int tag;
    int time;
};

class Cache{
    public:
    int cache_size;
    int block_size;
    int associativity;

    int num_sets;
    int global_time;

    int hits;
    int misses;

    vector<vector<Cache_line>> sets;

    Cache(int cs,int bs,int assoc);

};
int main(){

}