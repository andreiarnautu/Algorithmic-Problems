// @Worg
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
FILE *fin=freopen("meciul.in","r",stdin);
FILE *fout=freopen("meciul.out","w",stdout);

int n, m, O[100003];
vector <int> V[100003];
vector <int>::iterator it;
queue <int> Q;

void BFS(int first)
{
    int nod;
    Q.push(first);

    while( !Q.empty() )
    {
        nod = Q.front();
        for(it = V[nod].begin(); it < V[nod].end(); ++it)
            if( !O[*it] )
            {
                O[*it] = 3 - O[nod];
                Q.push(*it);
            }
        Q.pop();
    }
}

void Solve()
{
    int x, y;
    scanf("%d %d", &n, &m);

    scanf("%d %d", &x, &y);
    O[x] = 1, O[y] = 2;
    printf("YES\n");

    for(int i = 2; i <= m; ++i)
    {
        scanf("%d %d", &x, &y);
        if( !O[x] && !O[y] )
        {
            V[x].push_back(y);
            V[y].push_back(x);
            printf("YES\n");
        }
        else if( O[x] && !O[y] )
        {
            O[y] = 3 - O[x];
            printf("YES\n");
            BFS(y);
        }
        else if( !O[x] && O[y] )
        {
            O[x] = 3 - O[y];
            printf("YES\n");
            BFS(x);
        }
        else
        {
            if( O[x] == O[y] )
                printf("NO\n");
            else
                printf("YES\n");
        }
    }

    for(int i = 0; i <= n + 3; ++i)
    {
        V[i].clear();
    }
    memset(O, 0, sizeof(O));
}

int main()
{
    int t;
    for(scanf("%d", &t); t > 0 ; --t)
        Solve();
    return 0;
}
