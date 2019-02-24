/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
FILE *fin = freopen("berarii.in", "r", stdin);
FILE *fout = freopen("berarii.out", "w", stdout);

const int kMaxN = 1e5 + 1;
const long long kMaxInf = 2e13;

/*-------- Data --------*/
int N, K;
int beer[kMaxN];
std::vector<std::vector<std::pair<int, int > > > graph;

long long worst[kMaxN], closestBrewery[kMaxN];
long long maxDistance;
int needed;
/*-------- --------*/

void ReadTestData() {
    scanf("%d%d", &N, &K);
    graph = std::vector<std::vector<std::pair<int, int > > >(N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &beer[i]);
    }
    for(int i = 1; i < N; i++) {
        int u, v, length; scanf("%d%d%d", &u, &v, &length);
        graph[u - 1].push_back({v - 1, length});
        graph[v - 1].push_back({u - 1, length});
    }
}

void DFS(int node = 0, int father = -1, long long edgeLength = 0) {
    for(auto edge : graph[node]) {
        if(edge.first != father) {
            DFS(edge.first, node, edge.second);
            closestBrewery[node] = std::min(closestBrewery[node], closestBrewery[edge.first] + edge.second);
            worst[node] = std::min(worst[node], worst[edge.first] - edge.second);
        }
    }
    if(worst[node] >= closestBrewery[node]) {  //  We use the closest brewery in the subtree
        worst[node] = kMaxInf;
    }
    if(worst[node] - edgeLength < 0 || (node == 0 && worst[node] < kMaxInf)) {  //  New brewery here
        needed ++;
        worst[node] = kMaxInf; closestBrewery[node] = 0;
    }
}

bool TryDistance(long long distance) {
    for(int i = 0; i < N; i++) {
        closestBrewery[i] = kMaxInf;
        worst[i] = distance / beer[i];
    }
    maxDistance = distance; needed = 0;
    DFS();

    return needed <= K;
}

long long TestAnswer() {
    long long left = 0, right = kMaxInf, answer = 0;
    while(left <= right) {
        long long mid = (left + right) >> 1;
        bool verdict = TryDistance(mid);

        if(verdict == true) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return answer;
}

int main() {
    int testCount;
    for(scanf("%d", &testCount); testCount > 0; testCount--) {
        ReadTestData();
        printf("%lld\n", TestAnswer());
    }
    return 0;
}
