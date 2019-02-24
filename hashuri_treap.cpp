/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>

#define inf 2000000000

using namespace std;
FILE *fin=freopen("hashuri.in","r",stdin);
FILE *fout=freopen("hashuri.out","w",stdout);

struct treap {

        int key, priority;
        treap *left, *right;
        treap(){}
        treap(int key, int priority, treap *left, treap *right) {

            this -> key = key, this -> priority = priority;
            this -> left = left, this -> right = right;
        }
} *root, *nil;

void set() {

    srand(unsigned(time(0)));
    nil = new treap(0, 0, NULL, NULL);
    root = nil;
}

void rotLeft(treap *&node) {

    treap *t = node -> left;
    node -> left = t -> right, t -> right = node;
    node = t;
}

void rotRight(treap *&node) {

    treap *t = node -> right;
    node -> right = t -> left, t -> left = node;
    node = t;
}

void balance(treap *&node) {

    if(node -> priority < node -> left -> priority)
        rotLeft(node);
    else if(node -> priority < node -> right -> priority)
        rotRight(node);
}

void insert(treap* &node, int key, int priority) {

    if(node == nil) {
        node = new treap(key, priority, nil, nil);
        return;
    }

    if(key < node -> key)
        insert(node -> left, key, priority);
    else if(key > node -> key)
        insert(node -> right, key, priority);
}

void erase(treap *&node, int key) {

    if(node == nil)
        return;
    if(node -> key > key)
        erase(node -> left, key);
    else if(node -> key < key)
        erase(node -> right, key);
    else {

        if(node -> left == nil && node -> right == nil)
            delete node, node = nil;
        else {
            (node -> left -> priority > node -> right -> priority) ? rotLeft(node) : rotRight(node);
            erase(node, key);
        }
    }
}

int search(treap *node, int key) {

    if(node == nil)
        return 0;
    if(key == node -> key)
        return 1;
    if(key < node -> key)
        return search(node -> left, key);
    else
        return search(node -> right, key);
}

int main() {

    set();
    int n, op, x;
    for(scanf("%d", &n); n; --n) {

        scanf("%d %d", &op, &x);
        if( op == 1 )
            insert(root, x, rand() + 1);
        if( op == 2 )
            erase(root, x);
        if( op == 3 )
            printf("%d\n", search(root, x));
    }
    return 0;
}
