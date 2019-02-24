/*
    How about a coding trick?
*/
#include <cstdio>
#define MOD 100003
#define coef 29
#define DIM 2020
using namespace std;
FILE *fin=freopen("map.in","r",stdin);
FILE *fout=freopen("map.out","w",stdout);

int hash[DIM], reversed_hash[DIM];
char S[DIM][DIM];
int n, m;

void Read()
{
    int i;
    scanf("%d %d ", &n, &m);

    for(i = 1; i <= n; ++i)
        gets(S[i]);
}

inline bool check()
{
    for(int i = 1; i <= n; ++i)
        if( hash[i] != reversed_hash[i] )
            return 0;
    return 1;
}

int main()
{
    Read();
    int val = 1, i, j, col, dcol;

    for(i = 1; i <= n; ++i)
        hash[i] = S[i][0] - 'a' ;

    for(j = 1; j < m / 2 + 1; ++j)
    {
        val = (val * coef) % MOD;
        for(i = 1; i <= n; ++i)
            hash[i] = ( hash[i] + val * (S[i][j] - 'a') )  % MOD;
    }

    for(j = 0, col = m - 1; j < m / 2 + 1; ++j, --col)
    {
        for(i = 1; i <= n; ++i)
            reversed_hash[i] = (reversed_hash[i] * coef + S[i][col] - 'a') % MOD;
    }
    dcol = m / 2 + 1;

    while( !check() )
    {
        val = (val * coef) % MOD;
        for(i = 1; i <= n; ++i)
            hash[i] = ( hash[i] + val * (S[i][dcol] - 'a') ) % MOD;
        for(i = 1; i <= n; ++i)
            reversed_hash[i] = (reversed_hash[i] * coef + S[i][col] - 'a') % MOD;
        --col, ++dcol;
    }
    printf("%d ", dcol);
    return 0;
}
