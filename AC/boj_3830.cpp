#include <iostream>

using namespace std;
using ll = long long;
using pil = pair<int,  ll>;

constexpr int MX_SIZE = 100'000;
constexpr ll INF = 9'876'543'210LL;

int root[MX_SIZE + 1];
ll weight[MX_SIZE + 1];

int find_root(const int node) {
    if(node == root[node]) return node;
    int real_root = find_root(root[node]);
    weight[node] += weight[root[node]];
    return root[node] = real_root;
}

void join(const int a, const int b, const ll w) {
    int ra = find_root(a), rb = find_root(b);
    if(ra != rb) {
        root[rb] = ra;
        weight[rb] = weight[a] - weight[b] + w;
    }
}

void query(const int a, const int b) {
    int ra = find_root(a), rb = find_root(b);
    if(ra != rb) {
        cout << "UNKNOWN\n";
    }
    else {
        cout << weight[b] - weight[a] << "\n";
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    int N, M;
    while(cin >> N >> M && N) {
        for(int i = 1; i <= N; ++i) {
            root[i] = i, weight[i] = 0LL;
        }
        while(M--) {
            char q;
            int a, b, w;
            cin >> q >> a >> b;
            if(q == '!') {
                cin >> w;
                join(a, b, w); 
            }
            else {
                query(a, b);
            }
        }
    }
}