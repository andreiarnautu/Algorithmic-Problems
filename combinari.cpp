#include <cstdio>
using namespace std;
FILE *fin=freopen("combinari.in","r",stdin);
FILE *fout=freopen("combinari.out","w",stdout);

int n, k;
int V[20];

void Write()
{
    for(int i = 1; i <= k; ++i)
        printf("%d ", V[i]);
    printf("\n");
}

void Gen(int nr)
{
    if( nr == k )
        Write();
    else
    {
        for(int i = V[nr] + 1; i <= n - (k - nr - 1)  ; ++i)
        {
            V[nr + 1] = i; Gen(nr + 1);
        }
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    Gen(0);
    return 0;
}
