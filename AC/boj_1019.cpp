#include <iostream>
using namespace std;


int N, cnt[10];

void update_cnt(int num, int mult) {
    while(num) {
        cnt[num % 10] += mult;
        num /= 10; 
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> N;
    int a = 1, co = 1;
    while(a <= N) {
        while(a <= N && a % 10 != 0) {
            update_cnt(a++, co);    
        }
        if(a > N) break;
        while(a <= N && N % 10 != 9) {
            update_cnt(N--, co);
        }
        for(int i = 0; i < 10; ++i) {
            cnt[i] += co * (N / 10 - a / 10 + 1);
        }
        a /= 10, N /= 10, co *= 10;
    }
    for(const int &count : cnt) {
        cout << count << ' ';
    }
}