// How about a coding trick?
#include <cstdio>
#include <unordered_set>
#include <cstring>
#define DIM 276997
using namespace std;
FILE *fin=freopen("dtcsu.in","r",stdin);
FILE *fout=freopen("dtcsu.out","w",stdout);

unordered_set <long long int> elem;
char S[20];

long long int lastbit(long long int x)
{
    return ((x ^ (x - 1)) & x);
}

void Read()
{
    int i, len, j;
    long long int val;
    for(i = 1; i <= DIM; ++i)
    {
        scanf("%lld ", &val);
        if( val & 1 )
            elem.insert(val);
    }
}

void Solve()
{
    int q, sol = 0;;
    long long int query;
    scanf("%d", &q);
    for(int i = 1; i <= q; ++i)
    {
        scanf("%lld", &query);
        if( !query )
            continue;
        query /= lastbit(query);
        if( elem.find(query) != elem.end() )
            ++sol;
    }
    printf("%d", sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
