#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;
FILE *fin=freopen("gropi1.in","r",stdin);
FILE *fout=freopen("gropi1.out","w",stdout);

deque <int> D;
struct punct{int x, y;} V[1003];
int n, l;

inline int cmp(punct a, punct b)
{
    return (a.y > b.y);
}

void Read()
{
    scanf("%d %d", &n, &l);
    for(int i = 1; i <= n ; ++i)
        scanf("%d %d ", &V[i].x, &V[i].y);
    sort(V + 1, V + n + 1, cmp);
}

inline int ABS(int x)
{
    return (x > 0 ? x : -x);
}

void Solve()
{
    int best = 0, i, j;

    for( i = 1; i <= n; ++i )
    {
        D.clear();
        for(j = n; j > 0; --j)
            if( ABS(V[j].x - V[i].x) <= l && V[j].x <= V[i].x )
            {
                D.push_back(j);
                while( !D.empty() && ABS(V[D.front()].y - V[D.back()].y) > l )
                    D.pop_front();
                if( D.size() > best )
                {
                    best = D.size();
                }
            }
    }

    printf("%d", best);
}

int main()
{
    Read();
    Solve();
    return 0;
}
