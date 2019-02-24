/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
FILE *fin = freopen("parb2.in", "r", stdin);
FILE *fout = freopen("parb2.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MAX_LOG = 1 + 17;
int Zero = 0;

/*-------- Input data --------*/
struct Edge {
    int v, c;
    Edge(const int &v, const int &c) {
        this->v = v; this->c = c;
    }
};

int N, Q;
vector< Edge > graph[MAX_N];
/*-------- Graph stuff --------*/
int depth[MAX_N];
int ancestor[MAX_LOG][MAX_N];
char before[MAX_N];

/*-------- Suffix Arrays --------*/
int Index[MAX_LOG][MAX_N];
int Count[MAX_N], id1[MAX_N], id2[MAX_N];
int where[MAX_N];
/*-------- --------*/

void readInput() {
    scanf("%d%d", &N, &Q);
    for(int i = 1; i < N; i++) {
        int x, y; char c;
        scanf("%d %d %c", &x, &y, &c);
        graph[x].push_back(Edge(y, c));
        graph[y].push_back(Edge(x, c));
    }
}

void DFS(int node = 1, int father = 0, char above = '$') {
    before[node] = above;
  //  fout << Sir[node] << '\n';
    for(Edge edge : graph[node]) {
        if(edge.v != father) {
            ancestor[0][edge.v] = node;
            depth[edge.v] = depth[node] + 1;
            DFS(edge.v, node, edge.c);
        }
    }
}

void computeAncestors() {
    for(int i = 1; i < MAX_LOG; i++) {
        for(int j = 1; j <= N; j++) {
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
         //   printf("%d ", ancestor[i][j]);
        }
      //  printf("\n");
    }
}

void getSuffixArrays() {
    for(int i = 1; i <= N; i++) {
        Count[(int)before[i]] ++;
    }
    for(int i = 0, j = 0; i < 256; i++) {
        if(Count[i]) {
            Count[i] = j ++;
        }
    }
    for(int i = 1; i <= N; i++) {
        Index[0][i] = Count[(int)before[i]];
    }

    for(int i = 0; i < 256; i++) {
        Count[i] = 0;
    }

    for(int j = 1, Level = 0; j < MAX_LOG; j++, Level++) {
        /* construim id1 */
        for(int i = 0; i < N; i++) {
            Count[i] = 0;
        }
        for(int i = 1; i <= N; i++) {
            Count[Index[j - 1][ancestor[Level][i]]] ++;
        }
        for(int i = 1; i < N; i++) {
            Count[i] += Count[i - 1];
        }
        for(int i = N; i > 0; i--) {
            id1[--Count[Index[j - 1][ancestor[Level][i]]]] = i;
        }
        /* construim id2 */
        for(int i = 0; i < N; i++) {
            Count[i] = 0;
        }
        for(int i = 1; i <= N; i++) {
            Count[Index[j - 1][i]] ++;
        }
        for(int i = 1; i < N; i++) {
            Count[i] += Count[i - 1];
        }
        for(int i = N - 1; i >= 0; i--) {
            id2[--Count[Index[j - 1][id1[i]]]] = id1[i];
        }

        Index[j][id2[0]] = 0;
        for(int i = 1; i < N; i++) {
            if(Index[j - 1][id2[i]] == Index[j - 1][id2[i - 1]] &&
                            Index[j - 1][ancestor[Level][id2[i]]] == Index[j - 1][ancestor[Level][id2[i - 1]]]) {
                Index[j][id2[i]] = Index[j][id2[i - 1]];
            } else {
                Index[j][id2[i]] = Index[j][id2[i - 1]] + 1;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        printf("%d ", Index[MAX_LOG - 1][id2[i]]);
    }
    printf("\n");

    for(int i = 1; i <= N; i++) {
        //id1[Index[MAX_LOG - 1][i]] = i;
        printf("%d ", Index[MAX_LOG - 1][i]);
        where[i] = Index[MAX_LOG - 1][i];
        Count[Index[MAX_LOG - 1][i]] ++;
    }

    printf("\n");
}

int getLCP(int a, int b) {
    int Answer = 0;
    int A = a, B = b;
    a = where[a];
    b = where[b];
    for(int j = MAX_LOG - 1, Level = (MAX_LOG - 1); j >= 0; j--, Level--) {
        if(Index[j][a] == Index[j][b]) {
            Answer += (1 << Level);
            a = ancestor[Level][a];
            b = ancestor[Level][b];
        }
    }

        printf("%d\n", Answer);
    Answer = min(Answer, min(depth[A], depth[B]));
    return Answer;
}

void answerQueries() {

    printf("%d\n", getLCP(9, 2));

    for(int i = 1; i <= Q; i++) {
        int x, y; scanf("%d%d", &x, &y);
        int minWanted = depth[y] - depth[x];


    }
}

int main() {
    readInput();
    depth[1] = 1;
    DFS();
    computeAncestors();
    getSuffixArrays();
    answerQueries();
    return 0;
}
