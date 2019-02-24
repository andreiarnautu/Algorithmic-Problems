/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int kDim = 1000 + 5;
const int kModulo = 1e9 + 7;

/*-------- Data --------*/
long long part[kDim][kDim];
long long bell[kDim];

int M, N;
char s[kDim];
long long mask[kDim];

std::map<long long, int > map;
/*-------- --------*/


int main() {
  part[0][0] = 1;
  for(int i = 1; i < kDim; i++) {
    for(int j = 1; j < kDim; j++) {
      part[i][j] = (part[i - 1][j - 1] + 1LL * j * part[i - 1][j]) % kModulo;
    }
  }

  for(int i = 1; i < kDim; i++) {
    for(int j = 1; j < kDim; j++) {
      bell[i] = (bell[i] + part[i][j]) % kModulo;
    }
  }

  scanf("%d%d", &M, &N);
  for(int i = 0; i < N; i++) {
    scanf("%s", s);
    for(int j = 0; j < M; j++) {
      if(s[j] == '1') {
        mask[j] |= (1LL << i);
      }
    }
  }

  for(int i = 0; i < M; i++) {
    map[mask[i]]++;
  }

  long long sol = 1;
  for(auto& itr : map) {
    sol = (sol * bell[itr.second]) % kModulo;
  }
  printf("%lld\n", sol);
	return 0;
}
