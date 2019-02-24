#include <cstdio>
#define Nmax 501
using namespace std;
FILE *fin=freopen("magicmatrix.in","r",stdin);
FILE *fout=freopen("magicmatrix.out","w",stdout);
int T, N, A[Nmax][Nmax];

void Solve()
{
    int i, j;
    scanf("%d", &N);
    for( i = 1 ; i <= N ; ++i )
        for( j = 1 ; j <= N ; ++j )
            scanf("%d", &A[i][j]);
    for( i = 1 ; i < N ; ++i )
        for( j = 1 ; j < N ; ++j )
            if( A[i][j] + A[i + 1][j + 1] != A[i + 1][j] + A[i][j + 1] )
            {
                printf("NO\n");
                return;
            }
    printf("YES\n");
}

int main()
{
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
        Solve();
}
