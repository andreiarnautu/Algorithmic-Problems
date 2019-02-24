#include <cstdio>
#include <unordered_set>
#define DIM 100100
using namespace std;
FILE *fin=freopen("aria.in","r",stdin);
FILE *fout=freopen("aria.out","w",stdout);

struct punct
            {
                double x, y;
            };

int n;
unordered_set < int > abcd;
punct V[DIM];

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lf %lf", &V[i].x, &V[i].y);
    V[n + 1] = V[1];
}

void Solve()
{
    double A = 0;

    for(int i = 1; i <= n; ++i)
        A += ( V[i].x * V[i + 1].y - V[i + 1].x * V[i].y );

    A *= 0.5;
    printf("%.5f", A);
}

int main()
{
    Read();
    Solve();
    return 0;
}
