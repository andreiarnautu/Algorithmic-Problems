/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

#define fi      first
#define se      second
#define pb      push_back
#define mp      make_pair
#define dim     1010
#define inf     1000000000
#define inFile  "ciclu.in"
#define outFile "ciclu.out"
#define source  (n + 1)

using namespace std;

queue <int> Q;
vector < pair<int,int> > G[dim];
vector < pair<int,int> >::iterator it;

long long int dmin[dim];
int inCount[dim], inQueue[dim];
int n, m, sol;

void queue_clear()
{

    while(!Q.empty())
        Q.pop();
}

void elemset(int *p, int nr, int val)
{

    for(int i = 1; i <= nr; ++i)
        p[i] = val;
}

void elemsetLL(long long int *p, int nr, long long int val)
{

    for(int i = 1; i <= nr; ++i)
        p[i] = val;
}

void readData()
{

    freopen(inFile, "r", stdin);
    scanf("%d %d", &n, &m);

    int x, y, z;
    for(int i = 1; i <= m; ++i)
    {

        scanf("%d %d %d ", &x, &y, &z);
        G[x].pb(mp(y, z * 100));
    }

    for(int i = 1; i <= n; ++i)         /* we construct edges from the source node to the others */
        G[source].pb(mp(i, 0));
}

int bellman_ford(int val)
{

    elemsetLL(dmin, n, inf);
    elemset(inQueue, n, 0);
    elemset(inCount, n, 0);
    queue_clear();

    int node;
    Q.push(source);
    while(!Q.empty())
    {

        node = Q.front();
        Q.pop();
        inQueue[node] = 0;

        for(it = G[node].begin(); it != G[node].end(); ++it)
            if(dmin[it->fi] >= dmin[node] + 1LL * it->se - 1LL * val)
            {

                dmin[it->fi] = dmin[node] + 1LL * it->se - 1LL * val;
                if(!inQueue[it->fi])
                {

                    inQueue[it->fi] = 1;
                    ++inCount[it->fi];
                    Q.push(it->fi);
                    if(inCount[it->fi] >= n)
                        return 1;
                }
            }
    }
    return 0;
}

void writeData()
{

    float afis;

    if(bellman_ford(sol - 1))
        afis = (float) (sol - 1) / 100;
    else
        afis = (float) sol / 100;
    freopen(outFile, "w", stdout);
    printf("%.2f", afis);
}

int main()
{

    readData();

    int low = 1, high = 100000 * 100, mid;
    while(low <= high)
    {

        mid = (low + high) >> 1;
        if(bellman_ford(mid))
            sol = mid, high = mid - 1;
        else
            low = mid + 1;
    }

    writeData();
    return 0;
}
