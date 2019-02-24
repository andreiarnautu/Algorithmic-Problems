/**
  *  Worg
  */
#include <cmath>
#include <bitset>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("laser.in", "r", stdin); FILE *fout = freopen("laser.out", "w", stdout);

const double pi = acos(-1.0);
const double eps = 1e-8;
const int kDim = 1200;

/*-------- Data --------*/
int n, m;
std::vector<std::pair<double, double > > ends;

std::vector<double > ang, bis, sol;
std::bitset<kDim > sys[kDim];
std::vector<int > which;
/*-------- --------*/

double Angle(int x, int y) {
  double ans = atan2(y, x);
  return (ans < 0) ? (ans + 2 * pi) : (ans);
}

bool Intersect(double x, double y, double z) {
  if(y - x > pi) {
    return (z < x + eps || z > y - eps);
  } else {
    return (x - eps < z && z < y + eps);
  }
}

void ReadInput() {
  scanf("%d", &n); ends.resize(n);

  for(int i = 0; i < n; i++) {
    int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    double a1 = Angle(x1, y1), a2 = Angle(x2, y2);
    if(a1 > a2) std::swap(a1, a2);

    ang.push_back(a1); ang.push_back(a2);
    ends[i] = {a1, a2};
  }
}

void GetDirections() {
  //  Sort the angles then get their bisectors
  m = (int)ang.size();
  std::sort(ang.begin(), ang.end());

  for(int i = 0; i < m - 1; i++) {
    bis.push_back((ang[i] + ang[i + 1]) * 0.5);
  }

  bis.push_back((ang[m - 1] + ang[0] + 2 * pi) * 0.5);
  if(bis.back() > 2 * pi) {
    bis.back() -= 2 * pi;
  }
}

void BuildSystem() {
  //  Take every segment and see which lines it intersects with
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      sys[i][j] = Intersect(ends[i].first, ends[i].second, bis[j]);
    }

    int state; scanf("%d", &state);
    sys[i][m] = state;
  }
}

void SolveGauss() {
  int i, j; which.resize(n, -1);

  for(i = 0; i < n; i++) {
    for(j = 0; j <= m; j++) if(sys[i][j]) break;

    if(j == m + 1) continue;

    which[i] = j;

    for(int j = 0; j < n; j++) {
      if(i != j && sys[j][which[i]]) {
        sys[j] ^= sys[i];
      }
    }
  }

  for(int i = 0; i < n; i++) {
    if(which[i] != -1 && sys[i][m] == 1) {
      sol.push_back(bis[which[i]]);
    }
  }
}

int main() {
  ReadInput();
  GetDirections();
  BuildSystem();
  SolveGauss();

  printf("%d\n", (int)sol.size());
  for(auto& itr : sol) {
    printf("%.6f\n", itr / pi * 180);
  }
  return 0;
}
