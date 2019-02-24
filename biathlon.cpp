/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("biathlon.in", "r", stdin); FILE *fout = freopen("biathlon.out", "w", stdout);

/*-------- Data --------*/
struct Player {
  int x, y, idx;

  Player(const int _x, const int _y, const int _idx) {x = _x; y = _y; idx = _idx;}

  bool operator <(const Player &other) const {
    if(x != other.x) {
      return x < other.x;
    }
    return y < other.y;
  }

  bool operator ==(const Player &other) const {
    return x == other.x && y == other.y;
  }
};


int n;
std::vector<Player > v;

std::vector<int > can, bst, stk, sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    int x, y; scanf("%d%d", &x, &y); v.emplace_back(x, y, i);
  }
}

long long CrossProduct(Player A, Player B, Player C) {
  return 1LL * (A.x - C.x) * (A.y - B.y) * B.x * C.y - 1LL * (A.x - B.x) * (A.y - C.y) * C.x * B.y;
}

void Solve() {
  can.resize(n);
  std::sort(v.begin(), v.end());

  //  Check if there are equal players
  for(int i = 0; i < n; i++) {
    if(i > 0 && v[i] == v[i - 1]) {
      can[v[i].idx] = -1;
    }
    if(i < n - 1 && v[i] == v[i + 1]) {
      can[v[i].idx] = -1;
    }
  }

  //  Compute bst
  bst.resize(n + 1);
  bst.back() = 0;
  for(int i = n - 1; i >= 0; i--) {
    bst[i] = std::max(bst[i + 1], v[i].y);
  }

  //  The actual coordinates of the points are [1/x, 1/y]. Compute the "visible" face of the convex hull.
  int sz = 0;
  for(int i = 0; i < n; i++) {
    if(bst[i + 1] < v[i].y) {

      while(sz >= 2 && CrossProduct(v[stk[sz - 2]], v[stk[sz - 1]], v[i]) <= 0) {
        sz--; stk.pop_back();
      }

      if(sz == 1 && v[i].x > v[stk[0]].x && v[i].y > v[stk[0]].y) {
        sz--; stk.pop_back();
      }

      stk.push_back(i); sz++;
    }
  }

  //  Compute answer
  for(int i = 0; i < sz; i++) {
    if(can[v[stk[i]].idx] != -1) {
      sol.push_back(v[stk[i]].idx);
    }
  }
}

int main() {
  ReadInput();

  Solve();

  if(!sol.size()) {
    printf("-1\n");
  } else {
    std::sort(sol.begin(), sol.end());
    for(auto& itr : sol) {
      printf("%d ", itr);
    }
  }
  return 0;
}
