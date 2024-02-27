#include <iostream>
using namespace std;

main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    string a;
    cin >> a;
    for(int i = 0, j = a.length(); i < j; ++i)
        cout << i << '\n';
}