#include <cstdio>
#define MaxN 500013
#define MaxK 100013

using namespace std;

FILE *fin=freopen("divk.in","r",stdin);
FILE *fout=freopen("divk.out","w",stdout);

long long int Sum[MaxN], F[MaxK];
long long int n, k, a, b, cnt;


void Read()
{
    scanf("%lld%lld%lld%lld", &n, &k, &a, &b);

    int x;
    for(int i = 1;  i <= n ; ++i )
    {
        scanf("%lld", &x);
        Sum[i] = Sum[i - 1] + x;
        Sum[i] %= k;
    }
}

void Solve_Dynamic()
{
    for(int i = 1 ; i <= n ; ++i )
    {
        if( i >= a )
            ++F[Sum[i - a]];
        if( i > b )
            --F[Sum[i - b - 1]];
        cnt += F[Sum[i]];
    }
    printf("%lld", cnt);
}

int main()
{
    Read();
    Solve_Dynamic();
    return 0;
}
