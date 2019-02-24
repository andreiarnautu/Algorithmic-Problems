/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("grazing.in", "r", stdin); FILE *fout = freopen("grazing.out", "w", stdout);

const int kMaxDigits = 630;
const int kMaxN = 300 + 1;
const int kBase = 1e5;

/*-------- Data --------*/
struct Huge {
  int v[kMaxDigits];

  Huge() {
    memset(v, 0, sizeof(v)); v[0] = 1;
  }

  void operator +=(Huge &other) {
    int i, t;
    for(i = 1, t = 0; i <= v[0] || i <= other.v[0] || t != 0; i++, t /= kBase) {
      v[i] = (t += v[i] + other.v[i]) % kBase;
    }
    v[0] = i - 1;
  }

  void operator *=(int value) {
    int i, t;
    for(i = 1, t = 0; i <= v[0] || t != 0; i++, t /= kBase) {
      v[i] = (t += v[i] * value) % kBase;
    }
    v[0] = i - 1;
  }

  void operator /=(int value) {
    int i, t;
    for(i = v[0], t = 0; i > 0; i--, t %= value) {
      v[i] = (t = v[i] + t * kBase) / value;
    }
    while(v[0] > 1 && v[v[0]] == 0) {
      v[0]--;
    }
  }

  void write() {
    for(int i = v[0]; i > 0; i--){
      if(i != v[0]) {
        for(int j = kBase / 10; j > 1; j /= 10) {
          if(v[i] < j) {
            printf("0");
          }
        }
        printf("%d", v[i]);
      } else {
        printf("%d", v[i]);
      }
    }
    printf("\n");
  }
};

Huge dp[kMaxN];
/*-------- --------*/

int main() {
  int N; scanf("%d", &N);

  dp[1].v[1] = dp[0].v[1] = 1;

  for(int i = 2; i <= N; i++) {
    dp[i] = dp[i - 1];
    for(int j = i - 2; j >= 0; j--) {
      dp[j] *= (i - 1);

      Huge act = dp[j];
      if((i - j) % 3 == 0 || (i - j) < 3) {
        act *= (i - j);
      } else {
        act *= (1 + i - j);
      }
      act /= 2;

      dp[i] += act;
    }
  }

  dp[N].write();
	return 0;
}
