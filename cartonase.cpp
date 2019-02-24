#include <cstdio>
using namespace std;
FILE *fin=freopen("cartonase.in","r",stdin);
FILE *fout=freopen("cartonase.out","w",stdout);

void Solve()
{
    int n, xorsum = 0;
    char c;
    scanf("%d ", &n);

    for(int i = 1; i <= n; ++i)
    {
        scanf("%c ", &c);
        if( c == 'R' )
            xorsum ^= i;
    }
    if( xorsum )
        printf("DA\n");
    else
        printf("NU\n");
}

int main()
{
    int teste;
    for(scanf("%d", &teste); teste > 0; --teste)
        Solve();
    return 0;
}
