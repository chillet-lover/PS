#include <iostream>
using namespace std;
constexpr int MX = 100'000;

int sgt[MX * 4 + 10], 
pos[MX + 1], // 책의 현재 위치
pos2[MX + 1]; // 현재 위치에 꽂힌 책

void init(int node, int l, int r) {
    if(l == r) {
        pos2[l] = sgt[node] = l + 1;
        pos[l + 1] = l;
        return;
    }
    int m = l + r >> 1;
    init(node * 2, l, m);
    init(node * 2 + 1, m + 1, r);
}

void update(int node, int l, int r) {
    if(l == r) {
        int b = pos2[l - 1];
        pos2[l] = sgt[node] = b;
        pos[b] = l;
        return;
    }
    int m = l + r >> 1;
    update(node * 2 + 1, m + 1, r);
    update(node * 2, l, m);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int tc;
    cin >> tc;
    while(tc--) {
        int n, m;
        cin >> n >> m;
        init(1, 0, n - 1);
        while(m--) {
            int target;
            cin >> target;
            cout << pos[target] << ' ';
            if(!pos[target]) continue;
            update(1, 1, pos[target]);
            pos[target] = 0;
            pos2[0] = target;
        }
        cout << '\n';
    }
}