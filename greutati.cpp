/**
  *  Worg
  *  Mar 19, 2018
  *  12:10:44 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("greutati.in", "r", stdin); FILE *fout = freopen("greutati.out", "w", stdout);

const long long limit = 1e18;
const int maxN = 1e5;
const int mod = 1e9 + 7;

/*-------- Structures --------*/
struct Str {
  int p, f;

  Str() {p = 0; f = 0;}
};
/*-------- Data --------*/
int n, p;
Str v[maxN];

int sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &p);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &v[i].p, &v[i].f);
  }
}

void Raise(long long exp) {
  long long aux = 2;
  for(long long i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      sol = 1LL * sol * aux % mod;
    }
    aux = aux * aux % mod;
  }
}

void Solve() {
  std::sort(v, v + n, [&](Str a, Str b) {
    return a.p > b.p;
  });

  long long sum;
  sum = sol = v[0].f % 2;

  for(int i = 1; i < n; i++) {
    if(sum != 0) {
      int exp = v[i - 1].p - v[i].p;

      Raise(exp);

      while(sum < limit && exp) {
        exp--; sum *= 2;
      }

      if(sum > limit) {
        sum = limit;
      }
    }

    if(sum > v[i].f) {
      sum -= v[i].f;

      sol = (sol - v[i].f + mod) % mod;
    } else {
      sum = sol = (v[i].f - sum) % 2;
    }
  }

  Raise(v[n - 1].p);

  printf("%d\n", sol);
}

int main() {
  ReadInput();

  Solve();
  return 0;
}
