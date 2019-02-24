/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int maxN = 1e4 + 5;
const int ct = (1 << 18) - 1;

/*-------- Data --------*/
int n;
std::vector<std::pair<int, int > > v;
std::unordered_map<int, int > where;
std::vector<int > h[ct + 1];

int sol[maxN], crt[maxN];

clock_t start, finish;
/*-------- --------*/

void Insert(int idx) {
  int key = (v[idx].first & ct) ^ ((v[idx].first >> 13) & ct);
  h[key].push_back(idx);
}

int Find(long long value) {
  if(value <= 0) return -1;

  int key = (value & ct) ^ ((value >> 13) & ct);
  for(auto& itr : h[key]) {
    if(v[itr].first == value) {
      return itr;
    }
  }
  return -1;
}

void ReadInput() {
  scanf("%d", &n); v.resize(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &v[i].first); v[i].second = i + 1;
  }

  std::sort(v.begin(), v.end());

  std::vector<std::pair<int, int > > aux;
  for(int i = 0; i < n; i++) {
    if(i == 0 || v[i].first != v[i - 1].first) {
      aux.push_back(v[i]);
    }
  }
  v = aux; n = (int)v.size();

  for(int i = 0; i < n; i++) {
    Insert(i);
  }
}

void RunDP() {
  int solSize = 1; sol[1] = 1;
  int crtSize;

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      int ratio = v[j].first - v[i].first;

      if(ratio == 0 || Find(v[i].first - ratio) != -1 || Find(v[i].first + ratio * solSize) == -1) continue;

      crt[1] = v[i].second; crt[2] = v[j].second;
      crtSize = 2;

      int now = v[j].first, x;
      while((x = Find(now + ratio)) != -1) {
        crt[++crtSize] = v[x].second; now += ratio;
      }

      if(crtSize > solSize) {
        solSize = crtSize;
        for(int k = 1; k <= solSize; k++) {
          sol[k] = crt[k];
        }
      }
    }
  }

  finish = clock();
  //printf("%.3f\n", (double)(finish - start) / CLOCKS_PER_SEC);

  printf("%d\n", solSize);
  for(int i = 1; i <= solSize; i++) {
    printf("%d ", sol[i]);
  }
}

int main() {
  start = clock();
  ReadInput();

  RunDP();

  return 0;
}
