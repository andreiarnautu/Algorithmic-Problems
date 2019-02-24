/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define Dim 430000
#define buffDim 50500
#define i64 long long int


#define inf 100000000000000

using namespace std;
FILE *fin=freopen("biscuiti.in","r",stdin);
FILE *fout=freopen("biscuiti.out","w",stdout);

struct {i64 best;int p;} arb[Dim];
i64 lazy[Dim];
int pos, n, maxnode;
char buff[buffDim];

void read(int &nr) {

    while(buff[pos] < '0' || buff[pos] > '9')
        if(++pos == buffDim) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }

    nr = 0;
    while(buff[pos] >= '0' && '9' >= buff[pos]) {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDim) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }
    }
}

void lazy_update(int node, int left, int right, int first, int last, i64 val) {

    maxnode = max(maxnode, node);
    if(left == right)
        arb[node].p = left;
    int lSon = node * 2, rSon = node * 2 + 1;
    if( lazy[node] ) {          //if it needs to be updated
        if(left != right) {
                lazy[lSon] += lazy[node];
                lazy[rSon] += lazy[node];
        }
        arb[node].best += lazy[node];
        lazy[node] = 0;
    }
    if(first > right || left > last)
        return;

    if(first <= left && right <= last) {    // if the segment is fully in range
        arb[node].best += val;
        if(left != right) {
            lazy[lSon] += val;
            lazy[rSon] += val;
        }
        return;
    }

    int mid = (left + right) >> 1;
    if(first <= mid)
        lazy_update(lSon, left, mid, first, last, val);
    if(mid < last)
        lazy_update(rSon, mid + 1, right, first, last, val);

    i64 q1, q2;

    q1 = arb[lSon].best, q2 = arb[rSon].best;
    if(q1 <= q2)
        arb[node].best = arb[lSon].best, arb[node].p = arb[lSon].p;
    else
        arb[node].best = arb[rSon].best, arb[node].p = arb[rSon].p;
}

int main() {

    int x;
    i64 before = 0, after = 0;
    int P;
    fread(buff, 1, buffDim, stdin);

    read(n);
    for(int i = 1; i <= n; ++i) {

        read(x);
        before += 1LL * x;
        lazy_update(1, 1, n, i, i, 1LL * x);
    }

    for(int i = 1; i <= n; ++i) {

        after += arb[1].best;
        P = arb[1].p;
        lazy_update(1, 1, n, 1, P - 1, 1LL * i);
        lazy_update(1, 1, n, P, P, inf);
    }

    printf("%lld", after - before);
    printf(" %d", maxnode);
    return 0;
}
