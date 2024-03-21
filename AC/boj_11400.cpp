#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

constexpr int MX = 100'000;
int O, order[MX + 1];
vector<int> edge[MX + 1];
map<pair<int, int>, bool> ans;

int dfs(const int &node, const int parent) {
    int ret = order[node] = ++O;
    for(const int &child : edge[node]) {
        if(child == parent) continue;
        if(!order[child]) {
            int child_ret = dfs(child, node);
            ret = min(ret, child_ret);
            if(child_ret > order[node]) {
                pair<int, int> tmp = {node, child};
                if(tmp.first > tmp.second) swap(tmp.first, tmp.second);
                ans[tmp] = true;
            }
        }
        else {
            ret = min(ret, order[child]);
        }
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
        edge[A].push_back(B);
        edge[B].push_back(A);
    }

    for(i = 0; i < V; ++i) {
        if(!order[i]) dfs(i, 0);
    }

    cout << (V = ans.size());
    if(V) {
       for(auto it = ans.begin(); it != ans.end(); ++it) {
            const pair<int, int> &p = it -> first;
            cout << "\n" << p.first << " " << p.second;
       } 
    }
}