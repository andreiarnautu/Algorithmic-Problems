/**
  *  Worg
  */
#include <cstdio>

FILE *fin=freopen("euclid3.in","r",stdin);
FILE *fout=freopen("euclid3.out","w",stdout);

inline int gcd(int a, int b, int &x, int &y)
{
    if( !b )
    {
        x = 1, y = 0; return a;
    }
    int x0, y0;
    int div = gcd(b, a % b, x0, y0);
    x = y0;
    y = x0 - (a / b) * y0;
    return div;

}

int main()
{
    int teste, a, b, c;
    scanf("%d", &teste);
    for(; teste; --teste)
    {
        scanf("%d%d%d", &a, &b, &c);
        int div, x, y;
        div = gcd(a, b, x, y);

        if( c % div == 0 )
            printf("%d %d\n", x * (c / div), y * (c / div));
        else
            printf("0 0\n");
    }
    return 0;
}
