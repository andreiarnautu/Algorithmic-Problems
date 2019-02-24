#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin = freopen( "cursa.in" , "r", stdin );
FILE *fout = freopen( "cursa.out", "w", stdout );

int N, V[30000], D[30000] ;

void Read()
{
    int x;
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &x);
        V[i] = V[i - 1] + x;
    }
   // for(int i = 1 ; i <= N ; ++i )
     //   printf("%d ",V[i]);
}

void Solve()
{
    int Min = 100000, City, Optim;
    for(int i = 1 ; i < N ; ++i )
        for(int j = i + 1 ; j <= N ; ++j )
        {
            Optim = min( V[j - 1] - V[i - 1] , V[N] - V[j - 1] + V[i - 1] );
            D[j] += Optim ;
            D[i] += Optim ;
        }
    for(int i = 1 ; i <= N ; ++i )
        if( D[i] < Min )
        {
            Min = D[i];
            City = i;
        }
    printf("%d\n%d", City, Min);
}

int main()
{
    Read();
    Solve();
    return 0;
}
