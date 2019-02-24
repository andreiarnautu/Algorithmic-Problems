#include <cstdio>
using namespace std;
FILE *fin=freopen("minmax.in","r",stdin);
FILE *fout=freopen("minmax.out","w",stdout);
long long int S, V[10], Min = 10000000000 , Max;

void Process()
{
    long long int Sum = 0 , p = 1, Nr1 = 0, Nr2 = 0;
    for(int i = 9 ; i > 0 ; --i )
        if( V[i] )
        {
            Sum += i;
            Nr1 += p * i;
            p *= 10;
        }
    p = 1;
    for(int i = 1 ; i < 10 ; ++i )
        if( V[i] )
        {
            Nr2 += p * i;
            p *= 10;
        }
    if( Sum == S )
    {
        if( Nr2 > Max )
            Max = Nr2;
        if( Nr1 < Min )
        {
            Min = Nr1;
        }
    }

}

void Gen( int k )
{
    if( k == 10 )
    {
        Process();
        return;
    }
    V[k] = 0;
    Gen( k + 1 );
    V[k] = 1;
    Gen( k + 1 );
}

int main()
{
    scanf("%d", &S);
    Gen(1);
    Max *= 10;
    printf("%lld %lld", Min, Max);
    return 0;
}
