/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

#define Dim 100100 * 4
#define buffDim 50500

using namespace std;
FILE *fin=freopen("hotel.in","r",stdin);
FILE *fout=freopen("hotel.out","w",stdout);

struct {int left, right, best;} arb[Dim];
int pos, n, p;
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

void lazy_update(int node, int L, int R, int first, int last, int val) {

    if(last < L || R < first)
        return;

    if(first <= L && R <= last) {  //if the segment is fully in range

        if(val == 1)
            arb[node].best = arb[node].left = arb[node].right = 0;
        else
            arb[node].best = arb[node].left = arb[node].right = R - L + 1;
        return;
    }

    int lSon = node * 2, rSon = node * 2 + 1, mid = (L + R) >> 1;

    if(arb[node].best == 0) {   //if the segment is fully occupied, update the sons
        arb[lSon].best = arb[lSon].left = arb[lSon].right = 0;
        arb[rSon].best = arb[rSon].left = arb[rSon].right = 0;
    }
    else if(arb[node].best == R - L + 1) {  //if the segment is empty, update the sons
        arb[lSon].best = arb[lSon].left = arb[lSon].right = mid - L + 1;
        arb[rSon].best = arb[rSon].left = arb[rSon].right = R - mid;
    }

    lazy_update(lSon, L, mid, first, last, val);
    lazy_update(rSon, mid + 1, R, first, last, val);

    arb[node].left = arb[lSon].left + ((arb[lSon].left == mid - L + 1) ? arb[rSon].left : 0);
    arb[node].right = arb[rSon].right + ((arb[rSon].right == R - mid) ? arb[lSon].right : 0);

    arb[node].best = max(max(arb[lSon].best, arb[rSon].best), arb[lSon].right + arb[rSon].left);
}

int main() {

    read(n); read(p);
    lazy_update(1, 1, n, 1, n, 2);

    int op, a, b;
    for(int i = 1; i <= p; ++i) {

        read(op);
        if( op == 1 || op == 2 ) {
            read(a); read(b);
            b += a - 1;
            lazy_update(1, 1, n, a, b, op);
        }
        else
            printf("%d\n", arb[1].best);
    }
}
