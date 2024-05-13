#include <iostream>
#include <algorithm>
// #define DEBUG

using namespace std;
using ll = long long;

constexpr int MX = 100'000;
constexpr ll INF = 9'876'543'210;

ll dp[MX + 1 << 2];

void update(int node, int left, int right, int index, ll val) {
    if(index < left || index > right) return;
    if(left == right) {
        dp[node] = val;
        return;
    }
    int mid = left + right >> 1;
    update(node * 2, left, mid, index, val);
    update(node * 2 + 1, mid + 1, right, index, val);
    dp[node] = max(dp[node * 2], dp[node * 2 + 1]);
}

ll query(int node, int left, int right, int qs, int qe) {
    if(qe < left || qs > right) return -INF;
    if(qs <= left && right <= qe) return dp[node];
    int mid = left + right >> 1;
    return max(query(node * 2, left, mid, qs, qe),
            query(node * 2 + 1, mid + 1, right, qs, qe));
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int N, D;
    ll ans = -INF;
    cin >> N >> D;
    for(int i = 1; i <= N; ++i) {
        ll query_result;
        int ipt, min_left = max(0, i - D);
        cin >> ipt;
        query_result = query(1, 0, N, min_left, i - 1);
        #ifdef DEBUG
        cout << "i, query_result : " << i << ", " << query_result << "\n";
        #endif
        if(query_result < 0) query_result = 0;
        update(1, 0, N, i, query_result + ipt);
        #ifdef DEBUG
        cout << "i, current_answer : " << i << ", " << query_result + ipt << "\n";
        #endif
        ans = max(ans, query_result + ipt);
    }
    cout << ans;
}