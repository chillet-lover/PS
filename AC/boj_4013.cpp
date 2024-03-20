#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <unordered_map>
// #define DEBUG

using namespace std;

typedef long long ll;
typedef struct scc {
    vector<int> nodes;
    bool rstr;
    int indegree;
    int sum;
    unordered_map<int, bool> edges;

    scc() {
        rstr = false, indegree = 0, sum = 0;
        nodes.clear();
        edges.clear();
    }
} scc;

constexpr int MX = 500'000;
int cash[MX], group[MX], dp[MX];
vector<int> stack, graph[MX], trans[MX];
vector<scc> sccs;
bitset<MX> visit, curry;

inline int mx(const int &a, const int &b) {
    return a > b ? a : b;
}

void dfs(const int &node) {
    visit[node] = true;
    for(const int &next : graph[node]) {
        if(visit[next]) continue;
        dfs(next);
    }
    stack.push_back(node);
}

void make_scc(const int &node, const int &gnum, scc &result) {
    visit[node] = true;
    group[node] = gnum;
    result.sum += cash[node];
    result.rstr |= curry[node];
    result.nodes.push_back(node);
    for(const int &next : trans[node]) {
        if(visit[next]) continue;
        make_scc(next, gnum, result);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    register int i;
    int N, S;

    // 입력
    cin >> N >> i;
    for(int FROM, TO; i; --i) {
        cin >> FROM >> TO;
        --FROM, --TO;
        graph[FROM].push_back(TO);
        trans[TO].push_back(FROM);
    }
    for(i = 0; i < N; ++i) {
        cin >> cash[i];
    }
    cin >> S >> i;
    --S;
    for(int RSTR; i; --i) {
        cin >> RSTR;
        curry[RSTR - 1] = true;
    }

    // dfs 수행
    for(i = 0; i < N; ++i) {
        if(!visit[i]) {
            dfs(i);
        }
    }
    visit.reset(); 

    // SCC 생성
    while(stack.size()) {
        const int top = stack.back();
        stack.pop_back();
        if(!visit[top]) {
            const int gnum = sccs.size();
            scc tmp;
            make_scc(top, gnum, tmp);
            sccs.push_back(tmp);
        }
    }
    #ifdef DEBUG
    int sz = sccs.size();
    for(i = 0; i < sz; ++i) {
        cout << "scc " << i << " : \n";
        for(const int &node : sccs[i].nodes) {
            cout << node + 1 << ", ";
        }
        cout << "sum : " << sccs[i].sum << "\n";
    }
    #endif

    // S가 속한 SCC부터 시작해서 각 SCC의 진입차수를 구한다(위상정렬 준비)
    [](const int &gs) {
        queue<int> q;
        q.push(gs);
        while(q.size()) {
            const int cnum = q.front();
            scc &cur = sccs[cnum];
            q.pop();
            for(const int &node : cur.nodes) {
                for(const int &next : graph[node]) {
                    int next_scc = group[next];
                    if(next_scc == cnum) continue;
                    if(cur.edges.find(next_scc) == cur.edges.end()) {
                        cur.edges[next_scc] = true;
                        ++sccs[next_scc].indegree;
                        q.push(next_scc);
                    }
                }
            }
        }
    } (group[S]);
    #ifdef DEBUG
    for(i = 0; i < sz; ++i) {
        cout << "scc " << i << " can go to : ";
        for(const pair<int, bool> &p : sccs[i].edges) {
            cout << p.first << ", ";
        }
        cout << "indegree : " << sccs[i].indegree << "\n";
    }
    #endif

    // S가 속한 SCC부터 위상정렬을 수행, 도달한 SCC에 레스토랑이 있다면 최대값 갱신을 시도한다
    cout << [](const int &gs) -> int {
        queue<int> q;
        int ret = 0;
        dp[gs] = sccs[gs].sum;
        #ifdef DEBUG
        cout << "S, dp[S], ret : " << gs << ", " << dp[gs] << ", " << ret << "\n";
        #endif
        q.push(gs); 
        while(q.size()) {
            const int cnum = q.front();
            const scc &cur = sccs[cnum];
            if(cur.rstr) {
                ret = mx(ret, dp[cnum]);
            }
            q.pop();
            for(const pair<int, bool> &p : cur.edges) {
                const int &nnum = p.first;
                scc &nxt = sccs[nnum];
                --nxt.indegree;
                dp[nnum] = mx(dp[nnum], dp[cnum] + nxt.sum);
                #ifdef DEBUG
                cout << "nnum, dp[nnum], ret : " << nnum << ", " << dp[nnum] << ", " << ret << "\n";
                #endif
                if(!nxt.indegree) {
                    q.push(nnum);
                }
            }
        }
        return ret;
    } (group[S]);
}