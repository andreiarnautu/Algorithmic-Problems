/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

int a[1005];

int main() {
  int n, m, c; scanf("%d%d%d", &n, &m, &c);

  for(int i = 1, j; i <= m; i++) {
    int x; scanf("%d", &x);
    if(x * 2 > c) {
      for(j = n; a[j] >= x; j--);
    } else {
      for(j = 1; a[j] && a[j] <= x; j++);
    }
    a[j] = x; printf("%d\n", j); fflush(stdout);

    for(int j = 1; j <= n; j++) {
      if(a[j] == 0) {
        break;
      }
      if(j == n) {
        return 0;
      }
    }
  }
	return 0;
}
