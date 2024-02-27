#include <iostream>
// #define DEBUG
using namespace std;
typedef long long ll;

ll N, K;

// N개 원판의 이동횟수 -> 2 ^ N - 1, (1 << N) - 1
// N - 1개 원판의 이동횟수 -> 2 ^ (N - 1) - 1, (1 << (N - 1)) - 1
void hanoi(int st, int via, int to, ll lv, ll cnt) {
    ll required_move = (1LL << (lv - 1)) - 1;
    #ifdef DEBUG
    cout << "cur req : " << st << ' ' << via << ' ' << to << ' ' << lv << ' ' << cnt << '\n';
    cout << "required move : " << required_move << '\n';
    #endif
    if(cnt <= required_move) {
        hanoi(st, to, via, lv - 1, cnt);
    }
    else if(cnt == required_move + 1) {
        cout << st << ' ' << to << '\n';
    }
    else {
        hanoi(via, st, to, lv - 1, cnt - required_move - 1);
    }
    return;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> N >> K;
    hanoi(1, 2, 3, N, K);
}