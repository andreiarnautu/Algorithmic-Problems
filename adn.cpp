/**
  *  Worg
  */
#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;
FILE *fin = freopen("adn.in", "r", stdin);
ofstream out("adn.out");

const int MAX_N   = 18,
          MAX_LEN = 1 + 30000 + 1,
          MAX_INF = 0x3fffffff;

char s[MAX_N][MAX_LEN];
int lg[MAX_N];
int n;

int pi[MAX_LEN]; /* KMP */

int cost[MAX_N][MAX_N], dp[1 << MAX_N][MAX_N], previous[1 << MAX_N][MAX_N], trueCost[MAX_N][MAX_N]; /* Hamiltonian cycle */
int nodeMask[MAX_N], v[MAX_N], sol[MAX_N];
int cnt, solSize;
bool noNeed[MAX_N];
char bit[1 << MAX_N];

string adn;

void readData() {

    scanf("%d ", &n);
    for(int i = 0; i < n; ++i) {

        gets(s[i] + 1);
        lg[i] = strlen(s[i] + 1);
    }
    for(int i = 0; i < n; ++i)
        bit[1 << i] = i;
}

void getPrefix(int j) {

    int len = lg[j], k = 0;

    for(int i = 2; i <= len; ++i) {

        while(k && s[j][i] != s[j][k + 1])
            k = pi[k];
        if(s[j][i] == s[j][k + 1])
            k++;
        pi[i] = k;
    }
}

void matchStrings(int p, int q) {

    int len = lg[q], k = 0;

    for(int i = 1; i <= len; ++i) {

        while(k && s[q][i] != s[p][k + 1])
            k = pi[k];
        if(s[q][i] == s[p][k + 1])
            k++;
        if(k == lg[p]) {

            noNeed[p] = true;
            return;
        }
    }
    cost[q][p] = lg[p] - k;
}

void runDp() {

    int limit = 1 << cnt;
    for(int i = 0; i < limit; ++i)
        for(int j = 0; j < cnt; ++j)
            dp[i][j] = MAX_INF;
    for(int i = 0; i < cnt; ++i)
        dp[1 << i][i] = lg[v[i]];


    for(int mask = 1; mask < limit; ++mask) {

        int tmpMask = mask;
        while(tmpMask) {

            int newMask = tmpMask & (tmpMask - 1);
            int v = bit[newMask ^ tmpMask];
            tmpMask = newMask;

            int config = nodeMask[v];
            while(config) {

                int newConfig = config & (config - 1);
                int u = bit[config ^ newConfig];
                config = newConfig;

                if(dp[mask ^ (1 << v)][u] + trueCost[u][v] < dp[mask][v]) {

                    previous[mask][v] = u;
                    dp[mask][v] = dp[mask ^ (1 << v)][u] + trueCost[u][v];
                }
            }
        }
    }

    int lgSol = MAX_INF, lastNode = 0;
    for(int i = 0; i < cnt; ++i)
        if(dp[limit - 1][i] < lgSol) {

            lgSol = dp[limit - 1][i];
            lastNode = i;
        }

    int lastMask = limit - 1;
    while(lastMask) {

        sol[solSize++] = lastNode;
        int aux = previous[lastMask][lastNode];
        lastMask = lastMask ^ (1 << lastNode);
        lastNode = aux;
    }

    int ignoreCount = 0;
    for(int i = solSize - 1; i >= 0; --i) {

        for(int j = ignoreCount + 1; j <= lg[v[sol[i]]]; ++j)
            adn += s[v[sol[i]]][j];
        if(i)
            ignoreCount = lg[v[sol[i - 1]]] - trueCost[sol[i]][sol[i - 1]];
    }
    out << adn;
}

int main() {

    readData();
    for(int i = 0; i < n; ++i) {

        getPrefix(i);
        for(int j = 0; j < n; ++j)
            if(i != j)
                matchStrings(i, j);
    }

    for(int i = 0; i < n; ++i)
        if(!noNeed[i])
            v[cnt++] = i;

    for(int i = 0; i < cnt; ++i) {

        for(int j = 0; j < cnt; ++j)
            if(i != j) {

                trueCost[i][j] = cost[v[i]][v[j]];
                nodeMask[i] ^= (1 << j);
            }
    }
    runDp();
    return 0;
}
