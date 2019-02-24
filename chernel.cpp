#include <cstdio>
using namespace std;

FILE *fin=freopen("chernel.in","r",stdin);
FILE *fout=freopen("chernel.out","w",stdout);

int m, n;
int P[20], F[20], k, N[20];

void Prime_Divisors()
{
    int M;
    M = m;

    for(int i = 2; i * i <= m && i <= M ; ++i)
        if( M % i == 0 )
        {
            P[++k] = i;
            while(M % i == 0)
            {
                M /= i;
                ++F[k];
            }
        }

    if( M > 1 )
    {
        P[++k] = M;
        F[k] = 1;
    }

}

void Solve()
{
    int cnt = 0, val1, val2, i, j, aux, ok;

    if(m == 1)
    {
        printf("%d",n);
        return;
    }

    for(i = 2, val1 = n - 1, val2 = 1; i <= n; ++i, --val1, ++val2)
    {
        aux = val1;
        for(j = 1; j <= k ; ++j)
            while( aux % P[j] == 0 )
            {
                ++N[j];
                aux /= P[j];
            }

        aux = val2;
        for(j = 1; j <= k ; ++j)
            while( aux % P[j] == 0 )
            {
                --N[j];
                aux /= P[j];
            }
        ok = 1;
        for(j = 1; j <= k ; ++j)
            if( N[j] < F[j] )
                ok = 0;

        if(ok)
            ++cnt;

    }

    printf("%d",cnt);
}

int main()
{
    scanf("%d %d", &n, &m);
    Prime_Divisors();
    Solve();
}
