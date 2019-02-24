/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second
#define leftSon (node * 2)
#define rightSon (node * 2 + 1)

typedef std::pair<int, int > Point;

FILE *fin = freopen("cadrane.in", "r", stdin); FILE *fout = freopen("cadrane.out", "w", stdout);

const int maxN = 1e5 + 5;

/*-------- Data --------*/
struct Node {
  int val, lazy;

  Node() {val = 0; lazy = 0;}

  Node(int _val, int _lazy) {val = _val; lazy = _lazy;};
};

int n;
Point pts[maxN];
std::map<int, int > ord;

Node aint[maxN * 4];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &pts[i].x, &pts[i].y);
    ord[pts[i].y] = 1;
  }

  int idx = 0;
  for(auto& itr : ord) {
    itr.second = ++idx;
  }
}

void Propagate(int node, int left, int right) {
  aint[leftSon].lazy += aint[node].lazy; aint[rightSon].lazy += aint[node].lazy;
  aint[node].lazy = 0;
}

void Update(int node, int left, int right, int first, int last, int add) {
  if(first <= left && right <= last) {
    aint[node].lazy += add; return;
  }

  Propagate(node, left, right);

  int mid = (left + right) / 2;
  if(first <= mid) {
    Update(leftSon, left, mid, first, last, add);
  }
  if(mid < last) {
    Update(rightSon, mid + 1, right, first, last, add);
  }

  aint[node].val = std::min(aint[leftSon].val + aint[leftSon].lazy, aint[rightSon].val + aint[rightSon].lazy);
}

void Sweep() {
  //  Initialize
  for(int i = 0; i < n; i++) {
    Update(1, 1, n, 1, ord[pts[i].y], +1);
  }

  //  Start sweeping from right to left
  std::sort(pts, pts + n);
  pts[n].x = pts[n - 1].x + 1;

  int sol = 0;
  for(int i = 0, j = 0; i < n; i++) {
    //  Check changes
    Update(1, 1, n, ord[pts[i].y], n, +1);
    Update(1, 1, n, ord[pts[i].y], ord[pts[i].y], -1);

    if(pts[i].x != pts[i + 1].x) {
      sol = std::max(sol, aint[1].lazy + aint[1].val);

      for(; j <= i; j++) {
        Update(1, 1, n, ord[pts[j].y], ord[pts[j].y], +1);
        Update(1, 1, n, 1, ord[pts[j].y], -1);
      }
    }
  }

  printf("%d\n", sol);
}

int main() {
  ReadInput();

  Sweep();

  return 0;
}
