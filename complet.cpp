/**
  *  Worg
  *  Mar 23, 2018
  *  10:39:46 AM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("complet.in", "r", stdin); FILE *fout = freopen("complet.out", "w", stdout);

const int maxN = 1e5 + 5;
const int mod = 40099;

/*-------- Data --------*/
int n, q;
int v[maxN];

int initialSum;
int invMod;

int pows[mod + 1];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &q);

  for(int i = 1; i <= n; i++) {
    scanf("%d", &v[i]); initialSum += v[i];
  }

  std::sort(v + 1, v + n + 1);

  initialSum %= mod;
}

int Power(int base, long long exp) {
  int ans = 1, aux = base % mod;

  for(long long i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      ans = ans * aux % mod;
    }
    aux = aux * aux % mod;
  }

  return ans;
}

int GetSum(long long level) {
  return 1LL * initialSum * pows[level % (mod - 1)] % mod;
}

int Mod(int x) {
  if(x >= mod) return x - mod;
  if(x < 0) return x + mod;
  return x;
}

void Query(long long t, int p) {
  if(t % 2 == 1) {
    p = n - p + 1;
  }

  if(t % 2 == 0) {
    int x = Mod(GetSum(t) - initialSum);

    x = 1LL * x * invMod % mod;

    x = Mod(x + v[p]);

    printf("%d\n", x);
  } else {
    int x = Mod(GetSum(t) + initialSum);

    x = 1LL * x * invMod % mod;

    x = Mod(x - v[p]);

    printf("%d\n", x);
  }
}

void Precompute() {
  invMod = Power(n, mod - 2);

  pows[0] = 1;
  for(int i = 1; i < mod; i++) {
    pows[i] = 1LL * pows[i - 1] * (n-1) % mod;
  }
}

void Solve() {
  long long x, y, z, t1, t2, t3, p1, p2, p3;

  const long long modHere = 1e15;

  scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld", &x, &y, &z, &t1, &t2, &t3, &p1, &p2, &p3);

  Query(t1, p1); Query(t2, p2); Query(t3, p3);

  for(int i = 4; i <= q; i++) {
    long long t = 1 + (t1 * x + t2 * y + t3 * z) % modHere;
    long long p = 1 + (p1 * x + p2 * y + p3 * z) % n;

    Query(t, p);

    t1 = t2; t2 = t3; t3 = t;
    p1 = p2; p2 = p3; p3 = p;
  }
}

int main() {
  ReadInput();

  Precompute();

  Solve();
  return 0;
}
