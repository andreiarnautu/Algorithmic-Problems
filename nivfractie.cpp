#include <cstdio>
#include <fstream>
using namespace std;
ifstream in("nivfractie.in");
ofstream out("nivfractie.out");

inline long long int Min(long long int a, long long int b)
{
    if( a >= b )
        return b;
    return a;
}

inline long long int Max(long long int a, long long int b)
{
    if( a >= b )
        return a;
    return b;
}

long long int Calculate(long long int x, long long int y)
{
    long long int a, b;
    if( x == y )
        return 1;
    a = Min(x , y);
    b = Max(x , y);
    return 1 + Calculate(a , b - a);
}

inline long long int cmmdc(long long int a, long long int b)
{
    long long int r, op = 0;
    while( b )
    {
        r = a % b;
        ++ op;
        a = b;
        b = r;
    }
    return a;
}

int main()
{
    long long int N, M, a, Nr = 0;
    in >> N >> M;
    a = cmmdc( N , M );
    N /= a;
    M /= a;
    long long int x , y, ok = 1;
    while( ok )
    {
        Nr++;
        x = Min ( M , N );
        y = Max ( M , N );
        if( y > 10000 * x )
        {
            y -= 9999 * x;
            Nr += 9999;
        }
        if ( x == y )
            ok = 0;
        M = x;
        N = y - x;
    }
    out << Nr;
    return 0;
}
