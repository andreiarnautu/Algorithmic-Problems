/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

const double eps = 1e-12;

typedef std::pair<double, double > Point;

FILE *fin = freopen("babacu.in", "r", stdin); FILE *fout = freopen("babacu.out", "w", stdout);

/*-------- Data --------*/
int n;
std::vector<Point > pts;

int sol;
/*-------- --------*/

void Read() {
  int N; scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    double a, b, c; scanf("%lf%lf%lf", &a, &b, &c);

    if(c == 0.0) {
      sol++;
    } else {
      pts.emplace_back(a / c, b / c); n++;
    }
  }
}

double CrossProduct(Point A, Point B, Point C) {
  return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

void Solve() {
  pts.emplace_back(0, 0); n++;
  std::sort(pts.begin(), pts.end());

  std::vector<int > stk, used(n, false);

  stk.push_back(0); stk.push_back(1); used[1] = true;

  for(int i = 2, p = 1; !used[0]; i += (p = (i == n - 1) ? -p : p)) {
    if(used[i]) continue;

    while(stk.size() > 1 && CrossProduct(pts[stk[stk.size() - 2]], pts[stk.back()], pts[i]) > -eps) {
      used[stk.back()] = false; stk.pop_back();
    }

    used[i] = true; stk.push_back(i);
  }

  sol = (int)stk.size() - 1;
  for(int i = 0; i < (int)stk.size() - 1; i++) {
    if(stk[i] == 0) {
      sol--;
    }
  }

  printf("%d\n", sol);
}

int main() {
  Read();

  if(n <= 2) {
    printf("%d\n", sol + n);
  } else {
    Solve();
  }
  return 0;
}
