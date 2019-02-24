#include <cstdio>
using namespace std;
FILE *fin=freopen("cuburi2.in","r",stdin);
FILE *fout=freopen("cuburi2.out","w",stdout);
int a[51][51][21];
int N,C,D,Max;
void Read()
{
    int x,y;
    scanf("%d%d%d",&N,&C,&D);
    for(int i=0; i<C ; i++)
    {
        scanf("%d%d",&x,&y);
        ++a[x][y][0];
        if( a[x][y][0] > Max )
            Max=a[x][y][0];
        scanf("%d",&a[x][y][a[x][y][0]]);
    }
}
void Solve1()
{
    printf("%d %d\n",N,N);
    for(int i=1; i<=N ; ++i)
    {
        for(int j=1; j<=N ; ++j)
            printf("%d ",a[i][j][a[i][j][0]]);
        printf("\n");
    }
}
int Find(int x, int y)
{
    int p;
    p=a[x][N][y];
    for(int i=N-1; i>0 ;i--)
        if( a[x][i][y] != 0 )
            p=a[x][i][y];
    return p;
}
void Solve2()
{
    printf("%d %d\n",Max,N);
    for(int i=Max; i>0 ; --i)
    {
        for(int j=1; j<=N ; ++j)
            printf("%d ",Find(j,i));
        printf("\n");
    }
}
int Find2(int x, int y)
{
    int p;
    p=a[1][x][y];
    for(int i=2; i<=N ; ++i)
        if( a[i][x][y] != 0)
            p=a[i][x][y];
    return p;
}
void Solve3()
{
    printf("%d %d\n",Max,N);
    for(int i=Max; i>0 ; --i)
    {
        for(int j=1; j<=N ; ++j)
            printf("%d ",Find2(j,i));
        printf("\n");
    }
}
int main()
{
    Read();
    if( D==1 )
        Solve1();
    if( D==2 )
        Solve2();
    if( D==3 )
        Solve3();
    return 0;
}
