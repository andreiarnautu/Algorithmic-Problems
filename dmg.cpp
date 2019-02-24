/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second
#define Point std::pair<double, double >

FILE *fin = freopen("dmg.in", "r", stdin); FILE *fout = freopen("dmg.out", "w", stdout);

const double eps = 1e-3;

/*-------- Data --------*/
struct Line {
  double a, b, c;
  Line() {}
  Line(double _a, double _b, double _c) {a = _a; b = _b; c = _c;}
};

int n;
std::vector<Point > pts;
Point G;

std::vector<int > used;
std::vector<Line > sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n); used.resize(n);
  for(int i = 0; i < n; i++) {
    double x, y; scanf("%lf%lf", &x, &y); pts.emplace_back(x, y);
  }
}

bool Equal(double a, double b) {
  return (b - eps < a && a < b + eps);
}

bool Less(double a, double b) {
  return (a < b - eps);
}

Line GetLine(Point A, Point B) {
  return {B.y - A.y, A.x - B.x, A.y * B.x - A.x * B.y};
}

Line PerpendicularThroughPoint(Line line, Point P) {
  Line ans; ans.a = line.b; ans.b = -line.a; ans.c = -(ans.a * P.x + ans.b * P.y);
  return ans;
}

bool OnLine(Line line, Point P) {
  return Equal(line.a * P.x + line.b * P.y + line.c, 0.0);
}

Point LineIntersection(Line x, Line y) {
  Point P;
  P.x = (x.b * y.c - y.b * x.c) / (y.b * x.a - x.b * y.a);
  P.y = (y.a * x.c - x.a * y.c) / (y.b * x.a - x.b * y.a);
  return P;
}

int Found(Point P) {
  int left = 0, right = n - 1, ans = 0;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(Less(pts[mid].x, P.x) || (Equal(pts[mid].x, P.x) && Less(pts[mid].y, P.y))) {
      left = mid + 1;
    } else {
      right = mid - 1; ans = mid;
    }
  }

  if(Equal(P.x, pts[ans].x) && Equal(P.y, pts[ans].y)) {
    return ans;
  } else {
    return -1;
  }
}

int Try(const Line line) {
  for(int i = 0; i < n; i++) {
    used[i] = 0;
  }

  for(int i = n - 1; i >= 0; i--) {
    if(OnLine(line, pts[i]) || used[i]) continue;

    Line perp = PerpendicularThroughPoint(line, pts[i]);

    Point p0 = LineIntersection(line, perp);

    Point p1 = {2 * p0.x - pts[i].x, 2 * p0.y - pts[i].y};

    int which = Found(p1);
    if(which == -1) {
      return false;
    } else {
      used[which] = 1; used[i] = 1;
    }
  }

  return true;
}

void Solve() {
  std::sort(pts.begin(), pts.end());
  //  Find the center
  for(int i = 0; i < n; i++) {
    G.x += pts[i].x; G.y += pts[i].y;
  }
  G.x /= (double)n; G.y /= (double)n;

  //  Check the line pts[0] -> G
  Line l1 = GetLine(pts[0], G);
  if(Try(l1)) {
    sol.push_back(l1);
  }

  //  Check lines related to the other points
  for(int i = 1; i < n; i++) {
    Line line = GetLine(pts[0], pts[i]);

    Point M = {(pts[0].x + pts[i].x) * 0.5, (pts[0].y + pts[i].y) * 0.5};
    Line perp = PerpendicularThroughPoint(line, M);

    if(!Equal(perp.a * G.x + perp.b * G.y + perp.c, 0.0)) continue;

    if(Try(perp)) {
      sol.push_back(perp);
    }
  }
}

int main() {
  ReadInput();

  Solve();

  printf("%d\n", (int)sol.size());
  for(auto& itr : sol) {
    printf("%.10f %.10f %.10f\n", itr.a, itr.b, itr.c);
  }
  return 0;
}
