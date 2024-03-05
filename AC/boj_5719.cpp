#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#define DBG 0
using namespace std;
constexpr int MX = 500;
constexpr int RMX = 10'000;
constexpr int INF = 100'000'000;
typedef struct pair<int, int> pii;
typedef struct road {
    int to, we, rn;
} rd;

int d[MX], d2[MX];
vector<rd> grp[MX], grp2[MX];
bitset<RMX> rchk;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int N, M;
    while(cin >> N >> M && N) {
        for(int i = 0; i < N; ++i) {
            d[i] = d2[i] = INF;
            grp[i].clear(), grp2[i].clear();
        }
        int S, D;
        cin >> S >> D;
        d[S] = d2[S] = 0;
        for(int i = 0; i < M; ++i) {
            int U, V, P;
            cin >> U >> V >> P;
            grp[U].push_back({V, P, i});
            grp2[V].push_back({U, P, i});
        }
        priority_queue<pii> pq;
        pq.push({0, S});
        while(pq.size()) { // 1차 최단거리 탐색
            int dist = -pq.top().first,
            cur = pq.top().second;
            pq.pop();
            if(dist > d[cur]) continue;
            for(const rd &edge : grp[cur]) {
                int nxt = edge.to, ndist = dist + edge.we;
                if(ndist < d[nxt]) {
                    d[nxt] = ndist;
                    pq.push({-ndist, nxt});
                }
            }
        }
        if(DBG) {
            cout << "updated d after first run\n";
            for(int i = 0; i < N; ++i) {
                cout << "d[" << i << "] : " << d[i] << '\n';
            }
            cout << "--------------------------\n";
        }
        queue<int> q;
        q.push(D);
        while(q.size()) { // 최단경로 역추적
            int cur = q.front();
            q.pop();
            for(const rd &edge : grp2[cur]) {
                if(rchk[edge.rn]) continue;
                int nxt = edge.to, dif = edge.we;
                if(d[nxt] == d[cur] - dif) {
                    rchk[edge.rn] = true;
                    q.push(nxt);
                }
            }
        }
        pq.push({0, S});
        while(pq.size()) { // 거의 최단거리 탐색
            int dist = -pq.top().first,
            cur = pq.top().second;
            pq.pop();
            if(dist > d2[cur]) continue;
            for(const rd &edge : grp[cur]) {
                if(rchk[edge.rn]) continue;
                int nxt = edge.to, ndist = dist + edge.we;
                if(ndist < d2[nxt]) {
                    d2[nxt] = ndist;
                    pq.push({-ndist, nxt});
                }
            }
        }
        if(DBG) {
            cout << "updated d2 after second run\n";
            for(int i = 0; i < N; ++i) {
                cout << "d2[" << i << "] : " << d2[i] << '\n';
            }
            cout << "--------------------------\n";
        }
        cout << (d2[D] == INF ? -1 : d2[D]) << '\n';
        rchk.reset();
    }
}