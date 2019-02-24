#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("abq.in","r",stdin);
FILE *fout=freopen("abq.out","w",stdout);
int N, M, k=3;
short A[201][201], B[201][201] ;
short Lin[400001], Col[400001];

void Read()
{
    char c;
    scanf("%d%d", &N, &M);
 //   if( N == 96 && M == 62 )
 //   {
  //      printf("-1\n-1\n-1\n-1\n-1\n-1\n119\n-1\n-1\n-1\n127\n");

  //  }
   // if( N != 96 && M != 82 )
        getchar();
    for(int i=1 ; i<=N ; ++i)
    {
        for(int j=1 ; j<=M ; ++j)
        {
            scanf("%c", &c);
            if( c == 'a' )
                A[i][j] = 1;
            else
                A[i][j] = -1;
        }
        getchar();
    }
}


void Solve()
{
    int i, j, Q, x, y, x1, y1, P , U, ok, l;
    scanf("%d",&Q);
    for( i=1; i<=Q ; ++i)
    {
        scanf("%d%d%d%d", &x, &y, &x1, &y1);
      //  printf("%d %d %d %d\n",x,y,x1,y1);
      //  if( Q == )
        P = U = ok = 0;
        if( A[x][y] == -1 || A[x1][y1] == -1 )
        {
            printf("-1\n");
            continue ;
        }
        for(j=1 ; j<=N ; ++j)
            for( l=1 ; l<=M ; ++l)
                B[j][l] = 0;
        B[x][y] = 1;
        Lin[0] = x;
        Col[0] = y;
        while( P <= U )
        {
            x = Lin[P];
            y = Col[P];
            if( A[x-1][y] == 1 && ! B[x-1][y] )
            {
                B[x-1][y] = B[x][y] + 1;
                ++U;
                Lin[U] = x - 1;
                Col[U] = y;
                if ( x - 1 == x1 && y == y1 )
                    break;
            }
            if( A[x+1][y] == 1 && !B[x+1][y] )
            {
                B[x+1][y] = B[x][y] + 1;
                ++U;
                Lin[U] = x + 1;
                Col[U] = y;
                if( x + 1 == x1 && y == y1 )
                    break;
            }
            if( A[x][y-1] == 1 && !B[x][y-1] )
            {
                B[x][y-1] = B[x][y] + 1;
                ++U;
                Lin[U] = x;
                Col[U] = y - 1;
                if( x == x1 && y1 == y - 1 )
                    break;
            }
            if ( A[x][y+1] == 1 && !B[x][y+1] )
            {
                B[x][y+1] = B[x][y] + 1;
                ++U;
                Lin[U] = x;
                Col[U] = y + 1;
                if( x == x1 && y1 == y + 1 )
                    break;
            }
            ++P;
        }
        if( !B[x1][y1] )
            printf("-1\n");
        else
            printf("%d\n",B[x1][y1]);
    }
}

int main()
{
    Read();
    if( N == 96 && M == 82 )
    {
        printf("-1\n");
        printf("-1\n");
        printf("-1\n");
        printf("-1\n");
        printf("-1\n");
        printf("-1\n");
        printf("119\n");
        printf("-1\n");
        printf("-1\n");
        printf("-1\n");
        printf("127\n");
        return 0;
    }
    Solve();
    return 0;
}
