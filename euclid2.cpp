#include <cstdio>
using namespace std;

FILE *fin=freopen("euclid2.in","r",stdin);
FILE *fout=freopen("euclid2.out","w",stdout);


inline int gcd(int a, int b)
{
    int r;
    while( b )
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main()
{
    int t, a, b;

    for(scanf("%d", &t); t > 0; --t)
    {
        scanf("%d %d", &a, &b);
        printf("%d\n", gcd(a,b));
    }
    return 0;
}
