/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

typedef std::pair<int, int > Point;

FILE *fin = freopen("cmap.in", "r", stdin); FILE *fout = freopen("cmap.out", "w", stdout);

const int maxN = 1e5 + 5;
const long long inf = 1e18;
const int maxDiff = 8;

/*-------- Data --------*/
int n;
Point pts[maxN], aux[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &pts[i].x, &pts[i].y);
  }
}

void Merge(int left, int mid, int right) {
  int p1 = left, p2 = mid + 1, pos = 0;

  while(p1 <= mid && p2 <= right) {
    if(pts[p1].y < pts[p2].y) {
      aux[pos] = pts[p1]; p1++; pos++;
    } else {
      aux[pos] = pts[p2]; p2++; pos++;
    }
  }

  while(p1 <= mid) {
    aux[pos] = pts[p1]; p1++; pos++;
  }
  while(p2 <= right) {
    aux[pos] = pts[p2]; p2++; pos++;
  }

  for(int i = 0; i < pos; i++) {
    pts[left + i] = aux[i];
  }
}

long long Dist(Point A, Point B) {
  return 1LL * (A.x - B.x) * (A.x - B.x) + 1LL * (A.y - B.y) * (A.y - B.y);
}

long long Divide(int left, int right) {
  //  Check if there are less than 2 points
  if(right - left < 2) {
    if(right == left) {
      return inf;
    } else {
      Merge(left, left, right);
      return Dist(pts[left], pts[right]);
    }
  }

  //  Divide
  int mid = (left + right) / 2;
  long long d1 = Divide(left, mid), d2 = Divide(mid + 1, right);

  //  Conquer
  long long d = std::min(d1, d2);
  Merge(left, mid, right);

  for(int i = left; i <= right; i++) {
    for(int j = i - 1; j >= left && i - j < maxDiff; j--) {
      d = std::min(d, Dist(pts[i], pts[j]));
    }
  }
  return d;
}

int main() {
  ReadInput();

  std::sort(pts, pts + n);

  printf("%.10f\n", std::sqrt((double)Divide(0, n - 1)));

  return 0;
}
