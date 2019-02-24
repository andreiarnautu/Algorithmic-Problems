/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("mezzaluna.in", "r", stdin); FILE *fout = freopen("mezzaluna.out", "w", stdout);

const int kMaxC = 2000 + 5;
const int kModulo  = 1e9 + 7;

/*-------- Data --------*/
struct Str {
  int cuts, ways;

  Str() {cuts = 0; ways = 0;}

  Str(int _cuts, int _ways) {cuts = _cuts; ways = _ways;}
};

int n;
int count[kMaxC][kMaxC];
std::vector<int > xVals[kMaxC], yVals[kMaxC];

Str dp[kMaxC][kMaxC], colDp[kMaxC], aboveDp[kMaxC][kMaxC];
/*-------- --------*/
Str Combine(Str a, Str b) {
  if(a.ways == 0) {
    return b;
  } else if(b.ways == 0) {
    return a;
  } else {
    Str ans = a;
    if(b.cuts > a.cuts) {
      ans = b;
    } else if(b.cuts == a.cuts) {
      ans.ways += b.ways;
      if(ans.ways >= kModulo) ans.ways -= kModulo;
    }
    return ans;
  }
}

void ReadInput() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    int x, y; scanf("%d%d", &x, &y);
    count[x][y] ++;
    xVals[y].push_back(x); yVals[x].push_back(y);
  }

  for(int i = 1; i <= 2000; i++) {
    std::sort(xVals[i].begin(), xVals[i].end());
    std::sort(yVals[i].begin(), yVals[i].end());
  }
}

int CountY(int x, int limit) {
  return (!yVals[x].empty() && yVals[x].back() >= limit);
}

int CountX(int y, int limit) {
  return(!xVals[y].empty() && xVals[y][0] <= limit);
}

void RunDP() {
  const int limit = 2001;

  dp[0][limit]= {0, 1}; colDp[limit] = {0, 1};
  for(int i = 0; i <= limit; i++) {
    aboveDp[0][i] = {0, 1};
  }

  for(int i = 1; i < limit; i++) {
    Str lineDp = {0, 0};
    for(int j = limit - 1; j > i; j--) {
      //!  [i - k, j] -> [i, j]
      if(CountY(i, j)) {
        Str now = {colDp[j].cuts + 1, colDp[j].ways};
        dp[i][j] = Combine(dp[i][j], now);
      }
      //!  [i, j + k] -> [i, j]
      if(CountX(j, i)) {
        Str now = {lineDp.cuts + 1, lineDp.ways};
        dp[i][j] = Combine(dp[i][j], now);
      }

      //!  [i - p, j + q] -> [i, j]
      if(count[i][j]) {
        Str now = {aboveDp[i - 1][j + 1].cuts + 1, aboveDp[i - 1][j + 1].ways};
        dp[i][j] = Combine(dp[i][j], now);
      }

      lineDp = Combine(lineDp, dp[i][j]);
      colDp[j] = Combine(colDp[j], dp[i][j]);
      aboveDp[i][j] = Combine(aboveDp[i - 1][j], lineDp);
    }
  }

  Str ans = {0, 0};
  for(int i = 1; i < limit; i++) {
    for(int j = limit; j > i; j--) {
      ans = Combine(ans, dp[i][j]);
    }
  }
  printf("%d %d\n", ans.cuts, ans.ways);
}

int main() {
  ReadInput();

  RunDP();
	return 0;
}
