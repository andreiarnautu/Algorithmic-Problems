/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("biconex.in", "r", stdin);
FILE *fout = freopen("biconex.out", "w", stdout);

const int MAX_N = 1 + 100000;

/*--------------------------*/ /** General stuff */
int M, N;
vector< int > graph[MAX_N];
/*--------------------------*/ /** Biconnected components */
int level[MAX_N], dp[MAX_N];
stack< pair< int,int > > Stack;

vector< vector< int > > comps;
vector< int > aux;
/*--------------------------*/


void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void addComponent(pair< int,int > p) {
    pair< int,int > now;
    printf("Muchii: ");
    do {
        now = Stack.top(); Stack.pop();
        aux.push_back(now.first); aux.push_back(now.second);
        printf("%d %d; ", now.first, now.second);
    }while(now != p);
    printf("\n");

    sort(aux.begin(), aux.end());
    aux.erase(unique(aux.begin(), aux.end()), aux.end());
    comps.push_back(aux); aux.clear();
}

void biconnectedDFS(int node = 1, int father = 0) {
    dp[node] = level[node];
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(!level[*it]) {
            level[*it] = level[node] + 1;
            Stack.push(make_pair(node, *it)); /* we add the edge to the stack */
            biconnectedDFS(*it, node);
            if(dp[*it] > level[node]) {} /* the edge is critical */
            if(dp[*it] >= level[node]) { /* the node is critical */
                addComponent(make_pair(node, *it));
            }
        }
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
    printf("%d\n", (int)comps.size());
    for(int i = 0; i < (int)comps.size(); i++) {
        for(vector< int >::iterator it = comps[i].begin(); it != comps[i].end(); it++) {
            printf("%d ", *it);
        }
        printf("\n");
    }
}

int main() {
    readData();
    level[1] = 1; biconnectedDFS();
    writeData();
    return 0;
}
