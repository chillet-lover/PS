#include <iostream>
#include <vector>
#include <algorithm>
#define to first
#define fee second

using namespace std;
using uint = unsigned int;
using piu = pair<int, uint>;

constexpr int MX_CITY = 1'000;
constexpr int MX_HEAP = 1'000'000;
constexpr uint INF = 4'000'000'000;

struct mv {
    int node = 0; // 현재 도시
    int count = 0; // 현재 도시에 도착하기까지 거쳐온 간선의 수
    uint sum = 0; // 현재 도시에 도착하기까지 누적된 통행료

    bool operator< (const mv &cmp) {
        return sum < cmp.sum;
    }

    bool operator<= (const mv &cmp) {
        return sum <= cmp.sum;
    }

    bool operator> (const mv &cmp) {
        return sum > cmp.sum;
    }

    bool operator>= (const mv &cmp) {
        return sum >= cmp.sum;
    }    
};

struct mean_heap {
    int size = 0;
    mv heap[MX_HEAP + 1] = {0, 0, INF};

    bool empty() {
        return !size;
    }

    void push(const mv &new_element) {
        heap[++size] = new_element;
        int cur = size;
        while(cur != 1 && heap[cur] < heap[cur >> 1]) {
            swap(heap[cur], heap[cur >> 1]);
            cur >>= 1;
        }
    }

    mv pop() {
        const mv ret = heap[1];
        heap[1] = heap[size--];
        int cur = 1, nxt;
        while(true) {
            nxt = cur << 1;
            if(cur >= size || nxt > size) break;
            if(nxt + 1 <= size && heap[nxt + 1] < heap[nxt]) ++nxt;
            if(heap[cur] <= heap[nxt]) break;
            swap(heap[cur], heap[nxt]);
            cur = nxt;
        }
        return ret;
    }
};

mean_heap h;
uint dp[MX_CITY][MX_CITY + 1]; // [거친 간선의 수][도시 번호] -> 총 통행료
vector<piu> graph[MX_CITY + 1];

int main() {
    register int i, j;
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    
    int N, M, K, S, D;
    uint fee_sum = 0;
    cin >> N >> M >> K >> S >> D;
    for(i = 0; i < N; ++i)
        for(j = 1; j <= N; ++j)
            dp[i][j] = INF;
    for(i = 0; i < M; ++i) {
        int a, b;
        uint w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    h.push({S, 0, 0});
    while(!h.empty()) {
        const mv top = h.pop();
        const int cur = top.node, count = top.count;
        const unsigned int sum = top.sum;
        if(count + 1 >= N || sum > dp[count][cur]) continue;
        dp[count][cur] = sum;
        for(const piu &edge : graph[cur]) {
            const int nxt = edge.to;
            const uint nd = edge.fee;
            if(dp[count + 1][nxt] > sum + nd) {
                dp[count + 1][nxt] = sum + nd;
                h.push({nxt, count + 1, sum + nd});
            }
        }
    }

    auto ans = [&]() {
        uint result = INF;
        for(i = 1; i < N; ++i) {
            uint tmp = fee_sum * i + dp[i][D];
            if(tmp < result) result = tmp;
        }
        cout << result << "\n";
    };
    
    ans();
    while(K--) {
        uint f;
        cin >> f;
        fee_sum += f;
        ans();
    }
}