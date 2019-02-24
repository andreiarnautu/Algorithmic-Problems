#include <cstdio>
using namespace std;
FILE *fin=freopen("cds.in","r",stdin);
FILE *fout=freopen("cds.out","w",stdout);
int F[702], S, N, Max = 0;
int Min(int x, int y)
{
    if( x <= y )
        return x;
    return y;
}
int main()
{
    int x;
    scanf("%d", &N);
    F[0] = 1;
    for(int i=0 ; i < N ; ++i)
    {
        scanf("%d",&x);
        for(int j= Min(700-x, Max) ; j>=0 ; j--)
            if( F[j] && x + j <= 700 )
            {
                F[x + j] = 1;
                if( x + j > Max )
                    Max = x + j;
            }
        S += x;
    }
    S = S - Max;
    if( S > Max )
        printf("0 0 ");
    else
        printf("%d %d ",S,Max);
    return 0;
}
