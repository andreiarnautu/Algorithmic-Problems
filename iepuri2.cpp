/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("iepuri2.in", "r", stdin);
FILE *fout = freopen("iepuri2.out", "w", stdout);

const int MAX_N = 1 + 100;
const int MOD = 30011;

vector <int> G[MAX_N];
int n, k;
bool hasFather[MAX_N];

int dp[MAX_N][MAX_N];
int minK[MAX_N];

void readData() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i < n; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
        hasFather[v] = true;
    }
}

void runDP(int node) {
    if(G[node].size() == 0) {
        /* daca nodul e frunza */
        minK[node] = 1;
        for(int i = 1; i <= k; ++i) {
            dp[node][i] = i;
        }
    }
    else {
        for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
            runDP(*it);
            minK[node] = max(minK[node], minK[*it] + 1);
        }
        for(int i = minK[node]; i <= k; ++i) {
            int current = 1;
            for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
                current = (current * dp[*it][i - 1]) % MOD;
            }
            dp[node][i] = (dp[node][i - 1] + current) % MOD;
        }
    }

}

int main() {

    readData();
    for(int i = 1; i <= n; ++i) {
        if(!hasFather[i]) {
            runDP(i);
            printf("%d", dp[i][k]);
        }
    }
    return 0;
}
