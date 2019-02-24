/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("gard3.in", "r", stdin); FILE *fout = freopen("gard3.out", "w", stdout);

const int kMaxN = 50 + 1;
const int kMaxDigits = 50;
const int kBase = 1e3;

class Huge {
public:
    int v[kMaxDigits];

    Huge() {
        memset(v, 0, sizeof(v)); v[0] = 1;
    }

    void operator +=(const Huge &other) {
        int i, t;
        for(i = 1, t = 0; i <= v[0] || i <= other.v[0] || t != 0; i++, t /= kBase) {
            v[i] = (t += v[i] + other.v[i]) % kBase;
        }
        v[0] = i - 1;
    }

    void operator *=(const Huge &other) {
        int i, j, t;
        Huge answer;

        for(i = 1; i <= v[0]; i++) {
            for(j = 1, t = 0; j <= other.v[0] || t != 0; j++, t /= kBase) {
                answer.v[i + j - 1] = (t += answer.v[i + j - 1] + v[i] * other.v[j]) % kBase;
            }
            answer.v[0] = std::max(answer.v[0], i + j - 2);
        }

        memset(v, 0, sizeof(v));
        for(int i = 0; i <= answer.v[0]; i++) {
            v[i] = answer.v[i];
        }
    }

    void Print() {
        for(int i = v[0]; i > 0; i--) {
            if(i == v[0]) {
                printf("%d", v[i]);
            } else {
                if(v[i] < 100) printf("0");
                if(v[i] < 10) printf("0");
                printf("%d", v[i]);
            }
        }
        printf("\n");
    }
};

Huge dp[kMaxN][kMaxN][2];

int main() {
    int N, K; scanf("%d%d", &N, &K); K--;

    dp[3][0][0].v[1] = 1;

    for(int i = 4; i <= N; i++) {
        dp[i][0][0].v[1] = 1;

        for(int j = 1; j <= std::min(K, i - 3); j++) {
            //!  Compute dp[i][j][0]

            dp[i][j][0] += dp[i - 1][j][1];
            dp[i][j][0] += dp[i - 1][j][0];
            dp[i][j][0] += dp[i - 1][j - 1][1];
            dp[i][j][0] += dp[i - 1][j - 1][0];

            //!  Compute dp[i][j][1]

            for(int a = 3; a <= i - 1; a++) {
                for(int b = 0; b <= std::min(j, a - 3); b++) {
                    if(i - a + 2 < j - 1 - b + 2) continue;

                    Huge temp = dp[i - a + 2][j - 1 - b][0];
                    temp += dp[i - a + 2][j - 1 - b][1];
                    temp *= dp[a][b][0];

                    dp[i][j][1] += temp;
                }
            }
        }
    }

    Huge solution = dp[N][K][0];
    solution += dp[N][K][1];
    solution.Print();

	return 0;
}
