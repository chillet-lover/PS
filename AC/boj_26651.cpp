// 팬램그
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MX = 100'000;
constexpr int MOD = 30'000;

int X, mxDiv = 1;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> X;
    for(int i = 2; i * i <= X; ++i) {
        if(X % i) continue;
        mxDiv = i;
    }
    if(mxDiv + X / mxDiv + 24 > MX) {
        cout << string(MOD, 'A') + "BCDEFGHIJKLMNOPQRSTUVWXY" + string(X / MOD, 'Z');
        X %= MOD;
        cout << string(X, 'A') + "BCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    else {
        cout << string(X / mxDiv, 'A') + "BCDEFGHIJKLMNOPQRSTUVWXY" + string(mxDiv, 'Z');
    }
}