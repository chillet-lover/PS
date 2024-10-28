#include <iostream>
#include <set>
#define DEBUG

const int MX = 14;
int num_barbell, num_plate, weight_barbell[MX], weight_plate[MX], sums[1 << 14];
std::set<int> answer;

void dfs();
void input();
void solve();

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin.sync_with_stdio(0);

    input();
    solve();
}

void input() {
    std::cin >> num_barbell >> num_plate;
    for(int i = 0; i != num_barbell; ++i) {
        std::cin >> weight_barbell[i];
    }
    for(int i = 0; i != num_plate; ++i) {
        std::cin >> weight_plate[i];
    }
}

void dfs(int cnt, int bit, int sum) {
    if(cnt >= num_plate) {
        sums[bit] = sum;
        return;
    }
    dfs(cnt + 1, bit, sum);
    dfs(cnt + 1, bit | (1 << cnt), sum + weight_plate[cnt]);
}

void solve() {
    const int BIT_MAX = 1 << num_plate;
    dfs(0, 0, 0);
    for(int i = 0; i != num_barbell; ++i) {
        answer.insert(weight_barbell[i]);
        for(int j = 0; j != BIT_MAX; ++j) {
            for(int k = 0; k != BIT_MAX; ++k) {
                if(j & k) continue;
                if(sums[j] == sums[k]) answer.insert(weight_barbell[i] + (sums[j] << 1));
            }
        }
    }

    for(int ans : answer) {
        std::cout << ans << "\n";
    }
}