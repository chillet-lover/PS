#include <iostream>
#define MX 1'000
#define MOD 10'007
using namespace std;

int dp[MX][MX];

int solve(const string &str, int left_end, int right_end) {
    int &ret = dp[left_end][right_end];
    if(left_end > right_end) return ret = 0;
    if(left_end == right_end) return ret = 1;
    if(ret) return ret;
    if(str[left_end] == str[right_end])
        ret = 1 + solve(str, left_end + 1, right_end) + solve(str, left_end, right_end - 1);
    else
        ret = solve(str, left_end + 1, right_end) + solve(str, left_end, right_end - 1) - solve(str, left_end + 1, right_end - 1);
    ret = (ret + MOD) % MOD;
    return ret;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    string S;
    cin >> S;
    int len = S.length();

    cout << solve(S, 0, len - 1);
}