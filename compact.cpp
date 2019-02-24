// How about a coding trick?
#include <cstdio>
#include <deque>
using namespace std;
FILE *fin=freopen("compact.in","r",stdin);
FILE *fout=freopen("compact.out","w",stdout);

deque <int> minim, maxim;
int v[1000100], n;

inline int max(int a, int b)
{
    return ((a > b) ? a : b);
}

void Read()
{
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        scanf("%d", &v[i]);
}

inline int max_search()
{
    if( maxim.size() == 1 )
        return 1;
    else
        return maxim[maxim.size() - 2] + 1;
}

inline int min_search(int pos, int i)
{
    int sol = -1, st = 0, dr = minim.size() - 1, m, indmax;

    indmax = dr;
    while( indmax > 0 && i - minim[indmax] < 2 )
        --indmax;

    while( st <= dr )
    {
        m = (st + dr) / 2;
        if( minim[m] >= pos )
        {
            sol = m;
            dr = m - 1;
        }
        else
            st = m + 1;
    }
    if( sol == -1 || i - minim[sol] < 2 )
        return 0;
    return max(0, (indmax - sol + 1));
}

void Solve()
{
    int i, p1, p2, j;
    long long int ret = 0;

    for(i = 1; i <= n; ++i)
    {
        while( !minim.empty() && v[minim.back()] >= v[i] )
            minim.pop_back();
        minim.push_back(i);

        while( !maxim.empty() && v[maxim.back()] <= v[i] )
            maxim.pop_back();
        maxim.push_back(i);


        p1 = max_search();
        if( p1 > i - 2 )
            continue;
        p2 = min_search(p1, i);
        ret += 1LL * p2;
    }
    printf("%lld", ret);
}

int main()
{
    Read();
    Solve();
    return 0;
}
