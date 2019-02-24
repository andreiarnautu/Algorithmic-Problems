#include <cstdio>
#define DIM 100100
using namespace std;
FILE *fin=freopen("oz.in","r",stdin);
FILE *fout=freopen("oz.out","w",stdout);

struct triplet {
                    int i1, i2;
                    long long int div;
               };
long long int V[DIM];
triplet A[DIM];
int n, m;

inline long long int gcd(long long int a, long long int b)
{
    long long int r;
    while( b )
    {
        r = a % b, a = b, b = r;
    }
    return a;
}

void Read()
{
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i)
        scanf("%d%d%lld", &A[i].i1, &A[i].i2, &A[i].div);
}

void Solve()
{
    int i, x, y;
    long long int z;

    for(i = 1; i <= n; ++i)
        V[i] = 1 ;
    for(i = 1; i <= m; ++i)
    {
        x = A[i].i1, y = A[i].i2, z = A[i].div;
        V[x] = V[x] * z / gcd(V[x], z);
        V[y] = V[y] * z / gcd(V[y], z);
    }

    for(i = 1; i <= m; ++i)
    {
        x = A[i].i1, y = A[i].i2, z = A[i].div;
        if( gcd(V[x], V[y]) != z )
        {
            printf("-1"); return;
        }
    }

    for(i = 1; i <= n; ++i)
        printf("%lld ", V[i]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
