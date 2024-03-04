#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
constexpr int MX = 10'000;
constexpr int RMX = 100'000;
using namespace std;

typedef pair<int, int> pii;
typedef struct road {
    int to, time, rnum;
} road;

int d[MX + 1], cnt[MX + 1];
vector<pii> ig[MX + 1];
vector<road> bg[MX + 1];
bitset<RMX + 1> chk;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int st, ed, time;
        cin >> st >> ed >> time;
        ++cnt[ed];
        ig[st].push_back({ed, time});
        bg[ed].push_back({st, time, i});
    }
    int st, ed;
    cin >> st >> ed;
    queue<pii> q;
    q.push({st, 0});
    while(q.size()) {
        int cur = q.front().first,
        sum = q.front().second;
        q.pop();
        if(cur == ed) continue;
        for(const pii &p : ig[cur]) {
            int nxt = p.first, nt = p.second;
            --cnt[nxt];
            d[nxt] = max(d[nxt], sum + nt);
            if(!cnt[nxt]) q.push({nxt, d[nxt]});
        }
    }
    queue<int> qq;
    qq.push(ed);
    while(qq.size()) {
        int cur = qq.front();
        qq.pop();
        if(cur == st) continue;
        for(const road &r : bg[cur]) {
            int nxt = r.to, dif = r.time, rnum = r.rnum;
            if(d[cur] - dif == d[nxt] && !chk[rnum]) {
                chk[rnum] = true;
                qq.push(nxt);
            }
        }
    }
    cout << d[ed] << '\n' << chk.count();
}