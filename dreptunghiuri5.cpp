#include <cstdio>
#include <stack>
#define DIM 1003
using namespace std;
FILE *fin=freopen("dreptunghiuri5.in","r",stdin);
FILE *fout=freopen("dreptunghiuri5.out","w",stdout);

int A[DIM][DIM], Sum[DIM][DIM];
int m, n;
stack <int> St;
stack <bool> OK;

void Read()
{
    int x;
    scanf("%d %d ", &n, &m);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
        {
            scanf("%d", &x);
            if( !x )
                Sum[i][j] = 1 + Sum[i - 1][j];
        }
}

void Solve()
{
    int i, j, ansCount = 0, verif;

    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= m; ++j)
        {
            verif = 0;
            while( !St.empty() && Sum[i][j] < St.top() )
            {
                if( OK.top() == 1 || verif )
                {
                    ++ansCount;
                    verif = 1;
                }
                OK.pop(); St.pop();
            }

            if( !Sum[i][j] )
                continue;

            if( St.empty() )
            {
                St.push( Sum[i][j] );
                if( Sum[i][j] + 1 != Sum[i + 1][j] || verif )
                    OK.push(1);
                else
                    OK.push(0);
            }

            else
            {
                if( St.top() == Sum[i][j] )
                {
                    if( Sum[i][j] + 1 != Sum[i + 1][j] || verif )
                        OK.top() = 1;
                }

                else
                {
                    St.push( Sum[i][j] );
                    if( Sum[i][j] + 1 != Sum[i + 1][j] || verif )
                        OK.push(1);
                    else
                        OK.push(0);
                }
            }
        }

        verif = 0;
        while( !St.empty() )
        {
            if( OK.top() == 1 || verif )
            {
                ++ansCount;
                verif = 1;
            }
            OK.pop(); St.pop();
        }
    }

    printf("%d", ansCount);
}

int main()
{
    Read();
    Solve();
    return 0;
}
