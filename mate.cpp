/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("mate.in", "r", stdin); FILE *fout = freopen("mate.out", "w", stdout);

const int maxN = 5e5 + 5;

/*-------- Data --------*/
int n;
int v[maxN], cnt[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }
}

bool Check(int len) {
  for(int i = 1; i <= n; i++) {
    cnt[i] = 0;
  }

  for(int i = 1; i <= n; i++) {
    cnt[v[i]]++;

    if(i > len) {
      cnt[v[i - len]]--;
    }

    if(cnt[v[i]] >= (len + 1) / 2) {
      return true;
    }
  }

  return false;
}

int BinarySearch() {
  int left = 1, right = n, sol = 1;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(Check(mid)) {
      sol = mid; left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return sol;
}

int main() {
  ReadInput();

  printf("%d\n", BinarySearch());

  return 0;
}
