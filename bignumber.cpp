// How about a coding trick?
#include <cstdio>
#define DIM 1000100
#define INF 2000000000
using namespace std;
FILE *fin=freopen("bignumber.in","r",stdin);
FILE *fout=freopen("bignumber.out","w",stdout);

int E[DIM][10], last[10], Sol[DIM], Swaps[DIM], Used[10];
char S[DIM];
int n, x;

void Set()
{
    scanf("%d%d", &n, &x); gets(S);
    gets(S);
    for(int i = 0; i < 10; ++i)
        last[i] = INF;
    int cif, i, j;
    for(i = 0; i < 10; ++i)
        E[n + 1][i] = INF;

    for(i = n; i > 0; --i)
    {
        cif = S[i - 1] - '0';
        last[cif] = i;
        for(j = 0; j < 10; ++j)
            E[i][j] = last[j] - i;
    }
    for(i = 0; i < 10; ++i)
        E[0][i] = E[1][i] + 1;

}

void Solve()
{
    int i, j, swapCount = 0, pos, elem, aux;
    bool ok = 0;

    for(i = 1; i <= n; ++i)
    {
        //if( x )
        for(j = 9; j >= 0; --j)
                if( E[i - 1][j] )
                {
                    E[i][j] = E[i - 1][j] - 1;
                    if( !E[i][j] )
                        elem = j;
                }
        Sol[i] = elem;
        //for(j = 0; j < 10; ++j)
            //printf("%d ", E[i][j]);

        for(j = 9; j > elem; --j)
            if( E[i][j] <= x )
            {
                x -= E[i][j];
                pos = i + E[i][j];
                for(int l = 0; l < 10; ++l)
                    if( E[i][l] + i <= pos)
                        ++E[i][l];

                Sol[i] = j;


                E[i + 1][j] = E[pos + 1][j] + pos - i;
                E[pos][j] = E[pos + 1][j] + 1;
                E[i][j] = E[i + 1][j] + 1;
                break;
            }
        if(j == elem)
        {
            E[i][j] = E[i + 1][j] + 1;
        }
        if( Sol[i] )
            ok = 1;
        //if( ok )
            printf("%d", Sol[i]);
        ++Used[Sol[i]];
        if( !x )
            break;
    }
    //printf("\n");
    int cif;
    for(i = 1; i <= n; ++i)
    {
        cif = S[i - 1] - '0';
        if( !Used[cif] )
            printf("%d", cif);
        else
            --Used[cif];
    }
}

int main()
{
    Set();
    Solve();
    return 0;
}
