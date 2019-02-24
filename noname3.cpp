#include <cstdio>
using namespace std;

FILE *fin = freopen("noname3.in","r", stdin);
FILE *fout = freopen("noname3.out","w",stdout);

long long int N, S;


int main()
{
    long long int Sum, Buff = 0, x;
    scanf("%lld%lld", &N, &S);

    x = N * ( N + 1 ) / 2;
    if( x > S )
    {
        printf("-1");
        return 0;
    }

    if( N * (N + 1) / 2 == S )
    {
        for(int i = 1; i <= N ; ++i )
            printf("%d ", i);
        return 0;
    }

    Sum = N * (N - 1) / 2;
    S -= Sum;

    x = S / N;
    S -= N * x;
    printf("%lld ",x);

    for(int i = 2 ; i < N ; ++i )
    {
        if( N - i + 1 <= S )
        {
            ++Buff;
            S -= (N - i + 1);
        }
        printf("%lld ", x + i - 1 + Buff);
    }

    printf("%lld", x + N - 1 + Buff + S);
    return 0;
}
