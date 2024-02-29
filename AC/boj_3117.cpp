#include <iostream>
using namespace std;
constexpr int MX = 100'000;
constexpr int LN = 30;

int n[MX + 1], dp[LN][MX + 1];

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int N, K, M;
    cin >> N >> K >> M;
    for(int i = 1; i <= N; cin >> n[i++]);
    for(int i = 1; i <= K; cin >> dp[0][i++]);
    for(int i = 1; i < LN; ++i) {
        for(int j = 1; j <= K; ++j) {
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }
    for(int std = 1; std <= N; ++std) {
        int cnt = M - 1, num = n[std];
        for(int ln = LN - 1; cnt && ln >= 0; --ln) {
            int cur = 1 << ln;
            if(cnt >= cur) {
                cnt -= cur;
                num = dp[ln][num];
            }
        }
        cout << num << ' ';
    }
}