/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <utility>
#include <cstdlib>

//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1 + 100000;
const int kMaxEuler = 2 * kMaxN;
const int kMaxInf = 0x3fffffff;

/*-------- Input data --------*/
int N, M;
std::vector<std::vector<int > > graph;
/*-------- Centroid Decomposition --------*/
std::vector<std::vector<int > > centroidTree;
int centroidAncestor[kMaxN];

int subtreeSize[kMaxN];
bool good[kMaxN];
/*-------- Eulerian DFS --------*/
int index[kMaxEuler], depth[kMaxEuler], firstPosition[kMaxN], nodeRealDepth[kMaxN];
int eulerCursor;
/*-------- Arbint --------*/
std::pair<int, int > arbint[kMaxEuler * 4];  ///  first = depth; second = nodeIndex
/*-------- Final touch --------*/
int nodeAnswer[kMaxN];
/*-------- --------*/

void ReadInput() {
	scanf("%d%d", &N, &M); graph.resize(N + 1);
	for(int i = 1; i < N; i++) {
		int x, y; scanf("%d%d", &x, &y);
        graph[x].push_back(y); graph[y].push_back(x);
	}
}

inline void DFS(int node, int father = 0) {
    subtreeSize[node] = 1;
    for(auto adjNode : graph[node]) {
		if(good[adjNode] && adjNode != father) {
			DFS(adjNode, node);
			subtreeSize[node] += subtreeSize[adjNode];
		}
    }
}

int GetCentroid(std::vector<int > &nodes) {
    for(auto node : nodes) {
		bool ok = true;

		for(auto adjNode : graph[node]) {
			if(good[adjNode] && subtreeSize[adjNode] < subtreeSize[node]) {
				if(subtreeSize[adjNode] > (int)nodes.size() / 2) {
					ok = false; break;
				}
			}
		}

		if(ok && ((int)nodes.size() - subtreeSize[node]) <= (int)nodes.size() / 2) {
			return node;
		}
    }
}

inline void GetSet(int node, int father, std::vector<int > &currentSet) {
    currentSet.push_back(node);
    for(auto adjNode : graph[node]) {
		if(good[adjNode] && adjNode != father) {
			GetSet(adjNode, node, currentSet);
		}
    }
}

std::vector<std::pair<int, std::vector<int > > > Decompose(int centroidFather, std::vector<int > &nodes) {
    for(auto node : nodes) {
		good[node] = true;
    }
    DFS(*nodes.begin());

    int centroid = GetCentroid(nodes);

    if(centroidFather != 0) {
		centroidTree[centroidFather].push_back(centroid);
		centroidAncestor[centroid] = centroidFather;
    }

	std::vector<std::pair<int, std::vector<int > > > answer;
    for(auto adjNode : graph[centroid]) {
		if(good[adjNode]) {
			std::vector<int > currentSet;
			GetSet(adjNode, centroid, currentSet);
			answer.push_back(std::make_pair(centroid, currentSet));
		}
    }

    for(auto node : nodes) {
		good[node] = false;
    }
    return answer;
}

void GetCentroidTree() {
	centroidTree.resize(N + 1);

	std::vector<int > nodes;
	for(int i = 1; i <= N; i++) {
		nodes.push_back(i);
	}

	std::queue<std::pair<int, std::vector<int > > > queue; queue.push(std::make_pair(0, nodes));

	while(!queue.empty()) {
		int father = queue.front().first;
		nodes = queue.front().second;
		queue.pop();

        auto sets = Decompose(father, nodes);

        for(auto set : sets) {
            queue.push(set);
        }
	}
}

void AddNode(int node, int nodeDepth) {
    eulerCursor ++;
    index[eulerCursor] = node; depth[eulerCursor] = nodeDepth;
}

inline void EulerianDFS(int node = 1, int father = -1, int depth = 1) {
	AddNode(node, depth); firstPosition[node] = eulerCursor; nodeRealDepth[node] = depth;
	for(auto adjNode : graph[node]) {
		if(adjNode != father) {
			EulerianDFS(adjNode, node, depth + 1);
			AddNode(node, depth);
		}
	}
}

inline void BuildArbint(int node, int left, int right) {
	if(left == right) {
		arbint[node] = std::make_pair(depth[left], index[left]);
	} else {
		int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
		BuildArbint(leftSon, left, mid); BuildArbint(rightSon, mid + 1, right);
		arbint[node] = std::min(arbint[leftSon], arbint[rightSon]);
	}
}

inline void ArbintQuery(int node, int left, int right, int first, int last, int &queryAnswer) {
    if(first <= left && right <= last) {
		queryAnswer = std::min(queryAnswer, arbint[node].first);
    } else {
		int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
		if(first <= mid) {
			ArbintQuery(leftSon, left, mid, first, last, queryAnswer);
		}
		if(mid < last) {
			ArbintQuery(rightSon, mid + 1, right, first, last, queryAnswer);
		}
    }
}

int NodeDistance(int u, int v) {
	int lcaDepth = kMaxInf;
    ArbintQuery(1, 1, eulerCursor, std::min(firstPosition[u], firstPosition[v]), std::max(firstPosition[u], firstPosition[v]), lcaDepth);
    return nodeRealDepth[u] + nodeRealDepth[v] - 2 * lcaDepth;
}

void CentroidUpdate(int node, int updatedNode) {
    nodeAnswer[node] = std::min(nodeAnswer[node], NodeDistance(node, updatedNode));
    if(centroidAncestor[node] != 0) {
		CentroidUpdate(centroidAncestor[node], updatedNode);
    }
}

int CentroidQuery(int node) {
    int currentNode = node;
    int minDistance = kMaxInf;

    while(currentNode != 0) {
		minDistance = std::min(minDistance, nodeAnswer[currentNode] + NodeDistance(currentNode, node));
		currentNode = centroidAncestor[currentNode];
    }

    return minDistance;
}

void SolveQueries() {
    for(int i = 1; i <= N; i++) {
        nodeAnswer[i] = kMaxInf;
    }
	CentroidUpdate(1, 1);  ///  We know that node "1" is the first one painted in red

	for(; M > 0; M--) {
		int type, node; scanf("%d%d", &type, &node);
		if(type == 1) {
			CentroidUpdate(node, node);
		} else {
            printf("%d\n", CentroidQuery(node));
		}
	}
}

int main() {
	ReadInput();
    GetCentroidTree();
    EulerianDFS();
    BuildArbint(1, 1, eulerCursor);
    SolveQueries();
	return 0;
}
