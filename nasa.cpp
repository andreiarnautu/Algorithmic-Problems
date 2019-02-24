/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("nasa.in", "r", stdin); FILE *fout = freopen("nasa.out", "w", stdout);

const int limit = 50000;

int a, b;
int prime[limit], sgn[limit];


int main() {
  scanf("%d%d", &a, &b);

  for(int i = 1; i < limit; i++) {
    sgn[i] = 1; prime[i] = true;
  }

  for(int i = 2; 1LL * i * i <= b; i++) {
    if(prime[i]) {
      for(int j = i * i; j < limit; j += i * i) {
        sgn[j] = false;
      }

      for(int j = i; j < limit; j += i) {
        prime[j] = false; sgn[j] *= -1;
      }
    }
  }

  long long sol = 0;
  for(int i = 1; i < limit; i++) {
    sol += 1LL * sgn[i] * (b / (1LL * i * i) - (a - 1) / (1LL * i * i));
  }

  printf("%lld\n", sol);
  return 0;
}
