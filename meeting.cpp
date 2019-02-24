/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("meeting.in", "r", stdin); FILE *fout = freopen("meeting.out", "w", stdout);

int main() {
  double x, y, z; scanf("%lf%lf%lf", &x, &y, &z);

  double len = (y - x) * 60;

  if(z > len) {printf("1.0\n"); return 0;}

  double sol = ((len - z) * z + z * z / 2) / (len * len * 1/2);

  printf("%.12f\n", sol);
  return 0;
}
