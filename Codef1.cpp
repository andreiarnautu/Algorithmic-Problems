#include <cstdio>
using namespace std;

int main()
{
    long long int aux, a, b, val = 1000000, sol = 1;
    scanf("%I64d%I64d", &a, &b);
    if( a < b )
    {
        aux = a;
        a = b;
        b = aux;
    }

    while(! (a == b) )
    {
        if(a > val * b)
        {
            sol += val;
            a -= val * b;
        }
        else
        {
            a -= b;
            ++sol;
        }
        if( a < b )
        {
            aux = a;
            a = b;
            b = aux;
        }
    }
    printf("%I64d", sol);
    return 0;
}
