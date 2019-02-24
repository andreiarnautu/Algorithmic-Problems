/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("crescator2.in", "r", stdin); FILE *fout = freopen("crescator2.out", "w", stdout);

const int mod = 700001;

int N, sol;
std::vector<std::vector<int > > a, b;

int main() {
  scanf("%d", &N);
  int rad = std::max(2, (int)std::sqrt((double)N) + 1);
  a = b = std::vector<std::vector<int > >(2, std::vector<int >(N + 5, 0));

  //!  Compute a
  a[0][0] = 1;
  for(int i = 1; i < rad; i++) {
    for(int j = 0; j <= N; j++) {
      a[1][j] = a[0][j];
      if(j >= i) {
        a[1][j] = (a[1][j] + a[1][j - i]) % mod;
      }
    }
    a[0] = a[1];
  }

  for(int i = 1; i <= N; i++) {
    a[0][i] = (a[0][i] + a[0][i - 1]) % mod;
  }

  sol = (a[0][N] - 1 + mod) % mod;  //  Don't take the empty string
  //printf("%d\n", sol);

  //!  Compute b
  b[0][0] = 1;

  for(int i = 1; i < rad; i++) {
    for(int j = 0; j <= N; j++) {
      if(j > 0) {
        b[1][j] = b[0][j - 1];
      } else {
        b[1][j] = 0;
      }

      if(j >= i) {
        b[1][j] = (b[1][j] + b[1][j - i]) % mod;
      }

      int rest = N - j - i * (rad - 1);
      if(rest >= 0) {
        sol = (sol + 1LL * b[1][j] * a[0][rest] % mod) % mod;
      }
    }
    b[0] = b[1];
  }

  printf("%d\n", sol);
  return 0;
}
