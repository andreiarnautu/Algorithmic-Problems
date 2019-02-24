/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

#define leftSon (node * 2)
#define rightSon (node * 2 + 1)

FILE *fin = freopen("castori.in", "r", stdin); FILE *fout = freopen("castori.out", "w", stdout);

const int maxLog = 30;
const int maxN = 10000 + 5;

/*-------- Data --------*/
struct Node {
  int val, lazy;
};

int n, c;
std::vector<std::pair<int, int > > vec, rng;
std::map<int, int > norm;

Node aint[maxN * 4];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &c);
  for(int i = 0; i < n; i++) {
    int x, y; scanf("%d%d", &x, &y);
    vec.emplace_back(x + y, x - y);
    norm[vec.back().second] = 1;
  }

  int idx = 1;
  for(auto& itr : norm) {
    norm[itr.first] = idx++;
  }
}

void Update(int node, int left, int right, int first, int last, int val) {
  if(first <= left && right <= last) {
    aint[node].val += val; aint[node].lazy += val; return;
  }

  int mid = (left + right) / 2;
  if(first <= mid) {
    Update(leftSon, left, mid, first, last, val);
  }
  if(mid < last) {
    Update(rightSon, mid + 1, right, first, last, val);
  }

  aint[node].val = std::max(aint[leftSon].val, aint[rightSon].val) + aint[node].lazy;
}

void Build(int node, int left, int right) {
  aint[node].lazy = aint[node].val = 0;

  if(left != right) {
    int mid = (left + right) / 2;
    Build(leftSon, left, mid); Build(rightSon, mid + 1, right);
  }
}

bool Check(const int dist) {
  int best = 0, cursor = 0;

  Build(1, 1, n);

  for(int i = 0; i < n; i++) {
    auto it = norm.upper_bound(vec[i].second + dist); it--;
    rng[i] = {norm[vec[i].second], it->second};

    Update(1, 1, n, rng[i].first, rng[i].second, +1);

    while(cursor < i && vec[cursor].first + dist < vec[i].first) {
      Update(1, 1, n, rng[cursor].first, rng[cursor].second, -1);
      cursor++;
    }

    best = std::max(best, aint[1].val);
  }

  return (best >= c);
}

int main() {
  ReadInput();

  std::sort(vec.begin(), vec.end());
  rng.resize(n);

  int sol = 0;
  for(int step = (1 << maxLog); step > 0; step >>= 1) {
    if(!Check(sol + step)) {
      sol += step;
    }
  }
  printf("%d\n", sol + 1);
  return 0;
}
