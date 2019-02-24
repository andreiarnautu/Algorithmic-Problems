#include <cstdio>
#define DIM 30300
#define zeros(x) ( (x ^ (x - 1)) & x )
using namespace std;
FILE *fin=freopen("concurs4.in","r",stdin);
FILE *fout=freopen("concurs4.out","w",stdout);

int n, k, Primes[DIM], nr, AIB[DIM], R[DIM];
bool viz[700000];

void Ciur()
{
    long long int i, j;
    Primes[++nr] = 2;

    for(i = 3; i < 699000 && nr < n; i += 2)
        if( !viz[i] )
        {
            Primes[++nr] = i;
            for(j = i * i; j < 699000; j += 2 * i)
                viz[j] = 1;
        }
}

inline void Add(int pos, int val)
{
    for(int i = pos; i <= n; i += zeros(i))
        AIB[i] += val;
}

inline int Compute(int pos)
{
    int ret = 0;
    for(int i = pos; i > 0; i -= zeros(i))
        ret += AIB[i];
    return ret;
}

inline int Count(int x, int y)
{
    int ret = 0;
    if( y > n )
    {
        y -= n;
        ret = Compute(n) - Compute(x - 1) + Compute(y);
        return ret;
    }
    ret = Compute(y) - Compute(x - 1);
    return ret;
}

void Solve()
{
    int i, pos = 1, elem, aux, available;
    R[1] = Primes[1];
    Add(1, 1);

    for(i = 2; i <= n; ++i)
    {
        elem = Primes[i];
        aux = k % (n - i + 1);
        if( !aux )
            aux = n - i + 1;
        while( aux )
            {
                available = aux - Count(pos + 1, pos + aux);
                pos = (aux + pos) % n;
                if( !pos )
                    pos = n;
                aux -= available;
            }
        if( !pos )
            pos = n;
        R[pos] = elem;
        Add(pos, 1);
    }

    for(i = 1; i <= n; ++i)
        printf("%d ", R[i]);
}

int main()
{
    scanf("%d %d", &n, &k);
    Ciur();
    Solve();
    return 0;
}
