#include <cstdio>
using namespace std;
FILE *fin = freopen("modulo.in","r",stdin);
FILE *fout = freopen("modulo.out","w",stdout);

int main()
{
    long long int i, a, b, c, aux, sol = 1;
    scanf("%lld%lld%lld", &a, &b, &c);
    aux = a;
    for(i = 1; i <= b; i <<= 1)
    {
        if( i & b )
            sol = (sol * aux) % c;
        aux = (aux * aux) % c;
    }
    printf("%lld", sol);
    return 0;
}
