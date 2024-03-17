#include <iostream>
#include <vector>
#include <stack>
#include <bitset>
#define MX 100'000
// #define DEBUG
using namespace std;

vector<int> grp[MX];
bitset<MX> chk;
stack<int> stk;

void dfs(const int &node, const bool flag) {
    chk[node] = true;
    for(const int &next : grp[node]) {
        if(chk[next]) continue;
        dfs(next, flag);
    }
    if(flag) {
        stk.push(node);
        #ifdef DEBUG
        cout << "Top of Stack : " << node << "\n";
        #endif
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    int TC;
    register int i;
    cin >> TC;
    while(TC--) {
        int N, M, ans = 0;
        cin >> N >> M;
        for(i = M; i; --i) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            grp[x].push_back(y);
        }
        #ifdef DEBUG
        cout << "---------------------------\nGraph Status\n";
        for(i = 0; i < N; ++i) {
            cout << i + 1 << " : ";
            for(const int &node : grp[i]) {
                cout << node + 1 << " ";
            }
            cout << "\n";
        }
        cout << "---------------------------\n";
        #endif

        for(i = 0; i < N; ++i) {
            if(!chk[i]) dfs(i, true);
        }
        chk.reset();

        while(stk.size()) {
            const int S = stk.top();
            stk.pop();
            #ifdef DEBUG
            cout << "Top of Stack : " << S << "\n";
            #endif
            if(!chk[S]) {
                ++ans;
                dfs(S, false);
            }
        }

        cout << ans << "\n";
        for(i = 0; i < N; ++i) {
            grp[i].clear();
        }
        chk.reset();    
    }
}