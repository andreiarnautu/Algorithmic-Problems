/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("katyusha.in"); std::ofstream fout("katyusha.out");

const int maxN = 3e5 + 5;
const long double eps = 1e-8;

/*-------- Data --------*/
int n, m;
int cost[maxN];
long double xx0[maxN], yy0[maxN], xx1[maxN], yy1[maxN];

long double x, y, r;

std::vector<std::pair<long double, int > > events;
/*-------- --------*/

long double Dist(long double a0, long double b0, long double a1, long double b1) {
  return (a0 - a1) * (a0 - a1) + (b0 - b1) * (b0 - b1);
}

void SolveCircle() {
  int act = 0, sol = 0;

  for(int i = 1; i <= n; i++) {
    long double a1 = x - xx0[i];
    long double a2 = y - yy0[i];
    long double d1 = xx1[i] - xx0[i];
    long double d2 = yy1[i] - yy0[i];

    long double a = d1*d1 + d2*d2;
    long double b = -2*a1*d1 -2*a2*d2;
    long double c = a1*a1 + a2*a2 - r*r;

    long double delta = b*b - 4*a*c;

    if(delta < 0) continue;

    if(-eps < a && a < eps) {
      if(r * r + eps > Dist(x, y, xx0[i], yy0[i])) {
        act += cost[i];
      }
      continue;
    }

    delta = std::sqrt(delta);

    long double t1 = (-b - delta) / (2 * a);
    long double t2 = (-b + delta) / (2 * a);

    if(t2 < 0) continue;
    if(t1 < 0) t1 = 0.0;

    events.emplace_back(t1, -cost[i]); events.emplace_back(t2, +cost[i]);
  }

  std::sort(events.begin(), events.end());
  for(auto& ev : events) {
    act -= ev.second; sol = std::max(sol, act);
  }

  fout << std::max(act, sol) << '\n';
}

int main() {
  fin >> n >> m;
  for(int i = 1; i <= n; i++) {
    fin >> xx0[i] >> yy0[i] >> xx1[i] >> yy1[i] >> cost[i];
  }

  for(int i = 1; i <= m; i++) {
    fin >> x >> y >> r;

    SolveCircle();
    events.clear();
  }
  return 0;
}
