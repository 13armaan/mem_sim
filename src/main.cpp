#include <bits/stdc++.h>
#include "allocator/allocator.h"
#include "cache/cache.h"
using namespace std;
extern string curr_fit;

int main() {
    string cmd;
    cout<<"Welcome To Memory Simulator"<<endl;
    while (true) {
        cin >> cmd;

        if (cmd == "init") {
            int n; cin >> n;
            init_memory(n);
            cout << "Memory Initialized\n";
        }
        else if (cmd == "malloc") {
            int n; cin >> n;
            int addr = malloc_sim(n);
            if (addr == -1) cout << "Allocation unsuccessful\n";
            else {
                access_add(addr);
                cout << "Allocated id= " << addr << "\n";
            }
        }
        else if (cmd == "free") {
            int id; cin >> id;
            if (free_sim(id)) cout << "Block freed and merged\n";
            else cout << "Invalid id\n";
        }
        else if (cmd == "print") {
            print_memory();
        }
        else if (cmd == "stats") {
            show_stats();
        }
         else if (cmd == "cache_stats") {
    cout << "L1 Cache:\n";
    L1.print_stats();
    cout << "\nL2 Cache:\n";
    L2.print_stats();

}
else if (cmd == "set") {
    string type;
    cin >> type;

    if (type == "first" || type == "best" || type == "worst") {
        curr_fit = type;
        cout << "Allocation strategy set to " << type << "\n";
    } else {
        cout << "Invalid allocation strategy\n";
    }
}

        else if (cmd == "exit") {
            break;
        }
     

        else {
            cout << "Unknown command\n";
        }
    }
}
