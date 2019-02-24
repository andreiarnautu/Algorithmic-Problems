/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("itree.in", "r", stdin); FILE *fout = freopen("itree.out", "w", stdout);

std::vector<int > degree;
std::vector<std::vector<int > > graph;

void RunTest() {
    int N; scanf("%d", &N);
    graph = std::vector<std::vector<int > >(N + 1);
    degree = std::vector<int > (N + 1, 0);

    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
        degree[u] ++; degree[v] ++;
    }

    for(int i = 1; i <= N; i++) {
        if(degree[i] == 1 && graph[i].size() == 1) {
            degree[graph[i][0]] --; degree[i] = 0;
        }
    }

    int maxDegree = 0, oneDegree = 0;
    for(int i = 1; i <= N; i++) {
        maxDegree = std::max(maxDegree, degree[i]);
        if(degree[i] == 1) {
            oneDegree ++;
        }
    }

    if(maxDegree > 2 || (maxDegree == 2 && oneDegree != 2)) {
        printf("NO\n");
    } else {
        printf("YES\n");
    }
}

int main() {
    int testCount; scanf("%d", &testCount);
    for(int i = 0; i < testCount; i++) {
        RunTest();
    }
	return 0;
}
