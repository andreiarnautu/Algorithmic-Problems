/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("cabine.in", "r", stdin); FILE *fout = freopen("cabine.out", "w", stdout);

const int kDim = 1e5 + 5;

/*-------- Data --------*/
int n, k;
int v[kDim], where[kDim];
/*-------- --------*/

int main() {
  scanf("%d%d", &n, &k);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }

  int crt = 1;
  if(v[1] == 0) {
    v[1] = crt; where[crt] = 1; crt++;
  }
  if(v[n] == 0) {
    v[n] = crt; where[crt] = n; crt++;
  }

  for(int i = n - 1; i >= 1; i--) {
    if(v[i] == 0 && v[i + 1] == 0) {
      v[i] = crt; where[crt] = i; crt++;
    }
  }
  for(int i = 2; i < n; i++) {
    if(v[i] == 0) {
      v[i] = crt; where[crt] = i; crt++;
    }
  }

  printf("%d\n", where[k]);
	return 0;
}
