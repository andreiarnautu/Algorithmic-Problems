#include <cstdio>
using namespace std;
FILE *fin=freopen("jetoane.in","r",stdin);
FILE *fout=freopen("jetoane.out","w",stdout);
int S, a;
void Read()
{
    scanf("%d%d",&S,&a);
}
void Solve()
{
    long Nr = 0;
    if( a >= 1 )
        Nr += 1;
    if( a >= 2 )
        Nr += S;
    if( a >= 3 )
        Nr += S*(S+1)/2;
    printf("%d",Nr);
}
int main()
{
    Read();
    Solve();
    return 0;
}
