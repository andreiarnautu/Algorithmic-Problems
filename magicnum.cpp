#include <cstdio>
#define MaxY 1000013

using namespace std;

FILE *fin=freopen("magicnum.in","r",stdin);
FILE *fout=freopen("magicnum.out","w",stdout);

int X, Y, Div[MaxY];


void Ciur()
{
    int i, j;

    for(i = 2 ; i * 2 <= Y; ++i )
        for( j = i * 2 ; j <= Y ; j += i )
            ++Div[j];
}

int main()
{
    scanf("%d%d", &X, &Y);
    Ciur();

    int cnt = 0;
    if( X == 1 )
    {
        ++cnt;
        ++X;
    }
    for(int i = X ; i <= Y ; ++i )
    {
        if( i % (Div[i] + 2) == 0 )
            ++cnt;
    }

    printf("%d", cnt);

    return 0;
}
