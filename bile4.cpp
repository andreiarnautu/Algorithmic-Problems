/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define buffDIM 5000
#define DIM 500500
#define INF 2000000000

using namespace std;
FILE *fin=freopen("bile4.in","r",stdin);
FILE *fout=freopen("bile4.out","w",stdout);

int n, m, pos;
int q;
char buff[buffDIM];

void read(int &nr) {

    while(buff[pos] < '0' || buff[pos] > '9')
        if(++pos == buffDIM)
            fread(buff, 1, buffDIM, stdin), pos = 0;
    nr = 0;
    while(buff[pos] >= '0' && buff[pos] <= '9') {
        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDIM)
            fread(buff, 1, buffDIM, stdin), pos = 0;
    }

}

int getRand() {

    int ret = rand();
    ret %= 100000;
    if(ret < 0)
        ret = -ret;
    if(!ret)
        ++ret;
    return ret;
}

struct treap {

        int key, priority, cnt, total;
        treap *left, *right;

        treap(int key, int priority, int cnt, treap *left, treap *right) {

            this->key = key, this->priority = priority, this->cnt = this->total = cnt;
            this->left = left, this->right = right;
        }
} *A[DIM], *B[DIM], *empty[DIM], *t, *t1, *t2;

void write(treap *node, int i) {

    if(node == empty[i])
        return;
    write(node->left, i);
    for(int i = 1; i <= node->cnt; ++i)
        printf("%d ", node->key);
    write(node->right, i);
}

void update(treap *&node, int i) {

    if(node != empty[i] && node != NULL)
        node->total = node->left->total + node->right->total + node->cnt;
    else if(node != NULL)
        node->total = 0;
}

void rotLeft(treap *&node, int i) {

    treap *T = node->left;
    node->left = T->right, T->right = node;
    node = T;

    update(node->right, i); update(node, i);
}

void rotRight(treap *&node, int i) {

    treap *T = node->right;
    node->right = T->left, T->left = node;
    node = T;


    update(node->left, i); update(node, i);
}

void balance(treap *&node, int i) {

    if(node->priority < node->left->priority)
        rotLeft(node, i);
    else if(node->priority < node->right->priority)
        rotRight(node, i);
}

void _insert(treap *&node, int key, int priority, int nr, int i) {

    if(node == empty[i]) {
        if(priority != INF)
            priority %= 100000, priority++;
        node = new treap(key, priority, nr, empty[i], empty[i]);
        update(node, i);
        return;
    }
    if(key < node->key)
        _insert(node->left, key, priority, nr, i);
    else if(key > node->key)
        _insert(node->right, key, priority, nr, i);
    else
        node->cnt += nr;

    update(node, i);
    balance(node, i);
}

void insert(treap *&node, int key, int priority, int nr, int i) {

    if(node == empty[i]) {

        if(priority != INF)
            priority %= 100000, priority++;
        node = new treap(key, priority, nr, empty[i], empty[i]);
        update(node, i);
        return;
    }

    if(key < node->key)
        insert(node->left, key, priority, nr, i);
    else
        insert(node->right, key, priority, nr, i);
    update(node, i);
    balance(node, i);
}

void erase(treap *&node, int key, int i) {

    if(node == empty[i])
        {return;}

    if(key == node->key) {

        if(node->left == empty[i] && node->right == empty[i])
            {delete node, node = empty[i]; return;}
        else {

            if(node->left->priority > node->right->priority)  {
                rotLeft(node, i);
                erase(node->right, key, i);
            }
            else {
                rotRight(node, i);
                erase(node->left, key, i);
            }
        }

    }

    else if(key < node->key)
        erase(node->left, key, i);
    else
        erase(node->right, key, i);
    update(node, i);
}

int search(treap *&node, int key, int i) {

    if(node == empty[i])
        return 0;

    if(node->key < key)
        return node->left->total + node->cnt + search(node->right, key, i);

    if(node->key == key)
        return node->left->total + node->cnt;

    return search(node->left, key, i);
}

void split(treap *&root, treap *&lTreap, treap *&rTreap, int key, int i) {

    insert(root, key, INF, 1, i);
    lTreap = root->left;
    rTreap = root->right;
    delete root, root = empty[i];
}

void join(treap *&root, treap *&lTreap, treap *&rTreap, int key, int i) {

    root = new treap(-1, INF, 0, lTreap, rTreap);
    erase(root, -1, i);
}

void init() {

    srand(unsigned(time(0)));
    for(int i = 1; i <= n * 5; ++i) {
        A[i] = B[i] = empty[i] = new treap(0, 0, 0, NULL, NULL), empty[i]->left = empty[i]->right = empty[i];
    }
}

void updateTree(int node, int left, int right, int first, int last, int val) {

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    if(first <= left && right <= last) {

        _insert(B[node], val, getRand(), 1, node);
        _insert(A[node], val, getRand(), right - left + 1, node);
        return;
    }

    int intersection = min(right, last) - max(left, first) + 1;
    _insert(A[node], val, getRand(), intersection, node);

    if(first <= mid)
        updateTree(lSon, left, mid, first, last, val);
    if(mid < last)
        updateTree(rSon, mid + 1, right, first, last, val);
}

void query(int node, int left, int right, int first, int last, int val) {

    if(first <= left && right <= last) {

        q += search(A[node], val, node);
        return;
    }
    int intersection = min(right, last) - max(left, first) + 1;
    q += intersection * search(B[node], val, node);

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    if(first <= mid)
        query(lSon, left, mid, first, last, val);
    if(mid < last)
        query(rSon, mid + 1, right, first, last, val);

}

bool enough(int first, int last, int nr) {

    q = 0;
    query(1, 1, n, first, last, 30001);
    return q >= nr;
}

void b_search(int first, int last, int nr) {

    int left = 1, right = 30000, mid, sol = 1;

    while(left <= right) {

        mid = (left + right) >> 1;
        q = 0;
        query(1, 1, n, first, last, mid);

        if(q >= nr)
            sol = mid, right = mid - 1;
        else
            left = mid + 1;
    }
    printf("%d\n", sol);
}

int main() {

    read(n); read(m);
    init();

    int op, a, b, c;
    for(; m; --m) {

        read(op); read(a); read(b); read(c);
        if(op == 1)
            updateTree(1, 1, n, a + 1, b + 1, c);
        else {
            if( !enough(a + 1, b + 1, c) )
                printf("-1\n");
            else
                b_search(a + 1, b + 1, c);
        }
    }
    return 0;
}
