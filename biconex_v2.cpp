/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::stack;
using std::vector;

FILE *fin = freopen("biconex.in", "r", stdin);
FILE *fout = freopen("biconex.out", "w", stdout);

const int kMaxN = 1 + 100000;

/*-------- Input data --------*/
int N, M;
vector<int > graph[kMaxN];
/*-------- Algorithm data --------*/
int depth[kMaxN];
int dp[kMaxN];

stack<pair<int, int > > edge_stack;

vector<int > comp;
vector<vector<int > > comps;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void GetNewComp(const pair<int, int > first_edge) {
    pair<int, int > edge;
    do {
        edge = edge_stack.top(); edge_stack.pop();
        comp.push_back(edge.first); comp.push_back(edge.second);
    }while(edge != first_edge);

    std::sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    comps.push_back(comp); comp.clear();
}

void DFS(int node = 1, int father = 0) {
    dp[node] = depth[node];
    for(int son : graph[node]) {
        if(!depth[son]) {
            depth[son] = depth[node] + 1;
            edge_stack.push(std::make_pair(node, son));
            DFS(son, node);

            if(dp[son] > dp[node]) {}  //  Muchia e critica
            if(dp[son] >= dp[node]) {  //  Nodul e critic
                GetNewComp(std::make_pair(node, son));
            }
        }
    }

    bool ok_father = false;
    for(int son : graph[node]) {
        if(son == father && !ok_father) {
            ok_father = true;
        } else {
            dp[node] = std::min(dp[node], dp[son]);
        }
    }
}

void WriteOutput() {
    printf("%d\n", (int)comps.size());
    for(auto vec : comps) {
        for(auto node : vec) {
            printf("%d ", node);
        }
        printf("\n");
    }
}

int main() {
    ReadInput();
    depth[1] = 1; DFS();
    WriteOutput();
    return 0;
}
