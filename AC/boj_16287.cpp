#include <iostream>
using namespace std;
constexpr int M = 5'000;

int w, n, a[M], l[400'001], r[400'001];

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    for(int i = 0; i <= 400'000; ++i) {
        l[i] = r[i] = -1;
    }
    cin >> w >> n;
    for(int i = 0; i < n; cin >> a[i++]);
    for(int i = n - 1; i > 0; --i) {
        for(int j = i - 1; j >= 0; --j) {
            int tw = a[i] + a[j];
            l[tw] = i, r[tw] = j;
        }
    }
    for(int i = n - 1; i > 0; --i) {
        for(int j = i - 1; j >= 0; --j) {
            int tw = a[i] + a[j],
            dif = w - tw;
            if(dif <= 0 || dif > 400'000 || l[dif] == -1) continue;
            if(i != l[dif] && i != r[dif] && j != l[dif] && j != r[dif]) {
                cout << "YES\n";
                return 0;
            }
        }
    }
    cout << "NO\n";
}