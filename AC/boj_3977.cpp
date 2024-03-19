#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>
#define MX 100'000
#define DEBUG

using namespace std;

vector<int> grp[MX], rev[MX], stk, scc;
bitset<MX> chk;

void dfs(const int &node, const bool push_stack) {
    vector<int> &edges = push_stack ? grp[node] : rev[node],
                &results = push_stack ? stk : scc; 
    chk[node] = true;
    for(const int &next : edges) {
        if(chk[next]) continue;
        dfs(next, push_stack);
    }
    results.push_back(node);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    int TC;
    register int i;
    cin >> TC;
    while(TC--) {
        int N, M;
        cin >> N >> M;
        while(M--) {
            int A, B;
            cin >> A >> B;
            grp[A].push_back(B);
            rev[B].push_back(A);
        }

        for(i = 0; i < N; ++i) {
            if(!chk[i]) dfs(i, true);
        }
        chk.reset();

        const int top = stk.back();
        stk.pop_back();
        vector<int> tmp;
        [&] (vector<int> &result, const int &node) {
            queue<int> q;
            chk[node] = true;
            q.push(node);
            while(q.size()) {
                const int cur = q.front();
                q.pop();
                result.push_back(cur);
                for(const int &next : grp[cur]) {
                    if(chk[next]) continue;
                    chk[next] = true;
                    q.push(next);
                }
            }
            chk.reset();
        }(tmp, top);

        if(tmp.size() == N) {
            dfs(top, false);
            sort(scc.begin(), scc.end());
            for(const int &num : scc) {
                cout << num << "\n";
            }
            cout << "\n";
        }
        else {
            cout << "Confused\n\n";
        }

        for(i = 0; i < N; grp[i].clear(), rev[i].clear(), ++i);
        stk.clear(), scc.clear();
        chk.reset();
    }
}