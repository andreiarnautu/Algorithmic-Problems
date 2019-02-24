#include <cstdio>
using namespace std;
FILE *fin=freopen("kbiti.in","r",stdin);
FILE *fout=freopen("kbiti.out","w",stdout);
int N, K, M1[501][101], M2[501][101];
// In M1 si M2 am matricile de numere mari. Practic sunt 2 vectori de numere mari, care trebuie si ele stocate tot in vectori.
// In M2 este randul curent, iar in M1 cel precedent (triunghiul lui Pascal)
void Solve()
{
    int i, t, j, l;
//    M1[1][0] = 1;
 //   M1[1][1] = 1;
    for( i=2; i<=N/2 ; ++i)
    {
        M2[1][0] = 1;
        M2[1][1] = 1;
        M2[i][0] = 1;
        M2[i][1] = 1;
        for( j=2; j<i ; ++j)
        {
            for( l=0; l<=M1[j][0] ; ++l)
                M2[j][l] = M1[j][l];
            t = 0;
            for( l=0; l<=M1[j][0] || l<=M1[j-1][0] || t ; l++ , t/=10)
                M2[j][l] = ( t += M1[j][l] + M1[j-1][l] ) % 10;
           // t=0;
            M2[j][0] = l - 1;
        }
     /*   for( j=1; j<=i ; ++j)
        {
            for( l=0; l<=M2[j][0] ; ++l)
                printf("%d",M2[j][l]);
            printf("\n");
        }
        printf("\n");*/
        for( j=1; j<=i ; ++j)
            for( l=0; l<=M2[j][0] ; ++l)
                M1[j][l] = M2[j][l];
    }
    t=0;
    for( i=1; i<=M1[K+1][0] || i<=M1[K][0] ||t ; ++i, t/=10)
        M2[K+1][i] = ( t += M1[K+1][i] + M1[K][i] ) % 10;
    M2[K+1][0] = i-1;
    for( i=M2[K+1][0]; i>0 ; --i)
        printf("%d", M2[K+1][i]);
}
void Read()
{
    scanf("%d%d",&N,&K);
    if( N==1 )
        printf("0");
    else
        Solve();
}
int main()
{
    Read();
    return 0;
}
