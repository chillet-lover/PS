#include <iostream>
#define MX 200
#define INF 987654321
using namespace std;

// A -> 최단경로의 길이 저장, B -> 직접 이어진 가장 긴 간선의 길이 저장
int A[MX][MX], B[MX][MX]; 

template <typename T>
inline T mn(const T &a, const T &b) {
    return a < b ? a : b;
}

template <typename T>
inline T mx(const T &a, const T &b) {
    return a > b ? a : b;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cout << fixed;
    cout.precision(1);

    register int i, j, k;
    int N, M; 
    double ans = (double) INF;

    cin >> N >> M;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            if(i == j) continue;
            A[i][j] = INF;
        }
    }
    for(i = 0; i < M; ++i) {
        int S, E, L;
        cin >> S >> E >> L;
        --S, --E;
        A[S][E] = A[E][S] = mn(A[S][E], L);
        B[S][E] = B[E][S] = mx(B[S][E], L);
    }

    // 최단거리 갱신
    for(k = 0; k < N; ++k) {
        for(i = 0; i < N; ++i) {
            for(j = 0; j < N; ++j) {
                int d = A[i][k] + A[k][j];
                A[i][j] = mn(A[i][j], d);
            }
        }
    }

    // 모든 정점에 불을 붙여서 최소값을 구한다.
    for(k = 0; k < N; ++k) {
        double res_k = 0.0;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < N; ++j) {
                double t = A[k][j] + (B[i][j] - A[k][j] + A[k][i]) / 2.0;
                res_k = mx(res_k, t);
            }
        }
        ans = mn(ans, res_k);
    }
    
    cout << ans;
}