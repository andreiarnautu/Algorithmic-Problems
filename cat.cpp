#include <cstdio>
using namespace std;
FILE *fin=freopen("cat.in","r",stdin);
FILE *fout=freopen("cat.out","w",stdout);
int N, K, A, F[601];
void Read()
{
    scanf("%d%d%d", &N, &K, &A);
}

int Correct(int x)
{
    int p, nr = N, aux;
    for(int i = 1; i <= N ; ++i )
        F[i] = 0;
    p = x - 1;
    while( nr >1 )
    {
        aux = 1;
        while( aux <= K )
        {
            ++p;
            if( p > N )
                p -= N;
            if( !F[p] )
                ++aux;
        }
      //  p = p ;
        while( p > N )
            p -= N;

        if( p == A )
            return 0;
        else
            F[p] = 1;
     //   for(int i = 1 ; i <= N ; ++i )
     //       printf("%d ",F[i]);
        --nr;
    }
    return 1;
}

int main()
{
    Read();
    for(int i = 1 ; i <= N ; ++i )
        if( Correct(i) )
        {
            printf("%d",i);
            return 0;
        }
     //   else
      //      printf("\n");
}
