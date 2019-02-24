#include <cstdio>
#include <algorithm>
#define Nmax 1001
using namespace std;
FILE *fin=freopen("custi.in","r",stdin);
FILE *fout=freopen("custi.out","w",stdout);
int N;
short A[Nmax][Nmax], Lin[Nmax][Nmax], Col[Nmax][Nmax], R[Nmax][Nmax];
int F[Nmax];

void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
        {
            scanf("%d", &A[i][j]);
            if( A[i][j] == 1 )
            {
                Lin[i][j] = Lin[i][j - 1];
                Col[i][j] = Col[i - 1][j];
            }
            else
            {
                Lin[i][j] = j;
                Col[i][j] = i;
            }
        }
}

void Solve()
{
    int x, y, k;
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1; j <= N ; ++j )
        {
            x = Lin[i][j];
            y = Col[i][j];
            k = min( j - x , i - y );
            if( R[i - 1][j - 1] + 1 < k )
                k = R[i - 1][j - 1] + 1;
            R[i][j] = k;
            ++F[k];
        }
    for(int i = N - 1 ; i > 0 ; --i )
        F[i] += F[i + 1];
    for(int i = 1 ; i <= N ; ++i )
        printf("%d\n", F[i]);
}

int main()
{
    Read();
   Solve();
    return 0;
}
