#include <iostream>
// #define DBG
using namespace std;
typedef long long ll;

main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    ll x, y, z;
    cin >> x >> y;
    cout << "2\n";
    z = x * y - x;
    cout << z << '\n';
    #ifdef DBG
    cout << "cur : " << x + z << '\n'; 
    #endif
    z = -(x * y) + y;
    cout << z << '\n';
    #ifdef DBG
    cout << "cur : " << x * y + z << '\n'; 
    #endif
}