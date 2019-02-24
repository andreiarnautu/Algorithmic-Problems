/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("geamuri.in", "r", stdin); FILE *fout = freopen("geamuri.out", "w", stdout);

/*-------- Data --------*/
int C, N, M;
std::vector<std::vector<int > > a;
std::vector<int > cnt;
/*-------- --------*/

int main() {
  scanf("%d%d", &C, &N);
  a = std::vector<std::vector<int > >(C + 5, std::vector<int >(C + 5, 0));
  cnt = std::vector<int >(N + 1, 0);

  for(int i = 0; i < N; i++) {
    int xs, ys, xf, yf; scanf("%d%d%d%d", &xs, &ys, &xf, &yf);
    a[xs][ys]++; a[xs][yf + 1]--; a[xf + 1][ys]--; a[xf + 1][yf + 1]++;
  }

  for(int i = 1; i <= C; i++) {
    for(int j = 1; j <= C; j++) {
      a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];

      cnt[a[i][j]]++;
    }
  }

  scanf("%d", &M);
  for(int i = 0; i < M; i++) {
    int k; scanf("%d", &k);
    printf("%d\n", cnt[k]);
  }
	return 0;
}
