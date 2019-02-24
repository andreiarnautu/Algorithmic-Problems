/**
  *  Worg
  */
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>

#define pb          push_back

using namespace std;
FILE *fin = freopen("johnie.in", "r", stdin);
FILE *fout = freopen("johnie.out", "w", stdout);

const int MAX_N = 1 + 50000,
          MAX_M = 1 + 200000;

struct edge {

    int index, vertex;
    edge(const int &index, const int &vertex) {

        this->index = index; this->vertex = vertex;
    }
};

queue < int > coada;
stack < int > stiva;
vector < int > comp, nodes, cycle, aux, sol[MAX_M];
vector < edge > G[MAX_N];

bool checked[MAX_M], parcurs[MAX_N];

int degree[MAX_N], badNode[MAX_N];
int n, m, nextIndex, solIndex;

void addEdge(const int &u, const int &v) {

    G[u].pb(edge(nextIndex, v));
    G[v].pb(edge(nextIndex, u));
    degree[u]++; degree[v]++;
    nextIndex++;
}

int deleteNext(int node) {

    while(!G[node].empty() && checked[G[node].back().index])
        G[node].pop_back();

    int nxt = G[node].back().vertex;
    checked[G[node].back().index] = true;
    G[node].pop_back();

    degree[node]--, degree[nxt]--;
    return nxt;
}

void readData() {

    scanf("%d %d ", &n, &m);
    for(int i = 1; i <= m; ++i) {

        int x, y; scanf("%d %d ", &x, &y);
        addEdge(x, y);
    }
}

void getExtraEdges() {

    int count = 0, conexe = 0;
    for(int i = 1; i <= n; ++i)
        if(!parcurs[i]) {

            ++conexe;
            parcurs[i] = true;
            comp.pb(i); coada.push(i);
            while(!coada.empty()) {

                int node = coada.front(); coada.pop();
                for(vector < edge >::iterator it = G[node].begin(); it != G[node].end(); ++it)
                    if(!parcurs[it->vertex]) {

                        comp.pb(it->vertex);
                        parcurs[it->vertex] = true;
                        coada.push(it->vertex);
                    }
            }
            for(vector < int >::iterator it = comp.begin(); it != comp.end(); ++it)
                if(degree[*it] % 2 == 1)
                    nodes.pb(*it);
            for(int j = 0; j < (int)nodes.size(); j += 2) {

                count++;
                badNode[nodes[j]] = nodes[j + 1];
                badNode[nodes[j + 1]] = nodes[j];
                addEdge(nodes[j], nodes[j + 1]);
            }
            comp.clear(); nodes.clear();

        }
}

void solveTask() {

    for(int i = 1; i <= n; ++i)
        if(degree[i]) {

            stiva.push(i);
            while(!stiva.empty()) {

                int node = stiva.top();
                if(degree[node])
                    stiva.push(deleteNext(node));
                else {

                    aux.pb(node);
                    stiva.pop();
                }
            }

            bool ok = true;

            for(int j = 0; j < (int)aux.size() - 1; ++j)
                if(badNode[aux[j]] == aux[j + 1]) {

                    ok = false;
                    badNode[aux[j]] = badNode[aux[j + 1]] = 0;
                    for(int l = j + 1; l < (int)aux.size() - 1; ++l)
                        cycle.pb(aux[l]);
                    for(int l = 0; l <= j; ++l)
                        cycle.pb(aux[l]);
                    break;
                }
            if(ok)
                for(int j = 0; j < (int)aux.size(); ++j)
                    cycle.pb(aux[j]);


            for(int j = 0; j < (int)cycle.size(); j++) {

                sol[solIndex].pb(cycle[j]);
                if(j < (int)cycle.size() - 1 && badNode[cycle[j]] == cycle[j + 1]) {

                    ++solIndex;
                    badNode[cycle[j]] = 0;
                    badNode[cycle[j + 1]] = 0;
                }
            }
            ++solIndex;
            cycle.clear();
            aux.clear();
        }

    printf("%d\n", solIndex);
    for(int i = 0; i < solIndex; ++i) {

        printf("%d ", sol[i].size());
        for(vector < int >::iterator it = sol[i].begin(); it != sol[i].end(); ++it)
            printf("%d ", *it);
        printf("\n");
    }
}

int main() {

    readData();
    getExtraEdges();
    solveTask();
    return 0;
}
