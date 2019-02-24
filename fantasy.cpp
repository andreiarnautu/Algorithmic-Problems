/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

FILE *fin = freopen("fantasy.in", "r", stdin);
FILE *fout = freopen("fantasy.out", "w", stdout);

const int kMaxN = 1 + 1000;

/*-------- Input data --------*/
int test_count;
int N, D, C, V;
vector<int > graph[kMaxN];
/*-------- Test Solving data --------*/
int root;
int depth[kMaxN], dad[kMaxN];
/*-------- --------*/

void ReadTestData() {
    scanf("%d%d%d%d", &N, &D, &C, &V);
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void DFS(int node = root, int father = -1) {
    for(int son : graph[node]) {
        if(son != father) {
            depth[son] = depth[node] + 1;
            dad[son] = node;
            DFS(son, node);
        }
    }
}

int GetLCA(int u, int v) {
    while(u != v) {
        if(depth[u] < depth[v]) {
            v = dad[v];
        } else if(depth[u] > depth[v]) {
            u = dad[u];
        } else {
            u = dad[u]; v = dad[v];
        }
    }
    return u;
}

void ClearTestData() {
    for(int i = 1; i <= N; i++) {
        graph[i].clear();
        dad[i] = 0;
        depth[i] = 0;
    }
}

int main() {
    for(scanf("%d", &test_count); test_count > 0; test_count--) {
        ReadTestData();
        root = D; depth[D] = 1;
        DFS();
        int lca = GetLCA(V, C);
        //printf("%d ", lca);

        if(lca == root) {  /** aici e in regula */
            printf("NU\n");
            ClearTestData();
        } else {
            if(lca == C) {  /** aici e in regula */
                printf("DA\n"); ClearTestData();
            } else if(lca == V) {  /** aici e in regula */
                bool ok = false;
                for(int node = C; node != D; node = dad[node]) {
                    if(graph[node].size() >= 3 && std::abs(depth[V] - depth[node]) < std::abs(depth[C] - depth[node]) && std::abs(depth[C] - depth[node]) <= std::abs(depth[D] - depth[node])) {
                        ok = true; break;
                    }
                }
                if(ok == false) {
                    printf("NU\n");
                } else {
                    printf("DA\n");
                }

                ClearTestData();
            } else {  ///  LCA-ul nu este nici C, nu este nici V
                int time_D = std::abs(depth[D] - depth[lca]);
                int time_V = std::abs(depth[V] - depth[lca]);
                int time_C = std::abs(depth[C] - depth[lca]);

                if(time_C <= time_D) {  ///  V sta pe loc, iar C il va omori pe D
                    printf("DA\n"); ClearTestData();
                } else {  ///  Dragonul ajunge inaintea cavalerului in lca
                    if(time_V >= time_D) {  ///  Daca ajunge si inaintea vrajitorului in LCA, GG
                        printf("NU\n"); ClearTestData();
                    } else {
                        V = lca; ///  V urca in lca
                        for(int i = 1; i <= time_V; i++) {
                            C = dad[C];
                        }

                        vector<int > path;
                        for(int node = V; node != D; node = dad[node]) {
                            path.push_back(node);
                        }
                        std::reverse(path.begin(), path.end());
                        D = path[time_V - 1];

                        bool ok = false;
                        for(int node = C; node != D; node = dad[node]) {
                            if(graph[node].size() >= 3 && std::abs(depth[V] - depth[node]) < std::abs(depth[C] - depth[node]) && std::abs(depth[C] - depth[node]) <= std::abs(depth[D] - depth[node])) {
                                ok = true; break;
                            }
                        }

                        if(ok == false) {
                            printf("NU\n");
                        } else {
                            printf("DA\n");
                        }
                        ClearTestData();
                    }
                }
            }
        }
    }

    return 0;
}
