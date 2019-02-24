/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

using namespace std;
FILE *fin=freopen("mxl.in","r",stdin);
FILE *fout=freopen("mxl.out","w",stdout);

int n, k;
char S[41][41][256], *aux;
long long int sol[41][41];

long long int eval(char *s);
long long int term(char *s);
void build(int x, int y);

void read_data() {

    scanf("%d %d", &n, &k);

    int x, y;
    for(int i = 1; i <= k; ++i) {

        scanf("%d %d ", &x, &y);
        gets( S[x][y] );
    }

}

long long int eval(char *s) {
    long long int ret = term(s);
    s = aux;

    while( *s == '+' ) {
        ++s;
        ret += term(s);
        s = aux;
    }

    return ret;
}

long long int term(char *s) {
    long long int ret = 0, x = 0, a;

    while('0' <= *s && *s <= '9') {
        x = x * 10 + *s - '0';
        ++s;
    }

    if( *s == ':' ) {
        a = x, ++s, x = 0;

        while('0' <= *s && *s <= '9') {
            x = x * 10 + *s - '0';
            ++s;
        }

        if( !sol[a][x] )
            build(a, x);

        ret = sol[a][x];
    }

    else
        ret = x;

    aux = s;

    return ret;
}

void build(int x, int y) {

    if( !S[x][y][0] )
        return;

    char *s = S[x][y] + ( S[x][y][0] == '=' );

    sol[x][y] = eval(s);
}

int main() {

    read_data();

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if( !sol[i][j] )
                build(i, j);

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            printf("%lld ", sol[i][j]);
        printf("\n");
    }

    return 0;
}
