# include<cstdio>
# include<algorithm>
using namespace std;
FILE *f=freopen("cmlsc.in","r",stdin);
FILE *g=freopen("cmlsc.out","w",stdout);
int a[1025],b[1025],c[1025][1025], v[1025];
int main()
{
    int i,j;
    int m,n;
    scanf("%d%d",&m,&n);
    for( i = 1 ; i <= m; i++)
        scanf("%d",&a[i]);
    for( i = 1 ; i <= n; i++)
        scanf("%d",&b[i]);
    for( i = 1 ;i <= m ; i++ )
        for( j = 1 ; j <= n  ;j++)
    {
        if( a[i] == b[j]) c[i][j]= 1 + c[i - 1][j - 1];
        else c[i][j] = max(c[i][ j - 1], c[i - 1][j]);
    }

    /*for(i = 1; i <= m ; ++i)
    {
        for(j = 1; j <= n ; ++j)
            printf("%d ", c[i][j]);
        printf("\n");
    }*/
    printf("%d\n",c[m][n]);
    int t=0;
    for(i = m, j = n; i && j; )
    {
        if( a[i] == b[j] )
        {
            v[++t] = a[i];
            --i, --j;
        }
        else if( c[i - 1][j] > c[i][j - 1] )
            --i;
        else
            --j;
    }
    for(i = t; i > 0 ; --i)
        printf("%d ", v[i]);
      return 0;
}
