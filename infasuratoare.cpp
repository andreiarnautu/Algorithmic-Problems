/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

#define x first
#define y second

typedef std::pair<double, double > Point;

FILE *fin = freopen("infasuratoare.in", "r", stdin); FILE *fout = freopen("infasuratoare.out", "w", stdout);

/*-------- Data --------*/
int N;
std::vector<Point > points, stack;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &N); points.resize(N);
  for(auto& itr : points) {
    scanf("%lf%lf", &itr.x, &itr.y);
  }
}

double CCW(Point A, Point B, Point C) {
  return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}

std::vector<Point > ConvexHull(std::vector<Point > v) {
  for(int i = 1; i < N; i++) {
    if(points[i] < points[0]) {
      std::swap(points[0], points[i]);
    }
  }

  std::sort(points.begin() + 1, points.end(), [&](Point A, Point B) {
    return CCW(points[0], A, B) < 0;
  });

  for(auto& act : points) {
    while((int)stack.size() > 1 && CCW(stack[(int)stack.size() - 2], stack[(int)stack.size() - 1], act) > 0) {
      stack.pop_back();
    }
    stack.push_back(act);
  }

  reverse(stack.begin(), stack.end());
  return stack;
}

int main() {
  ReadInput();

  auto sol = ConvexHull(points);

  printf("%d\n", (int)sol.size());
  for(auto& itr : sol) {
    printf("%.10f %.10f\n", itr.first, itr.second);
  }

  return 0;
}
