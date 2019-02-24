/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1 + 500000;
const int kMaxQ = 1 + 500000;
const int kMaxLog = 19;

/*-------- Input data --------*/
int N, M;
std::vector<std::vector<int > > graph;
std::vector<std::vector<int > > powers;
/*-------- Centroid Decomposition --------*/
int subtreeSize[kMaxN];
bool solved[kMaxN];
/*-------- Damage data --------*/
std::vector<int > howMany;  ///  How many nodes with destruction level i
long long totalFlareons;
long long totalDamage;

long long solution[kMaxN];
/*-------- --------*/

void ReadData() {
    scanf("%d%d", &N, &M);
    graph.resize(N + 1); powers.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        int x; scanf("%d", &x);
        graph[x].push_back(i); graph[i].push_back(x);
    }
    for(int i = 1; i <= M; i++) {
        int node, power; scanf("%d%d", &node, &power);
        powers[node].push_back(power);
    }
}

void DFS(int node, int father = -1) {
    subtreeSize[node] = 1;
    for(auto adjNode : graph[node]) {
        if(!solved[adjNode] && adjNode != father) {
            DFS(adjNode, node);
            subtreeSize[node] += subtreeSize[adjNode];
        }
    }
}

int FindCentroid(int node, int father, int size) {
    for(auto adjNode : graph[node]) {
        if(!solved[adjNode] && adjNode != father && subtreeSize[adjNode] > size / 2) {
            return FindCentroid(adjNode, node, size);
        }
    }
    return node;
}

void AddSubtreePowers(int node, int father, int distance) {
    for(auto power : powers[node]) {
        if(power > distance) {  ///  Otherwise the power becomes negative
            if(power - distance < (int)howMany.size()) {
                howMany[power - distance] ++;
            }
            totalFlareons ++; totalDamage += (power - distance);
        }
    }
    for(auto adjNode : graph[node]) {
        if(!solved[adjNode] && adjNode != father) {
            AddSubtreePowers(adjNode, node, distance + 1);
        }
    }
}

void RemoveSubtreePowers(int node, int father, int distance) {
    for(auto power : powers[node]) {
        if(power > distance) {
            if(power - distance < (int)howMany.size()) {
                howMany[power - distance] --;
            }
            totalFlareons --; totalDamage -= (power - distance);
        }
    }
    for(auto adjNode : graph[node]) {
        if(!solved[adjNode] && adjNode != father) {
            RemoveSubtreePowers(adjNode, node, distance + 1);
        }
    }
}

void UpdateSubtreeSolutions(int node, int father, int distance) {
    totalDamage -= 1LL * distance * howMany[distance]; totalFlareons -= howMany[distance];

    solution[node] += totalDamage - 1LL * totalFlareons * distance;

    for(auto adjNode : graph[node]) {
        if(!solved[adjNode] && adjNode != father) {
            UpdateSubtreeSolutions(adjNode, node, distance + 1);
        }
    }

    totalDamage += 1LL * distance * howMany[distance]; totalFlareons += howMany[distance];
}

void Decompose(int root) {
    DFS(root);
    int centroid = FindCentroid(root, root, subtreeSize[root]);
    solved[centroid] = true;

    howMany = std::vector<int >(subtreeSize[root], 0); totalDamage = totalFlareons = 0;

    for(auto adjNode : graph[centroid]) {
        if(!solved[adjNode]) {
            AddSubtreePowers(adjNode, centroid, 1);
        }
    }

    for(auto power : powers[centroid]) {
        if(power < (int)howMany.size()) {
            howMany[power] ++;
        }
        totalFlareons ++; totalDamage += power;
    }

    solution[centroid] += totalDamage;

    for(auto adjNode : graph[centroid]) {
        if(!solved[adjNode]) {
            RemoveSubtreePowers(adjNode, centroid, 1);
            UpdateSubtreeSolutions(adjNode, centroid, 1);
            AddSubtreePowers(adjNode, centroid, 1);
        }
    }

    for(auto adjNode : graph[centroid]) {
        if(!solved[adjNode]) {
            Decompose(adjNode);
        }
    }
}

void WriteOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%lld\n", solution[i]);
    }
}

int main() {
    ReadData();
    Decompose(1);
    WriteOutput();
    return 0;
}
