/*
    How about a coding trick?
*/
#include <fstream>
#include <algorithm>
#define DIM 2010
#define INF 2000000000000000
using namespace std;
ifstream in("gaz.in");
ofstream out("gaz.out");

int G[DIM];
long long int DP[DIM], adaos;
int L, P, D, C;
int n;

void Read()
{
    int i;
    in >> L >> P >> D >> C >> n;
    for(i = 1; i <= n; ++i)
    {
        in >> G[i];
        adaos += 1LL * D * G[i];
    }
}

int main()
{
    int i, j;
    long long int sum, val;
    Read();

    for(i = 1; i <= n; ++i)
    {
        sum = G[i], val = 0, DP[i] = 1LL * INF;
        for(j = i - 1; j >= 0; --j)
        {
            DP[i] = min( DP[i], P + C * val + DP[j] );
            val += max(1LL * 0, 1LL * sum - 1LL * L);
            sum += 1LL * G[j];
        }
    }
    out << DP[n] + adaos;
    return 0;
}
