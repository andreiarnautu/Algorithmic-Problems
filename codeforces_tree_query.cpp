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

const int kMaxN = 1 + 100000;
const int kMaxQueries = 1 + 100000;
const int kMaxEuler = kMaxN * 2;
const int kMaxInf = 0x3fffffff;

/*-------- Structures --------*/
struct Queryy {
    int node, index;
    long long length;
    Queryy() {}
};
/*-------- Input data --------*/
int N, M;
std::vector<std::vector<std::pair<int, int > > > graph;
/*-------- Centroid Decomposition --------*/
int centroidAncestor[kMaxN];

int subtreeSize[kMaxN];
bool good[kMaxN];
/*-------- Eulerian DFS --------*/
std::pair<int, int > euler[kMaxEuler];
int firstPosition[kMaxN];
long long rootDistance[kMaxN];
int eulerCursor;

std::pair<int, int > arbint[4 * kMaxEuler];
/*-------- Centroid data --------*/
std::vector<std::vector<int > > nodeLists;
std::vector<std::vector<Queryy > > queryLists;
int querySolution[kMaxQueries];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M); graph.resize(N + 1);
    for(int i = 1; i < N; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        graph[u].push_back({v, w}); graph[v].push_back({u, w});
    }
}

inline void DFS(int node, int father = -1) {
    subtreeSize[node] = 1;
    for(auto adjNode : graph[node]) {
        if(good[adjNode.first] && adjNode.first != father) {
            DFS(adjNode.first, node);
            subtreeSize[node] += subtreeSize[adjNode.first];
        }
    }
}

int FindCentroid(std::vector<int > &nodes) {
    for(auto node : nodes) {
        bool ok = true;
        for(auto adjNode : graph[node]) {
            if(good[adjNode.first] && subtreeSize[adjNode.first] < subtreeSize[node]) {
                if(subtreeSize[adjNode.first] > (int)nodes.size() / 2) {
                    ok = false; break;
                }
            }
        }

        if(ok == true && ((int)nodes.size() - subtreeSize[node]) <= (int)nodes.size() / 2) {
            return node;
        }
    }
}

inline void GetSet(int node, int father, std::vector<int > &currentSet) {
    currentSet.push_back(node);
    for(auto adjNode : graph[node]) {
        if(good[adjNode.first] && adjNode.first != father) {
            GetSet(adjNode.first, node, currentSet);
        }
    }
}

std::vector<std::pair<int, std::vector<int > > > Decompose(int centroidFather, std::vector<int > &nodes) {
    for(auto node : nodes) {
        good[node] = true;
    }
    DFS(nodes.back());
    int centroid = FindCentroid(nodes);
    centroidAncestor[centroid] = centroidFather;

    std::vector<std::pair<int, std::vector<int > > > answer;
    for(auto adjNode : graph[centroid]) {
        if(good[adjNode.first]) {
            std::vector<int > currentSet;
            GetSet(adjNode.first, centroid, currentSet);
            answer.push_back({centroid, currentSet});
        }
    }
    for(auto node : nodes) {
        good[node] = false;
    }
    return answer;
}

void GetCentroidDecomposition() {
    std::vector<int > nodes;
    for(int i = 1; i <= N; i++) {
        nodes.push_back(i);
    }

    std::queue<std::pair<int, std::vector<int > > > queue; queue.push({0, nodes});
    while(!queue.empty()) {
        int centroidFather = queue.front().first;
        nodes = queue.front().second;
        queue.pop();

        auto sets = Decompose(centroidFather, nodes);
        for(auto set : sets) {
            queue.push(set);
        }
    }
}

void AddNode(int node, int depth) {
    euler[++ eulerCursor] = {depth, node};
}

inline void EulerianDFS(int node = 1, int father = 0, int depth = 1) {
    AddNode(node, depth);
    firstPosition[node] = eulerCursor;
    for(auto adjNode : graph[node]) {
        if(adjNode.first != father) {
            rootDistance[adjNode.first] = rootDistance[node] + 1LL * adjNode.second;
            EulerianDFS(adjNode.first, node, depth + 1);
            AddNode(node, depth);
        }
    }
}

inline void BuildArbint(int node = 1, int left = 1, int right = eulerCursor) {
    if(left == right) {
        arbint[node] = euler[left];
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        BuildArbint(leftSon, left, mid); BuildArbint(rightSon, mid + 1, right);
        arbint[node] = std::min(arbint[leftSon], arbint[rightSon]);
    }
}

inline void Query(int node, int left, int right, int first, int last, std::pair<int, int > &queryAnswer) {
    if(first <= left && right <= last) {
        queryAnswer = std::min(queryAnswer, arbint[node]);
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        if(first <= mid) {
            Query(leftSon, left, mid, first, last, queryAnswer);
        }
        if(mid < last) {
            Query(rightSon, mid + 1, right, first, last, queryAnswer);
        }
    }
}

long long NodeDistance(int u, int v) {
    std::pair<int, int > queryAnswer = {kMaxInf, kMaxInf};
    Query(1, 1, eulerCursor, std::min(firstPosition[u], firstPosition[v]), std::max(firstPosition[u], firstPosition[v]), queryAnswer);
    return rootDistance[u] + rootDistance[v] - 2 * rootDistance[queryAnswer.second];
}

inline void AddToLists(int currentNode, int initialNode) {
    nodeLists[currentNode].push_back(initialNode);
    if(centroidAncestor[currentNode] != 0) {
        AddToLists(centroidAncestor[currentNode], initialNode);
    }
}

inline void AddToQueries(int currentNode, Queryy query) {
    queryLists[currentNode].push_back(query);
    if(centroidAncestor[currentNode] != 0) {
        AddToQueries(centroidAncestor[currentNode], query);
    }
}

void BuildNodeLists() {
    nodeLists.resize(N + 1); queryLists.resize(N + 1);
    for(int i = 1; i <= N; i++) {
        AddToLists(i, i);
    }
    for(int i = 1; i <= M; i++) {
        Queryy query; scanf("%d%lld", &query.node, &query.length); query.index = i;
        AddToQueries(query.node, query);
    }
}

int CountLower(long long value, std::vector<long long > &vector) {
    int left = 0, right = (int)vector.size() - 1, answer = 0;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(vector[mid] <= value) {
            left = answer = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return answer;
}

void AddEverything(int centroidNode) {
    std::vector<long long > distances;
    for(auto node : nodeLists[centroidNode]) {
        distances.push_back(NodeDistance(centroidNode, node));
    }
    std::sort(distances.begin(), distances.end());
    for(auto query : queryLists[centroidNode]) {
        querySolution[query.index] += CountLower(query.length - NodeDistance(centroidNode, query.node), distances);
    }
}

void SubstractCommon(int centroidNode) {
    if(centroidAncestor[centroidNode] == 0) return;  ///  We don't have an ancestor, therefore we have nothing to substract

    std::vector<long long > distances;
    for(auto node : nodeLists[centroidNode]) {
        distances.push_back(NodeDistance(centroidAncestor[centroidNode], node));
    }
    std::sort(distances.begin(), distances.end());
    for(auto query : queryLists[centroidNode]) {
        querySolution[query.index] -= CountLower(query.length - NodeDistance(centroidAncestor[centroidNode], query.node), distances);
    }
}

void SolveNode(const int centroidNode) {
    AddEverything(centroidNode);
    SubstractCommon(centroidNode);
}

void ProcessQueries() {
    for(int i = 1; i <= N; i++) {
        SolveNode(i);
    }
    for(int i = 1; i <= M; i++) {
        printf("%d\n", querySolution[i]);
    }
}

int main() {
    ReadInput();
    GetCentroidDecomposition();
    EulerianDFS();
    BuildArbint();
    BuildNodeLists();
    ProcessQueries();
    return 0;
}
