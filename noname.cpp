// How about a coding trick?
#include <cstdio>
#include <bitset>
#define DIM 1010
using namespace std;
FILE *fin=freopen("noname.in","r",stdin);
FILE *fout=freopen("noname.out","w",stdout);

bitset <DIM> OK[DIM], Sol[DIM];
int lin[DIM], col[DIM];
int n;

void Read()
{
    int i, x;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        lin[x] = i;
    }
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        col[x] = i;
    }
}

void Solve()
{
    int i, j, last = 1, dr = n, st = 1;
    for(i = 1; i <= n; ++i)
    {
        if(last)
        {
            for(j = 1; j <= n; ++j)
                if( !OK[lin[dr]][j] )
                    OK[lin[dr]][j] = 1, Sol[lin[dr]][j] = 1;

            for(j = 1; j <= n; ++j)
                if( !OK[j][col[dr]] )
                    OK[j][col[dr]] = 1, Sol[j][col[dr]] = 1;
            --dr;
        }
        else
        {
            for(j = 1; j <= n; ++j)
                if( !OK[lin[st]][j] )
                    OK[lin[st]][j] = 1;

            for(j = 1; j <= n; ++j)
                if( !OK[j][col[st]] )
                    OK[j][col[st]] = 1;
            ++st;
        }
        last ^= 1;
    }

    printf("1\n");
    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= n; ++j)
            {
                if( Sol[i][j] == 1 )
                    printf("1 ");
                else
                    printf("0 ");
            }
        printf("\n");
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
