#include <cstdio>
#define Mod 666013
#define Dim 1003
using namespace std;
FILE *fin=freopen("kperms.in","r",stdin);
FILE *fout=freopen("kperms.out","w",stdout);
int A[Dim][Dim], N , K;


int main()
{
    scanf("%d%d", &N , &K);
    A[1][1] = 1;
    for(int i = 2 ; i <= N ; ++i )
        for(int j = 1 ; j <= i ; ++j )
        {
            A[i][j] = 1ll * ( A[i - 1][j] * j ) % Mod;
            A[i][j] = 1ll * ( A[i][j] + A[i - 1][j - 1] * (i - j + 1) ) % Mod;
        }
    printf("%d", A[N][K]);
    return 0;
}
