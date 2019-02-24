/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("echival1.in", "r", stdin); FILE *fout = freopen("echival1.out", "w", stdout);

/*-------- Data --------*/
int N;
std::vector<int > v[2];
std::vector<std::vector<int > > graph;

std::vector<int > seen, freq[2];

int cycleLength;
/*-------- --------*/

void DFS(int node) {
    seen[node] = true; cycleLength ++;

    for(auto& son : graph[node]) {
        if(!seen[son]) {
            DFS(son);
        }
    }
}

void ReadBipermutation() {
    for(int i = 1; i <= N; i++) {
        graph[i].clear();
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &v[i][j]);
            if(i == 1) {
                graph[v[0][j]].emplace_back(v[1][j]);
                graph[v[1][j]].emplace_back(v[0][j]);
            }
        }
    }
}

void ComputePattern() {
    ReadBipermutation();

    for(int i = 1; i <= N; i++) {
        if(!seen[i]) {
            cycleLength = 0;

            DFS(i);

            freq[0][cycleLength] ++;
        }
    }
}

int main() {
    scanf("%d", &N);
    v[0].resize(N); v[1].resize(N); freq[0].resize(N + 1); freq[1].resize(N + 1); seen.resize(N + 1); graph.resize(N + 1);

    ComputePattern();

    const int testCount = 10;
    for(int i = 0; i < testCount; i++) {
        ReadBipermutation();

        seen = std::vector<int >(N + 1, 0);
        freq[1] = std::vector<int >(N + 1, 0);

        for(int j = 1; j <= N; j++) {
            if(!seen[j]) {
                cycleLength = 0;

                DFS(j);

                freq[1][cycleLength] ++;
            }
        }

        int ok = true;
        for(int j = 1; j <= N; j++) {
            if(freq[0][j] != freq[1][j]) {
                ok = false; break;
            }
        }

        printf("%d\n", ok);
    }
	return 0;
}
