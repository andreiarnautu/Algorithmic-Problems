/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("color3.in", "r", stdin); FILE *fout = freopen("color3.out", "w", stdout);

const int maxN = 200 + 5;
const int modulo = 666013;

/*-------- Data --------*/
int n, m, k, c;
int col[maxN], init[maxN][maxN];

int sys[maxN][maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d%d%d", &n, &m, &k, &c);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &col[i]);
  }

  for(int i = 1; i <= m; i++) {
    for(int j = 1; j <= n; j++) {
      scanf("%d", &init[j][i]);
    }
  }
}

void Euclid(int a, int b, int& x, int& y) {

  if (!b) {
    x = 1;
    y = 0;
    return;
  }

  int xa, ya;
  Euclid(b, a%b, xa, ya);

  xa = ya;
  ya = xa - (a / b)*ya;
}

int InvMod(int a, int mod) {

  int x, y;
  Euclid(mod, a, x, y);

  while (y < 0)
    y += mod;
  y %= mod;

  return y;
}

int SolveCase(const int mod) {
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      sys[i][j] = init[i][j] % mod;
    }
    sys[i][m + 1] = (c % mod - col[i] % mod + mod) % mod;
  }

  int cntFree = 0;

  for(int i = 1, j = 1; i <= n && j <= m; i++, j++) {
    int k;
    for(k = i; k <= n && !sys[k][j]; k++);

    if(k == n + 1) {  //  Found a free one
      cntFree++; i--;
      continue;
    }

    //  Swap lines
    for(int itr = 1; itr <= m + 1; itr++) {
      std::swap(sys[i][itr], sys[k][itr]);
    }

    for(int k = i + 1; k <= n; k++) {
      int coef = (1LL * sys[k][j] * InvMod(sys[i][j], mod)) % mod;

      for(int itr = 1; itr <= m + 1; itr++) {
        sys[k][itr] = (sys[k][itr] - (1LL * coef * sys[i][itr]) % mod + mod) % mod;
      }
    }
  }

  int ans = 1;
  for(int i = 1; i <= cntFree; i++) {
    ans = (1LL * ans * mod) % modulo;
  }
  return ans;
}

int Solve() {
  int sol = 1;
  for(int i = 2; i * i <= k; i++) {
    if(k % i) continue;

    sol = 1LL * sol * SolveCase(i) % modulo;
    k /= i;
  }

  if(k > 1) {
    sol = 1LL * sol * SolveCase(k) % modulo;
  }

  return sol;
}

int main() {
  ReadInput();

  printf("%d\n", Solve());

  return 0;
}
