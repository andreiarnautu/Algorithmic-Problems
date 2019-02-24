/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

int h, n;
std::vector<int > a, lst, now;
std::vector<int > f1, f2;

int main() {
  scanf("%d", &h); a.resize(h + 1);
  for(auto& itr : a) {
    scanf("%d", &itr); n += itr;
  }

  f1.resize(n + 1); f2.resize(n + 1);

  f1[1] = f2[1] = 0;
  lst.push_back(1);

  int ok = true;
  for(int i = 1, act = 1; i <= h; i++) {
    if(lst.size() == 1) {
      for(int j = 1; j <= a[i]; j++) {
        act++; now.push_back(act); f1[act] = lst[0]; f2[act] = lst[0];
      }
    } else {
      if(a[i] == 1) {
        act++;
        now.push_back(act); f1[act] = lst[0]; f2[act] = lst[0];
      } else {
        ok = false;
        for(int j = 1; j <= a[i]; j++) {
          act++; now.push_back(act);
          f1[act] = lst[0];
          if(j == 1) {
            f2[act] = lst[0];
          } else {
            f2[act] = lst[1];
          }
        }
      }
    }

    lst = now; now.clear();
  }

  if(ok) {
    printf("perfect\n");
  } else {
    printf("ambiguous\n");
    for(int i = 1; i <= n; i++) {
      printf("%d ", f1[i]);
    }
    printf("\n");
    for(int i = 1; i <= n; i++) {
      printf("%d ", f2[i]);
    }
  }
  return 0;
}
