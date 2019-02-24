/**
  *  Worg
  */
#include <ctime>
#include <vector>
#include <utility>
#include <cstdlib>
//#include <iostream>

#define fi          first
#define se          second
#define mp          make_pair
#define pb          push_back
#define mod         ((1 << 13) - 1)
#define MAX_K       1 + 500000

using namespace std;

vector < pair<long long,int> > h[mod + 1];

long long N, M;
long long nr;

/**********************************TREAP_ZONE**************************************************/

struct treap {

        long long key = 0;
        int priority = 0, cnt = 0, total = 0;
        treap *left, *right;

        treap(long long _key, int _priority, int _cnt, treap *_left, treap *_right) {

            this->key = _key, this->priority = _priority, this->total = this->cnt = _cnt;
            this->left = _left, this->right = _right;
        }
} *root[MAX_K], *empty[MAX_K];

void init() {

    srand(unsigned(time(0)));
    for(int i = 1; i < MAX_K; ++i)
        root[i] = empty[i] = new treap(0, 0, 0, NULL, NULL);
}

void updateTreap(treap *&node, int i) {

    if(node != empty[i])
        node->total = node->left->total + node->right->total + node->cnt;
    else
        node->cnt = node->total = 0;
}

void rotLeft(treap *&node, int i) {

    treap *T = node->left;
    node->left = T->right, T->right = node;
    node = T;

    updateTreap(node->right, i); updateTreap(node, i);
}

void rotRight(treap *&node, int i) {

    treap *T = node->right;
    node->right = T->left, T->left = node;
    node = T;

    updateTreap(node->left, i); updateTreap(node, i);
}

void balance(treap *&node, int i) {

    if(node->priority < node->left->priority)
        rotLeft(node, i);
    else if(node->priority < node->right->priority)
        rotRight(node, i);
}

/*void write(treap *node, int i) {

    if(node->left != empty[i])
        write(node->left, i);
    cout << node->key << " " << node->cnt << '\n';
    if(node->right != empty[i])
        write(node->right, i);
}*/

void insert(treap *&node, long long key, int priority, int x, int i) {

    if(node == empty[i]) {

        node = new treap(key, priority, x, empty[i], empty[i]);
        updateTreap(node, i);
        return;
    }
    if(key < node->key)
        insert(node->left, key, priority, x, i);
    else if(key > node->key)
        insert(node->right, key, priority, x, i);
    else
        node->cnt += x;
    updateTreap(node, i);
    balance(node, i);
}

int searchTreap(treap *&node, long long int key, int i) {

    if(node == empty[i])
        return 0;
    if(node->key > key)
        return searchTreap(node->left, key, i);
    if(node->key < key)
        return node->left->total + node->cnt + searchTreap(node->right, key, i);
    return node->left->total + node->cnt;
}

/*************************************END_OF_THE_TREAP_ZONE***********************************************/




/*************************************HASH_ZONE***********************************************/

int hashFind(long long val) {

    int level = val & mod;
    for(vector < pair<long long,int> >::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(it->fi == val)
            return it->se;
    return 0;
}

void hashInsert(long long val) {

    int level = val & mod;
    h[level].pb(mp(val, nr));
}

/************************************END_OF_THE_HASH_ZONE************************************************/



void initialize(long long n, long long m) {

    N = n, M = m;
    init();
}
void update(long long x, long long y1, long long y2) {

    int val;
    val = hashFind(x);

    if(!val) {

        ++nr;
        hashInsert(x);
        val = nr;
    }
    insert(root[val], y1, (rand() & mod) + 1, 1, val);
    insert(root[val], y2 + 1, (rand() & mod) + 1, -1, val);
}
int query(long long x, long long y) {

    int val = hashFind(x);
    if(!val)
        return 0;
    return searchTreap(root[val], y, val);
}

