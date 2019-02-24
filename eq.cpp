/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define Dim 100100 * 3
#define buffDim 50500
#define notDigit(c) c < '0' || c > '9'
#define isDigit(c) '0' <= c && c <= '9'
#define inf 1 << 29

using namespace std;
FILE *fin=freopen("eq.in","r",stdin);
FILE *fout=freopen("eq.out","w",stdout);

struct node_info{int Min, Max, trioMin, trioMax, sumMin, sumMax, difMin, difMax;} arb[Dim];
int pos, n, m, high, low, Y, Z;
char buff[buffDim];

void read(int &nr) {

    while(buff[pos] < '0' || buff[pos] > '9')
        if(++pos == buffDim) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }

    nr = 0;
    while(buff[pos] >= '0' && buff[pos] <= '9') {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDim) {

            fread(buff, 1, buffDim, stdin);
            pos = 0;
        }
    }
}

void update(int node, int left, int right, int pos, int val){

    if(pos < left || pos > right)
        return;

    if(left == right) {
        arb[node].Max = arb[node].Min = arb[node].trioMax = arb[node].trioMin = val;
        arb[node].difMax = arb[node].difMin = 0;
        arb[node].sumMax = arb[node].sumMin = 2 * val;
        return;
    }

    int mid = (left + right) >> 1, lSon = (node << 1), rSon = (node << 1) + 1;
    if(pos <= mid)
        update(lSon, left, mid, pos, val);
    else
        update(rSon, mid + 1, right, pos, val);

    arb[node].Max = max(arb[lSon].Max, arb[rSon].Max);
    arb[node].Min = min(arb[lSon].Min, arb[rSon].Min);
    arb[node].difMax = max(max(arb[lSon].difMax, arb[rSon].difMax), arb[lSon].Max - arb[rSon].Min);
    arb[node].difMin = min(min(arb[lSon].difMin, arb[rSon].difMin), arb[lSon].Min - arb[rSon].Max);
    arb[node].sumMax = max(max(arb[lSon].sumMax, arb[rSon].sumMax), arb[lSon].Max + arb[rSon].Max);
    arb[node].sumMin = min(min(arb[lSon].sumMin, arb[rSon].sumMin), arb[lSon].Min + arb[rSon].Min);
    arb[node].trioMax = max(max(arb[lSon].trioMax, arb[rSon].trioMax), max(arb[lSon].sumMax - arb[rSon].Min, arb[lSon].difMax + arb[rSon].Max));
    arb[node].trioMax = max(arb[node].trioMax, arb[lSon].Max + max(arb[lSon].Max, arb[rSon].Max) - arb[rSon].Min);
    arb[node].trioMin = min(min(arb[lSon].trioMin, arb[rSon].trioMin), min(arb[lSon].sumMin - arb[rSon].Max, arb[lSon].difMin + arb[rSon].Min));
    arb[node].trioMin = min(arb[node].trioMin, arb[lSon].Min + min(arb[lSon].Min, arb[rSon].Min) - arb[rSon].Max);
}

void query(int node, int left, int right, int first, int last) {

    if(left > last || right < first)
        return;

    if(first <= left && right <= last) {

        if(high == -inf) {
            Y = arb[node].trioMax, Z = arb[node].trioMin;
            high = arb[node].Max, low = arb[node].Min;
            return;
        }
        Y = max(max(Y, arb[node].Max + high - low), max(arb[node].sumMax - low, arb[node].difMax + high));
        Y = max(Y, arb[node].trioMax);
        Z = min(min(Z, arb[node].Min + low - high), min(arb[node].sumMin - high, arb[node].difMin + low));
        Z = min(Z, arb[node].trioMin);
        high = max(high, arb[node].Max), low = min(low, arb[node].Min);
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    if(mid < last)
        query(rSon, mid + 1, right, first, last);
    if(first <= mid)
        query(lSon, left, mid, first, last);
}

int main() {

    fread(buff, 1, buffDim, stdin);
    int x, y;
    read(n); read(m);
    for(int i = 1; i <= n; ++i) {

        read(x);
        update(1, 1, n, i, x);
    }

    for(int i = 1; i <= m; ++i) {

        read(x); read(y);
        Y = -inf, Z = inf, high = -inf, low = inf;
        query(1, 1, n, x, y);
        printf("%d\n", Y + Z);
    }

    return 0;
}
