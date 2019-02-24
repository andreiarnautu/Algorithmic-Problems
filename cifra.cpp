#include <cstdio>
#define Dim 100000
using namespace std;
FILE *fin=freopen("cifra.in","r",stdin);
FILE *fout=freopen("cifra.out","w",stdout);

long Nrc[Dim], N, S;

int Cifre(int x)
{
    int nr = 0;
    while( x )
    {
        ++nr;
        x /= 10;
    }
    return nr;
}

int main()
{
    Nrc[1] = 1;
    scanf("%ld", &N);
    if( N == 1 )
    {
        printf("1");
        return 0;
    }
    S = 1;
    int i;
    for( i = 2 ; S < N ; ++i )
    {
        Nrc[i] = Nrc[i - 1] + Cifre(i);
        if( S + Nrc[i] >= N )
            break;
        S += Nrc[i];
    }
    for( int j = 1 ; j <= i ; ++j )
        if( S + Nrc[j] >= N )
        {
            printf("%d ",j);
            return 0;
        }
    return 0;
}
