#include <cstdio>
using namespace std;
FILE *fin=freopen("lacusta.in","r",stdin);
FILE *fout=freopen("lacusta.out","w",stdout);
int M, N, A[260][260], B[260][260];

void Read()
{
    scanf("%d%d",&M,&N);
    for(int i=0; i<M ; ++i)
        for(int j=0; j<N ; ++j)
            scanf("%d",&A[i][j]);
    B[1][0] = 50000;
}

void Solve()
{
    int Min1, Min2, Jmin;
    for(int i=1; i<N ; ++i)
        B[1][i] = A[0][0] + A[0][i] + A[1][i];
    for(int i=1; i<M-1 ; ++i)
    {
        if( B[i][0] <= B[i][1])
        {
            Min1 = B[i][0];
            Min2 = B[i][1];
            Jmin = 0;
        }
        else
        {
            Min1 = B[i][1];
            Min2 = B[i][0];
            Jmin = 1;
        }
        for(int j=2; j<N ; ++j)
        {
            if( B[i][j] < Min1 )
            {
                Min2 = Min1;
                Min1 = B[i][j];
                Jmin = j;
            }
            else if( B[i][j] < Min2 )
                Min2 = B[i][j];
        }
        for(int j=0; j<N ; ++j)
        {
            if( j != Jmin )
                B[i+1][j] = Min1 + A[i+1][j] + A[i][j];
            else
                B[i+1][j] = Min2 + A[i+1][j] + A[i][j];
        }
    }
    Min1 = B[M-1][0];
    for(int j=1; j<N ; ++j)
        if( B[M-1][j] < Min1 )
            Min1 = B[M-1][j];
    printf("%d\n", Min1 + A[M-1][N-1] );
}

int main()
{
    Read();
    Solve();
    return 0;
}
