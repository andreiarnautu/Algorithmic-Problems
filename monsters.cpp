/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 750 + 2;

/*-------- Input data --------*/
int N, M;
int mat[kMaxN][kMaxN];
char s[kMaxN];
/*-------- Solution --------*/
long long solution[kMaxN][kMaxN];
int left[kMaxN];
bool ok[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%s", s + 1);
        for(int j = 1; j <= M; j++) {
            mat[i][j] = s[j] - '0';
        }
    }
}

long long GetSolution() {
    long long total = 0;
    for(int x1 = 1; x1 <= N; x1++) {
        for(int i = 1; i <= M; i++) {
            ok[i] = 1;
        }
        for(int x2 = x1; x2 <= N; x2++) {
            for(int i = 1; i <= M; i++) {
                ok[i] &= mat[x2][i];
                if(ok[i]) {
                    left[i] = left[i - 1] + 1;
                } else {
                    left[i] = 0;
                }
            }
            for(int i = M, right = 0; i > 0; i--) {
                if(ok[i]) {
                    right ++;
                    solution[x1][i] += right * left[i];
                    solution[x2 + 1][i] -= right * left[i];
                } else {
                    right = 0;
                }
                total += right;
            }
        }
    }

    long long maxLoss = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            solution[i][j] += solution[i - 1][j];
            maxLoss = std::max(maxLoss, solution[i][j]);
        }
    }

    return total - maxLoss;
}

int main() {
    ReadInput();
    printf("%lld\n", GetSolution());
    return 0;
}
