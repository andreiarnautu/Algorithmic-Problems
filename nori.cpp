/**
  *  Worg
  *  Mar 10, 2018
  *  7:50:27 PM
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("nori.in", "r", stdin); FILE *fout = freopen("nori.out", "w", stdout);

const int maxN = 1e5 +5;
const int coef = 1e6;

/*-------- Data --------*/
int n, m;
int v[coef * 2 + 5];
/*-------- --------*/

void ReadData() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    double x, y, r; scanf("%lf%lf%lf", &x, &y, &r);

    double dist = std::sqrt(x*x + y*y);

    double a = std::atan(y / x);

    double b = std::asin(r / dist);

    a *= coef; b *= coef;

    v[int(a + b)]--; v[int(a - b)]++;
  }

  for(int i = 1; i < coef * 2 + 5; i++) {
    v[i] += v[i - 1];
  }
}

void Solve() {
  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    double x, y; scanf("%lf%lf", &x, &y);
    double a = coef * atan(y / x);

    if(v[(int)a]) {
      printf("0");
    } else {
      printf("1");
    }
  }
}

int main() {
  ReadData();

  Solve();
  return 0;
}
