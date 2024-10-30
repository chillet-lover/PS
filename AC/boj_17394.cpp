#include <iostream>
#include <queue>

using pii = std::pair<int, int>;

const int MX = 1'010'101, INF = 987'654'321;
int tc, n, a, b, vst[MX];
bool isNotPrime[MX] = {true, true};

void input();
void sieve();
void solve();
void run();

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin.sync_with_stdio(0);

    solve();
}

void input() {
    std::cin >> n >> a >> b;
}

void sieve() {
    for(int i = 2; i != MX; ++i) {
        if(isNotPrime[i]) continue;
        for(int j = i << 1; j < MX; j += i) {
            isNotPrime[j] = true;
        }
    }
}

void run() {
    std::queue<pii> q;
    q.push({n, 0});
    vst[n] = 0;
    int ans = INF;
    for(int i = 0; i != MX; ++i) {
        vst[i] = INF;
    }
    while(!q.empty()) {
        int num = q.front().first,
        cnt = q.front().second;
        q.pop();
        if(a <= num && num <= b && !isNotPrime[num]) {
            ans = cnt;
            break;
        }
        if(cnt + 1 < vst[num / 3]) {
            vst[num / 3] = cnt + 1;
            q.push({num / 3, cnt + 1});
        }
        if(cnt + 1 < vst[num >> 1]) {
            vst[num >> 1] = cnt + 1;
            q.push({num >> 1, cnt + 1});
        }
        if(num + 1 < MX && cnt + 1 < vst[num + 1]) {
            vst[num + 1] = cnt + 1;
            q.push({num + 1, cnt + 1});
        }
        if(num - 1 >= 0 && cnt + 1 < vst[num - 1]) {
            vst[num - 1] = cnt + 1;
            q.push({num - 1, cnt + 1});
        }
    }
    std::cout << (ans == INF ? -1 : ans) << "\n";
}

void solve() {
    std::cin>>tc;
    sieve();
    for(int i = 0; i != tc; ++i) {
        input();
        run();
    }
}