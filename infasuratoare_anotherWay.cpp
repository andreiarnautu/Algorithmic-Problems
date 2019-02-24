/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

typedef std::pair<double, double > Point;

FILE *fin = freopen("infasuratoare.in", "r", stdin); FILE *fout = freopen("infasuratoare.out", "w", stdout);

const double eps = 1e-12;

/*-------- Data --------*/
int n;
std::vector<Point > pts;
/*-------- --------*/

void Read() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    double x, y; scanf("%lf%lf", &x, &y); pts.emplace_back(x, y);
  }
}

double CrossProduct(Point A, Point B, Point C) {
  return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}


void ConvexHull() {
  std::sort(pts.begin(), pts.end());

  std::vector<int > stk, used(n, false);

  stk.push_back(0); stk.push_back(1);
  used[1] = true;


  for(int i = 2, add = 1; i >= 0;  i += (add = (i == n - 1) ? -add : add)) {
    if(used[i]) continue;

    while(stk.size() > 1 && CrossProduct(pts[stk[stk.size() - 2]], pts[stk[stk.size() - 1]], pts[i]) < eps) {
      used[stk.back()] = false; stk.pop_back();
    }
    stk.push_back(i); used[i] = true;
  }

  printf("%d\n", (int)stk.size() - 1);
  for(int i = 0; i < (int)stk.size() - 1; i++) {
    printf("%.6f %.6f\n", pts[stk[i]].x, pts[stk[i]].y);
  }
}

int main() {
  Read();

  ConvexHull();
  return 0;
}
