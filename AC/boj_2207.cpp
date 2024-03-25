#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

constexpr int MX = 10'000;
int order[MX * 2 + 1];
vector<int> stack, graph[MX * 2 + 1], trans[MX * 2 + 1];
bitset<MX * 2 + 1> visit;

void dfs(const int &cur) {
    visit[cur] = true;
    for(const int &nxt : graph[cur]) {
        if(visit[nxt]) continue;
        dfs(nxt);
    }
    stack.push_back(cur);
}

void make_scc(const int &cur, const int &num) {
    visit[cur] = true;
    order[cur] = num;
    for(const int &nxt : trans[cur]) {
        if(visit[nxt]) continue;
        make_scc(nxt, num);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    register int i;
    int N, M;
    cin >> N >> M;
    for(i = N; i; --i) {
        int x, y, nx, ny;
        cin >> x >> y;
        x = x < 0 ? abs(x) + MX : x,
        y = y < 0 ? abs(y) + MX : y,
        nx = x > MX ? x - MX : x + MX,
        ny = y > MX ? y - MX : y + MX;
        graph[x].push_back(ny),
        graph[y].push_back(nx),
        trans[nx].push_back(y),
        trans[ny].push_back(x);
    }
    for(i = 1; i <= M; ++i) {
        int ni = i + MX;
        if(!visit[i]) dfs(i);
        if(!visit[ni]) dfs(ni);
    }
    visit.reset();
    int num = 1;
    while(stack.size()) {
        const int top = stack.back();
        stack.pop_back();
        if(visit[top]) continue;
        make_scc(top, num);
        ++num; 
    }
    for(i = 1; i <= M; ++i) {
        if(order[i] == order[i + MX]) {
            cout << "OTL\n";
            return 0;
        }
    }
    cout << "^_^\n";
}
