/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("drumuri.in", "r", stdin); FILE *fout = freopen("drumuri.out", "w", stdout);

/*-------- Structures --------*/
struct Trio {
    int u, v, t;
    Trio(int _u, int _v, int _t) {
        u = _u; v = _v; t = _t;
    }
};
/*-------- Data --------*/
int N, M;
std::vector<std::vector<int > > graph;

std::vector<bool > seen;
std::vector<Trio > solution;
/*-------- --------*/

bool DFS(int node, int dad) {
    seen[node] = true;

    std::vector<int > v;
    for(auto& son : graph[node]) {
        if(seen[son] && son != dad) {
            v.emplace_back(son);
        }
    }

    for(auto& son : graph[node]) {
        if(son != dad && !seen[son]) {
            bool add = DFS(son, node);

            if(add) {
                v.emplace_back(son);
            }
        }
    }

    while((int)v.size() > 1) {
        int u = v.back(); v.pop_back();
        int t = v.back(); v.pop_back();
        solution.emplace_back(u, node, t);
    }

    if(v.size() == 1) {
        solution.emplace_back(v.back(), node, dad);
        return false;
    }
    return true;
}

int main() {
    scanf("%d%d", &N, &M);
    graph.resize(N); seen = std::vector<bool >(N, false);

    for(int i = 0; i < M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        u--; v--;
        graph[u].emplace_back(v); graph[v].emplace_back(u);
    }

    if(M & 1) {
        printf("0\n"); return 0;
    }

    DFS(0, -1);

    printf("1\n");
    for(auto& itr : solution) {
        printf("%d %d %d\n", itr.u + 1, itr.v + 1, itr.t + 1);
    }
	return 0;
}
