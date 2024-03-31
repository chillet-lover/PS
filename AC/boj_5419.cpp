#include <iostream>
#include <algorithm>
#include <unordered_map>
#define MX 75'000
#define x first
#define y second
#define DEBUG

using namespace std;
using ll = long long;
using pii = pair<int, int>;

int val[MX], sgt[MX * 4 + 1];
pii arr[MX];
unordered_map<int, int> um;

void update(int node, int l, int r, int index) {
    if(l > index || index > r) return;
    if(l == r) {
        ++sgt[node];
        return;
    }
    int m = l + r >> 1;
    update(node * 2, l, m, index);
    update(node * 2 + 1, m + 1, r, index);
    sgt[node] = sgt[node * 2] + sgt[node * 2 + 1];
}

int query(int node, int l, int r, int st, int ed) {
    if(ed < l || st > r) return 0;
    if(st <= l && r <= ed) return sgt[node];
    int m = l + r >> 1;
    return query(node * 2, l, m, st, ed) +
    query(node * 2 + 1, m + 1, r, st, ed);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    register int i;
    int TC;
    cin >> TC;
    while(TC--) {
        int N, idx = 0;
        ll ans = 0;
        cin >> N;
        for(i = 0; i < N; ++i) {
            cin >> arr[i].x >> arr[i].y;
            val[i] = arr[i].y;
        }
        sort(val, val + N);
        sort(arr, arr + N, [](const pii &a, const pii &b) {
            if(a.x == b.x) return a.y > b.y;
            return a.x < b.x;
        });
        for(i = 0; i < N; ++i) {
            if(!um[val[i]]) um[val[i]] = ++idx;
        }
        for(i = 0; i < N; ++i) {
            const int &pos = um[arr[i].y];
            ans += query(1, 1, N, pos, N);
            update(1, 1, N, pos);
        }
        cout << ans << "\n";
        for(i = N * 4; i >= 0; --i) {
            sgt[i] = 0;
        }
        um.clear();
    }
}