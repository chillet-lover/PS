#include <iostream>
using namespace std;
constexpr int M = 200'000;
constexpr int LN = 19;

int m, dp[LN][M + 1];

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> m;
    for(int i = 1; i <= m; cin >> dp[0][i++]);
    for(int i = 1; i < LN; ++i) {
        for(int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }
    int Q;
    cin >> Q;
    while(Q--) {
        int n, x;
        cin >> n >> x;
        for(int p = LN - 1; n && p >= 0; --p) {
            if(n >= 1 << p) {
                n -= 1 << p;
                x = dp[p][x];
            }
        }
        cout << x << '\n';
    }
}