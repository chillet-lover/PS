#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

constexpr int MX = 1'000;
int order[MX * 2 + 1];
vector<int> stack, graph[MX * 2 + 1], trans[MX * 2 + 1];
bitset<MX * 2 + 1> visit;

void dfs(const int &cur) {
    visit[cur] = true;
    for(const int &nxt : graph[cur]) {
        if(visit[nxt]) continue;
        dfs(nxt);
    }
    graph[cur].clear();
    stack.push_back(cur);
}

void make_scc(const int &cur, const int &num) {
    visit[cur] = true;
    order[cur] = num;
    for(const int &nxt : trans[cur]) {
        if(visit[nxt]) continue;
        make_scc(nxt, num);
    }
    trans[cur].clear();
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    register int i;
    int N, M;
    while(cin >> N >> M) {
        int num = 0;
        for(i = M; i; --i) {
            int A, B, NA, NB;
            cin >> A >> B;
            A = A < 0 ? abs(A) + MX : A,
            B = B < 0 ? abs(B) + MX : B,
            NA = A > MX ? A - MX : A + MX,
            NB = B > MX ? B - MX : B + MX;
            graph[A].push_back(NB),
            graph[B].push_back(NA),
            trans[NA].push_back(B),
            trans[NB].push_back(A);
        }
        for(i = 1; i <= N; ++i) {
            int ni = i + MX;
            if(!visit[i]) dfs(i);
            if(!visit[ni]) dfs(ni);
        }
        visit.reset();
        while(stack.size()) {
            const int top = stack.back();
            stack.pop_back();
            if(visit[top]) continue;
            make_scc(top, ++num);
        }
        visit.reset();
        for(i = 1; i <= N; ++i) {
            if(order[i] == order[i + MX]) {
                cout <<  "0\n";
                goto END;
            }
        }
        cout << "1\n";
        END : ;
    }
}