/**
  *  Worg
  */
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

/*-------- Data --------*/
struct Matrix {
  long long m[2][2];

  Matrix() {m[0][0] = m[0][1] = m[1][0] = m[1][1] = 0;}

  Matrix(long long a, long long b, long long c, long long d) {m[0][0] = a; m[0][1] = b; m[1][0] = c; m[1][1] = d;}
};

long long modulo, a, b;

/*-------- --------*/

Matrix MatrixProduct(Matrix a, Matrix b) {
  Matrix ans;
  ans.m[0][0] = (a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0]) % modulo;
  ans.m[0][1] = (a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1]) % modulo;
  ans.m[1][0] = (a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0]) % modulo;
  ans.m[1][1] = (a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1]) % modulo;

  return ans;
}

Matrix Raise(Matrix a, long long exp) {
  Matrix ans = {1, 0, 0, 1}, aux = a;

  for(long long i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      ans = MatrixProduct(ans, aux);
    }
    aux = MatrixProduct(aux, aux);
  }

  return ans;
}

void RunTest() {
  scanf("%lld%d%d", &modulo, &a, &b);

  long long kMagic = std::sqrt(6 * modulo - 1) + 1;

  //!  Add values in hash table
  std::map<std::pair<long long, long long >, long long > map;

  for(int i = 0; i <= kMagic; i++) {
    Matrix act = Raise({modulo - 1, 1, 1, 0}, 1LL * kMagic * i);

    long long x = (act.m[0][0] * a + act.m[1][0] * b) % modulo;
    long long y = (act.m[0][1] * a + act.m[1][1] * b) % modulo;

    if(map.find({x, y}) == map.end()) {
      map[{x, y}] = 1LL * i * kMagic;
    }
  }

  //!  Meet in the middle
  long long sol = -1;

  Matrix act = {1, 0, 0, 1}, aux = {0, 1, 1, 1};
  for(int i = 0; i < kMagic; i++) {
    long long x = act.m[1][0], y = act.m[1][1];

    if(map.find({x, y}) != map.end()) {
      if(sol == -1 || sol > 1LL * i + map[{x, y}]) {
        sol = 1LL * i + map[{x, y}];
      }
    }

    act = MatrixProduct(act, aux);
  }

  printf("%lld\n", sol);
}

int main() {
  int t; scanf("%d", &t);
  for(int i = 0; i < t; i++) {
    RunTest();
  }
	return 0;
}
