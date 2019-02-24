/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin=freopen("banda.in","r",stdin);
FILE *fout=freopen("banda.out","w",stdout);

int n, nr;
bool move[33];

int getPosition(int lin, int col, int k, int x, int lat) {
    if( x == 0 )
        return lin;

    if( k > (1 << (x - 1)) && col > (1 << (x - 1)) )
        return getPosition(lin + lat, col - (1 << (x - 1)), k - (1 << (x - 1)), x - 1, lat * 2);

    if( k > (1 << (x - 1)) && col <= (1 << (x - 1)) )
        return getPosition(lat - lin + 1, (1 << (x - 1)) - col + 1, k - (1 << (x - 1)), x - 1, lat * 2);

    if( k <= (1 << (x - 1)) && col > (1 << (x - 1)) )
        return getPosition(lat - lin + 1, (1 << x) - col + 1, k, x - 1, lat * 2);

    return getPosition(lin + lat, col, k, x - 1, lat * 2);

}

void getMoves(int x, int k) {
    if( !x )
        return;

    if( k > (1 << (x - 1)) ) {
        move[ ++nr ] = 1;
        getMoves(x - 1, k - (1 << (x - 1)) );
    }

    else {
        move[ ++nr ] = 0;
        getMoves(x - 1, k);
    }
}

int getNumber(int lin, int col, int x, int lg, int lat) {
    if( !x )
        return col;

    if( move[x] == 1 && lin > lg / 2 )
        return getNumber(lin - lg / 2, col + lat, x - 1, lg / 2, lat * 2);

    if( move[x] == 1 && lin <= lg / 2 )
        return getNumber(lg / 2 - lin + 1, lat - col + 1, x - 1, lg / 2, lat * 2);

    if( move[x] == 0 && lin > lg / 2 )
        return getNumber(lin - lg / 2, col, x - 1, lg / 2, lat * 2);

    return getNumber(lg / 2 - lin + 1, 2 * lat - col + 1, x - 1, lg / 2, lat * 2);
}

int main() {
    int op, pos, k;
    scanf("%d %d %d %d", &n, &k, &op, &pos);

    if( op == 1 )
        printf("%d", (1 << n) - getPosition(1, pos, k, n, 1) + 1);

    else {
        getMoves(n, k);
        pos =  (1 << n) - pos + 1;
        printf("%d", getNumber(pos, 1, n, 1 << n, 1));
    }
}
