#include <iostream>
#include <vector>
#include <algorithm>
#define ed first
#define we second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
constexpr int MX = 100'000;
constexpr int LN = 17;

int depth[MX + 1]{-1}, parent[MX + 1][LN];
ll dist[MX + 1][LN];
vector<pii> grp[MX + 1];

void tree(int cur, int prv, int pwe) {
    depth[cur] = depth[prv] + 1,
    parent[cur][0] = prv,
    dist[cur][0] = pwe;
    for(int i = 1; i < LN) {
        int m = parent[cur][i - 1];
        parent[cur][i] = parent[m][i - 1];
        dist[cur][i] = dist[cur][i - 1] + dist[m][i - 1];
    }
    for(const pii &p : grp[cur]) {
        int nxt = p.ed, nwe = p.we;
        if(nxt == prv) continue;
        tree(nxt, cur, nwe);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i = 1; i < N; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        grp[u].push_back({v, w});
        grp[v].push_back({u, w});
    }
    tree(1, 0, 0);
    int M;
    cin >> M;
    while(M--) {
        int op, u, v;
        cin >> op >> u >> v;
        if(op & 1) {
            ll sum = 0;
            if(u == v) goto query1;
            if(depth[u] > depth[v]) swap(u, v);
            for(int i = LN - 1; i >= 0; --i) {
                int nv = parent[v][i];
                if(depth[nv] >= depth[u]) {
                    sum += dist[v][i];
                    v = nv;
                }
            }
            if(u == v) goto query1;
            for(int i = LN - 1; i >= 0; --i) {
                int pu = parent[u][i],
                pv = parent[v][i];
                if(pu != pv) {
                    sum += dist[u][i] + dist[v][i];
                    u = pu, v = pv;
                }
                sum += dist[u][0] + dist[v][0];
            }
            query1 :
                cout << sum << '\n';
        }
        else {
            int k, ans = u;
            cin >> k;
            --k;
            if(!k) goto query2;
            for(int i = LN - 1; k && i >= 0; --i) {
                if(k >= 1 << i) {
                    ans = 
                }
            }
            query2 :
                cout << ans << '\n';
        }
    }
}
