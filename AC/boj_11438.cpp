#include <iostream>
#include <vector>
#include <algorithm>
#define DBG 0
using namespace std;
constexpr int MX = 100'000;
constexpr int LN = 17;

int N, depth[MX + 1]{-1, }, parent[LN][MX + 1];
vector<int> grp[MX + 1];

void make_tree(int cur, int prev) {
    depth[cur] = depth[prev] + 1;
    parent[0][cur] = prev;
    for(int i = 1; i < LN; ++i) {
        parent[i][cur] = parent[i - 1][parent[i - 1][cur]];
    }
    for(const int &nxt : grp[cur]) {
        if(nxt == prev) continue;
        make_tree(nxt, cur);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> N;
    for(int i = 1; i < N; ++i) {
        int p1, p2;
        cin >> p1 >> p2;
        grp[p1].push_back(p2);
        grp[p2].push_back(p1);
    }
    make_tree(1, 0);
    int M;
    cin >> M;
    while(M--) {
        int p1, p2;
        cin >> p1 >> p2;
        if(p1 == 1 || p2 == 1) {
            cout << "1\n";
            continue;
        }
        if(depth[p2] < depth[p1]) swap(p1, p2);
        for(int i = LN - 1; depth[p1] != depth[p2] && i >= 0; --i) {
            if(depth[parent[i][p2]] >= depth[p1]) {
                p2 = parent[i][p2];
            }
        }
        if(p1 == p2) {
            cout << p1 << '\n';
            continue;
        }
        int ans = 1;
        for(int i = LN - 1; i >= 0; --i) {
            if(DBG) {
                cout << "parent[" << i << "][" << p1 << "] : " << parent[i][p1] << '\n';
                cout << "parent[" << i << "][" << p2 << "] : " << parent[i][p2] << '\n';
            }
            if(parent[i][p1] != parent[i][p2]) {
                if(DBG) {
                    cout << "p1 and p2 are updated\n";
                    cout << "previous p1, p2 : " << p1 << ", " << p2 << '\n';
                    cout << "new p1, p2 : " << parent[i][p1] << ", " << parent[i][p2] << '\n';
                }
                p1 = parent[i][p1],
                p2 = parent[i][p2];
            }
            ans = parent[i][p1];
        }
        if(DBG) cout << "ans : ";
        cout << ans << '\n';
    }
}