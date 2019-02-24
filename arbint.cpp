/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define Dim 4 * 100100
#define buffDim 50500

using namespace std;
FILE *fin=freopen("arbint.in","r",stdin);
FILE *fout=freopen("arbint.out","w",stdout);

int arb[Dim];
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

void query(int node, int left, int right, int first, int last) {

    if(first <= left && right <= last) {
        ans = max(ans, arb[node]);
        return;
    }

    int mid = (left + right) >> 1;
    if(first <= mid)
        query(node * 2, left, mid, first, last);
    if(mid < last)
        query(node * 2 + 1, mid + 1, right, first, last);
}

int main() {

    fread(buff, 1, buffDim, stdin);
    read(n); read(m);

    int x, op, a, b;
    for(int i = 1; i <= n; ++i) {

        read(x);
        update(1, 1, n, i, x);
    }

    for(int i = 1; i <= m; ++i) {

        read(op); read(a); read(b);
        if( !op ) {
            ans = 0;
            query(1, 1, n, a, b);
            printf("%d\n", ans);
        }
        else {
            update(1, 1, n, a, b);
        }
    }

    return 0;
}
