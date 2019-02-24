/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("clepsidra.in", "r", stdin);
FILE *fout = freopen("clepsidra.out", "w", stdout);

const int MAX_N = 1 + 200002;
const int MOD = 666013;

/*--------------------------*/ /** General data */
int N, M;
vector< int > graph[MAX_N];
/*--------------------------*/ /** Articulation points + ccCount for each node */
int level[MAX_N], dp[MAX_N], ccCount[MAX_N];
int p2[MAX_N];
/*--------------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void Generate() {
    p2[0] = 1;
    for(int i = 1; i <= N; i++) {
        p2[i] = (p2[i - 1] << 1) % MOD;
    }
}

void biconnectedDFS(int node = 1, int father = 0) {
    dp[node] = level[node];
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(!level[*it]) {
            level[*it] = level[node] + 1;
            biconnectedDFS(*it, node);
            if(dp[*it] >= level[node]) {
                ccCount[node]++;
            }
        }
    }

    if(father != 0) {
        ccCount[node]++;
    }

    bool okFather = false;
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(*it == father && !okFather) {
            okFather = true;
        } else {
            dp[node] = min(dp[node], dp[*it]);
        }
    }
}

void writeData() {
    for(int i = 1; i <= N; i++) {
        int value = p2[ccCount[i]] - 2;
        if(value < 0) {
            value += MOD;
        }
        printf("%d\n", value);
      //  printf("%d\n", ccCount[i]);
    }
}

int main() {
    readData();
    Generate();
    level[1] = 1; biconnectedDFS();
    writeData();

    return 0;
}
