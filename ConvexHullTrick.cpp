/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);
using namespace std;

const long long inf = 1e18;

*-------- Convex Hull Trick --------*/
struct Line {
  long long a, b;
  mutable long double slope;

  Line(long long _a, long long _b, long double _slope) { a = _a; b = _b; slope = _slope; }

  bool operator <(const Line &other) const {
    if(this->b == inf || other.b == inf) {
      return slope < other.slope;
    }
    if(a != other.a) {
      return a > other.a;
    }
    return b < other.b;
  }
};

struct Batch {
  set<Line > lines;

  bool Bad(set<Line >::iterator it) {
    if(next(it) == lines.end() || it == lines.begin()) {
      return false;
    }

    //return (long double) (next(it)->a - prev(it)->a) * (it->b - prev(it)->b) >= (long double) (it->a - prev(it)->a) * (next(it)->b - prev(it)->b);
    return (long double) (prev(it)->a - next(it)->a) * (next(it)->b - it->b) <= (long double) (it->a - next(it)->a) * (next(it)->b - prev(it)->b);
  }

  void Compute(set<Line >::iterator it) {
    if(next(it) == lines.end()) {
      it->slope = inf;
    } else {
      it->slope = (long double)(it->b - next(it)->b) / (next(it)->a - it->a);
    }
  }

  void Update(Line d) {
    if(lines.find(d) != lines.end()) return;

    auto it = lines.insert(d).first;
    //  Check previous
    if(it != lines.begin() && prev(it)->a == it->a) {
      lines.erase(it); return;
    }
    //  Check next
    if(next(it) != lines.end() && next(it)->a == it->a) {
      lines.erase(next(it));
    }
    //  Check current
    if(Bad(it)) {
      lines.erase(it); return;
    }

    while(it != lines.begin() && Bad(prev(it))) {
      lines.erase(prev(it));
    }
    while(next(it) != lines.end() && Bad(next(it))) {
      lines.erase(next(it));
    }

    Compute(it);
    if(it != lines.begin()) {
      Compute(prev(it));
    }
  }

  long long Query(long long x) {
    if(lines.empty()) {
      return inf;
    }

    auto it = lines.lower_bound(Line(0, inf, x));

    return it->a * x + it->b;
  }
};
int main() {

}
