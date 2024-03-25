#include <iostream>
#include <vector>
#include <bitset>
// #define DEBUG

using namespace std;

constexpr int MX = 5'000;
bitset<MX * 2 + 1> chk;
string ans(MX, '\0');
vector<int> stk, grp[MX * 2 + 1], rev[MX * 2 + 1];
vector<vector<int>> SCCs;

void dfs(const int &cur) {
    chk[cur] = true;
    for(const int &nxt : grp[cur]) {
        if(chk[nxt]) continue;
        dfs(nxt);
    }
    stk.push_back(cur);
}

void make_scc(const int &cur, vector<int> &scc) {
    chk[cur] = true;
    scc.push_back(cur);
    for(const int &nxt : rev[cur]) {
        if(chk[nxt]) continue;
        make_scc(nxt, scc);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    register int i;
    int k, n;
    cin >> k >> n;
    for(i = n; i; --i) { // R : lx / B : lx + MX
        int l1, l2, l3, nl1, nl2, nl3;
        char c1, c2, c3;
        cin >> l1 >> c1 >> l2 >> c2 >> l3 >> c3;
        l1 = c1 == 'B' ? l1 + MX : l1,
        l2 = c2 == 'B' ? l2 + MX : l2,
        l3 = c3 == 'B' ? l3 + MX : l3,
        nl1 = l1 > MX ? l1 - MX : l1 + MX,
        nl2 = l2 > MX ? l2 - MX : l2 + MX,
        nl3 = l3 > MX ? l3 - MX : l3 + MX;
        // l1 V l2
        grp[l1].push_back(nl2), grp[l2].push_back(nl1), 
        rev[nl1].push_back(l2), rev[nl2].push_back(l1);
        // l2 V l3
        grp[l2].push_back(nl3), grp[l3].push_back(nl2),
        rev[nl2].push_back(l3), rev[nl3].push_back(l2);
        // l3 V l1
        grp[l3].push_back(nl1), grp[l1].push_back(nl3),
        rev[nl3].push_back(l1), rev[nl1].push_back(l3);
    }
    for(i = 1; i <= k; ++i) {
        int ni = i + MX;
        if(!chk[ni]) dfs(ni);
        if(!chk[i]) dfs(i);
    }
    chk.reset();
    while(stk.size()) {
        const int top = stk.back();
        stk.pop_back();
        if(chk[top]) continue;
        vector<int> scc;
        make_scc(top, scc);
        SCCs.push_back(scc);
        #ifdef DEBUG
        cout << "SCC " << SCCs.size() << "\n";
        for(const int &vtx : scc) {
            cout << vtx << " ";
        }
        cout << "\n=======================================\n";
        #endif
    }
    for(const vector<int> &scc : SCCs) {
        chk.reset();
        for(const int &vtx : scc) {
            int idx = vtx > MX ? vtx - MX : vtx,
            nvtx = vtx > MX ? vtx - MX : vtx + MX; 
            chk[vtx] = true;
            if(chk[nvtx]) {
                cout << "-1\n";
                return 0;
            }
            if(ans[idx - 1] == '\0') {
                ans[idx - 1] = vtx > MX ? 'B' : 'R';
            }
        }
    }
    cout << ans + "\n";
}