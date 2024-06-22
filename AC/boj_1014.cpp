#include <iostream>
#include <vector>
#include <bitset>
#include <memory.h>

using namespace std;
using pii = pair<bitset<12>, int>;

constexpr int SZ = 10;
int tc, n, m, ans, cache[SZ + 1][(1 << SZ + 1) + 1];
string seat[SZ];
vector<pii> bits[SZ + 1];

void create_bit(const int row, const int col, bitset<12> bit) {
    if(col > m) {
        bits[row].push_back({bit, bit.count()});
        return;
    }
    create_bit(row, col + 1, bit);
    // 현재 좌석이 배치 가능한 좌석이고 바로 직전 좌석에 인원이 배치되지 않은 경우 배치가 확정
    if(seat[row - 1][col - 1] == '.' && !bit[col -  1]) {
        bit[col] = true;
        create_bit(row, col + 1, bit);
    }
}

bool compare_bit(const bitset<12> a, const bitset<12> b) {
    for(int i = 1; i <= m; ++i) {
        if(!a[i]) continue; // 현재 좌석에 배치된 학생이 없는 경우는 넘어감
        // 학생이 배치 되었고, 그 학생의 전방 대각선 방향에 학생이 배치되어 있는 경우는 현재의 배치가 불가능함
        if((b[i - 1] || b[i + 1])) return false;
    }
    return true;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    cin >> tc;
    bits[0].push_back({bitset<12>(0), 0});
    while(tc--) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            cin >> seat[i];
            create_bit(i + 1, 1, bitset<12>(0));
        }
        for(int row = 1; row <= n; ++row) {
            for(pii bit_pair : bits[row]) {
                bitset<12> bit = bit_pair.first;
                int cnt = bit.count(), bitval = (int) bit.to_ulong();
                cache[row][bitval] = cnt;
                for(pii pbit_pair : bits[row - 1]) { // 직전 열의 배치와 대조
                    bitset<12> &pbit = pbit_pair.first;
                    int pbitval = (int) pbit.to_ulong();
                    // 대조해서 문제가 없을 시에는 갱신한다
                    if(compare_bit(bit, pbit))
                        cache[row][bitval] = max(cache[row][bitval], cache[row - 1][pbitval] + cnt);

                }
                ans = ans > cache[row][bitval] ? ans : cache[row][bitval];
            }
        }
        cout << ans << "\n";
        ans = 0;
        for(int i = 1; i <= n; ++i)
            bits[i].clear();
        memset(cache, 0, sizeof(cache));
    }
}