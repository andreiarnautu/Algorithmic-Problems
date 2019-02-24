#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *fin=freopen("carnati.in","r",stdin);
FILE *fout=freopen("carnati.out","w",stdout);

vector < pair<int,int> > V;
int DP[2020];
int n, c;

void Read()
{
    int i, x, y;
    scanf("%d%d", &n, &c);
    V.push_back(make_pair(-2, 0));

    for(i = 0; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        V.push_back(make_pair(x, y));
    }
    sort(V.begin() + 1, V.end());
}

void Solve()
{
    int ans = 0, i, j, P, val;
    DP[0] = -10000;

    for(i = 1; i <= n; ++i)
    {
        P = V[i].second;
        for(j = 1; j <= n; ++j)
        {
            if( V[j].second >= P )
                val = P;
            else
                val = 0;

            DP[j] = max( val - c, val + DP[j - 1] - c * (V[j].first - V[j - 1].first));

            if( DP[j] > ans )
                ans = DP[j];

        }
    }

    printf("%d", ans);
}

int main()
{
    Read();
    Solve();
    return 0;
}
