#include <cstdio>

using namespace std;

FILE *fin=freopen("dezastru.in","r",stdin);
FILE *fout=freopen("dezastru.out","w",stdout);

int n, k;
double P[30], Sum[30][30], No[30][30];


void Read()
{
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++i )
        scanf("%lf", &P[i]);
}

void Solve_Dynamic()
{
    int i, j;
    for(i = 0 ; i <= n ; ++i)
        Sum[i][0] = No[i][0] = 1;

    for(i = 1 ; i <= n ; ++i)
        for(j = 1 ; j <= k ; ++j)
        {
            Sum[i][j] = Sum[i - 1][j] + Sum[i - 1][j - 1] * P[i];
            No[i][j] = No[i - 1][j] + No[i - 1][j - 1];
        }
}

void Write()
{
    printf("%.7f", (double) Sum[n][k] / (double) No[n][k] );
}

int main()
{
    Read();
    Solve_Dynamic();
    Write();
    return 0;
}
