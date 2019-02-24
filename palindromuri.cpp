#include <cstdio>
#include <algorithm>
#define Big long long int

using namespace std;

FILE *fin=freopen("palindromuri.in","r",stdin);
FILE *fout=freopen("palindromuri.out","w",stdout);

Big a, b, nrA, nrB;


Big palindrom(Big y)
{
    Big x = 0;
    while( y )
    {
        x = x * 10 + y % 10;
        y /= 10;
    }
    return x;
}

Big nr_cif(Big k)
{
    int c = 0;
    while( k )
    {
        ++c;
        k /= 10;
    }
    return c;
}

void Read()
{
    scanf("%lld%lld", &a, &b);
}

Big Pow(Big nr, Big p)
{
    Big sol = 1;
    for(;p > 0;--p)
        sol = 1LL * sol * nr;
    return sol;
}

void Calc_A()
{
    Big c, i;

    --a;
    if( a < 0 )
        return;
    if( a == 0 )
    {
        nrA = 1;
        return;
    }

    c = nr_cif(a);
    for( i = 1 ; i * 2 < c ; ++i )
        nrA = 1LL * (nrA + 9 * Pow(10, i - 1));
    for( i = 1 ; i * 2 + 1 < c ; ++i )
        nrA = 1LL * (nrA + 9 * Pow(10, i));

    for( i = 0 ; i <= 9 ; ++i )
        if( i <= a )
            ++nrA;

    if( c % 2 == 0 )
    {
        Big aux1 = 0, aux2 = 0, aa;
        aa = a;

        aux1 = a % Pow(10, c / 2);

        aa = a;
        aux2 = aa / Pow(10, c / 2);

        nrA = 1LL * (nrA + aux2 - Pow(10, c / 2 - 1));

        if( palindrom(aux2) <= aux1 )
            ++nrA;
    }

    else if( c > 1 )
    {
        Big aux1 = 0, aux2 = 0, aa, m;
        aa = a;

        aux1 = a % Pow(10, c / 2);
        m = ((a - aux1) / Pow(10, c / 2)) % 10;
        aux2 = a / Pow(10, c / 2 + 1);

        nrA = 1LL * (nrA + (aux2 - Pow(10, c / 2 - 1)) * 10);

        if( palindrom(aux2) <= aux1 )
            nrA += m + 1;
        else
            nrA += m;

    }

}

void Calc_B()
{
    Big c, i;

    nrB = nrA;
    nrA = 0;

    a = b;


    if( a < 0 )
        return;
    if( a == 0 )
    {
        nrA = 1;
        return;
    }

    c = nr_cif(a);
    for( i = 1 ; i * 2 < c ; ++i )
        nrA = 1LL * (nrA + 9 * Pow(10, i - 1));

    for( i = 1 ; i * 2 + 1 < c ; ++i )
        nrA = 1LL * (nrA + 9 * Pow(10, i));

    for( i = 0 ; i <= 9 ; ++i )
        if( i <= a )
            ++nrA;

    if( c % 2 == 0 )
    {
        Big aux1 = 0, aux2 = 0, aa;
        aa = a;
        aux1 = a % Pow(10, c / 2);
        aux2 = aa / Pow(10, c / 2);

        nrA = 1LL * (nrA + aux2 - Pow(10, c / 2 - 1));

        if( palindrom(aux2) <= aux1 )
            ++nrA;
    }

    else if( c > 1 )
    {
        Big aux1 = 0, aux2 = 0, aa, m;
        aa = a;

        aux1 = a % Pow(10, c / 2);
        m = ((a - aux1) / Pow(10, c / 2)) % 10;
        aux2 = a / Pow(10, c / 2 + 1);

        nrA = 1LL * (nrA + (aux2 - Pow(10, c / 2 - 1)) * 10);

        if( palindrom(aux2) <= aux1 )
            nrA += m + 1;
        else
            nrA += m;

    }
}

int main()
{
    Read();
    Calc_A();
    Calc_B();
    printf("%lld", nrA - nrB);
}
