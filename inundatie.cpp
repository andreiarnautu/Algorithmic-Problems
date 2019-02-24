#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *fin=freopen("inundatie.in","r",stdin);
FILE *fout=freopen("inundatie.out","w",stdout);

vector <int> E;
vector <long long int> Sum;
int n, m;

void Read()
{
    scanf("%d%d", &n, &m);
    int x;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
        {
            scanf("%d", &x);
            E.push_back(x);
        }
    sort(E.begin(), E.end());
    long long int s = 0;
    for(int i = 0; i < E.size(); ++i)
    {
        s += E[i];
        Sum.push_back(s);
    }
}

void Solve()
{
    int val, sol = -1;
    scanf("%d", &val);

    int st = 0, dr = m * n - 1, mid;
    while( st <= dr )
    {
        mid= (st + dr) / 2;
        if( E[mid] < val )
        {
            sol = mid;
            st = mid + 1;
        }
        else
            dr = mid - 1;
    }
    if( sol >= 0 )
        printf("%lld\n", Sum[sol] + (val - 1) * (m * n - 1 - sol));
    else if( val > 0 )
        printf("%lld\n",(val - 1) * (m * n));
    else
        printf("0\n");
}

int main()
{
    Read();
    int q;
    for(scanf("%d", &q); q > 0; --q)
        Solve();
    return 0;
}
