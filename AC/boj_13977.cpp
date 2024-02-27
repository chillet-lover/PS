#include <iostream>
using namespace std;
constexpr int MX = 4'000'000;
constexpr long long MOD = 1'000'000'007;
typedef long long ll;

int M;
ll ft[MX + 1]{1, 1};

ll pw(ll a, ll b) {
    if(b == 0) return 1;
    ll ret = pw(a, b >> 1);
    ret = ret * ret % MOD;
    if(b & 1) ret = ret * a % MOD;
    return ret;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    for(ll i = 2; i <= MX; ++i) {
        ft[i] = i * ft[i - 1] % MOD;    
    }
    cin >> M;
    while(M--) {
        ll N, K;
        cin >> N >> K;
        cout << ft[N] * pw(ft[K] * ft[N - K] % MOD, MOD - 2) % MOD << '\n';
    }
}
