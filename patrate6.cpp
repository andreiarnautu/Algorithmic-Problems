#include <fstream>
#include <algorithm>

using namespace std;
ifstream in("patrate6.in");
ofstream out("patrate6.out");

int N, x, Max, ok = 1 ;
long long int F[2000002], V[100003];


int Maxim(long long int a, long long int b)
{
    if( a > b )
        return a;
    return b;
}

int main()
{
    int P;
    in >> N;
    for(int i = 0 ; i < N ; ++i )
    {
        in >> V[i];
        ++F[x];
        if( x > Max )
            Max = x;
    }

    P = Max;
    P = Maxim( 0 , Max - 100000 );

    for(int i = 0 ; i < N ; ++i )
    {
        if( V[i] - P < 0 )
            ok = 0;
        else
            ++F[ V[i] - P ];
    }

    Max = P

    for(long long int i = 0 ; i <= Max ; ++i )
    {
        if( F[i] % 4 != 0 && F[i] > 0 )
        {
            ok = 0;
        }
        F[i + 1] += F[i] / 4;
        if( F[i + 1] > 0 && i + 1 > Max )
            Max = i + 1;
    }

    if( F[Max] % 4 != 0 && ok == 1 )
        ok = 0;
    //Max += F[Max] / 4;
    if( ok )
        out << Max;
    else
        out << Max + 1;
    return 0;
}
