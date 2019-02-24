/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using std::pair;
using std::vector;

FILE *fin = freopen("camion2.in", "r", stdin);
FILE *fout = freopen("camion2.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_P = 1 + 25;
const int MAX_INF = 1e9;

/*-------- Input data --------*/
int N, P;
vector<pair<int, int > > graph[MAX_N];
/*-------- Algorithm data --------*/
int dp[2][MAX_N][MAX_P][2];  //  Retinem doar ultimele 2 etaje de la dinamica
/*-------- ---------*/

void ReadInput() {
    scanf("%d%d", &N, &P);
    for(int i = 1; i < N; i++) {
        int u, v, dist; scanf("%d%d%d", &u, &v, &dist);
        graph[u].push_back(std::make_pair(v, dist));
        graph[v].push_back(std::make_pair(u, dist));
    }
}

void Initialize() {
    for(int i = 0; i <= N; i++) {
        for(int j = 1; j <= P; j++) {
            for(int k = 0; k <= 1; k++) {
                dp[0][i][j][k] = dp[1][i][j][k] = MAX_INF;
            }
        }
        dp[0][i][0][0] = dp[0][i][0][1] = dp[1][i][0][0] = dp[1][i][0][1] = 0;
    }
}

void DFS(int node = 1, int father = -1) {  //  Radacina arborelui este nodul 1
    for(pair<int, int > edge : graph[node]) {
        if(edge.first != father) {
            DFS(edge.first, node);
        }
    }

    if(graph[node].size() == 1 && father != -1) {  // Daca am ajuns intr-o frunza, initializam dinamica
        dp[0][node][1][0] = dp[0][node][1][1] = dp[1][node][1][0] = dp[1][node][1][1] = 0;
    } else {
        //  Intai ne ocupam de cazul cand din niciun fiu nu se intoarce nimic
        int sons = 0;
        int now = 0, before;
        for(pair<int, int > edge : graph[node]) {
            if(edge.first != father) {
                int son = edge.first;
                int dist = edge.second;

                before = now; now ^= 1;
                dp[now][node][0][0] = dp[now][node][0][1] = MAX_INF;

                for(int p = 1; p <= P; p++) {  //  In {node} intra {p} camioane
                    dp[now][node][p][0] = dp[now][node][p][1] = MAX_INF;
                    for(int ps = 1; ps <= p; ps++) {  //  In {son} intra {pf} camioane
                        //  Calculam dp[node][p][0]
                        dp[now][node][p][0] = std::min(dp[now][node][p][0], dp[before][node][p - ps][0] + dist * ps + dp[0][son][ps][0]);
                        dp[now][node][p][0] = std::min(dp[now][node][p][0], dp[before][node][p - ps + 1][1] + dist * ps + dp[0][son][ps][0]);
                        dp[now][node][p][0] = std::min(dp[now][node][p][0], dp[before][node][p - ps + 1][0] + dist * (ps + 1) + dp[0][son][ps][1]);

                        //  Calculam dp[node][p][1]
                        dp[now][node][p][1] = std::min(dp[now][node][p][1], dp[before][node][p - ps][0] + dist * (ps + 1) + dp[0][son][ps][1]);
                        dp[now][node][p][1] = std::min(dp[now][node][p][1], dp[before][node][p - ps + 1][1] + dist * (ps + 1) + dp[0][son][ps][1]);
                    }

                }
            }
        }

        //  Copiem dinamica pe ambele etaje
        for(int i = 1; i <= P; i++) {
            for(int j = 0; j <= 1; j++) {
                dp[now ^ 1][node][i][j] = dp[now][node][i][j];
            }
        }
        dp[0][node][0][0] = dp[1][node][0][0] = dp[0][node][0][1] = dp[1][node][0][1];
    }

    //printf("Pentru nodul %d:\n", node);
    //printf("%d %d\n", dp[0][node][1][0], dp[0][node][1][1]);
}

void WriteOutput() {
    int solution = MAX_INF;
    for(int i = 1; i <= P; i++) {
        for(int j = 0; j <= 1; j++) {
            solution = std::min(solution, dp[0][1][i][j]);
        }
    }
    printf("%d\n", solution);
}

int main() {
    ReadInput();
    Initialize();
    DFS();
    WriteOutput();
    return 0;
}
