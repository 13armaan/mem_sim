#include<bits/stdc++.h>
#include "cache/cache.h"
using namespace std;


int cache_miss=0;


Cache:: Cache(int cs,int bs,int assoc){
    cache_size=cs;
    block_size=bs;
    associativity=assoc;

    int num_blocks=cache_size/block_size;
     num_sets=num_blocks/associativity;

    sets.resize(num_sets,vector<Cache_line> (associativity));

    for(int i=0;i<num_sets;i++){
        for(int j=0;j<associativity;j++){
            sets[i][j].valid=false;
            sets[i][j].tag=-1;
            sets[i][j].time=0;
        }
    }

    global_time=0;
    hits=0;
    misses=0;
}
int Cache::get_set_i(int address){
    int block_a=address/block_size;
    return block_a%num_sets;
    }
 int Cache::get_tag(int address){
        int block_a=address/block_size;
        return block_a/num_sets;
    }
 Cache L1(64,8,2);
    Cache L2(256,8,4);

void access_add(int add){
    if(L1.access(add)) return;
    if(L2.access(add)) {
        L1.insert(add);
    }
    else{
        cache_miss++;
    L2.insert(add);
    L1.insert(add);
}
}
bool Cache::access(int address){
     int ind=get_set_i(address);
    int taga=get_tag(address);
    global_time++;
   for(int i=0;i<associativity;i++){
    if(sets[ind][i].tag==taga && sets[ind][i].valid ){
        cout<<"hit"<<endl;
        hits++;
       /// sets[ind][i].time=global_time;  it can be toggled on for LRU 
        return true;
        }
      
   }
    cout<<"miss"<<endl;
    misses++;
    
    return false;
}
void Cache::insert(int address){
      global_time++;
        int ind=get_set_i(address);
         int taga=get_tag(address);
        for(int i=0;i<associativity;i++){
        if(!sets[ind][i].valid){
          sets[ind][i].tag=taga;
          sets[ind][i].valid=true;
          sets[ind][i].time=global_time;
          return;
        }  
    }
    int min_t=INT_MAX;
    for(int i=0;i<associativity;i++){
        min_t=min(min_t,sets[ind][i].time); 
    }
    for(int i=0;i<associativity;i++){
        if(sets[ind][i].time==min_t){
            sets[ind][i].tag=taga;
            sets[ind][i].time=global_time;
            sets[ind][i].valid=true;
             return;
        } 
    }
}
 void Cache::print_stats(){
        cout<<"Hits: "<<hits<<endl;
        cout<<"Misses: "<<misses<<endl;
        if(hits || misses)cout<<"Hit Ratio: "<<float(hits)/float(hits+misses)<<endl;
        else cout<<"Hit Ratio: "<<"not defined"<<endl;
        cout<<"Cache Miss Penalty: "<<cache_miss<<endl;
    }