#include <cstdio>
#include <cstring>
#define Dim 45000
#define Mod 10000
using namespace std;

int Apoz[Dim], Aneg[Dim], Bpoz[Dim], Bneg[Dim], N, M, X;

#define B(i) (((i) <= 0) ? Bneg[ -(i) ] : Bpoz[ (i) ] )
#define A(i) (((i) <= 0) ? Aneg[ -(i) ] : Apoz[ (i) ] )

FILE *fin=freopen("diamant.in","r",stdin);
FILE *fout=freopen("diamant.out","w",stdout);

int main()
{
    int Max = 0, Min = 0;
    scanf("%d%d%d", &N, &M, &X);
    Aneg[0] = 1;

    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= M ; ++j )
        {
            memcpy(Bpoz, Apoz, sizeof(Bpoz));
            memcpy(Bneg, Aneg, sizeof(Bneg));

            Max += i * j;
            Min -= i * j;

            for(int l = Max ; l >= Min ; --l )
                A(l) = ( B(l) + B(l - i * j) + B(l + i * j) ) % Mod;


        }

    if( X < -45000 || X > 45000 )
        printf("0");
    else
        printf("%d", A(X) );

    return 0;
}
