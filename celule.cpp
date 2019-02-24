#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("celule.in","r",stdin);
FILE *fout=freopen("celule.out","w",stdout);
int A, B , k;
bool Viz[1000000];

int CMMDC(int m, int n)
{
    int r;
    while( n )
    {
        r = m % n;
        m = n;
        n = r;
    }
    return m;
}

void Ciur()
{
    int i , j;
    for( i = 3 ; i * i * i * i <= k  ; i += 2 )
        if( !Viz[i] )
            for( j = i * i ; j * j  <= k  ; j += ( i << 1 ) )
                Viz[j] = 1;
}

void Solve()
{
    int Sol = 0 , Nrdiv = 0, Div, AA, BB;
    AA = A;
    if( A != 1 )
    {
        while( AA % 2 == 0 )
        {
            AA /= 2;
            ++Sol;
        }

        for(int i = 3 ; i * i <= A && AA > 1 ; i += 2)
            if( !Viz[i] )
                while( AA % i == 0 )
                {
                    AA /= i;
                    ++Sol;
                }
        if( AA > 1 )
            ++Sol;
    }
    BB = B;
    if( B != 1 )
    {
        while( BB % 2 == 0 )
        {
            BB /= 2;
            ++Sol;
        }
        for(int i = 3 ; i * i <= B && BB > 1 ; i += 2)
            if( !Viz[i] )
                while( BB % i == 0 )
                {
                    BB /= i;
                    ++Sol;
                }
        if( BB > 1 )
            ++Sol;
    }
    printf("%d", Sol);
}

int main()
{
    int x;
    scanf("%d%d", &A, &B);
    x = CMMDC ( A , B );
    A /= x;
    B /= x;
    k = max( A , B );
    Ciur();
    Solve();
    return 0;
}
