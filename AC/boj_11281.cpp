#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <bitset>
// #define DEBUG

using namespace std;

constexpr int MX = 10'000;
int ans[MX + 1];
vector<int> edges[MX * 2 + 1], trans[MX * 2 + 1];
vector<vector<int>> sccs;
stack<int> stk;
bitset<MX * 2 + 1> visit;

inline void normalize(int &vertex) {
    if(vertex < 0) vertex = abs(vertex) + MX;  
}

inline int get_not(const int &vertex) {
    return vertex > MX ? vertex - MX : vertex + MX;
}

inline void update_ans(const int &vertex) {
    const int index = vertex > MX ? vertex - MX : vertex;
    ans[index] = vertex > MX ? 1 : 0;
}

void dfs(const int &vertex) {
    visit[vertex] = true;
    for(const int &next : edges[vertex]) {
        if(visit[next]) continue;
        dfs(next);
    }
    stk.push(vertex);
}

void make_scc(const int &vertex, vector<int> &scc) {
    visit[vertex] = true;
    scc.push_back(vertex);
    for(const int &next : trans[vertex]) {
        if(visit[next]) continue;
        make_scc(next, scc);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    register int i;
    int N, M;

    cin >> N >> M;
    for(i = M; i; --i) {
        int xi, xj, nxi, nxj;
        cin >> xi >> xj;
        normalize(xi), normalize(xj);
        nxi = get_not(xi), nxj = get_not(xj);
        edges[xi].push_back(nxj);
        edges[xj].push_back(nxi);
        trans[nxi].push_back(xj);
        trans[nxj].push_back(xi);
    }

    for(i = 1; i <= N; ++i) {
        if(!visit[i]) dfs(i);
        if(!visit[i + MX]) dfs(i + MX);
    }
    visit.reset();
    while(stk.size()) {
        const int top = stk.top();
        stk.pop();
        if(!visit[top]) {
            vector<int> scc;
            make_scc(top, scc);
            sccs.push_back(scc);
            #ifdef DEBUG
                cout << "scc group : " <<  sccs.size() << "\n";
                for(const int &vertex : scc) {
                    cout << vertex << " ";
                }
                cout << "\n";
            #endif
        }
    }
    for(const vector<int> &scc : sccs) {
        visit.reset();
        for(const int &vertex : scc) {
            visit[vertex] = true;
            if(visit[vertex] && visit[get_not(vertex)]) {
                cout << "0\n";
                return 0;
            }
            update_ans(vertex);
        }
    }
    cout << "1\n";
    for(i = 1; i <= N; ++i) {
        cout << ans[i] << " ";
    }
}