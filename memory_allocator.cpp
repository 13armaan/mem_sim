#include<bits/stdc++.h>
using namespace std;

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
   head=new Block{0,n,-1,true,nullptr};
}
int malloc_sim(int s){
    Block* curr=head;
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
            return true;
        }
        curr=curr->next;
    }
    cout<<-1<<endl;
    return false;

}
int main(){
    init_memory(100);
    print_memory();

    int a = malloc_sim(40);
    cout << "allocated id = " << a << endl;
    print_memory();

    int b = malloc_sim(30);
    cout << "allocated id = " << b << endl;
    print_memory();
}