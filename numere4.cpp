#include <cstdio>
#include <cmath>
using namespace std;
FILE *fin=freopen("numere4.in","r",stdin);
FILE *fout=freopen("numere4.out","w",stdout);
int N, K, P;

void SolveOne()
{
    int sum, nr, j, Sol = 0, Rezerva = 0;
    for(int i = 1 ; i <= N ; ++i )
    {
        sum = i * (i + 1) / 2;
        nr = 1;
        if( sum == 1 )
        {
            if( K <= 1 )
                ++Sol;
            continue;
        }
        if( sum % 2 == 0 )
        {
            ++nr;
            Rezerva += sum;
        }
        for( j = 3 ; j * j < sum ; ++j )
            if( sum % j == 0 )
                ++nr;
        nr *= 2;
        j = sqrt( (double) sum );
        if( j * j == sum )
            ++nr;
       // printf("%d ",nr);
        if( nr >= K )
            Sol += sum;
    }
    if( Sol > 0 )
        printf("%d\n", Sol);
    else
        printf("%d\n",Rezerva);
}

void SolveTwo()
{
    int Aux;
    Aux = P * 2;
    Aux = sqrt( (double) Aux );
    while( Aux * (Aux + 1) / 2 > P )
        --Aux;
    if( P == Aux * (Aux + 1) / 2)
        printf("%d\n%d",Aux,Aux);
    else
        printf("%d\n%d", P - Aux * (Aux + 1) / 2, Aux + 1);
}

int main()
{
    scanf("%d%d%d", &N, &K, &P);
    SolveOne();
    SolveTwo();
    return 0;
}
