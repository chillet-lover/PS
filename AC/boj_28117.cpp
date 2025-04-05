#include <iostream>
// #define DEBUG
using namespace std;

int len;
string str;
long long ans = 1;
long long fibo[30] = {1, 1, 2, };

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    for(int i = 3; i != 30; ++i) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }

    cin >> len >> str;

    int streak = 0;
    for(int i = 0, j = str.length() - 4; i <= j;) {
        string sub = str.substr(i, 4);
        #ifdef DEBUG
        cout << i << ", " << sub + "\n";
        #endif
        if(sub == "long") {
            ++streak;
            i += 4;
            continue;
        }
        ans *= fibo[streak];
        streak = 0;
        ++i;
    }
    ans *= fibo[streak];

    cout << ans;
}