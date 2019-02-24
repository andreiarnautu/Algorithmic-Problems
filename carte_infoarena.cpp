/**
  *  Worg
  */
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>

#define DIM 3030

using namespace std;
FILE *fin=freopen("carte.in","r",stdin);
FILE *fout=freopen("carte.out","w",stdout);

bitset < DIM > O[DIM];
char S[DIM], B[DIM];
int pi[DIM], DP[DIM];

void Prefix()                           // construct "pi" array
{
    int i, k = 0, lg = strlen(B + 1);
    for(i = 2; i <= lg; ++i)
    {
        while( k && B[i] != B[k + 1] )
            k = pi[k];
        if( B[i] == B[k + 1] )
            ++k;
        pi[i] = k;
    }
    pi[lg + 1] = 0;
}

void Solve()
{
    int i, len, d = 0, n, j, lg;            // we use dynamic programming
                                            // O[i][j] = 1 just if we have a word matching the caracters between positions
                                            //           i and j
                                            // DP[i] = the minimum cost of the first i caracters of the string
    gets( S + 1 ); len = strlen(S + 1);
    scanf("%d ", &n);
    for(i = 1; i <= n; ++i)
    {
        gets(B + 1); lg = strlen(B + 1);
        Prefix(); d = 0;
        for(j = 1; j <= len; ++j)
        {
            while( d && S[j] != B[d + 1] )
                d = pi[d];
            if( S[j] == B[d + 1] )
                ++d;
            if( d == lg )
                O[j - lg + 1][j] = 1;
        }
    }

    for(i = 1; i <= len; ++i)
    {
        DP[i] = DP[i - 1] + 1;
        for(j = i; j > 0; --j)
            if( O[j][i] )
                DP[i] = min( DP[i], DP[j - 1] );
    }
    printf("%d\n", DP[len]);

    for(i = 1; i <= len; ++i)
        for(j = i; j <= len; ++j)
            O[i][j] = 0;
}

int main()
{
    int teste;
    for(scanf("%d ", &teste); teste; --teste)
        Solve();
}
