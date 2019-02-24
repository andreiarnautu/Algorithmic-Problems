/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("cia.in", "r", stdin); FILE *fout = freopen("cia.out", "w", stdout);

const int maxT = 7e4 + 5;
const int maxN = 1e7 + 5;

/*-------- Data --------*/
int n, t, k, mod;
int a[maxT], b[maxT];

int v[maxN];

std::vector<int > pref, suff;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d%d%d", &n, &t, &k, &mod);
  for(int i = 0; i < t; i++) {
    scanf("%d", &a[i]);
  }
  for(int i = 0; i < t; i++) {
    scanf("%d", &b[i]);
  }

  for(int i = 0; i < n; i++) {
    v[i] = (a[i % t] ^ b[i / t]) % mod;
  }
}

void ComputePartials(int i) {
  std::vector<int > prefHere(k), suffHere(k);
  prefHere[0] = 1; suffHere[0] = v[i];

  for(int j = 1; j < k && i - j >= 0; j++) {
    prefHere[j] = 1LL * prefHere[j - 1] * v[i - j] % mod;
  }
  for(int j = 1; j < k && i + j < n; j++) {
    suffHere[j] = 1LL * suffHere[j - 1] * v[i + j] % mod;
  }

  suff = suffHere; pref = prefHere;
}

void Solve() {
  int sol = 0;

  ComputePartials(0);

  for(int left = 0, right = k - 1; right < n; left++, right++) {
    if(right % k == 0) {
      ComputePartials(right);
    }

    if(left % k == 0) {
      sol ^= suff[k - 1];
    } else if(right % k == 0) {
      sol ^= (1LL * pref[k - 1] * v[right] % mod);
    } else {
      int idx = right / k;

      sol ^= (1LL * pref[idx * k - left] * suff[right - idx * k] % mod);
    }
  }

  printf("%d\n", sol);
}

int main() {
  ReadInput();

  Solve();

  return 0;
}
