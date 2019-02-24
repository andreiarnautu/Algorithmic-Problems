/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("mission.in", "r", stdin); FILE *fout = freopen("mission.out", "w", stdout);

/*-------- Data --------*/
struct Point {
  double x, y; int idx;

  Point() {}

  Point(double _x, double _y, int _idx) {x = _x; y = _y; idx = _idx;}
};

int n;
std::vector<Point > pts;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    double x, y; scanf("%lf%lf", &x, &y); pts.emplace_back(x, y, i);
  }
}

void Solve() {
  Point G; G.x = G.y = 0;

  for(int i = 0; i < n; i++) {
    G.x += pts[i].x; G.y += pts[i].y;
  }
  G.x /= (double)n; G.y /= (double)n;

  std::sort(pts.begin(), pts.end(), [&](Point A, Point B) {
    return std::atan2(A.y - G.y, A.x - G.x) < std::atan2(B.y - G.y, B.x - G.x);
  });

  int where = 0;
  for(int i = 0; i < n; i++) {
    if(pts[i].idx == 0) {
      where = i; break;
    }
  }

  for(int i = where; i < n; i++) {
    printf("%d ", pts[i].idx);
  }
  for(int i = 0; i < where; i++) {
    printf("%d ", pts[i].idx);
  }
}

int main() {
  ReadInput();

  Solve();
	return 0;
}
