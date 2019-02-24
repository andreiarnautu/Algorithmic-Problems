#include <cstdio>
#include <vector>
#include <queue>
#define DIM 100003
using namespace std;

FILE *fin=freopen("dfs.in","r",stdin);
FILE *fout=freopen("dfs.out","w",stdout);

vector <bool> viz(DIM);
queue <int> Q;
vector <int> V[DIM];
vector <int>::iterator it;
int n, m;

void Read()
{
    scanf("%d %d", &n, &m);
    int x, y;

    for(int i = 1; i <= m; ++i)
    {
        scanf("%d %d ", &x, &y);
        V[x].push_back(y);
        V[y].push_back(x);
    }
}

void BFS(int first)
{
    int nod;
    viz[first] = 1;
    Q.push(first);

    while( !Q.empty() )
    {
        nod = Q.front();
        viz[nod] = 1;
        for(it = V[nod].begin(); it < V[nod].end() ; ++it)
            if( !viz[*it] )
            {
                Q.push(*it);
                viz[*it] = 1;
            }
        Q.pop();
    }
}

void Solve()
{
    int ansCount = 0;
    for(int i = 1; i <= n; ++i)
        if( !viz[i] )
        {
            ++ansCount;
            BFS(i);
        }
    printf("%d", ansCount);
}

int main()
{
    Read();
    Solve();
    return 0;
}
