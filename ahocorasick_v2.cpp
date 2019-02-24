/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::queue;
using std::vector;
FILE *fin = freopen("ahocorasick.in", "r", stdin);
FILE *fout = freopen("ahocorasick.out", "w", stdout);

const int sigma = 26;
const int kMaxWords = 1 + 100;
const int kMaxWordLen = 1 + 10000;
const int kMaxTextLen = 1 + 1000000;

/*-------- Structures --------*/
struct Trie {
    Trie *son[sigma];
    Trie *fail_link;
    vector<int > word_list;
    int count;

    Trie() {
        for(int i = 0; i < sigma; i++) {
            this->son[i] = NULL;
        }
        this->fail_link = NULL;
        this->count = 0;
    }
};
/*-------- Input data --------*/
int N;
char text[kMaxTextLen], word[kMaxWordLen];
/*-------- Algorithm data --------*/
Trie *root = new Trie();

queue<Trie* > my_queue;
vector<Trie* > node_list;

int word_frequency[kMaxWords];
/*-------- --------*/

void Insert(Trie *node, char *s, int word_index) {
    if(*s == '\0') {
        node->word_list.push_back(word_index);
    } else {
        if(node->son[*s - 'a'] == NULL) {
            node->son[*s - 'a'] = new Trie();
        }
        Insert(node->son[*s - 'a'], s + 1, word_index);
    }
}

void ReadInput() {
    scanf("%s", text); scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%s", word);
        Insert(root, word, i);
    }
}

void ComputeFailLinks() {
    root->fail_link = root;
    for(int i = 0; i < sigma; i++) {
        if(root->son[i] != NULL) {
            root->son[i]->fail_link = root;
            my_queue.push(root->son[i]);
        }
    }

    while(!my_queue.empty()) {
        Trie *node = my_queue.front(); my_queue.pop();

        for(int i = 0; i < sigma; i++) {
            if(node->son[i] != NULL) {
                Trie *fail_node = node->fail_link;

                while(fail_node != root && fail_node->son[i] == NULL) {
                    fail_node = fail_node->fail_link;
                }

                if(fail_node->son[i] != NULL && fail_node->son[i] != node->son[i]) {
                    fail_node = fail_node->son[i];
                }
                node->son[i]->fail_link = fail_node;

                my_queue.push(node->son[i]);
            }
        }
    }
}

void FindAppearances(Trie *root, char *text) {  //  Parcurgem textul, mergand pe trie-ul format
    Trie *node = root;
    while(*text != '\0') {
        while(node != root && node->son[*text - 'a'] == NULL) {
            node = node->fail_link;
        }
        if(node->son[*text - 'a'] != NULL) {
            node = node->son[*text - 'a'];
        }

        node->count ++;  //  Crestem numarul de ori de care am ajuns in nodul curent
        text ++;
    }

    my_queue.push(root);  //  Observatie: coada era goala
    while(!my_queue.empty()) {
        Trie* node = my_queue.front(); my_queue.pop();
        node_list.push_back(node);

        for(int i = 0; i < sigma; i++) {
            if(node->son[i] != NULL) {
                my_queue.push(node->son[i]);
            }
        }
    }

    std::reverse(node_list.begin(), node_list.end());  //  Parcurgem nodurile de jos in sus

    for(auto node : node_list) {
        for(auto word_id : node->word_list) {
            word_frequency[word_id] += node->count;
        }
        if(node->fail_link != NULL) {
            node->fail_link->count += node->count;
        }
    }
}

void WriteOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%d\n", word_frequency[i]);
    }
}

int main() {
    ReadInput();
    ComputeFailLinks();
    FindAppearances(root, text);
    WriteOutput();
    return 0;
}
