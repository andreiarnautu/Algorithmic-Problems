/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("ahocorasick.in", "r", stdin);
FILE *fout = freopen("ahocorasick.out", "w", stdout);

const int Sigma = 26;
const int MAX_N = 1 + 100;
const int MAX_WORD = 1 + 10000;
const int MAX_TEXT = 1 + 1000000;

/*-------- Input data --------*/
char Text[MAX_TEXT], Word[MAX_WORD];
int N;
/*-------- Aho Corasick data --------*/
struct Trie {
    Trie *sons[Sigma];
    Trie *failLink;
    /* failLink = cel mai lung sufix care este si prefix al unui cuvant din dictionar */
    vector< int > wordlist;
    int Count;

    Trie() {
        this->failLink = NULL;
        for(int i = 0; i < Sigma; i++) {
            this->sons[i] = NULL;
        }
        this->Count = 0;
    }
};

Trie *Root = new Trie();

queue< Trie* > Queue;
vector< Trie* > List;
/*-------- Solution --------*/
int frequency[MAX_N];
/*-------- --------*/

void Insert(Trie *root, char *word, int wordId) {
    if(*word == '\0') {
        root->wordlist.push_back(wordId);
    } else {
        if(root->sons[*word - 'a'] == NULL) {
            root->sons[*word - 'a'] = new Trie();
        }
        Insert(root->sons[*word - 'a'], word + 1, wordId);
    }
}

void readInput() {
    scanf("%s", Text);
    scanf("%d ", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%s", Word);
        Insert(Root, Word, i);
    }
}

void computeAhoLinks() {
    Root->failLink = Root;
    for(int i = 0; i < Sigma; i++) {
        if(Root->sons[i] != NULL) {
            Root->sons[i]->failLink = Root;
            Queue.push(Root->sons[i]);
        }
    }

    while(!Queue.empty()) {
        Trie *node = Queue.front(); Queue.pop();

        for(int i = 0; i < Sigma; i++) {
            if(node->sons[i] != NULL) {
                Trie *failNode = node->failLink;

                while(failNode != Root && failNode->sons[i] == NULL) {
                    failNode = failNode->failLink;
                }
                if(failNode->sons[i] != NULL && failNode->sons[i] != node->sons[i]) {
                    failNode = failNode->sons[i];
                }
                node->sons[i]->failLink = failNode;

                Queue.push(node->sons[i]);
            }
        }
    }
}

void Find(Trie *root, char *text) {
    Trie *node = root;
    while(*text != '\0') {
        while(node != Root && node->sons[*text - 'a'] == NULL) {
            node = node->failLink;
        }
        if(node->sons[*text - 'a'] != NULL) {
            node = node->sons[*text - 'a'];
        }

        node->Count ++;
        text ++;
    }


    Queue.push(root);
    while(!Queue.empty()) {
        Trie *node = Queue.front(); Queue.pop();
        List.push_back(node);

        for(int i = 0; i < Sigma; i++) {
            if(node->sons[i] != NULL) {
                Queue.push(node->sons[i]);
            }
        }
    }

    reverse(List.begin(), List.end());
    for(Trie *node : List) {
        for(int wordId : node->wordlist) {
            frequency[wordId] += node->Count;
        }
        if(node->failLink != NULL) {
            node->failLink->Count += node->Count;
        }
    }
}

void writeOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%d\n", frequency[i]);
    }
}

int main() {
    readInput();
    computeAhoLinks();
    Find(Root, Text);
    writeOutput();
    return 0;
}
