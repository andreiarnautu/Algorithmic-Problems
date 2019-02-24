#include <cstdio>
using namespace std;
FILE *fin=freopen("expo.in","r",stdin);
FILE *fout=freopen("expo.out","w",stdout);
unsigned long long H, W, N;
void Read()
{
    scanf("%lld%lld%lld",&H,&W,&N);
}
void Solve()
{
    unsigned long long a, b, m, nr, x1, x2;
    a = 0;
    if( H >= W )
        b = N * H;
    else
        b = N * W;
    while( b - a > 1 )
    {
        m = ( a + b ) / 2;
        nr = 0;
        x1 = m / H;
        x2 = m / W;
        if( x1 * x2 >= N )
            b = m;
        else
            a = m;
    }
    printf("%lld",b);
}
int main()
{
    Read();
    Solve();
    return 0;
}
