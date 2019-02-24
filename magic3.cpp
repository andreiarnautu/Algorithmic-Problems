// Algoritmiada 2014 etapa finala
#include <cstdio>
using namespace std;

FILE *fin=freopen("magic3.in","r",stdin);
FILE *fout=freopen("magic3.out","w",stdout);


int Log(int k)
{
    int p = 0;
    while( k > 1 )
    {
        k /= 2;
        ++p;
    }
    return p;
}

void Easy_Way(int A, int B)
{
    int k, r, Steps;
    if( A % B == 0 )
    {
        k = A / B;
        Steps = k - 2;
        if( ((2 * B) & (2 * B - 1)) == 0 )
            Steps += Log( 2 * B );
        else
            Steps += Log( 2 * B ) + 1;
    }
    else
    {
        k = A / B;
        r = A % B;
        Steps = k - 1;
        if( ((r + B) & (r + B - 1)) == 0 )
            Steps += Log( B + r ) ;
        else
            Steps += Log( B + r ) + 1;
    }
    printf("%d\n", Steps);
}

int Half(int x)
{
    if( x % 2 == 0 )
        return x / 2;
    return x / 2 + 1;
}


int main()
{
    int T, N, K;
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
    {
        scanf("%d%d", &N, &K);
        if( N - K < K )
            K = N - K;
        Easy_Way(N , K);
    }
}
