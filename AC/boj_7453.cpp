#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

constexpr int SZ = 4'000;
int arr[4][SZ];
long long ans;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> arr[0][i] >> arr[1][i] >> arr[2][i] >> arr[3][i];
    }

    vector<int> sum_ab, sum_ac;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            sum_ab.push_back(arr[0][i] + arr[1][j]);
            sum_ac.push_back(arr[2][i] + arr[3][j]);
        }
    }
    sort(sum_ac.begin(), sum_ac.end());
    for(int ab : sum_ab) {
        // upper_bound와 lower_bound를 구해서 그 간격의 차이가 해당 값의 개수,
        // 그 개수만큼 ans에 더한다
        ans += upper_bound(sum_ac.begin(), sum_ac.end(), -ab) - lower_bound(sum_ac.begin(), sum_ac.end(), -ab);
    }

    cout << ans;
}