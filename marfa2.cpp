/**
  *  Worg
  *  Mar 25, 2018
  *  11:59:10 AM
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("marfa2.in", "r", stdin); FILE *fout = freopen("marfa2.out", "w", stdout);

const int maxN = 20;
const int mod = 40099;
const int dim = 5*5;

/*-------- Struct --------*/
struct Matrix {
  int size;
  int a[dim][dim];

  Matrix() {size = 0; memset(a, 0, sizeof(a));};

  Matrix(const int _size) {
    size = _size; memset(a, 0, sizeof(a));
  }

  void Basic() {
    for(int i = 0; i < size; i++) {
      a[i][i] = 1;
    }
  }

  int Answer() {
    int ans = 0;

    for(int j = 0; j < size; j++) {
      ans += a[0][j];
    }

    ans %= mod;
    return ans;
  }
};

Matrix Product(Matrix m1, Matrix m2) {
  Matrix ans = Matrix(m1.size);

  for(int i = 0; i < ans.size; i++) {
    for(int j = 0; j < ans.size; j++) {
      for(int k = 0; k < ans.size; k++) {
        ans.a[i][j] += m1.a[i][k] * m2.a[k][j];
        ans.a[i][j] %= mod;
      }
    }
  }

  return ans;
}
/*-------- Data --------*/
int z, k, n;
int weekday[maxN];

Matrix day[3], week;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d%d", &z, &k, &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &weekday[i]);
  }
}

int Value(int left, int right) {
  return left * k + right;
}

std::pair<int, int > Add(int left, int right, int addLeft, int addRight) {
  std::pair<int, int > ans = {left + addLeft, right + addRight};

  if(!addLeft) {
    ans.first = 0;
  }
  if(!addRight) {
    ans.second = 0;
  }

  if(ans.first >= k || ans.second >= k) {
    return {-1, -1};
  }
  return ans;
}

void Construct(int x) {
  day[x] = Matrix(k * k);

  for(int left = 0; left < k; left++) {
    for(int right = 0; right < k; right++) {
      for(int addLeft = 0; addLeft <= x; addLeft++) {
        if(addLeft > 1 || x - addLeft > 1) continue;

        auto next = Add(left, right, addLeft, x - addLeft);

        if(next.first == -1) continue;

        day[x].a[Value(left, right)][Value(next.first, next.second)] = 1;
      }
    }
  }
}

Matrix Raise(Matrix m, int exp) {
  Matrix ans = Matrix(m.size); ans.Basic();
  Matrix aux = Matrix(m.size); aux = m;

  for(int i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      ans = Product(ans, aux);
    }
    aux = Product(aux, aux);
  }

  return ans;
}

void Solve() {
  Construct(0); Construct(1); Construct(2);

  week = Matrix(k * k);
  week = day[weekday[0]];

  for(int i = 1; i < n; i++) {
    week = Product(week, day[weekday[i]]);
  }
  week = Raise(week, z / n);

  Matrix sol = Matrix(k * k);
  sol = week;

  int rest = z % n;
  for(int i = 0; i < rest; i++) {
    sol = Product(sol, day[weekday[i]]);
  }

  printf("%d\n", sol.Answer());
}

int main() {
  ReadInput();

  Solve();

  return 0;
}
