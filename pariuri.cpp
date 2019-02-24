/*
    How about a coding trick?
*/
#include <cstdio>
#include <vector>
#define MOD 10003
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;

FILE *fin=freopen("pariuri.in","r",stdin);
FILE *fout=freopen("pariuri.out","w",stdout);

vector < PII > Hash[MOD];
vector < PII >::iterator it;

void Add(int val, int cant)
{
    bool ok = 0;
    for(it = Hash[val % MOD].begin(); it != Hash[val % MOD].end(); ++it)
        if( it -> fi == val )
            { ok = 1; break; }
    if( !ok )
    {
        Hash[val % MOD].push_back( make_pair( val, cant ) );
    }
    else
    {
        it -> se += cant;
    }

}

void Set()
{
    int n, m, i, x, y;
    for(scanf("%d", &n); n > 0; --n)
    {
        scanf("%d", &m);
        for(i = 1; i <= m; ++i)
        {
            scanf("%d%d", &x, &y);
            Add(x, y);
        }
    }
}

void Write()
{
    int nr = 0;
    for(int i = 0; i < MOD; ++i)
        nr += Hash[i].size();
    printf("%d\n", nr);
    for(int i = 0; i < MOD; ++i)
        for(it = Hash[i].begin(); it != Hash[i].end(); ++it)
            printf("%d %d ", it -> fi, it -> se);
}

int main()
{
    Set();
    Write();
    return 0;
}
