#include <iostream>
// #define DEBUG
#define SZ 100
#define MOD 1'000'000'007LL

using namespace std;
using ll = long long;
using m = struct matrix {
    
    ll a[SZ][SZ] = {{0,}, };

    matrix() {}

    matrix(const matrix &src, const int sz = SZ) {
        for(int i = 0; i < sz; ++i) {
            for(int j = 0; j < sz; ++j) {
                a[i][j] = src.a[i][j];
            }
        }
    }

    matrix operator * (const matrix &m2) {
        matrix ret = matrix();
        for(int i = 0; i < SZ; ++i) {
            for(int j = 0; j < SZ; ++j) {
                for(int k = 0; k < SZ; ++k) {
                    ret.a[i][j] += a[i][k] * m2.a[k][j];
                    ret.a[i][j] %= MOD;
                }
            }
        }
        return ret;
    }

    void print_matrix(const int sz = SZ) {
        cout << "----------------------------------\n";
        for(int i = 0; i < sz; ++i) {
            for(int j = 0; j < sz; ++j) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "----------------------------------\n";
    }
};

m mpow(const int t, const m &base) {
    if(t == 1) {
        m ret = m(base);
        return ret;
    }
    m ret = m(mpow(t >> 1, base));
    ret = ret * ret;
    if(t & 1) ret = ret * base;
    return ret;
}

int n, k;
m init;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> init.a[i][j];
        }
    }
    #ifdef DEBUG
    init.print_matrix(n);
    #endif
    ll cnt = 0;
    m ret = mpow(k, init);
    #ifdef DEBUG
    ret.print_matrix(n);
    #endif
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cnt += ret.a[i][j];
            cnt %= MOD;
        }
    }
    cout << cnt;
}