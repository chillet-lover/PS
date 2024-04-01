#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#define x first
#define y second

using namespace std;
using ll = long long;
using pii = pair<int, int>;

constexpr int MX = 200'000;
constexpr int MOD = 1'000'000'007;
int xval[MX], sgt[MX * 4 + 1];
map<int, vector<int>> m;
unordered_map<int, int> um;

void update(int node, int l, int r, int idx) {
    if(idx < l || idx > r) return;
    if(l == r) {
        ++sgt[node];
        return;
    }
    int m = l + r >> 1;
    update(node * 2, l, m, idx),
    update(node * 2 + 1, m + 1, r, idx);
    sgt[node] = sgt[node * 2] + sgt[node * 2 + 1];
}

ll query(int node, int l, int r, int s, int e) {
    if(e < l || s > r) return 0;
    if(s <= l && r <= e) return sgt[node];
    int m = l + r >> 1;
    return query(node * 2, l, m, s, e) + query(node * 2 + 1, m + 1, r, s, e);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    register int i;
    int N, count = 0;
    ll ans = 0;
    cin >> N;
    for(i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        m[-y].push_back(x);
        xval[i] = x;
    }
    sort(xval, xval + N);
    for(i = 0; i < N; ++i) {
        if(!um[xval[i]]) {
            um[xval[i]] = ++count;
        }
    }
    for(const pair<int, vector<int>> &cpv : m) {
        for(const int &cur : cpv.second) {
            ans += query(1, 1, count, 1, um[cur] - 1) * query(1, 1, count, um[cur] + 1, count) % MOD;
            ans %= MOD;
        }
        for(const int &cur : cpv.second) {
            update(1, 1, count, um[cur]);
        }
    }
    cout << ans << "\n";
}
