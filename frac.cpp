/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("frac.in", "r", stdin); FILE *fout = freopen("frac.out", "w", stdout);

/*-------- Data --------*/
long long n, p;
std::vector<long long > divs;
/*-------- --------*/

void GetDivisors() {
  for(long long i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      divs.push_back(i);

      while(n % i == 0) {
        n /= i;
      }
    }
  }

  if(n != 0) {
    divs.push_back(n);
  }
}

long long Count(const long long x) {
  long long limit = 1LL << (int)divs.size();
  long long ans = 0;

  for(long long i = 0; i < limit; i++) {
    long long cnt = 0, prod = 1;

    for(long long j = 0; j < (int)divs.size(); j++) {
      if(i & (1LL << j)) {
        cnt++; prod *= divs[j];
      }
    }

    if(cnt % 2 == 0) {
      ans += x / prod;
    } else {
      ans -= x / prod;
    }
  }

  return ans >= p;
}

int main() {
  scanf("%lld%lld", &n, &p);

  GetDivisors();

  long long sol = 0;
  for(long long step = 1LL << 60; step > 0; step >>= 1) {
    if(Count(sol + step) == false) {
      sol += step;
    }
  }

  printf("%lld\n", sol + 1);
  return 0;
}
