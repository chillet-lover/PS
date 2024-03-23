#include <iostream>
#include <vector>
#include <stack>
#include <bitset>
// #define DEBUG

using namespace std;

constexpr int MX = 1'000;
vector<int> edges[MX * 2 + 1], trans[MX * 2 + 1];
vector<vector<int>> sccs;
stack<int> stk;
bitset<MX * 2 + 1> visit;

inline void to_index(int &vertex) {
    if(vertex < 0) vertex = -vertex +  MX;
}

inline int get_inv(const int &vertex) {
    return vertex > MX ? vertex - MX : vertex + MX;
}

void dfs(const int &vertex) {
    visit[vertex] =  true;
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
    int n, m;
    
    while(cin >> n >> m) {
        bool flag = true;
        edges[1].push_back(1001);
        trans[1001].push_back(1);
        while(m--) {
            int a, b, ra, rb;
            cin >> a >> b;
            to_index(a), to_index(b);
            ra = get_inv(a), rb = get_inv(b);
            edges[a].push_back(rb);
            edges[b].push_back(ra);
            trans[ra].push_back(b);
            trans[rb].push_back(a);
        }
        for(i = 1; i <= n; ++i) {
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
                cout << "scc group : " << sccs.size() << "\n";
                for(const int &vertex : scc) {
                    cout << vertex << " ";
                }
                cout << "\n";
                #endif
            }
        }
        for(const vector<int> &scc : sccs) {
            if(!flag) break;
            visit.reset();
            for(const int &vertex : scc) {
                visit[vertex] = true;
                if(visit[vertex] && visit[get_inv(vertex)]) {
                    flag = false;
                    break;
                }
            }
        }
        for(i = 1; i <= n; ++i) {
            edges[i].clear();
            edges[i + MX].clear();
            trans[i].clear();
            trans[i + MX].clear();
        }
        sccs.clear();
        visit.reset();
        cout << (flag ? "yes\n" : "no\n");
    }
}