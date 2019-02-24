#include <cstdio>
using namespace std;
FILE *fin=freopen("el.in","r",stdin);
FILE *fout=freopen("el.out","w",stdout);
int M, N, V[201][201], O[201][201];
void Read()
{
    int x;
    scanf("%d%d",&M,&N);
    for(int i=1; i<=M ; ++i)
        for(int j=1; j<=N ; ++j)
        {
            scanf("%d",&x);
            V[i][j] = x + V[i-1][j];
            O[i][j] = x + O[i][j-1];
        }
}
void Solve()
{
    int Max=0, X, Y, o, v, Val, c1, c2;
    for(int i=1; i<=M ; ++i)
        for(int j=1; j<=N ; ++j)
        {
            Val=0;
            if( V[i][j] <= V[M][j] - V[i-1][j])
            {
                Val += V[M][j] - V[i-1][j];
                c1 = i - M - 1;
            }
            else
            {
                Val += V[i][j];
                c1 = i;
            }
            if( O[i][j] >= O[i][N] - O[i][j-1])
            {
                Val += O[i][j];
                c2 = -j ;
            }
            else
            {
                Val += O[i][N] - O[i][j-1];
                c2 = N - j +1;
            }
            Val -= ( O[i][j] - O[i][j-1] );
            if( Val > Max )
            {
                Max = Val;
                X = i;
                Y = j;
                v = c1;
                o = c2;
            }
        }
    printf("%d\n",Max);
    printf("%d %d %d %d",X,Y,o,v);
}
int main()
{
    Read();
    Solve();
    return 0;
}
