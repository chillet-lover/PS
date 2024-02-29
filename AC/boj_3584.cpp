#include <iostream>
using namespace std;
constexpr int MX = 10'000;

int root[MX + 1];
bool vst[MX + 1];

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        for(int i = 1, A, B; i < N; ++i) {
            cin >> A >> B;
            root[B] = A;
        }
        int A, B, LCA = 0;
        cin >> A >> B;
        if(!root[A]) LCA = A;
        else if(!root[B]) LCA = B;
        else {
            vst[A] = vst[B] = true;
            while(root[A]) {
                int nxt = root[A];
                if(vst[nxt]) {
                    LCA = nxt;
                    goto result;
                }
                vst[nxt] = true;
                A = nxt;
            }
            while(root[B]) {
                int nxt = root[B];
                if(vst[nxt]) {
                    LCA = nxt;
                    goto result;
                }
                vst[nxt] = true;
                B = nxt;
            }
        }
        result :
        cout << LCA << '\n';
        for(int i = 1; i <= N; root[i] = 0, vst[i++] = false);
    }
}