#include <iostream>
#include <vector>
#define ed first
#define we second
#define swap(a, b) {int tmp = a; a = b, b = tmp;}
constexpr int MX = 40'000;
constexpr int LN = 16;
using namespace std;
typedef pair<int, int> pii;

int depth[MX + 1]{-1,}, parent[MX + 1][LN];
long long dist[MX + 1][LN];
vector<pii> grp[MX + 1];

void make_tree(int cur, int prv, int pdt) {
    depth[cur] = depth[prv] + 1,
    dist[cur][0] = pdt,
    parent[cur][0] = prv;
    for(int i = 1; i < LN; ++i) {
        int m = parent[cur][i - 1];
        dist[cur][i] = dist[cur][i - 1] + dist[m][i - 1];
        parent[cur][i] = parent[m][i - 1];
    }
    for(const pii &p : grp[cur]) {
        int nxt = p.ed, ndt = p.we;
        if(nxt == prv) continue;
        make_tree(nxt, cur, ndt);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i = 1; i < N; ++i) {
        int p1, p2, dist;
        cin >> p1 >> p2 >> dist;
        grp[p1].push_back({p2, dist});
        grp[p2].push_back({p1, dist});
    }
    make_tree(1, 0, 0);
    int M;
    cin >> M;
    while(M--) {
        int p1, p2;
        long long ans = 0;
        cin >> p1 >> p2;
        if(depth[p2] < depth[p1]) swap(p1, p2);
        for(int i = LN - 1; i >= 0; --i) {
            int par = parent[p2][i];
            if(depth[par] >= depth[p1]) {
                ans += dist[p2][i];
                p2 = par;
            }
        }
        if(p1 == p2) goto print_ans;
        for(int i = LN - 1; i >= 0; --i) {
            if(parent[p1][i] != parent[p2][i]) {
                ans += dist[p1][i] + dist[p2][i],
                p1 = parent[p1][i],
                p2 = parent[p2][i];
            }
        }
        ans += dist[p1][0] + dist[p2][0];
        print_ans :
        cout << ans << '\n';
    }
}