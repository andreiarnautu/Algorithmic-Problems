/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int kDim = 705;
const int mod = 1e9 + 7;

/*-------- Data --------*/
int n, nr[kDim];
char s[kDim];
int dp[kDim][kDim][2][2];
/*-------- --------*/

void Add(int &to, int from) {
  to = (to + from >= mod) ? (to + from - mod) : (to + from);
}

void ComputeDp(const int digit) {
  memset(dp, 0, sizeof(dp)); dp[0][0][0][0] = 1;

  //!  dp[i][j][a][b] -> primele {i} cifre au fost procesate, {j} sunt <= decat digit, {a} numarul e deja mai mic sau nu ca nr, {b} numaram sau nu digit

  for(int i = 0; i < n; i++) {
    for(int j = 0; j <= i; j++) {
      //  Cazul 1 - numarul nu e deja mai mic
      for(int d = 0; d <= nr[i + 1]; d++) {
        if(d != digit) {
          Add(dp[i + 1][j + (d < digit)][d < nr[i + 1]][0], dp[i][j][0][0]);
          Add(dp[i + 1][j + (d < digit)][d < nr[i + 1]][1], dp[i][j][0][1]);
        } else {
          Add(dp[i + 1][j + 1][d < nr[i + 1]][0], dp[i][j][0][0]);

          Add(dp[i + 1][j + 1][d < nr[i + 1]][1], dp[i][j][0][0]);

          Add(dp[i + 1][j][d < nr[i + 1]][1], dp[i][j][0][1]);
        }
      }

      //  Cazul 2 - numarul e deja mai mic
      for(int d = 0; d < 10; d++) {
        if(d != digit) {
          Add(dp[i + 1][j + (d < digit)][1][0], dp[i][j][1][0]);
          Add(dp[i + 1][j + (d < digit)][1][1], dp[i][j][1][1]);
        } else {
          Add(dp[i + 1][j + 1][1][0], dp[i][j][1][0]);

          Add(dp[i + 1][j + 1][1][1], dp[i][j][1][0]);

          Add(dp[i + 1][j][1][1], dp[i][j][1][1]);
        }
      }
    }
  }
}

int main() {
  scanf("%s", s); n = strlen(s);
  for(int i = 1; i <= n; i++) {
    nr[i] = s[i - 1] - '0';
  }

  long long sol = 0;
  for(int digit = 1; digit < 10; digit++) {
    ComputeDp(digit);

    long long pow10 = 1;
    for(int pos = n; pos > 0; pos--) {
      long long here = (dp[n][pos][0][1] + dp[n][pos][1][1]) % mod;

      here = here * (pow10 * digit % mod) % mod;

      sol = (sol + here) % mod;

      pow10 = pow10 * 10 % mod;
    }
  }

  printf("%lld\n", sol);
	return 0;
}
