#include <cstdio>
#include <algorithm>
#define Nmax 100001
#define Inf 2000000001
using namespace std;
FILE *fin=freopen("bus.in","r",stdin);
FILE *fout=freopen("bus.out","w",stdout);

int A, B, N, V[Nmax], L[Nmax];
typedef struct{int x, y ;} struc;
struc Point[Nmax];

void Read()
{
    scanf("%d%d%d", &A, &B, &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d%d", &Point[i].x, &Point[i].y);
}

inline int cmp(const void *a, const void *b)
{
    struc p = * ((struc*)a);
    struc q = * ((struc*)b);
    return ( p.x != q.x ) ? ( p.x - q.x ) :  ( p.y - q.y ) ;
}

void Solve()
{
    int Max = 0, st, dr, m, l;
    L[1] = Inf;
    for(int i = 2 ; i <= N ; ++i)
        L[i] = -Inf;
    for(int i = N ; i > 0 ; --i )
    {
        st = 1, dr = N, l = 0;
        while( st <= dr )
        {
            m = (st + dr) / 2;
            if( Point[i].y <= L[m] )
            {
                l = m;
                st = m + 1;
            }
            else
                dr = m - 1;
        }
        Max = max( Max , l++ );
        L[l] = max ( L[l] , Point[i].y );
   //     for(int w = 1 ; w <= N ; ++w )
      //      printf("%d ",L[w]);
        printf("\n");
    }
    printf("%d",Max);
}

int main()
{
    Read();
    qsort(Point, N + 1, sizeof(struc), cmp);
   // for(int i = 1; i <= N; ++i )
        //printf("%d %d\n",Point[i].x,Point[i].y);
    Solve();
    return 0;
}
