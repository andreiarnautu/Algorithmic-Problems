/**
  *  Worg
  *  Mar 9, 2018
  *  5:33:21 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("fibo4.in", "r", stdin); FILE *fout = freopen("fibo4.out", "w", stdout);

const int mod = 666013;
const int period = 1332028;
const int maxN = 1e6 + 5;

/*-------- Data --------*/
int fib[period];

int n, m;
int v[maxN];
/*-------- --------*/

int Mod(int x) {
  if(x >= mod) return x - mod;
  if(x < 0) return x + mod;
  return x;
}

void Precompute() {
  fib[0] = 0; fib[1] = 1;
  for(int i = 2; i < period; i++) {
    fib[i] = Mod(fib[i - 1] + fib[i - 2]);
  }
}

void ProcessQueries() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    long long x, y, k; scanf("%lld%lld%lld", &x, &y, &k);

    v[x] = Mod(v[x] + fib[k % period]);
    v[x + 1] = Mod(v[x + 1] + fib[(k - 1) % period]);
    v[y + 1] = Mod(v[y + 1] - fib[(k + y - x + 1) % period]);
    v[y + 2] = Mod(v[y + 2] - fib[(k + y - x) % period]);
  }
}

void Write() {
  for(int i = 2; i <= n; i++) {
    v[i] = Mod(v[i] + Mod(v[i - 1] + v[i - 2]));
  }

  for(int i = 1; i <= n; i++) {
    printf("%d ", v[i]);
  }
}

int main() {
  Precompute();

  ProcessQueries();

  Write();

  return 0;
}
