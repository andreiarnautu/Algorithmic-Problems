#include <cstdio>
#define MaxN 1000013
#define Mod 2011

using namespace std;

FILE *fin=freopen("minusk.in","r",stdin);
FILE *fout=freopen("minusk.out","w",stdout);

int N, K;
int Plus[MaxN], Minus[MaxN];


int main()
{
    scanf("%d%d", &N, &K);

    if( K == 1 )
    {
        printf("1");
        return 0;
    }

    Plus[1] = Minus[1] = 1;
    Minus[0] = Plus[0] = 1;

    for(int i = 2 ; i <= N ; ++i )
    {
        Plus[i] = ( Minus[i - 1] + Plus[i - 1] ) % Mod;

        if( i >= K )
            Minus[i] = ( Minus[i - 1] + Plus[i - 1] - Plus[i - K] );

        else
            Minus[i] = Plus[i];

        if( Minus[i] < 0 )
            Minus[i] += Mod;

        else
            Minus[i] = Minus[i] % Mod;
    }

    printf("%d", (Minus[N] + Plus[N]) % Mod );

    return 0;
}
