#include<bits/stdc++.h>
#include "allocator/allocator.h"
using namespace std;

string curr_fit="first";
int total_mem=0;

struct Block {
    int start;
    int size;
    int id;
    bool free;
    Block* next;
};
Block* head=nullptr;
int gid=1;
void print_memory(){
    
    if(!head){
    cout<<"Memory not initialized\n";
    return;
}

    Block* curr=head;
    while(curr){
    cout<<"["<<curr->start<<","<<curr->start+curr->size-1<<"] ";
    cout<<(curr->free? "FREE":"USED");
    if(!curr->free) cout<<"id= "<<curr->id;
    cout<<endl;
    curr=curr->next;
}
}
void init_memory(int n){
    total_mem=n;
   head=new Block{0,n,-1,true,nullptr};
}
void show_stats(){
     if(!head){
    cout<<"Memory not initialized\n";
    return;
     }

    Block* curr=head;
    int used=0,free=0,lar=0;
    while(curr){
        if(curr->free==true){
           
            free+=curr->size;
            lar=max(lar,curr->size);
        }
        else if(curr->free==false){
            
            used+=curr->size;
        }
        curr=curr->next;
    }
    float f=(float(lar)/float(free));
    cout<<"Total memory : "<<total_mem<<endl;
    cout<<"used memory : "<<used<<endl;
    cout<<"External Fragmentation : "<<(1-f)*100<<"%"<<endl;
    
    
}
int malloc_sim(int s){
    Block* curr=head;
    if(curr_fit=="first"){
    curr=head;
    while(curr){
        if(curr->free && curr->size>=s){
        if(curr->size>s) {
            Block* temp=new Block;
            temp->start=curr->start+s;
            temp->size=curr->size-s;
            temp->free=true;
            temp->next=curr->next;
            temp->id=-1;
            curr->next=temp;
            curr->size=s;
        }
            curr->free=false;
            curr->id=gid++;
            return curr->id;
        }
        else curr=curr->next;
   
    }
    return -1;
    }
    else if(curr_fit=="best"){
        curr=head;
        Block* best=nullptr;
        while(curr){
        if(curr->free && curr->size>=s){
            if(best==nullptr) best=curr;
            else{
                if(best->size>curr->size) best=curr;
            }
        }
        curr=curr->next;
        }
       if(best!=nullptr){
        if(best->size>s){
            Block* temp=new Block;
            temp->start=best->start+s;
            temp->size=best->size-s;
            temp->free=true;
            temp->next=best->next;
            temp->id=-1;
            best->next=temp;
            best->size=s;
        }
            best->free=false;
            best->id=gid++;
            return best->id;
       }
       
   
    
    return -1;
    }
    else if(curr_fit=="worst"){
        curr=head;
        Block* worst=nullptr;
        while(curr){
        if(curr->free && curr->size>=s){
            if(worst==nullptr) worst=curr;
            else{
                if(worst->size<curr->size) worst=curr;
            }
        }
        curr=curr->next;
        }
       if(worst!=nullptr){
        if(worst->size>s){
            Block* temp=new Block;
            temp->start=worst->start+s;
            temp->size=worst->size-s;
            temp->free=true;
            temp->next=worst->next;
            temp->id=-1;
            worst->next=temp;
            worst->size=s;
        }
            worst->free=false;
            worst->id=gid++;
            return worst->id;
       }
       
   
    
    return -1;
    }
}
void coalesce(){
    Block* curr=head;
    while(curr){
        if(curr->free){
            if(curr->next && curr->next->free){
                
                curr->size+=curr->next->size;
                curr->next=curr->next->next;
                continue;
            }
        }
        curr=curr->next;
    }
}
bool free_sim(int fid){
    Block* curr=head;
    while(curr){
        if(curr->id==fid){
            curr->id=-1;
            curr->free=true;
            coalesce();
            return true;
        }
        curr=curr->next;
    }
    cout<<-1<<endl;
    return false;

}
