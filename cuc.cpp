#include <cstdio>
using namespace std;
FILE *fin = freopen("cuc.in", "r", stdin);
FILE *fout = freopen("cuc.out", "w", stdout);
long long int x, h, Min = 10000;
int V[96];
int main()
{
    scanf("%lld", &x);
    h = (x / 90) * 12;
    x %= 90;
    if( x == 0 || x == 1)
    {
        printf("%lld",h);
        return 0 ;
    }
    int i, j;
    for(i = 1 ; i <= 24 ; i ++)
    {
        if( i % 2 == 1 )
            V[i] = V[i - 1] + 1;
        else
            V[i] = V[i - 1] + (i + 1) / 2;
    }
    for(i = 25 ; i <= 48 ; ++i)
        V[i] = V[i - 24] + V[24];
    for(i = 1; i <= 24 ; i += 2)
    {
        for( j = i + 1 ; V[j] - V[i - 1] <= x ; j += 2 )
            if( V[j] - V[i - 1] == x )
                if( (j - i + 1) / 2 < Min )
                {
                    Min = (j - i + 1) / 2;
                }
    }

    h += Min;
    printf("%lld",h);
    return 0;
}
