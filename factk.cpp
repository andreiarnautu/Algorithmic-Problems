#include <fstream>
using namespace std;
ifstream in("factk.in");
ofstream out("factk.out");

int n, k, nr;
bool viz[5005];
int Primes[1001], Fact[30], P[30], f;


void Gen()
{
    int i, j;
    Primes[++nr] = 2;

    for(i = 3; i <= 5000; i += 2)
        if( !viz[i] )
        {
            Primes[++nr] = i;
            for(j = i * i; j <= 5000; j += 2 * i)
                viz[j] = 1;
        }
}

void Prime_Divisors()
{
    int i;
    for(i = 1; i <= nr; ++i)
        if( k % Primes[i] == 0 )
        {
            Fact[++f] = Primes[i];
            while( k % Primes[i] == 0 )
            {
                ++P[f];
                k /= Primes[i];
            }
        }
}

void Solve()
{
    int i, MIN = 1 << 30, cnt;
    long long int p;

    for(i = 1; i <= f; ++i)
    {
        cnt = 0;
        p = Fact[i];

        while( p <= n )
        {
            cnt += n / p;
            p *= 1LL * Fact[i];
        }

        cnt /= P[i];

        if( cnt < MIN )
            MIN = cnt;
    }

    out << MIN;
}

int main()
{
    in >> n >> k;
    Gen();
    Prime_Divisors();
    Solve();
    return 0;
}
