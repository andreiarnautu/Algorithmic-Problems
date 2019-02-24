/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("drum2.in", "r", stdin);
FILE *fout = freopen("drum2.out", "w", stdout);

const int MAX_N = 1 + 30;

/*----------------------*/
int N, M;
int ord[MAX_N][MAX_N][MAX_N], value[MAX_N][MAX_N][MAX_N];
/*----------------------*/
int dp[MAX_N][MAX_N][MAX_N];
pair< int,int > nxt[MAX_N][MAX_N][MAX_N];
/*----------------------*/
int answer = 0;
pair< int,int > start;
/*----------------------*/


void readInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        M += (i * i);
    }

    int crtIndex = 0;
    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= k; i++) {
            for(int j = 1; j <= k; j++) {
                scanf("%d", &value[k][i][j]);
                ord[k][i][j] = (++crtIndex);
            }
        }
    }
}

int getDP(int k, int i, int j) {
    if(dp[k][i][j] > 0) {
        return dp[k][i][j];
    } else {
        if(k == N) {
            dp[k][i][j] = value[k][i][j];
        } else {
            int A = getDP(k + 1, i, j + 1);
            int B = getDP(k + 1, i + 1, j);
            int C = getDP(k + 1, i + 1, j + 1);
            int best = max(A, max(B, C));

            if(A == best) {
                nxt[k][i][j] = make_pair(i, j + 1);
            } else if(B == best) {
                nxt[k][i][j] = make_pair(i + 1, j);
            } else {
                nxt[k][i][j] = make_pair(i + 1, j + 1);
            }
            dp[k][i][j] = best + value[k][i][j];
        }

        return dp[k][i][j];
    }
}

void runDP() {
    answer = getDP(1, 1, 1);
}

void writeOutput() {
    printf("%d\n", answer);
    int k = 1, i = 1, j = 1;

    while(k < N) {
        printf("%d ", ord[k][i][j]);
        pair< int,int > crt = nxt[k][i][j];
        k++; i = crt.first; j = crt.second;
    }

    printf("%d ", ord[k][i][j]);
}

int main() {
    readInput();
    runDP();
    writeOutput();

    return 0;
}
