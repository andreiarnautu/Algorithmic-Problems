#include <cstdio>
#define inf 2000000000

using namespace std;
int i, j, t, c, p, n, k, v, z, Max, Min, a[100], d[100][100], x[100][100];
int main()
{
    freopen("optim.in", "r", stdin);
    freopen("optim.out", "w", stdout);
    scanf("%d%d\n", &n, &k);
    for (i=1; i<=n; ++i) scanf("%d", &a[i]);

    x[0][0] = 0; d[0][0] = 0;
    for (i=1; i<=n; ++i) {
      x[i][0]=x[i-1][0] + a[i];
      d[i][0]=d[i-1][0] + a[i];
      for (j=1; j<i && j<=k; ++j) {
         if (j<i-1) {
             Min = x[i-1][j] + a[i];
             Max = d[i-1][j] + a[i];
         }
         else {
             Min = inf;
             Max = -inf;
         }
         p=a[i];
         for (t=1; t<=j; t++) {
            p *=a[i-t];
            if (i-1 > j || (i-t-1 == 0)){
                z = x[i - t -1][j - t] + p;
                v = d[i - t -1][j - t] + p;
                if (z < Min) Min = z;
                if (v > Max) Max = v;
            }
         }
         x[i][j] = Min;
         d[i][j] = Max;

      }
    }
    printf("%d %d\n",x[n][k],d[n][k]);
    return 0;
}

