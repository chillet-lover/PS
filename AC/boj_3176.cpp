#include <iostream>
#include <vector>
#include <algorithm>
#define ed first
#define we second
#define DBG 0
constexpr int INF = 1'000'001;
constexpr int MX = 100'000;
constexpr int LN = 17;
using namespace std;

typedef pair<int, int> pii;
typedef struct node {
    int parent = 0, mx = 0, mn = INF; 
} node;

int depth[MX + 1]{-1};
node dp[MX + 1][LN];
vector<pii> grp[MX + 1];

void make_tree(int cur, int prv, int pwe) {
    depth[cur] = depth[prv] + 1,
    dp[cur][0].parent = prv,
    dp[cur][0].mx = pwe ? pwe : 0,
    dp[cur][0].mn = pwe ? pwe : INF;
    for(int i = 1; i < LN; ++i) {
        node &cn = dp[cur][i], &pn = dp[cur][i - 1],
        gpn = dp[pn.parent][i - 1];
        cn.parent = gpn.parent;
        cn.mx = max(cn.mx, max(pn.mx, gpn.mx));
        cn.mn = min(cn.mn, min(pn.mn, gpn.mn));
        if(DBG) {
            cout << "cmx, cmn : " << cn.mx << ", " << cn.mn << '\n';
        }
    }
    for(const pii &p : grp[cur]) {
        int nxt = p.ed, nwe = p.we;
        if(nxt == prv) continue;
        make_tree(nxt, cur, nwe);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i = 1; i < N; ++i) {
        int A, B, C;
        cin >> A >> B >> C;
        grp[A].push_back({B, C});
        grp[B].push_back({A, C});
    }
    make_tree(1, 0, 0);

    int K;
    cin >> K;
    while(K--) {
        int D, E, mx = 0, mn = INF;
        cin >> D >> E;
        if(depth[E] < depth[D]) swap(D, E);
        for(int i = LN - 1; i >= 0; --i) {
            int par = dp[E][i].parent;
            if(depth[par] >= depth[D]) {
                mx = max(mx, dp[E][i].mx),
                mn = min(mn, dp[E][i].mn),
                E = par;
                if(DBG) {
                    cout << "mx, mn : " << mx << ", " << mn << '\n';
                }
            }
        }
        if(D == E) goto print_ans;
        for(int i = LN - 1; i >= 0; --i) {
            node &pd = dp[D][i], &pe = dp[E][i];
            if(pd.parent != pe.parent) {
                mx = max(mx, max(pd.mx, pe.mx)),
                mn = min(mn, min(pd.mn, pe.mn)),
                D = pd.parent, E = pe.parent;
            }
            mx = max(mx, max(dp[D][0].mx, dp[E][0].mx));
            mn = min(mn, min(dp[D][0].mn, dp[E][0].mn));
            if(DBG) {
                cout << "mx, mn : " << mx << ", " << mn << '\n';
            }
        }
        print_ans :
        cout << mn << ' ' << mx << '\n';
    }
}
