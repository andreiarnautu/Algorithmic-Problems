/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <bitset>
#include <algorithm>

FILE *fin = freopen("jmenoasa.in", "r", stdin); FILE *fout = freopen("jmenoasa.out", "w", stdout);

const int kMaxN = 1000 + 5;
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
      while(!digit(buffer[cursor])) {
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

      return *this;
    }
} cin;

/*-------- Data --------*/
int n, m;
int a[kMaxN][kMaxN];
std::bitset<2 * kMaxN > b[2 * kMaxN];
/*-------- --------*/

int main() {
  clock_t startTime = clock();
  //  Read

  cin >> n >> m;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  //  Build b[][]

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      b[i * 2][j * 2] = 1;
    }
    for(int j = 0; j < m - 1; j++) {
      if(a[i][j] < a[i][j + 1]) {
        b[i * 2][j * 2 + 1] = 1;
      }
    }

    if(i == n - 1) continue;

    for(int j = 0; j < m; j++) {
      if(a[i][j] < a[i + 1][j]) {
        b[i * 2 + 1][j * 2] = 1;
      }
    }
  }

  for(int i = 1; i < 2 * n; i += 2) {
    for(int j = 1; j < 2 * m; j += 2) {
      b[i][j] = 1;
    }
  }
  //  Run algorithm
  int sol = 1;

  auto UpdateSol = [&](int x1, int y1, int x2, int y2) {
    if(x2 & 1) x2--;
    if(x1 & 1) x1++;
    if(y2 & 1) y2--;
    if(y1 & 1) y1++;

    int dx = (x2 - x1) / 2 + 1, dy = (y2 - y1) / 2 + 1;

    sol = std::max(sol, dx * dy);
  };

  std::vector<int > h(2 * m, 0);
  for(int i = 0; i <= 2 * (n - 1); i++) {
    for(int j = 0; j <= 2 * (m - 1); j++) {
      h[j] = (b[i][j] == 0) ? 0 : (h[j] + 1);
    }

    std::vector<std::pair<int, int > > stk;
    stk.emplace_back(-1, -1);

    for(int j = 0; j <= 2 * (m - 1); j++) {
      std::pair<int, int > here(h[j], j);

      while(here < stk.back()) {
        int wHere = j - 1 - stk[(int)stk.size() - 2].second;
        int hHere = stk.back().first;

        UpdateSol(i - hHere + 1, stk[(int)stk.size() - 2].second + 1, i, j - 1);

        stk.pop_back();
      }

      stk.push_back(here);
    }

    while(stk.size() > 1) {
      int hHere = stk.back().first;
      int wHere = 2 * m - 2 - stk[(int)stk.size() - 2].second;

      UpdateSol(i - hHere + 1, stk[(int)stk.size() - 2].second + 1, i, 2 * m - 2);
      stk.pop_back();
    }
  }

  printf("%d\n", sol);

  clock_t finishTime = clock();
  printf("%.3f\n", (double)(finishTime - startTime) / CLOCKS_PER_SEC);
  return 0;
}
