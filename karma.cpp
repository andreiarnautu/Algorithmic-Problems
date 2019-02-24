/**
  *  Worg
  *  Mar 18, 2018
  *  11:48:27 AM
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <algorithm>

FILE *fin = freopen("karma.in", "r", stdin); FILE *fout = freopen("karma.out", "w", stdout);

const int maxN = 21;
const int mod = 1e9 + 7;

/*-------- Data --------*/
int n, m;
char s[maxN];
int a[maxN][maxN], sht[maxN];

int dp[1 << maxN];
int cnt[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);

  assert(n <= 20); assert(m <= 20);

  for(int i = 0; i < n; i++) {
    scanf("%s", s);

    for(int j = 0; j < m; j++) {
      if(s[j] == '(') {
        a[i][j] = 1;
      } else {
        a[i][j] = -1;
      }
    }
  }
}

int Mod(int x) {
  if(x >= mod) return x - mod;
  if(x < 0) return x + mod;
  return x;
}

int RunDp() {
  dp[0] = 1;

  int limit = (1 << m);
  for(int msk = 1; msk < limit; msk++) {
    memset(cnt, 0, sizeof(cnt));

    int bits = 0, add = 0;
    for(int j = 0; j < m; j++) {
      if(msk & (1 << j)) {
        bits++;
        add = Mod(add + dp[msk - (1 << j)]);

        for(int i = 0; i < n; i++) {
          cnt[i] += a[i][j];
        }
      }
    }

    bool ok = true;
    for(int i = 0; i < n; i++) {
      if(cnt[i] < 0) {
        ok = false; break;
      }
    }

    if(ok) {
      dp[msk] = add;
    }
  }

  return dp[limit - 1];
}

int main() {
  ReadInput();
  printf("%d\n", RunDp());
  return 0;
}
