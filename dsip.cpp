/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

typedef std::pair<int,int > Point;

FILE *fin = freopen("dsip.in", "r", stdin); FILE *fout = freopen("dsip.out", "w", stdout);

const int maxN = 2e3 + 5;
const int maxM = 2e5 + 5;
const double inf = 1e30;

/*-------- Data --------*/
struct Line {
  int a, b, c;
};

struct Event {
  double slope;
  int a, b;

  Event(const double _slope, const int _a, const int _b) {slope = _slope; a = _a; b = _b;}

  bool operator <(const Event &other) const {
    return this->slope < other.slope;
  }
};

int n, m;
Point pts[maxN];
Line lns[maxM];

int pos[maxN];
std::vector<Event > events;
std::pair<int, int > sol[maxM];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &pts[i].x, &pts[i].y);
    pos[i] = i;
  }
  std::sort(pts, pts + n);

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < i; j++) {
      if(pts[i].x != pts[j].x) {
        events.emplace_back((double)(pts[i].y - pts[j].y) / (pts[i].x - pts[j].x), i, j);
      }
    }
  }


  for(int i = 0; i < m; i++) {
    int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    lns[i].a = y1 - y2; lns[i].b = x2 - x1; lns[i].c = - lns[i].a * x1 - lns[i].b * y1;

    if(lns[i].b < 0 || (lns[i].b == 0 && lns[i].a < 0)) {
      lns[i].a *= -1; lns[i].b *= -1; lns[i].c *= -1;
    }

    if(lns[i].b == 0) {
      events.emplace_back(-inf, -1, i);
    } else {
      events.emplace_back((double)-lns[i].a / lns[i].b, -1, i);
    }
  }

  std::sort(events.begin(), events.end());
}

int LowerBound(Line L) {
  int left = 0, right = n - 1, ans = 0;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(L.a * pts[mid].x + L.b * pts[mid].y + L.c < 0) {
      left = mid + 1; ans = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return ans;
}

int UpperBound(Line L) {
  int left = 0, right = n - 1, ans = 0;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(L.a * pts[mid].x + L.b * pts[mid].y + L.c > 0) {
      right = mid - 1;
    } else {
      left = mid + 1; ans = mid + 1;
    }
  }

  return ans;
}

void Solve() {
  for(auto& ev : events) {
    if(ev.a == -1) {
      int a = LowerBound(lns[ev.b]), b = n - UpperBound(lns[ev.b]);

      sol[ev.b] = {std::min(a, b), std::max(a, b)};
    } else {
      std::swap(pos[ev.a], pos[ev.b]);
      std::swap(pts[pos[ev.a]], pts[pos[ev.b]]);
    }
  }
}

int main() {
  ReadInput();

  Solve();

  for(int i = 0; i < m; i++) {
    printf("%d %d\n", sol[i].first, sol[i].second);
  }
  return 0;
}
