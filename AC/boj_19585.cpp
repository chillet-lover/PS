#include <iostream>
#include <map>
#include <unordered_map>
// #define DEBUG
#ifdef DEBUG
#include <vector>
#endif

using namespace std;

string input;
unordered_map<string, bool> um;
struct trie {
    bool check;
    map<char, trie *> child;

    void insert() {
        trie *node = this;
        char c;
        while(true) {
            if(input.empty()) {
                node -> check = true;
                return;
            }
            c = input.back();
            if(node -> child[c] == nullptr) node -> child[c] = new trie();
            node = node -> child[c];
            input.pop_back();
        }
    }

    #ifdef DEBUG
    void print() {
        vector<pair<trie *, string>> stack;
        stack.push_back({this, ""});
        while(stack.size()) {
            trie *node = stack.back().first;
            string word = stack.back().second;
            stack.pop_back();
            if(node -> check) cout << word + "\n";
            for(auto it = node -> child.begin(); it != node -> child.end(); ++it) {
                stack.push_back({it -> second, word + it -> first});
            }
        }
    }
    #endif

    trie() {
        check = false;
        child.clear();
    }

    ~trie() {
        for(auto it = child.begin(); it != child.end(); ++it) {
            delete it -> second;
        }
        child.clear();
    }
} *nroot;

bool find_post(trie *node) {
    char c;
    while(input.length()) {
        if(node -> check && um.find(input) != um.end()) return true;
        c = input.back();
        if(node -> child.find(c) == node -> child.end()) return false;
        node = node -> child[c];
        input.pop_back();
    }
    return false;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    nroot = new trie();
    int C, N, Q;
    cin >> C >> N;
    while(C--) {
        cin >> input;
        um[input] = true;
    }
    while(N--) {
        cin >> input;
        nroot -> insert();
    }
    #ifdef DEBUG
    for(auto it = um.begin(); it != un.end(); ++it) {
        cout << it -> first + "\n";
    }
    nroot -> print();
    #endif
    cin >> Q;
    while(Q--) {
        cin >> input;
        cout << (input.length() > 2000 || !find_post(nroot) ? "No\n" : "Yes\n");
    }
    delete nroot;
}