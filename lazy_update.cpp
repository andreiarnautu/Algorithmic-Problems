/**
  *  Worg
  *  Lazy update/propagation algorithm
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

#define Dim 4 * 100100
#define buffDim 50500

using namespace std;
FILE *fin=freopen("arbint.in","r",stdin);
FILE *fout=freopen("arbint.out","w",stdout);

int arb[Dim], lazy[Dim];
int pos, n, m, ans;
char buff[buffDim];

void read(int &nr) {

    while( buff[pos] < '0' || buff[pos] > '9' )
        if( ++pos == buffDim ) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }

    nr = 0;
    while( buff[pos] >= '0' && buff[pos] <= '9' ) {

        nr = nr * 10 + buff[pos] - '0';
        if( ++pos == buffDim ) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }
    }
}

void update(int node, int left, int right, int pos, int val) {

    if( left == right ) {
        arb[node] = val;
        return;
    }

    int mid = (left + right) >> 1;
    if( pos <= mid )
        update(node * 2, left, mid, pos, val);
    else
        update(node * 2 + 1, mid + 1, right, pos, val);

    arb[node] = max(arb[2 * node], arb[2 * node + 1]);
}

void build_tree() {

    read(n); read(m);
    int x;
    for(int i = 1; i <= n; ++i) {

        read(x);
        update(1, 1, n, i, x);
    }
}

int verif(int node) {

    return ((lazy[node] == -1) ? arb[node] : lazy[node]);
}

void lazy_update(int node, int left, int right, int first, int last, int val) {

    if(first <= left && right <= last) { // if the segment is fully in range
        lazy[node] = val;
        return;
    }

    if(lazy[node] != -1) {              // if it's not fully in range but it needs to be updated
        lazy[node * 2] = lazy[node * 2 + 1] = arb[node] = lazy[node];
        lazy[node] = -1;
    }

    int mid = (left + right) >> 1;
    if(first <= mid)
        lazy_update(node * 2, left, mid, first, last, val);
    if(mid < last)
        lazy_update(node * 2 + 1, mid + 1, right, first, last, val);

    arb[node] = max(verif(node * 2), verif(node * 2 + 1));
}

void query(int node, int left, int right, int first, int last) {

    if(first <= left && right <= last) {
        ans = max(ans, verif(node));
        return;
    }

    if(lazy[node] != -1) {
        lazy[node * 2] = lazy[node * 2 + 1] = arb[node] = lazy[node];
        lazy[node] = -1;
    }

    int mid = (left + right) >> 1;
    if(first <= mid)
        query(node * 2, left, mid, first, last);
    if(mid < last)
        query(node * 2 + 1, mid + 1, right, first, last);
}

int main() {

    build_tree(); memset(lazy, -1, sizeof(lazy));

    int op, a, b;
    for(int i = 1; i <= m; ++i) {

        read(op); read(a); read(b);
        if( !op ) {
            ans = 0;
            query(1, 1, n, a, b);
            printf("%d\n", ans);
        }
        if( op ) {
            lazy_update(1, 1, n, a, a, b);
        }
    }
    return 0;
}
