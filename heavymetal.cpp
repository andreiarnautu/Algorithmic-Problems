#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *fin=freopen("heavymetal.in","r",stdin);
FILE *fout=freopen("heavymetal.out","w",stdout);

vector < pair<int,int> > V;
int best[100010];
int n;


void Read()
{
    int i, x, y;

    scanf("%d", &n);
    for(i = 0; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        V.push_back(make_pair(y , x));
    }
    sort(V.begin(), V.end());
}

inline int binary(int pos)
{
    int left = 0, right = pos - 1, mid, sol = -1;

    while( left <= right )
    {
        mid = (left + right) / 2;
        if( V[mid].first <= V[pos].second )
        {
            sol = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    return sol;
}

void Solve()
{
    int i, j;
    best[0] = V[0].first - V[0].second;

    for(i = 1; i < n; ++i)
    {
        best[i] = max( V[i].first - V[i].second , best[i - 1] );

        j = binary(i);
        if( j > -1 )
        {
            best[i] = max( best[i], best[j] + V[i].first - V[i].second );
        }
    }

    printf("%d", best[n - 1]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
