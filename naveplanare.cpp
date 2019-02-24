/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("naveplanare.in", "r", stdin);
FILE *fout = freopen("naveplanare.out", "w", stdout);

const int MAX_N = 1 + 200;
const int MAX_COORD = 1 + 2500;
const int MAX_INF = 0x3fffffff;
const int Delay = 1200;

/*--------------------------*/
int N, K;
pair< int,int > vec[MAX_N];
/*--------------------------*/
int dp[2][MAX_N][MAX_COORD];
/*--------------------------*/

void readInput() {
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; i++) {
        int a, b; scanf("%d%d", &a, &b);
        vec[i] = make_pair(a, b);
    }
}

int runDP() {
    const int Min_Coord = vec[1].first - N;
    const int Max_Coord = vec[N].first + N;

    for(int j = 0; j <= N; j++) {
        for(int k = Min_Coord; k <= Max_Coord; k++) {
            dp[0][j][k + Delay] = dp[1][j][k + Delay] = MAX_INF;
        }
    }

    for(int i = Min_Coord; i <= Max_Coord; i++) {
        dp[1][1][i + Delay] = abs(i - vec[1].first);
        if(i > Min_Coord) {
            dp[1][1][i + Delay] = min(dp[1][1][i + Delay], dp[1][1][i - 1 + Delay]);
        }
    }

    int line = 0;
    for(int i = 2; i <= N; i++) {
        for(int j = 0; j <= N; j++) {
            for(int k = Min_Coord - 1; k <= Max_Coord; k++) {
                dp[line][j][k + Delay] = MAX_INF;
            }
        }
        for(int j = 1; j <= i; j++) {
            for(int k = Min_Coord + j - 1; k <= Max_Coord; k++) {
                if(j == 1) {
                    dp[line][j][k + Delay] = dp[line ^ 1][j][k + Delay] + abs(k - vec[i].first);
                } else {
                    dp[line][j][k + Delay] = min(dp[line ^ 1][j - 1][k - 1 + Delay] + abs(k - vec[i].first),
                                                  dp[line][j][k - 1 + Delay]);
                     if(j < i) {
                        dp[line][j][k + Delay] = min(dp[line][j][k + Delay], dp[line ^ 1][j][k + Delay]);
                     }
                }
            }
        }
        line ^= 1;
    }

    int Answer = MAX_INF;
    for(int j = K; j <= N; j++) {
        for(int k = Min_Coord + j - 1; k <= Max_Coord; k++) {
            Answer = min(Answer, dp[line ^ 1][j][k + Delay]);
        }
    }

    return Answer;
}

int getAnswer() {
    sort(vec + 1, vec + N + 1);
    int Answer = runDP();
    for(int i = 1; i <= N; i++) {
        swap(vec[i].first, vec[i].second);
    }
    sort(vec + 1, vec + N + 1);
    Answer += runDP();

    return Answer;
}

int main() {
    readInput();
    printf("%d\n", getAnswer());
    return 0;
}
