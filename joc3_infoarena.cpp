// It's not the load that breaks you down, it's the way you carry it!

#include <cstdio>
#define DIM 100100
using namespace std;
FILE *fin=freopen("joc3.in","r",stdin);
FILE *fout=freopen("joc3.out","w",stdout);

int V[DIM];
int n;

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &V[i]);
}

void Solve()
{
    int i, xorsum = 0;

    if((n - 1) % 2 == 1)
        i = 1;
    else
        i = 2;
    for(; i < n; i += 2)
        xorsum ^= V[i];

    if( !xorsum )
    {
        printf("-1\n");
        return;
    }

    if((n - 1) % 2 == 1)
        i = 1;
    else
        i = 2;

    int start = i, val;

    for(i = 1; i < n; i++)
    {
        if( (i - start) % 2 == 0 )
        {
            val = V[i] - (V[i] ^ xorsum);
        }
        else
            val = (V[i + 1] ^ xorsum) - V[i + 1];

        if( 0 < val && val <= V[i] )
        {
            printf("%d %d", i, val); return;
        }
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
