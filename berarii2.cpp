/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

#define DIM 1000100
#define buffDIM 100000

using namespace std;
FILE *fin=freopen("berarii2.in","r",stdin);
FILE *fout=freopen("berarii2.out","w",stdout);      // the problem is easly solveable by visiting all the nodes available
                                                    // from the starting ones
vector <int> G[DIM];
vector <int>::iterator it;
queue <int> Q;

char buff[buffDIM];
bool viz[DIM];
int n, m, p, pos, ramase;

void read(int &nr)
{
    nr = 0;
    while( buff[pos] < '0' || buff[pos] > '9' )
        if( ++pos == buffDIM )
            fread(buff, 1, buffDIM, stdin), pos = 0;

    while( buff[pos] >= '0' && buff[pos] <= '9' )
    {
        nr = nr * 10 + buff[pos] - '0';
        if( ++pos == buffDIM )
            fread(buff, 1, buffDIM, stdin), pos = 0;
    }
}

void Set()
{
    int i, x, y;

    fread(buff, 1, buffDIM, stdin);
    read(n); read(m); read(p);
    for(i = 1; i <= m; ++i)
    {
        read(x); read(y);
        G[y].push_back(x);
    }
    for(i = 1; i <= p; ++i)
    {
        read(x); Q.push(x); viz[x] = 1;
    }
    ramase = n - p;
}

void Solve()
{
    int vf;

    while( !Q.empty() )
    {
        vf = Q.front(); Q.pop();
        for(it = G[vf].begin(); it != G[vf].end(); ++it)
            if( !viz[*it] )
            {
                viz[*it] = 1;
                Q.push(*it);
                --ramase;
            }
    }
    printf("%d\n", ramase);
    for(int i = 1; i <= n; ++i)
        if( !viz[i] )
            printf("%d\n", i);
}

int main()
{
    Set();
    Solve();
    return 0;
}
