/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const long long inf = 1e16;

/*-------- Data --------*/
int n, m;
std::vector<int > a, b;
std::vector<long long > up, down;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m); a.resize(n + 1); b.resize(m + 1);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for(int i = 1; i <= m; i++) {
    scanf("%d", &b[i]);
  }
}

int Get(int x, int y) {
  return (a[x] + y) ^ (b[y] + x);
}

void Divide(int l1, int c1, int l2, int c2) {
  if(l1 == l2) {
    for(int i = c1; i < c2; i++) {
      printf("R");
    }
    return;
  }

  up = down = std::vector<long long >(m + 2, 0);

  int lm = (l1 + l2) / 2;

  for(int j = c1; j <= c2; j++) {
    up[j] = up[j - 1] + Get(l1, j);
  }
  for(int i = l1 + 1; i <= lm; i++) {
    up[c1] += Get(i, c1);
    for(int j = c1 + 1; j <= c2; j++) {
      up[j] = Get(i, j) + std::min(up[j], up[j - 1]);
    }
  }

  for(int j = c2; j >= c1; j--) {
    down[j] = down[j + 1] + Get(l2, j);
  }
  for(int i = l2 - 1; i > lm; i--) {
    down[c2] += Get(i, c2);
    for(int j = c2 - 1; j >= c1; j--) {
      down[j] = Get(i, j) + std::min(down[j], down[j + 1]);
    }
  }

  long long answer = inf;
  int idx = 0;

  for(int j = c1; j <= c2; j++) {
    if(answer > up[j] + down[j]) {
      answer = up[j] + down[j]; idx = j;
    }
  }

  Divide(l1, c1, lm, idx);
  printf("D");
  Divide(lm + 1, idx, l2, c2);
}

int main() {
  ReadInput();
  Divide(1, 1, n, m);
  return 0;
}
