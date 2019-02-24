#include <cstdio>
#include <cmath>
using namespace std;
FILE *fin=freopen("cartier.in","r",stdin);
FILE *fout=freopen("cartier.out","w",stdout);
int N, H[5001], L[5001];
int Cmmdc(int x, int y)
{
    int r;
    while(y)
    {
        r=x%y;
        x=y;
        y=r;
    }
    return x;
}
void Read()
{
    int j, x, Hmax=0, Nr=0, Sum=0;
    scanf("%d",&N);
    int root;
    for(int i=0; i<N ; ++i)
    {
        scanf("%d",&x);
        root=sqrt((double)x);
        for(j=root; j>0 ; j--)
            if( x%j == 0 )
            {
                L[i] = j;
                Sum += L[i];
                H[i] = x / j;
                break;
            }
        if( H[i] > Hmax )
        {
            Hmax = H[i];
            Nr = 1;
        }
        else if( H[i] == Hmax )
            ++Nr;
    }
    printf("%d\n%d\n",Nr,Sum);
}
void Solve()
{
    int Max=1;
    for(int i=0; i<N-1 ; ++i)
        for(int j=N-1; j>i ; --j)
            if( Cmmdc( H[i], H[j] )>1)
                {
                    if(j-i+1>Max)
                        Max=j-i+1;
                    break;
                }
    printf("%d",Max);
}
int main()
{
    Read();
    Solve();
    return 0;
}
