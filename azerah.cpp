#include <cstdio>
#define MOD 1000000007
using namespace std;
FILE *fin=freopen("azerah.in","r",stdin);
FILE *fout=freopen("azerah.out","w",stdout);

inline int F(int x)
{
    if( x >= MOD )
        return x - MOD;
    return x;
}

void Solve()
{
    int n, x, aux_pare, aux_impare, impar = 0, par = 0;
    scanf("%d", &n);

    for(int i = 1; i <= n ; ++i)
    {
        scanf("%d", &x);
        if( x % 2 == 0 )
        {
            impar = F(impar * 2);
            par = F(par * 2 + 1);
        }
        else
        {
            aux_pare = par; aux_impare = impar;
            par = F( par + aux_impare );
            impar = F( impar + aux_pare + 1 );
        }
    }

    printf("%d\n", par);
}

int main()
{
    int t;

    for(scanf("%d", &t); t > 0; --t)
        Solve();

    return 0;
}
