// 검열
#include <iostream>
#include <deque>
using namespace std;

string A, T;
deque<char> fr, bk;
int fp, bp;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cin >> A >> T;
    bp = T.length() - 1;
    if(A.length() > T.length()) {
        cout << T;
        return 0;
    }
    while(fp <= bp) {
        // 2번 프로세스
        for(; fp <= bp;) {
            fr.push_back(T[fp++]);
            if(fr.size() >= A.length() && fr.back() == A.back()) {
                bool flag = false;
                int lenDif = fr.size() - A.length(), pop_cnt = A.length();
                for(int pos = pop_cnt - 1; pos >= 0; --pos) {
                    if(fr[pos + lenDif] != A[pos]) break;
                    if(!pos) {
                        flag = true;
                        while(pop_cnt--) fr.pop_back();
                    }
                }
                if(flag) break;
            }
        }
        // 4번 프로세스
        for(; bp >= fp;) {
            bk.push_front(T[bp--]);
            if(bk.size() >= A.length() && bk.front() == A.front()) {
                bool flag = false;
                int pop_cnt = A.length();
                for(int pos = 0; pos < pop_cnt; ++pos) {
                    if(bk[pos] != A[pos]) break;
                    if(pos == pop_cnt - 1) {
                        flag = true;
                        while(pop_cnt--) bk.pop_front();
                    }        
                }
                if(flag) break;
            }
        }
    }
    T = "";
    for(const char &c : fr)
        T.push_back(c);
    for(const char &c : bk) {
        T.push_back(c);
        if(T.length() >= A.length() && T.back() == A.back()) { // 더는 갱신되지 않는 두 덱을 합치면서 모든 A를 제거
            int lenDif = T.length() - A.length(), pop_cnt = A.length();
            for(int pos = pop_cnt - 1; pos >= 0; --pos) {
                if(T[pos + lenDif] != A[pos]) break;
                if(!pos) {
                    while(pop_cnt--) T.pop_back();
                }
            }
        }
    }
    cout << T;
}