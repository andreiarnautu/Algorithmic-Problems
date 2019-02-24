#include <cstdio>
#include <algorithm>
#include <cstring>
#define Smax 32641
#define Mod 194767
using namespace std;

FILE *fin=freopen("1-sir.in","r",stdin);
FILE *fout=freopen("1-sir.out","w",stdout);

int N, S, A[2][Smax], Max;


int main()
{
    scanf("%d%d", &N, &S);
    A[0][0] = 1;
    S = abs( S );
    Max = N * (N - 1) / 2;

    for(int i = 2 ; i <= N ; ++i )
    {
        for(int j = 0 ; j <= i * (i - 1) / 2 ; ++j )
            A[1][j] = ( A[0][abs(j - i + 1)] + A[0][abs(j + i - 1)] ) % Mod;
        memcpy( A[0] , A[1], sizeof(A[0]) );
    }

    printf("%d", A[1][S] );

    return 0;
}
