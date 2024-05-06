#include <iostream>
// #define DEBUG
#define N_MAX 20
#define T_MAX 100
#define MOD 1'000'000'007LL

using namespace std;
using ll = long long;
using mtx = struct matrix { 
    ll arr[N_MAX + 1][N_MAX + 1] = {0,};

    void to_unit_matrix(const int sz = N_MAX) {
        for(int i = 1; i <= sz; ++i) {
            arr[i][i] = 1;
        }
    }
    
    void print_matrix(const int sz = N_MAX) {
        for(int i = 1; i <= sz; ++i) {
            for(int j = 1; j <= sz; ++j) {
                cout << arr[i][j] << (j != sz ? " " : "\n");
            }
        }
    }

    matrix multiply_matrix(const matrix &target, const int sz = N_MAX) {
        matrix ret = matrix();
        for(int r = 1; r <= sz; ++r) {
            for(int c = 1; c <= sz; ++c) {
                // ret.arr[r][c] = 0;
                for(int k = 1; k <= sz; ++k) {
                    ret.arr[r][c] += arr[r][k] * target.arr[k][c];
                    ret.arr[r][c] %= MOD;
                }
            }
        }
        return ret;
    }

    matrix() {}

    matrix(const matrix &org) {
        for(int i = 1; i <= N_MAX; ++i) {
            for(int j = 1; j <= N_MAX; ++j) {
                arr[i][j] = org.arr[i][j];
            }
        }
    }
};

mtx exponentiate_matrix(const mtx &base, const int pow) {
    mtx ret;
    if(pow == 0) {
        ret = mtx();
        ret.to_unit_matrix();
    }
    else if(pow == 1) {
        ret = mtx(base);
    }
    else {
        ret = exponentiate_matrix(base, pow >> 1);
        ret = ret.multiply_matrix(ret);
        if(pow & 1) ret = ret.multiply_matrix(base);
    }
    return ret;
}

mtx mat[T_MAX + 1];

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);

    int i, T, N, D;
    cin >> T >> N >> D;
    mat[0].to_unit_matrix(N);
    for(i = 1; i <= T; ++i) {
        int M;
        cin >> M;
        for(int a, b, c; M--;) {
            cin >> a >> b >> c;
            mat[i].arr[a][b] = c;
        }
        mat[i] = mat[i - 1].multiply_matrix(mat[i], N);
        #ifdef DEBUG
        mat[i].print_matrix(N);
        #endif
    }
    mtx ans = exponentiate_matrix(mat[T], D / T).multiply_matrix(mat[D % T], N);
    ans.print_matrix(N);
}
