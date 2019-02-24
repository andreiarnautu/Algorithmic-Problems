#include <cstdio>
#include <vector>
using namespace std;

FILE *fin=freopen("divmul.in","r",stdin);
FILE *fout=freopen("divmul.out","w",stdout);

vector <bool> p(100003);
vector <int> Primes;
int cnt = 1;

void Ciur()
{
    int i, j;
    Primes.push_back(2);

    for(i = 3; i * i <= 10000; i += 2 )
        if( !p[i] )
            for(j = i * i ; j <= 10000 ; j += 2 * i )
                p[j] = 1;

    for(i = 3 ; i <= 10000 ; i += 2 )
        if( !p[i] )
        {
            Primes.push_back(i);
            ++cnt;
        }
}

void Solve()
{
    int x, y, nr = 0, i;
    scanf("%d%d", &x, &y);

    if( x > y || y % x != 0 )
    {
        printf("0\n");
        return;
    }

    if( x == y )
    {
        printf("1\n");
        return;
    }

    y /= x;

    for(i = 0 ; Primes[i] * Primes[i] <= y && y > 1 ; ++i )
        if( y % Primes[i] == 0 )
        {
            ++nr;
            while( y % Primes[i] == 0 )
                y /= Primes[i];
        }

    if( y > 1 )
        ++nr;

    printf("%d\n", 1 << nr);

}

int main()
{
    int t;
    Ciur();
    for(scanf("%d", &t); t > 0 ; --t)
        Solve();
    return 0;
}
