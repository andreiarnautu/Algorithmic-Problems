/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("pamant.in", "r", stdin);
FILE *fout = freopen("pamant.out", "w", stdout);

const int MAX_N = 1 + 100000;

/*------------------------*/
int N, M;
vector< int > graph[MAX_N];
/*------------------------*/
vector< vector< int > > Comps;
vector< int > crtComp, criticalNodes;

int level[MAX_N], dp[MAX_N];
/*------------------------*/

void readInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void DFS(int node, int father, int crtLevel) {
    crtComp.push_back(node);
    dp[node] = level[node] = crtLevel;

    int Count = 0;
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(!level[*it]) {
            DFS(*it, node, crtLevel + 1);
            if(dp[*it] >= level[node]) {
                Count++;
            }
        }
    }

    if(Count) {
        if(father) {
            criticalNodes.push_back(node);
        } else if(Count > 1) {
            criticalNodes.push_back(node);
        }
    }

    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(*it != father) {
            dp[node] = min(dp[node], dp[*it]);
        }
    }
}

void writeOutput() {
    printf("%d\n", (int)Comps.size());
    for(int i = 0; i < (int)Comps.size(); i++) {
        printf("%d ", Comps[i][0]);
    }
    printf("\n");

    sort(criticalNodes.begin(), criticalNodes.end());
    printf("%d\n", (int)criticalNodes.size());
    for(vector< int >::iterator it = criticalNodes.begin(); it != criticalNodes.end(); it++) {
        printf("%d ", *it);
    }
}

int main() {
    readInput();
    for(int node = 1; node <= N; node++) {
        if(!level[node]) {
            DFS(node, 0, 1);
            Comps.push_back(crtComp); crtComp.clear();
        }
    }
    writeOutput();
}
