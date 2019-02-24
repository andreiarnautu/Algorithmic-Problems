/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

int n;
int a[30], sol[30];
std::pair<int, int > b[30];

int main() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]); b[i] = {a[i], i};
  }
  std::sort(b, b + n);
  for(int i = 0; i < n; i++) {
    sol[b[i].second] = b[(i + 1) % n].first;
  }
  for(int i = 0; i < n; i++) {
    printf("%d ", sol[i]);
  }
  return 0;
}
