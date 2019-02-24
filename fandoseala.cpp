/**
  *  Worg
  *  Mar 12, 2018
  *  7:06:30 PM
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("fandoseala.in", "r", stdin); FILE *fout = freopen("fandoseala.out", "w", stdout);

const int maxN = 300 + 5;
const int kBufferSize = 1e5;

class InputReader {
public:
    char buffer[kBufferSize];
    int cursor;

    void getBuffer() {
      cursor = 0; fread(buffer, 1, kBufferSize, stdin);
    }

    InputReader() {
      getBuffer();
    }

    bool digit(char c) {
      return '0' <= c && c <= '9';
    }

    InputReader& operator >>(int &number) {
      char sgn = '+';
      while(!digit(buffer[cursor])) {
        sgn = buffer[cursor];
        if(++cursor == kBufferSize) {
          getBuffer();
        }
      }

      number = 0;
      while(digit(buffer[cursor])) {
        number = number * 10 + buffer[cursor] - '0';
        if(++cursor == kBufferSize) {
          getBuffer();
        }
      }

      number = (sgn == '-') ? -number : number;

      return *this;
    }
} cin;
/*-------- Data --------*/
struct Point {
  int x, y, idx, area, special;
  double prod;

  Point() {}
};

int n, k;
Point pts[maxN];
/*-------- --------*/

long long CrossProduct(Point A, Point B, Point C) {
  return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

long long Dist(Point A, Point B) {
  return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

long long Obtuz(Point A, Point B, Point C) {
  long long a = Dist(A, B), b = Dist(A, C), c = Dist(B, C);

  return a > b + c;
}

int Comp2(Point A, Point B) {
  return A.prod * B.area < B.prod * A.area;
}

int Comp(Point A, Point B) {
  if(A.special == 0 && B.special == 0) {
    return Comp2(A, B);
  } else if(A.special == 0 && B.special == 1) {
    return 0;
  } else if(A.special == 1 && B.special == 0) {
    return 1;
  } else {
    return Comp2(B, A);
  }
}

void SolveTest() {
  cin >> n >> k;
  for(int i = 0; i < n; i++) {
    cin >> pts[i].x >> pts[i].y; pts[i].idx = i + 1;
  }

  for(int i = 1; i < n; i++) {
    if(pts[i].x < pts[0].x || (pts[i].x == pts[0].x && pts[i].y < pts[0].y)) {
      std::swap(pts[i], pts[0]);
    }
  }

  for(int i = 2; i < n; i++) {
    if(CrossProduct(pts[0], pts[1], pts[i]) > 0) {
      std::swap(pts[i], pts[1]);
    }
  }

  for(int i = 2; i < n; i++) {
    pts[i].prod = std::sqrt(Dist(pts[0], pts[i]) * Dist(pts[1], pts[i]));
    pts[i].area = std::abs(CrossProduct(pts[0], pts[1], pts[i]));
    pts[i].special = Obtuz(pts[0], pts[1], pts[i]);
  }

  std::nth_element(pts + 2, pts + k - 1, pts + n, Comp);

  std::swap(pts[2], pts[k - 1]);
  std::sort(pts, pts + 3, [&](Point A, Point B) {
    return A.idx < B.idx;
  });


  printf("%d %d %d\n", pts[0].idx, pts[1].idx, pts[2].idx);
}

int main() {
  int t; cin >> t;

  for(int i = 0; i < t; i++) {
    SolveTest();
  }

  return 0;
}
