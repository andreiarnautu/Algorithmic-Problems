/**
  *  Worg
  *  Mar 18, 2018
  *  10:09:15 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("galeti2.in", "r", stdin); FILE *fout = freopen("galeti2.out", "w", stdout);

const int maxN = 1e5 + 5;

/*-------- Data --------*/
long long n, e;

int crtH, maxH;
std::vector<int > list[maxN];
/*-------- --------*/

void Solve() {
  list[0].push_back(1);

  int i;
  for(i = 2; i <= n; i++) {
    if((crtH + 1) + (n - i) <= e) {
      crtH++; list[crtH].push_back(i);
      e -= crtH;
    } else {
      break;
    }
  }

  maxH = crtH;
  for(; i <= n; i++) {
    while(crtH > 0 && crtH + (n - i) > e) {
      crtH--;
    }

    list[crtH].push_back(i); e -= crtH;
  }
}

int main() {
  scanf("%lld %lld", &n, &e);

  Solve();

  for(int i = maxH; i > 0; i--) {
    for(auto& itr : list[i]) {
      printf("%d %d\n", itr, list[i - 1][0]);
    }
  }

  return 0;
}
