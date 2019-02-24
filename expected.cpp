/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("expected.in", "r", stdin);
FILE *fout = freopen("expected.out", "w", stdout);

const int MAX_N = 1 + 200;

/*------------------------*/
int N, K;
int sizeSmall, sizeBig, Small, Big;
int countSmall[MAX_N], countBig[MAX_N];
/*------------------------*/
long double probAB[MAX_N][MAX_N]; // probabilitatea sa alegem i sosete mici si j sosete mari dupa a+b etape */
long double probDiff[MAX_N][MAX_N]; // probabilitatea sa alegem i sosete mici si j sosete mari care sa aiba culori diferite */
long double howMany[MAX_N][MAX_N]; // in cate moduri putem alege i sosete mici si j sosete mari */
long double dp[MAX_N][MAX_N][MAX_N]; // (k,i,j): in cate moduri putem alege i sosete mici si j sosete mari cu culori din
                                     //  intervalul [1..k], astfel incat oricare 2 din ele sa aiba culori diferite */
/*------------------------*/

void readInput() {
    scanf("%d%d", &N, &K);
    scanf("%d%d", &sizeSmall, &sizeBig);
    for(int i = 1; i <= N; i++) {
        int color, size; scanf("%d%d", &color, &size);

        if(size == 0) {
            Small ++;
            countSmall[color] ++;
        } else {
            Big ++;
            countBig[color] ++;
        }
    }
}

void computeDP() {
    probAB[0][0] = 1.0;
    for(int i = 0; i <= Small; i++) {
        for(int j = 0; j <= Big; j++) {
            long double coefSmall = (Small - i) * sizeSmall;
            long double coefBig = (Big - j) * sizeBig;

            probAB[i + 1][j] += probAB[i][j] * coefSmall / (coefSmall + coefBig);
            probAB[i][j + 1] += probAB[i][j] * coefBig   / (coefSmall + coefBig);
        }
    }

    /*------------------------*/

    howMany[0][0] = 1.0;
    for(int i = 0; i <= Small; i++) {
        for(int j = 0; j <= Big; j++) {
            howMany[i + 1][j] = howMany[i][j] * (Small - i);
            howMany[i][j + 1] = howMany[i][j] * (Big - j);
        }
    }

    /*------------------------*/

    dp[0][0][0] = 1.0;
    for(int k = 0; k <= N; k++) {
        for(int i = 0; i <= Small; i++) {
            for(int j = 0; j <= Big && i + j <= K; j++) {
                dp[k + 1][i][j] += dp[k][i][j];
                dp[k + 1][i + 1][j] += dp[k][i][j] * (i + 1) * countSmall[k + 1];
                dp[k + 1][i][j + 1] += dp[k][i][j] * (j + 1) * countBig[k + 1];
            }
        }
    }

    /*------------------------*/

    for(int i = 0; i <= Small; i++) {
        for(int j = 0; j <= Big; j++) {
            probDiff[i][j] = dp[N][i][j] / howMany[i][j];
        }
    }
}

void writeOutput() {
    long double Solution = 0;

    for(int i = 0; i <= Small; i++) {
        for(int j = 0; j <= Big; j++) {
            if(i + j == K) {
                Solution += (1.0 - probDiff[i][j]) * probAB[i][j];
            }
        }
    }

    printf("%.15Lf", Solution);
}

int main() {
    readInput();
    computeDP();
    writeOutput();
    return 0;
}
