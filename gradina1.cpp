#include <cstdio>
using namespace std;
FILE *fin=freopen("gradina1.in","r",stdin);
FILE *fout=freopen("gradina1.out","w",stdout);
int N,K;
long P,A[1001][1001];
void Read()
{
    int x,y;
    scanf("%d%d%d",&N,&P,&K);
    for(long i=0; i<P ; ++i)
    {
        scanf("%d%d",&x,&y);
        A[x][y]=1;
    }
}
void Solve()
{
    long nr,Max=0,sol=0;
    for(long i=1; i<=N ; ++i)
        for(long j=1; j<=N ; ++j)
            A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1] ;
    for(long i=K; i<=N ; ++i)
        for(long j=K; j<=N ; ++j)
        {
            nr = A[i][j] - A[i-K][j] - A[i][j-K] + A[i-K][j-K];
            if( nr > Max )
            {
                sol = 1 ;
                Max = nr ;
            }
            else if( nr == Max)
                ++sol;
        }
    printf("%d\n%d",Max,sol);
}
int main()
{
    Read();
    Solve();
    return 0;
}
