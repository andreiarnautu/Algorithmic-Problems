/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("borg.in", "r", stdin); FILE *fout = freopen("borg.out", "w", stdout);

const int mod = 30103;
const int maxV = 8000 + 5;

int n, m, h, k;
int fact[maxV];

int Power(int base, int exp) {
  int ans = 1, aux = base;

  for(int i = 1; i <= exp; i <<= 1) {
    if(exp & i) {
      ans = ans * aux % mod;
    }
    aux = aux * aux % mod;
  }

  return ans;
}

int Comb(int a, int b) {
  if(b > a) return 0;

  //  a! / [b! * (a - b)!]
  int ans = fact[a] * Power(fact[b], mod - 2) % mod;

  return ans * Power(fact[a - b], mod - 2);
}

int main() {
  fact[0] = 1;
  for(int i = 1; i < maxV; i++) {
    fact[i] = (fact[i - 1] * i) % mod;
  }

  int sol = 0;

  scanf("%d%d%d%d", &n, &m, &h, &k);

  for(int i1 = 0; i1 < n; i1++) {
    for(int i2 = 0; i2 < m; i2++) {
      for(int i3 = 0; i3 < h; i3++) {
        int here = 1LL * Comb(n, i1) * Comb(m, i2) % mod * Comb(h, i3) % mod * Comb((n - i1) * (m - i2) * (h - i3), k) % mod;
        //printf("%d\n", here);

        if((i1 + i2 + i3) % 2 == 1) {
          sol = (sol - here + mod) % mod;
        } else {
          sol = (sol + here) % mod;
        }
      }
    }
  }

  printf("%d", sol % mod);

  return 0;
}
