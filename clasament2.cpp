/**
  *  Worg
  */
#include <map>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
FILE *fin = freopen("clasament2.in", "r", stdin);
FILE *fout = freopen("clasament2.out", "w", stdout);

const int MAX_N = 1 + 500000;
const int bufferDim = 100000;
const long long MOD = 1000000007;
const long long MOD2 = 1000000021;
const long long Val = 1000000003;
const long long Val2 = 666013;

/*-------- Input reader --------*/
class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }
public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++ pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++ pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

/*-------- Input data --------*/
int N, M;
/*-------- Treap data --------*/
long long coef[MAX_N], coef2[MAX_N];

struct Treap {
    Treap *left, *right;
    pair< int,int > key;
    int index, priority, weight, when;
    long long hashValue, hashValue2;
    /* index = index-ul concurentului din nodul curent
       weight = greutatea subarborelui;
       hashValue = valoarea hash cu care se codifica subarborele */
    Treap(pair< int,int > key, int index, int priority, int weight, Treap *left, Treap *right) {
        this->key = key;
        this->index = index;
        this->priority = priority;
        this->weight = weight;
        this->hashValue = 1LL * index;
        this->hashValue2 = 1LL * index;
        this->left = left;
        this->right = right;
    }

};

Treap *Root, *nil;

void Initialize() {
    srand(unsigned(time(0)));

    Root = nil = new Treap(make_pair(0, 0), 0, 0, 0, NULL, NULL);
    nil->left = nil->right = nil;

    coef[0] = coef2[0] = 1;
    for(int i = 1; i <= N; i++) {
        coef[i] = (coef[i - 1] * Val) % MOD;
        coef2[i] = (coef2[i - 1] * Val2) % MOD2;
    }
}

void writeTreap(Treap *node) {
    if(node->left != nil) {
        writeTreap(node->left);
    }
    printf("(Key: %d %d; Index: %d; Weight: %d; Hash: %lld)\n", node->key.first, node->key.second, node->index, node->weight, node->hashValue);
    if(node->right != nil) {
        writeTreap(node->right);
    }
}

void Update(Treap* &node) {
    if(node != nil) {
        /* facem update la greutatea subarborelui pe baza fiilor */
        node->weight = node->left->weight + node->right->weight + 1;
        /* calculam valoarea hash a subarborelui pe baza fiilor */
        node->hashValue = (1LL * node->right->hashValue * coef[0]) % MOD;
        node->hashValue = (node->hashValue + 1LL * node->index * coef[node->right->weight]) % MOD;
        node->hashValue = (node->hashValue + 1LL * node->left->hashValue * coef[node->right->weight + 1]) % MOD;

        node->hashValue2 = (1LL * node->right->hashValue2 * coef2[0]) % MOD2;
        node->hashValue2 = (node->hashValue2 + 1LL * node->index * coef2[node->right->weight]) % MOD2;
        node->hashValue2 = (node->hashValue2 + 1LL * node->left->hashValue2 * coef2[node->right->weight + 1]) % MOD2;
    }
}

void rotateLeft(Treap* &node) {
    Treap *t = node->left;
    node->left = t->right; t->right = node;
    node = t;

    Update(node->right); Update(node);
}

void rotateRight(Treap* &node) {
    Treap *t = node->right;
    node->right = t->left; t->left = node;
    node = t;

    Update(node->left); Update(node);
}

void Balance(Treap* &node) {
    if(node->left->priority > node->priority) {
        rotateLeft(node);
    }
    if(node->right->priority > node->priority) {
        rotateRight(node);
    }
}

void Insert(Treap* &node, pair< int,int > key, int index, int priority) {
    if(node == nil) {
        node = new Treap(key, index, priority, 1, nil, nil);
    } else {
        if(key < node->key) {
            Insert(node->left, key, index, priority);
        } else {
            Insert(node->right, key, index, priority);
        }
        Balance(node);
        Update(node);
    }
}

void Erase(Treap* &node, pair< int,int > key) {
    if(node != nil) {
         if(node->key == key) {
            /* daca nodul curent e chiar cel pe care vrem sa il stergem */
            if(node->left == nil && node->right == nil) {
                delete node; node = nil;
            } else {
                if(node->left->priority > node->right->priority) {
                    rotateLeft(node);
                    Erase(node->right, key);
                } else {
                    rotateRight(node);
                    Erase(node->left, key);
                }
                Update(node);
            }
        } else if(key < node->key) {
            Erase(node->left, key);
            Update(node);
        } else {
            Erase(node->right, key);
            Update(node);
        }
    }
}


/*-------- Table data --------*/
int points[MAX_N], when[MAX_N];
map< pair< long long,long long >, int > Map;
/*-------- --------*/

void insertElements() {
    for(int i = 1; i <= N; i++) {
        int x; cin >> x;
        x ++;
        points[i] = x;
        Insert(Root, make_pair(x, M), i, rand() + 1);
        when[i] = M;
    }
}

void SimulateTableChanges() {
    /* inseram starea initiala */
    Map[make_pair(Root->hashValue, Root->hashValue2)] = 1;

    for(int i = 1; i <= M; i++) {
        int x, y;
        cin >> x; cin >> y; y ++;

        Erase(Root, make_pair(points[x], when[x]));

        points[x] = y; when[x] = M - i;

        Insert(Root, make_pair(points[x], when[x]), x, rand() + 1);

        printf("%d\n", Map[make_pair(Root->hashValue, Root->hashValue2)]);

        Map[make_pair(Root->hashValue, Root->hashValue2)] ++;
    }
}

int main() {
    cin.getBuffer(); cin >> N; cin >> M;
    Initialize();
    insertElements();
    SimulateTableChanges();
    return 0;
}
