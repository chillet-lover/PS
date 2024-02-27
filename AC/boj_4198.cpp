#include <iostream>
using namespace std;
constexpr int MX = 2'000;

int N, n[MX], lis[MX], lds[MX], mx;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> N;
    for(int i = 0; i < N; lis[i] = lds[i] = 1, cin >> n[i++]);
    for(int i = N - 1; i >= 0; --i) {
        for(int j = i + 1; j < N; ++j) {
            if(n[j] > n[i])
                lis[i] = lis[i] > lis[j] + 1 ? lis[i] : lis[j] + 1; 
            if(n[j] < n[i])
                lds[i] = lds[i] > lds[j] + 1 ? lds[i] : lds[j] + 1;
        }
    }
    for(int i = 0, tmp; i < N; i++) {
        tmp = lis[i] + lds[i] - 1;
        mx = mx > tmp ? mx : tmp;
    }
    cout << mx;
}