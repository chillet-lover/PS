#include <iostream>
#include <algorithm>
// #define DEBUG

int coin[20], dp[10001];

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin.sync_with_stdio(0);
    
    int tc;
    std::cin >> tc;

    while(tc) {
        --tc;
        
        int N, M;

        std::cin >> N;
        for(int i = 0; i != N; ++i) {
            std::cin >> coin[i];
        }
        std::cin >> M;

        for(int i = 0; i != N; ++i) {
            ++dp[coin[i]];
            for(int j = coin[i] + 1; j <= 10000; ++j) {
                dp[j] += dp[j - coin[i]];
            }
            
        }

        std::cout << dp[M] << "\n";
        
        for(int i = 0; i <= 10000; ++i) dp[i] = 0;
    }
}

