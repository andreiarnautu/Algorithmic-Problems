/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("karb2.in", "r", stdin);
FILE *fout = freopen("karb2.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MOD = 666013;

/*---------------------*/
int N, K;
bool cartel[MAX_N];
vector< int > G[MAX_N];
/*---------------------*/
int INT[MAX_N], EXT[MAX_N];
/*---------------------*/

int inv_mod(int val) {
    long long answer = 1;
    long long aux = 1LL * val;
    for(int pow = 1; pow <= MOD - 2; pow <<= 1) {
        if(pow & (MOD - 2)) {
            answer = (answer * aux) % MOD;
        }
        aux = (aux * aux) % MOD;
    }

    return (int)answer;
}

void readData() {
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= K; i++) {
        int node; scanf("%d", &node);
        cartel[node] = true;
    }
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v); G[v].push_back(u);
    }
}

void DFS(int node = 1, int father = 0) {
    int X = 1;

    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(father != *it) {
            DFS(*it, node);

            X = (1LL * X * (INT[*it] + EXT[*it])) % MOD;
        }
    }

    if(!cartel[node]) {
        EXT[node] = X; INT[node] = 0;
        for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
            if(father != *it) {
                INT[node] = (1LL * INT[node] + 1LL * INT[*it] * X * inv_mod(INT[*it] + EXT[*it])) % MOD;
            }
        }
    } else {
        EXT[node] = 0; INT[node] = X;
    }

}

void writeData() {
   /* for(int i = 1; i <= N; i++) {
        printf("Nodul %d: INT = %d; EXT = %d;\n", i, INT[i], EXT[i]);
    }  */


    printf("%d", INT[1]);
}

int main() {
    readData();
    DFS();
    writeData();
    return 0;
}
