#include <iostream>
#include <functional>
// #define DEBUG

using namespace std;

constexpr int MX = 100'000;
int pos[MX + 1], sgt[(MX << 3) + MX];

int query(const int node, const int l, const int r, const int st, const int ed) {
    if(r < st || l > ed) return 0;
    if(st <= l && r <= ed) return sgt[node];
    int m = l + r >> 1;
    return query(node * 2, l, m, st, ed) + query(node * 2 + 1, m + 1, r, st, ed);
}

void update(const int node, const int l, const int r, const int &index, const int val) {
    if(index < l || index > r) return;
    if(l == r) {
        if(l == index) sgt[node] = val;
        return;
    }
    int m = l + r >> 1;
    update(node * 2, l, m, index, val);
    update(node * 2 + 1, m + 1, r, index, val);
    sgt[node] = sgt[node * 2] + sgt[node * 2 + 1];
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    register int i, j;
    int tc;
    cin >> tc;
    for(i = tc; i; --i) {
        int n, m, lim;
        cin >> n >> m;
        lim = n + m;
        for(j = 1; j <= n; ++j) {
            pos[j] = n - j + 1;
            update(1, 1, lim, j, 1);
        }
        for(j = 0; j < m; ++j) {
            int movie;
            cin >> movie;
            #ifdef DEBUG
            cout << "\nbefore query\n";
            for(int k = 1; k <= n; ++k) {
                cout << "movie : " << k << ", position : " << pos[k] << "\n";
                cout << "position sum : " << query(1, 1, lim, 1, pos[k]) << "\n";
            }
            #endif
            if(pos[movie] == n + j) {
                cout << "0 ";
                continue;
            }
            cout << n - query(1, 1, lim, 1, pos[movie]) << " ";
            update(1, 1, lim, pos[movie], 0);
            update(1, 1, lim, pos[movie] = n + j + 1, 1);
            #ifdef DEBUG
            cout << "\nafter query\n";
            for(int k = 1; k <= n; ++k) {
                cout << "movie : " << k << ", position : " << pos[k] << "\n";
                cout << "position sum : " << query(1, 1, lim, 1, pos[k]) << "\n";
            }
            #endif
        }
        cout << "\n";
        for(j = (lim << 2) + lim; j; --j) {
            sgt[j] = 0;
        }
    }
}