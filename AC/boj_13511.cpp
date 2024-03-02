#include <iostream>
#include <vector>
#include <algorithm>
#define DBG 0
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
    for(int i = 1; i < LN; ++i) {
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
                if(DBG) cout << "sum : " << sum << '\n';
            }
            sum += dist[u][0] + dist[v][0];
            query1 :
                cout << sum << '\n';
        }
        else {
            int k, ans = u, su = u, sv = v, lca = 1, du, dv, duv;
            cin >> k;
            if(DBG) cout << "current query : " << op << ' ' << u << ' ' << v << ' ' << k << '\n';
            if(k == 1) goto query2; // u 노드에 해당하므로 바로 처리
            if(u == 1 || k == 1) goto lca_found; 
            // 두 노드의 높이를 맞춘다
            if(DBG) cout << "depth[u], depth[v] : " << depth[u] << ", " << depth[v] << '\n';
            if(depth[u] > depth[v]) {
                for(int i = LN - 1; i >= 0; --i) {
                    int p = parent[u][i];
                    if(depth[p] >= depth[v]) {
                        u = p;
                    }
                }
            } 
            else if(depth[v] > depth[u]) {
                for(int i = LN - 1; i >= 0; --i) {
                    int p = parent[v][i];
                    if(depth[p] >= depth[u]) {
                        v = p;
                    }
                }
            }
            if(u == v) {
                lca = u;
                goto lca_found;
            }
            // LCA를 구한다
            for(int i = LN - 1; i >= 0; --i) {
                int pu = parent[u][i], pv = parent[v][i];
                if(pu != pv) {
                    u = pu, v = pv;
                }
                lca = parent[u][0];
            }
            lca_found :
            if(DBG) cout << "lca : " << lca << '\n';
            // LCA를 포함한 u - v 경로에 속하는 노드 개수를 구한다
            du = depth[su] - depth[lca],
            dv = depth[sv] - depth[lca],
            duv = du + 1 + dv;
            if(DBG) {
                cout << "du : " << du << ", dv : " << dv << ", duv : " << duv << '\n' 
                << "k : " << k << '\n';
            }
            // k가 u, lca, v에 해당하는지, u와 lca 사이에 속하는지,
            // v와 lca 사이에 속하는지 구분하고 구한다
            if(k <= du) { // k는 u와 lca 사이에 속함
                if(DBG) cout << "case 1\n";
                --k;
                for(int i = LN - 1; i >= 0; --i) {
                   if(k >= 1 << i) {
                        k -= 1 << i;
                        su = parent[su][i];
                   } 
                }
                ans = su;
            }
            else if(k == 1 + du) { // k는 lca이다
                if(DBG) cout << "case 2\n";
                ans = lca;
            }
            else if(k == duv) { // k는 v다
                if(DBG) cout << "case 3\n";
                ans = sv;
            }
            else { // k는 lca와 v 사이에 속한다
                k = duv - k;
                if(DBG) cout << "case 4\n k : " << k << '\n';
                for(int i = LN - 1; i >= 0; --i) {
                    if(k >= 1 << i) {
                        k -= 1 << i;
                        sv = parent[sv][i];
                    }
                }
                ans = sv;
            }
            query2 :
                cout << ans << '\n';
        }
    }
}
