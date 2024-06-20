#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#define DEBUG

using namespace std;
using ll = long long;
using mp = struct manipulation {
    int a, b, c;
};
using plv = pair<ll, vector<int>>;

constexpr ll INF = 9876543210;
vector<mp> edges;  
map<vector<int>, ll> cache;
priority_queue<plv> pq;

void print_vector(const vector<int> &vec) {
    for(int i : vec) {
        cout << i << " ";
    }
    cout << "\n";
}


int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    int N, M;
    vector<int> init, ans;
    cin >> N;
    for(int i = 0, j; i < N; ++i) {
        cin >> j;
        init.push_back(j), ans.push_back(j);
    }
    sort(ans.begin(), ans.end());
    cache[ans] = INF;

    cin >> M;
    for(int i = 0, a, b, c; i < M; ++i) {
        cin >> a >> b >> c;
        edges.push_back({a - 1, b - 1, c});
    }

    pq.push({0, init});
    while(pq.size()) {
        plv cur = pq.top();
        ll csum = -cur.first;
        vector<int> &cvec = cur.second;
        pq.pop();
        if(cache.find(cvec) == cache.end() || csum < cache[cvec]) cache[cvec] = csum;
        else if(csum >= cache[cvec]) continue;
        for(const mp &e : edges) {
            ll nsum = csum + e.c;
            swap(cvec[e.a], cvec[e.b]);
            pq.push({-nsum, cvec});
            swap(cvec[e.a], cvec[e.b]);           
        }
    }

    cout << (cache[ans] == INF ? -1 : cache[ans]);
}