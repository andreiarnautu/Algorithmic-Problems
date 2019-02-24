/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

int n;
std::vector<int > a, b, c, d;

int main() {
  scanf("%d", &n);
  a = b = c = d = std::vector<int >(n + 1, 0);

  a[1] = 1; b[0] = 1;
  for(int i = 2; i <= n; i++) {
    c = a; d = b;
    a = b = std::vector<int >(n + 1, 0);

    for(int j = 0; j < i; j++) {
      a[j + 1] = c[j];
    }
    b = c;

    //!  Try adding
    bool ok = true;

    std::vector<int > e = a;
    for(int j = 0; j < n; j++) {
      e[j] += d[j];
      if(e[j] > 1 || e[j] < -1) {
        ok = false;
      }
    }

    if(ok) {
      a = e;
    } else {
      for(int j = 0; j < n; j++) {
        a[j] -= d[j];
      }
    }
  }

  printf("%d\n", n);
  for(int i = 0; i <= n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n%d\n", n - 1);
  for(int i = 0; i < n; i++) {
    printf("%d ", b[i]);
  }
	return 0;
}
