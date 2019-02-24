#include <bits/stdc++.h>
#define maxN 100002
#define maxB 5000002
using namespace std;
int n, m, b[maxB], ans, l[maxB];
int s[maxB];
struct interv
{
    int x, y;
} v[maxN];
void read()
{
    int i;
    freopen("bucket.in", "r", stdin);
    scanf("%d %d", &n, &m);
    for (i = 0; i <= n + 1; ++ i)
        l[i] = -1;
    for (i = 1; i <= m; ++ i)
    {
        scanf("%d %d", &v[i].x, &v[i].y);
        if (i > 1 && v[i].x < v[i - 1].x && v[i].y < v[i - 1].y)
        {
            ans = -1;
            return ;
        }
        if (i > 1 && v[i].x < v[i - 1].x)
        {
            ++ s[v[i].x];
            -- s[v[i - 1].x];
        }
        if (i > 1 && v[i].y < v[i - 1].y)
        {
            l[v[i].x] = max(l[v[i].x], v[i - 1].x);
        }
    }
}
void solve()
{
    int i, j;
    if (ans == -1)
        return ;
    for (i = 1; i <= n; ++ i)
    {
        s[i] += s[i - 1];
        l[i] = max(l[i], l[i - 1]);
    }

    for (i = 1; i <= n; ++ i)
    {
        bool ok = 1;
        int maxValue = 0;
        for (j = 1; i * j <= n; ++ j)
        {
            int val = i * j;
            maxValue = max(maxValue, i * j);
            if (s[val] != 0 || (l[val] > val - i))
            {
                ok = 0;
                break;
            }
        }

        if(ok) {
            if(l[n] > maxValue) {
                ok = 0;
            }
        }

        if (ok)
            b[++ ans] = i;
    }
}
void write()
{
    freopen("bucket.out", "w", stdout);
    if (ans == -1)
        printf("0\n");
    else
    {
        printf("%d\n", ans);
        for (int i = 1; i <= ans; ++ i)
            printf("%d ", b[i]);
    }
}
int main()
{
    read();
    solve();
    write();
    return 0;
}
