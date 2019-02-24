/**
  *  Worg
  */
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

const int sigma = 30;
const int MAX_LEN = 10000;

struct trie {

    bool checked[2], checkedFinal[2];
    trie *fiu[1 + sigma];

    trie() {
        checked[0] = checked[1] = checkedFinal[0] = checkedFinal[1] = false;
        for(int i = 0; i <= sigma; ++i)
            fiu[i] = NULL;
    }
};

trie *root = new trie;
string s, current, sol[MAX_LEN];
int solPos;

char text[MAX_LEN];

void insert(trie *node, int pos, int ind) {

    node->checked[ind] = true;
    if(pos == (int)s.size()) {
        node->checkedFinal[ind] = true;
        return;
    }

    if(!node->fiu[s[pos] - 'a']) {
        node->fiu[s[pos] - 'a'] = new trie;
    }

    if(pos < (int)s.size()) {
        insert(node->fiu[s[pos] - 'a'], pos + 1, ind);
    }
}

void dfs(trie *node) {

    if(!node->checked[0] || !node->checked[1]) {
        return;
    }
    if(node->checkedFinal[0] && node->checkedFinal[1]) {
        sol[solPos++] = current;
    }

    for(int i = 0; i <= 'z' - 'a'; i++)
        if(node->fiu[i]) {

            current += ('a' + i);
            dfs(node->fiu[i]);
            current.pop_back();
        }
}

bool comp(string s1, string s2) {

    int size1 = s1.size(), size2 = s2.size();
    for(int i = 0; i < min(size1, size2); i++)
        if(s1[i] != s2[i])
            return s1[i] < s2[i];

    return size1 < size2;
}

int main() {

    gets(text);
    int lg = strlen(text);

    for(int i = 0; i < lg; i++)
        if('A' <= text[i] && text[i] <= 'Z')
            text[i] += 32;

    for(int i = 0; i < lg; i++)
        if('a' <= text[i] && text[i] <= 'z') {

            s.clear();
            while('a' <= text[i] && text[i] <= 'z') {
                s += text[i];
                i++;
            }
            i--;

            insert(root, 0, 0);
        }

    gets(text);
    lg = strlen(text);

    for(int i = 0; i < lg; i++)
        if('A' <= text[i] && text[i] <= 'Z')
            text[i] += 32;

    for(int i = 0; i < lg; i++)
        if('a' <= text[i] && text[i] <= 'z') {

            s.clear();
            while('a' <= text[i] && text[i] <= 'z') {
                s += text[i];
                i++;
            }
            i--;

            insert(root, 0, 1);
        }

    dfs(root);
    sort(sol, sol + solPos, comp);


    for(int i = 0; i < solPos; ++i) {
        cout << sol[i] << '\n';
    }

    return 0;
}
