#include<bits/stdc++.h>
using namespace std;

struct Cache_line{
    bool valid;
    int tag;
    int time;
};
int cache_miss=0;
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

    int get_set_i(int address){
    int block_a=address/block_size;
    return block_a%num_sets;
    }
    int get_tag(int address){
        int block_a=address/block_size;
        return block_a/num_sets;
    }
  bool access(int add){
    int ind=get_set_i(add);
    int taga=get_tag(add);
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
    void insert(int add){
        global_time++;
        int ind=get_set_i(add);
         int taga=get_tag(add);
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
    void print_stats(){
        cout<<"Hits: "<<hits<<endl;
        cout<<"Misses: "<<misses<<endl;
        if(hits || misses)cout<<"Hit Ratio: "<<float(hits)/float(hits+misses)<<endl;
        else cout<<"Hit Ratio: "<<"not defined"<<endl;
        cout<<"Cache Miss Penalty: "<<cache_miss<<endl;
    }
};

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
int main(){

   
    cout << "Sets: " << L1.num_sets << endl;

    cout << "Addr 0  -> set " << L1.get_set_i(0)
         << " tag " << L1.get_tag(0) << endl;

    cout << "Addr 8  -> set " << L1.get_set_i(8)
         << " tag " << L1.get_tag(8) << endl;

    cout << "Addr 16 -> set " << L1.get_set_i(16)
         << " tag " << L1.get_tag(16) << endl;
}