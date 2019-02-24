/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define Dim 200200 * 3
#define buffDim 50500

using namespace std;
FILE *fin=freopen("maxq.in","r",stdin);
FILE *fout=freopen("maxq.out","w",stdout);

struct{int best, lBest, rBest, sum;} arb[Dim];
long long int ans, S;
int pos, n, m;
char buff[buffDim];

void read(int &nr) {

    char semn = '+';
    while(buff[pos] < '0' || buff[pos] > '9') {

        semn = buff[pos];
        if(++pos == buffDim) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }
    }

    nr = 0;
    while('0' <= buff[pos] && buff[pos] <='9') {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDim) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }
    }
    nr = ((semn == '-')? -nr : nr);
}

void update(int node, int left, int right, int pos, int val) {

    if(left == right) {
        arb[node].best = val, arb[node].lBest = val, arb[node].rBest = val, arb[node].sum = val;
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    if(pos <= mid)
        update(lSon, left, mid, pos, val);
    if(mid < pos)
        update(rSon, mid + 1, right, pos, val);

    arb[node].best = max(max(arb[lSon].best, arb[rSon].best), arb[lSon].rBest + arb[rSon].lBest);
    arb[node].lBest = max(arb[lSon].lBest, arb[lSon].sum + arb[rSon].lBest);
    arb[node].rBest = max(arb[rSon].rBest, arb[rSon].sum + arb[lSon].rBest);
    arb[node].sum = arb[lSon].sum + arb[rSon].sum;
}

void query(int node, int left, int right, int first, int last) {

    if(left > last || right < first)
        return;
    if(first <= left && right <= last) {
        S = max(S, 0LL);
        ans = max(ans, 1LL * max(S + 1LL * arb[node].lBest, 1LL * arb[node].best));
        S = max(S + 1LL * arb[node].sum, 1LL * arb[node].rBest);
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    query(lSon, left, mid, first, last);
    query(rSon, mid + 1, right, first, last);
}

int main() {

    int op, x, y;
    read(n);
    for(int i = 1; i <= n; ++i) {

        read(x);
        update(1, 1, n, i, x);
    }

    read(m);
    for(int i = 1; i <= m; ++i) {

        read(op); read(x); read(y);
        if( !op ) {
            update(1, 1, n, x + 1, y);
        }
        else {
            ans = 0, S = 0;
            query(1, 1, n, x + 1, y + 1);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
