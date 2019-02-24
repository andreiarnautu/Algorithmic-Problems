#include <cstdio>
using namespace std;
FILE *fin=freopen("m01.in","r",stdin);
FILE *fout=freopen("m01.out","w",stdout);
int V[1001], F[1001], N;

int Rest(int x)
{
    int i, t=0;
    for( i = x ; i > 0 ; --i )
        t = ( t * 10 + 1 ) % N;
    return t;
}

int main()
{
    int k, i , j , l;
    scanf("%d",&N);
    for( i=1 ; i<=N ; ++i)
    {
        k = Rest(i);
        V[i] = k;
        ++ F[k];
        if ( k == 0 )
        {
            for(int j=1; j<=i ; ++j)
                printf("1");
            return 0;
        }
        if( F[k] == 2 )
        {
            for( j=1; j<=i && V[j] != V[i] ; ++j);
            for( l=i ; l>j ; --l)
                printf("1");
            for( l=j ; l>0 ; l--)
                printf("0");
            return 0;
        }
    }
    return 0;
}
