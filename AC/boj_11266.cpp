#include <iostream>
#include <vector>
#include <algorithm>
// #define DEBUG

using namespace std;

constexpr int MX = 10'000;
int T, order[MX];
vector<int> ap, edge[MX];

inline int mn(const int &a, const int &b) {
    return a < b ? a : b;
}

int dfs(const int &node, const bool is_root) {
    int ret = order[node] = ++T, child_count = 0;
    bool check = false;
    for(const int &next : edge[node]) {
        if(order[next]) {
            ret = mn(ret, order[next]);
        }
        else {
            int child_ret = dfs(next, false);
            ++child_count;
            ret = mn(ret, child_ret);
            if(!check && !is_root && child_ret >= order[node]) {
                check = true;
                #ifdef DEBUG
                cout << node + 1 << " is articular point\n"; 
                #endif
                ap.push_back(node + 1);
            }
        }
    }
    if(is_root && child_count > 1) {
        #ifdef DEBUG
        cout << node + 1 << " is root node and articular point\n"; 
        #endif
        ap.push_back(node + 1);
    }
    return ret;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    register int i;
    int V;
    
    cin >> V >> i;
    for(int A, B; i; --i) {
        cin >> A >> B;
        edge[--A].push_back(--B);
        edge[B].push_back(A);
    }

    for(i = 0; i < V; ++i) {
        if(!order[i]) dfs(i, true);
    }

    sort(ap.begin(), ap.end());
    cout << (V = ap.size());
    if(V) {
        cout << "\n";
        for(i = 0; i < V; ++i) {
            cout << ap[i] << " ";
        }
    }
}