#include <cstdio>
#include <vector>
using namespace std;
FILE *fin=freopen("crescator.in","r",stdin);
FILE *fout=freopen("crescator.out","w",stdout);

vector <int> V;
int n;

int main()
{
    int i, x, cnt = 1, j, best = 0;
    long long int sol = 0;

    scanf("%d", &n);
    for(i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        V.push_back(x);
    }

    for(i = 1; i < n ; ++i)
    {
        if( V[i] < V[i - 1] )
        {
            sol += 1LL * cnt * (cnt + 1) / 2;
            if( cnt > best )
                best = cnt;
            cnt = 1;
        }
        else
            ++cnt;
    }
    if( cnt > best )
        best = cnt;
    sol += 1LL * cnt * (cnt + 1) / 2;

    printf("%lld %d", sol, best);
}
