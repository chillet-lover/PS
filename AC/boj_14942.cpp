#include <iostream>
#include <vector>
#define ed first
#define we second
#define swap(a, b) {int tmp = a; a = b, b = tmp;}
constexpr int MX = 100'000;
constexpr int LN = 17;
using namespace std;
typedef pair<int, int> pii;

int energy[MX + 1], depth[MX + 1]{-1}, parent[MX + 1][LN];
long long dist[MX + 1][LN];
vector<pii> grp[MX + 1];

void make_tree(int cur, int prv, int pwe) {
    depth[cur] = depth[cur] + 1,
    parent[cur][0] = prv,
    dist[cur][0] = pwe;
    for(int i = 1; i < LN; ++i) {
        int m = parent[cur][i - 1];
        parent[cur][i] = parent[m][i - 1],
        dist[cur][i] = dist[cur][i - 1] + dist[m][i - 1];
    }
    for(const pii &p : grp[cur]) {
        int nxt = p.ed, nwe = p.we;
        if(nxt == prv)  continue;
        make_tree(nxt, cur, nwe);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; cin >> energy[i++]);
    for(int i = 1; i < n; ++i) {
        int st, ed, we;
        cin >> st >> ed >> we;
        grp[st].push_back({ed, we});
        grp[ed].push_back({st, we});
    }
    make_tree(1, 0, 0);
    cout << "1\n";
    for(int i = 2; i <= n; ++i) {
        int pos = i;
        long long eg = energy[i];
        for(int i = LN - 1; i >= 0; --i) {
            if(eg >= dist[pos][i]) {
                eg -= dist[pos][i];
                pos = parent[pos][i];
            }
        }
        cout << (pos ? pos : 1) << '\n';
    }
}