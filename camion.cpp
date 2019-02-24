/**
  *  Worg
  *  Mar 13, 2018
  *  9:18:30 AM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("camion.in", "r", stdin); FILE *fout = freopen("camion.out", "w", stdout);

const int maxN = 600 + 5;
const int maxK = 3e4 + 5;

/*-------- Data --------*/
int n, m, k, c;
int a[maxN][maxN];

int xbeg[maxK], ybeg[maxK], xfin[maxK], yfin[maxK];
/*-------- --------*/

int main() {
  scanf("%d%d%d%d", &n, &m, &k, &c);

  for(int i = 1; i <= k; i++) {
    scanf("%d%d%d%d", &xbeg[i], &ybeg[i], &xfin[i], &yfin[i]);
  }

  for(int line = 1; line <= n; line++) {
    int pos = c;

    for(int i = k; i >= 1; i--) {
      if(line < xbeg[i] || xfin[i] < line) continue;

      if(ybeg[i] <= pos) {
        pos += yfin[i] - ybeg[i] + 1;
        if(pos > m) break;
      }
    }

    printf("%d\n", (pos <= m) ? pos : 0);
  }

  return 0;
}
