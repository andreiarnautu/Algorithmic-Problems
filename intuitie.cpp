/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("intuitie.in", "r", stdin);
FILE *fout = freopen("intuitie.out", "w", stdout);

const int MAX_N = 1 + 500;
const int MAX_S = 5;
const int mod = 999017;

/*-------- Input data --------*/
int N, P, Q;
/*-------- Dp data --------*/
int dp[2][MAX_S][MAX_N][MAX_N];
/*-------- --------*/

void Read_Input() {
    scanf("%d%d%d", &N, &P, &Q);
}

void fix_value(int &value) {
    while(value < 0) {
        value += mod;
    }
    if(value >= mod) {
        value %= mod;
    }
}

int Get_Solution() {
    int now = 0, prev = 1;
    int solution = 0;

    dp[now][1][0][2] = 1;
    dp[now][4][0][1] = dp[now][4][0][2] = 1;

    for(int i = 3; i <= N; i++) {
        now ^= 1;
        prev ^= 1;

        for(int p = 0; p <= min(P, i); p++) {
            for(int h = 1; h <= i; h++) {
                dp[now][0][p][h] = dp[now][0][p][h - 1] + dp[prev][0][p][h - 1];
                fix_value(dp[now][0][p][h]);

                dp[now][1][p][h] = dp[now][1][p][h - 1] + dp[prev][1][p][h - 1] + dp[prev][3][p][h - 1];
                fix_value(dp[now][1][p][h]);

                dp[now][2][p][h] = dp[now][2][p][h - 1] + dp[prev][2][p][h - 1] + dp[prev][4][p][h - 1];
                fix_value(dp[now][2][p][h]);

                dp[now][3][p][h] = dp[now][3][p][h - 1] + dp[prev][3][p][i - 1] - dp[prev][3][p][h - 1];
                if(p > 0) {
                    dp[now][3][p][h] += dp[prev][1][p - 1][i - 1] - dp[prev][1][p - 1][h - 1];
                }
                fix_value(dp[now][3][p][h]);

                dp[now][4][p][h] = dp[now][4][p][h - 1] + dp[prev][4][p][i - 1] - dp[prev][4][p][h - 1];
                if(p > 0) {
                    dp[now][4][p][h] += dp[prev][2][p - 1][i - 1] - dp[prev][2][p - 1][h - 1];
                }
                fix_value(dp[now][4][p][h]);

            }
        }
    }

    if(P == Q) {
        solution = dp[now][1][P][N] + dp[now][4][P][N];
    } else {
        solution = dp[now][0][P][N] + dp[now][3][P][N];
    }

    fix_value(solution);
    return solution;
}

int main() {
    Read_Input();
    if(P < Q) {
        swap(P, Q);
    }
    if(P > Q + 1) {
        printf("0\n");
    } else {
        printf("%d\n", Get_Solution());
    }

    return 0;
}
