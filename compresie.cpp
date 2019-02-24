/**
  *  Worg
  */
#include <cmath>
#include <cstring>
#include <cstdio>

#define DIM 1023

using namespace std;
FILE *fin=freopen("compresie.in","r",stdin);
FILE *fout=freopen("compresie.out","w",stdout);

int len, pos, imp, n;

char A[DIM][DIM], S[DIM * DIM];

void buildMatrix(int x1, int y1, int x2, int y2) {
    int i, j, xm, ym;

    if( x1 <= x2 && y1 <= y2 && pos < len ) {

        if( '0' <= S[pos] && S[pos] <= '9' ) {
            while( '0' <= S[pos] && S[pos] <= '9' )
                ++pos;

            for(i = x1; i <= x2; ++i)
                for(j = y1; j <= y2; ++j)
                    A[i][j] = S[pos];
            ++pos;
        }

        else if( 'a' <= S[pos] && S[pos] <= 'z' )
            A[x1][y1] = S[pos++];

        else {
            xm = (x1 + x2) / 2;
            ym = (y1 + y2) / 2;
            ++pos;

            buildMatrix(x1, y1, xm, ym);
            buildMatrix(x1, ym + 1, xm, y2);
            buildMatrix(xm + 1, y1, x2, ym);
            buildMatrix(xm + 1, ym + 1, x2, y2);
        }

    }
}

int main() {
    gets(S); len = strlen(S);

    for(pos = 0; pos < len; ++pos)
        imp += (S[pos] == '*');
    printf("%d\n", imp);

    int nr = 0, aux;
    for(pos = 0; pos < len; ++pos) {
        if( 'a' <= S[pos] && S[pos] <= 'z' )
            ++nr;

        else if( '0' <= S[pos] && S[pos] <= '9' ) {
            aux = S[pos++] - '0';
            while( pos < len && ( '0' <= S[pos] && S[pos] <= '9' ) )
                aux = aux * 10 + S[pos++] - '0';
            nr += aux;
        }
    }
    n = sqrt((double)nr);

    pos = 0;
    buildMatrix(1, 1, n, n);

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            printf("%c", A[i][j]);
        printf("\n");
    }

    return 0;
}
