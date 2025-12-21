#include <bits/stdc++.h>
#include "allocator/allocator.h"
#include "cache/cache.h"
using namespace std;

int main() {
    string cmd;

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
        else if (cmd == "exit") {
            break;
        }
        else {
            cout << "Unknown command\n";
        }
    }
}
