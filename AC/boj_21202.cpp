#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
// #define DEBUG

using pii = std::pair<int, int>;

const int MX = 200'000;
int n, army[MX + 1];
bool visit[MX + 1];
std::vector<int> graph[MX + 1];

void input();
void solve();

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin.sync_with_stdio(0);

    input();
    solve();
}

void input() {
    int m, a, b;
    std::cin >> n >> m;
    while(m) {
        --m;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(m = n; m; --m) {
        std::cin >> army[n - m + 1];
    }
}

void solve() {
    std::priority_queue<pii> pq;
    int sz = 0;
    visit[1] = true;
    pq.push({-army[1], 1});

    while(!pq.empty()) {
        int node = pq.top().second,
        val = -pq.top().first;
        #ifdef DEBUG
        std::cout << node << ", " << val << "\n";
        _sleep(500);
        #endif
        pq.pop();
        if(node == 1 || val < sz) sz += val;
        else continue;
        for(int nxt : graph[node]) {
            if(visit[nxt]) continue;
            pq.push({-army[nxt], nxt});
            visit[nxt] = true;
        }
    }
    
    std::cout << sz << "\n";
}