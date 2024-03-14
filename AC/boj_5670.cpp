#include <iostream>
#include <map>
#define MX 26
#define DBG 0

using namespace std;

typedef struct trie_node {
    bool check; // 현재 노드로 완성된 단어가 존재하는지 체크
    map<char, trie_node *> child; // 알파벳에 대응되는 자식 노드를 저장

    trie_node() { // 생성자
        check = false;
        child.clear();
    }

    ~trie_node() { // 소멸자
        for(auto it = child.begin(); it != child.end(); ++it) {
            delete it -> second;
        }
        child.clear();
    }

    void insert(const string &word, const int index) {
        const int mx = word.length() - 1;
        const char ch = word[index];
        
        if(child.find(ch) == child.end()) { // 글자에 해당하는 자식노드가 없는 경우
            child[ch] = new trie_node();
        }

        if(index >= mx) {
            child[ch] -> check = true; // 자식노드에서 한 단어가 완성되었다.
            return;
        }
        child[ch] -> insert(word, index + 1); // 단어가 완성되지 않았으므로 자식 노드에서 다음 글자의 삽입을 이어나간다.
    }

    void print(string &word) { // 디버깅용 함수, 트라이 내의 단어들을 출력
        if(check) cout <<  "word : " + word + "\n";
        for(auto it = child.begin(); it != child.end(); ++it) {
            word += it -> first;
            it -> second -> print(word); 
            word.pop_back();
        }
    }

    int get_sum(const int count) { 
        const int child_count = child.size();
        int ret = check ? count : 0,
        flag = check || child_count > 1 ? 1 : 0;
        if(child_count > 0) {
            for(auto it = child.begin(); it != child.end(); ++it) {
                ret += it -> second -> get_sum(count + flag);
            }
        }
        if(DBG && check) { // 디버깅용, 현재 노드에서 단어가 완성됐다면 검색에 필요한 입력의 수를 개별적으로 출력해 확인한다. 
            cout << "required count : " << count << '\n';
        }
        return ret;
    }
} trie;

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cout << fixed;
    cout.precision(2); // 소수점 아래 둘째 자리까지 출력
    
    int TC;
    trie *root = NULL;

    while(cin >> TC) {
        root = new trie();
        root -> check = true;
        for(int i = TC; i; --i) {
            string word;
            cin >> word;
            root -> insert(word, 0);
        }
        cout << root -> get_sum(0) / (double) TC << '\n';
        delete root;
    }
}