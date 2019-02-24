#include <cstdio>
#include <algorithm>

using namespace std;

FILE *fin=freopen("hacker3.in","r",stdin);
FILE *fout=freopen("hacker3.out","w",stdout);

long long int Dynamic[44], Summin, A[10003], B[10003], maxim = 50, P2[69];

long long int Min(long long int x, long long int y)
{
    if( x < y )
        return 1LL * x;
    return 1LL * y;
}

int main()
{
    long long int n, a, b, i, j, aux;
    scanf("%lld", &n);

    if( n < 100 )
    {
        for( i = 1; i <= n ; ++i )
            scanf("%lld%lld", &A[i], &B[i]);

        long long int Sum = 0;

        for( i = n ; i > 0 ; --i )
        {
            if( A[i] + Sum * 2 < B[i] + Sum )
                Sum = 2 * Sum + A[i];
            else
                Sum += B[i];
        }

        printf("%lld", Sum);

        return 0;
    }

    P2[0] = 1;

    for(i = 1 ; i <= 62 ; ++i )
        P2[i] = P2[i - 1] * 2;

    for(i = 1 ; i <= n ; ++i )
    {
        scanf("%lld%lld", &a, &b);
        maxim = i;
        for( j = Min(35,i); j >= 1 ; --j )
        {
             aux = 0;

            if( a <= P2[62 - j - 1] )
                aux = Dynamic[j - 1] + 1LL * a * P2[j - 1];

            if( b <= P2[62 - j] )
                aux = Min(aux , Dynamic[j] + 1LL * b * P2[j]);

            if( !aux )
                maxim = j - 1;
            else
                Dynamic[j] = aux;
        }

        Dynamic[0] += b;
    }

    Summin = Dynamic[0];

    for(int i = 0 ; i <= Min(35, maxim) ; ++i )
        if( Dynamic[i] < Summin && Dynamic[i] != 0 )
            Summin = Dynamic[i];

    printf("%lld", Summin);

    return 0;
}

