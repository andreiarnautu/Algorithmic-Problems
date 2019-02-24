/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb          push_back
#define mod         2999
#define MAX_N       1 + 100000

using namespace std;
FILE *fin=freopen("chimichangas.in","r",stdin);
FILE *fout=freopen("chimichangas.out","w",stdout);

vector < int > comb[MAX_N], dp[MAX_N], add[MAX_N];
vector < bool > ok[MAX_N];

int c[MAX_N], sol[MAX_N];
int n, k, maxC;

void readData() {

    scanf("%d %d ", &n, &k);
    for(int i = 1; i <= n; ++i) {

        scanf("%d ", &c[i]);
        maxC = max(maxC, c[i]);
    }
}

void genComb() {

    for(int i = 1; i <= k + 3; ++i)
        for(int j = 0; j <= i; ++j)
            comb[i].pb(0);

    comb[1][1] = 1;
    for(int i = 2; i <= k + 3; ++i) {

        for(int j = 1; j < i; ++j)
            comb[i][j] = ( comb[i - 1][j - 1] + comb[i - 1][j] ) % mod;
        comb[i][i] = comb[i - 1][i - 1];
    }
}

void runDp() {

    maxC *= k;
    for(int i = 0; i <= maxC ; ++i)
        for(int j = 0; j <= k ; ++j){

            dp[i].pb(0);
            ok[i].pb(0);
            add[i].pb(0);
        }

    dp[0][0] = ok[0][0] = 1;
    for(int l = 1; l <= n; ++l) {

        for(int i = 0; i <= maxC; ++i)
            for(int j = 0; j <= k; ++j)
                if(dp[i][j])
                    for(int p = 1; j + p <= k && i + p * c[l] <= maxC; ++p)
                        add[i + p * c[l]][j + p] = 1LL * (add[i + p * c[l]][j + p] + dp[i][j] * comb[j + p + 1][p + 1]) % mod;

        for(int i = 0; i <= maxC; ++i)
            for(int j = 0; j <= k; ++j)
                if(add[i][j]) {

                    ok[i][j] = 1;
                    dp[i][j] = (dp[i][j] + add[i][j]) % mod;
                    add[i][j] = 0;
                }

        /*for(int i = 1; i <= maxC; ++i) {

            for(int j = 1; j <= 4; ++j)
                printf("%d ", dp[i][j]);
            printf("\n");
        }
        printf("------------\n");*/
    }
    //printf("%d", dp[8][k]);
}

void answerQuery() {

    int q;
    scanf("%d ", &q);
    if(q > maxC)
        printf("0\n");
    else
        printf("%d\n", dp[q][k]);
}

int main() {

    readData();
    genComb();
    runDp();
    int q;
    for(scanf("%d ", &q); q; --q)
        answerQuery();
    return 0;
}
