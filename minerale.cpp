/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
FILE *fin = freopen("minerale.in", "r", stdin);
FILE *fout = freopen("minerale.out", "w", stdout);

const int MAX_M = 1 + 100 + 1;
const int SIGMA = 26;

/*---------------------*/
int R, M;
int charMask[SIGMA], charDuoMask[SIGMA][SIGMA];
char X[3], Y[3];
/*---------------------*/
char Str[MAX_M];
int len;
int Left[MAX_M], Right[MAX_M];
int dp[MAX_M][MAX_M];
/*---------------------*/

void readInput() {
    scanf("%d%d", &R, &M);
    for(int i = 1; i <= R; i++) {
        scanf("%s%s", X, Y);
        if(Y[0] >= 'a') {
            charMask[Y[0] - 'a'] |= 1 << (X[0] - 'a');
        } else {
            charDuoMask[Y[0] - 'A'][Y[1] - 'A'] |= 1 << (X[0] - 'a');
        }
    }
}

int getMask(int x, int y) {
    if(x == 0 || y == 0) {
            return 0;
    }


    int Answer = 0;
    int leftSize = 0, rightSize = 0;

    for(int i = 0, p2 = 1; p2 <= x || p2 <= y; i++, p2 <<= 1) {
        if(p2 & x) {
            Left[++leftSize] = i;
        }
        if(p2 & y) {
            Right[++rightSize] = i;
        }
    }

    for(int i = 1; i <= leftSize; i++) {
        for(int j = 1; j <= rightSize; j++) {
            Answer |= charDuoMask[Left[i]][Right[j]];
        }
    }

    return Answer;
}

void solveTest() {
    for(int i = 1; i <= len; i++) {
        for(int j = 1; j <= len; j++) {
            dp[i][j] = 0;
        }
    }

    for(int i = 1; i <= len; i++) {
        dp[i][i] = charMask[Str[i] - 'a'];
    }
    for(int crtLen = 2; crtLen <= len; crtLen++) {
        for(int right = crtLen; right <= len; right++) {
            const int left = right - crtLen + 1;

            for(int middle = left; middle < right; middle++) {
                dp[left][right] |= getMask(dp[left][middle], dp[middle + 1][right]);
            }
        }
    }

    if(dp[1][len] & (1 << ('S' - 'A'))) {
        printf("1\n");
    } else if(dp[1][len] > 0) {
        printf("2\n");
    } else {
        printf("0\n");
    }
}

int main() {
    readInput();
    for(; M; M--) {
        scanf("%s", Str + 1); len = strlen(Str + 1);
        solveTest();
    }
    return 0;
}

