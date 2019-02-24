#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin=freopen("linterv.in","r",stdin);
FILE *fout=freopen("linterv.out","w",stdout);

struct interval{int a, b;} v[10003];


int comp(interval x, interval y)
{
    return (x.a < y.a);
}

void Solve()
{
    int n, i, len, Max;
    scanf("%d", &n);

    for(i = 1; i <= n ; ++i)
        scanf("%d %d", &v[i].a, &v[i].b);

    sort(v + 1, v + n + 1, comp);

    //for(i = 1 ; i <= n ; ++i)
      //  printf("%d %d\n", v[i].a, v[i].b);

    len = v[1].b - v[1].a;
    Max = v[1].b;

    for(i = 2 ; i <= n ; ++i)
    {
        len += max(0, v[i].b - max(v[i].a, Max));
        Max = max(Max, v[i].b);
    }

    printf("%d\n", len);
}

int main()
{
    int t;
    for(scanf("%d", &t); t > 0 ; --t)
        Solve();
    return 0;
}
