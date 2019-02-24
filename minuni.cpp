/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

#define leftSon (node * 2)
#define rightSon (node * 2 + 1)
#define mid ((left + right) / 2)

FILE *fin = freopen("minuni.in", "r", stdin); FILE *fout = freopen("minuni.out", "w", stdout);

const int maxM = 1e5 + 5;
const int inf = 1e9;

/*-------- Data --------*/
struct Event {
  int pos, type, idx;

  Event() {}

  Event(const int _pos, const int _type, const int _idx) {pos = _pos; type = _type; idx = _idx;}

  bool operator <(const Event &other) const {
    return this->pos < other.pos;
  }
};
int n, m;
std::pair<int, int > rng[maxM];

int whichIdx[maxM], t[maxM];
int aint[maxM * 4];

Event events[maxM * 2];
long long sol[maxM];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);

  for(int i = 1; i <= m; i++) {
    scanf("%d%d", &rng[i].first, &rng[i].second);
  }
}

void BuildEvents() {
  for(int i = 1; i <= m; i++) {
    events[i] = {rng[i].first, 0, i};
    events[i + m] = {rng[i].second, 1, i};
  }
  std::sort(events + 1, events + 2 * m + 1);
}

void Update(int node, int left, int right, int pos, int val) {
  if(left == right) {
    aint[node] = val; return;
  }

  if(pos <= mid) {
    Update(leftSon, left, mid, pos, val);
  } else {
    Update(rightSon, mid + 1, right, pos, val);
  }

  aint[node] = std::max(aint[leftSon], aint[rightSon]);
}

int Query(int node, int left, int right, int pos) {
  if(pos < left) {
    return 0;
  }
  if(right <= pos) {
    return aint[node];
  }

  int q1 = Query(leftSon, left, mid, pos), q2 = 0;

  if(pos > mid) {
    q2 = Query(rightSon, mid + 1, right, pos);
  }
  return std::max(q1, q2);
}

void ProcessEvents() {
  int crtTime = 0;

  for(int i = 1; i <= 2 * m; i++) {
    if(events[i].type == 0) {
      int q = Query(1, 1, m, events[i].idx - 1);

      whichIdx[events[i].idx] = t[q];
      t[++crtTime] = events[i].idx;

      Update(1, 1, m, events[i].idx, crtTime);
    } else {
      Update(1, 1, m, events[i].idx, 0);
    }
  }

  for(int i = 1; i <= m; i++) {
    int a = rng[i].first, b = rng[i].second;

    if(whichIdx[i] == 0) {
      sol[i] = 1LL * a * (n - b + 1);
    } else {
      int p = rng[whichIdx[i]].first, q = rng[whichIdx[i]].second;

      sol[i] = 1LL * a * (q - b) + 1LL * (a - p) * (n - b + 1) - 1LL * (a - p) * (q - b);
    }
  }
}

void WriteOutput() {
  for(int i = 1; i <= m; i++) {
    printf("%lld\n", sol[i]);
  }
}

int main() {
  ReadInput();

  BuildEvents();

  ProcessEvents();

  WriteOutput();

  return 0;
}
