/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define lsb(i) (i & (-i))

using namespace std;
FILE *fin = freopen("arbfind.in", "r", stdin);
FILE *fout = freopen("arbfind.out", "w", stdout);

const int MAX_N = 1 + 64000;
const int MAX_LEN = 2 * MAX_N;
const int MAX_LOG = 1 + 17;
int Zero = 0;

/*-------- Input data --------*/
int N, M;
vector< int > graph[2][MAX_N];
/*-------- Linearization --------*/
char S[MAX_LEN];
int where[MAX_N];
int Size, start;
/*-------- Suffix Arrays --------*/
int Index[MAX_LOG][MAX_LEN];
int Count[MAX_LEN], id1[MAX_LEN], id2[MAX_LEN], trueID[MAX_LEN];
/*-------- AIB --------*/
int aib[MAX_LEN + 1];
/*-------- --------*/

void readInput() {
    /* citim arborele model */
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        int k; scanf("%d", &k);
        for(int j = 1; j <= k; j++) {
            int son; scanf("%d", &son);
            graph[0][i].push_back(son);
        }
    }
    /* citim arborele de evaluat */
    scanf("%d", &M);
    for(int i = 1; i <= M; i++) {
        int k; scanf("%d", &k);
        for(int j = 1; j <= k; j++) {
            int son; scanf("%d", &son);
            graph[1][i].push_back(son);
        }
    }
}

void DFS(int level, int node = 1, int father = 0) {
    if(level == 1) {
        where[node] = Size;
    }
    for(int son : graph[level][node]) {
        if(son != father) {
            S[Size ++] = 'D';
            DFS(level, son, node);
        }
    }
    if(father != 0) {
        S[Size ++] = 'U';
    }
}

void transformIntoString() {
    DFS(0);
    start = Size; /* indexul de unde incepe cel de-al doilea arbore */
    DFS(1);
    S[Size ++] = '$';
    S[Size] = 0;
}

int& index(int i, int j) {
    if(j < MAX_LEN) {
        return Index[i][j];
    } else {
        return Zero;
    }
}

void buildSuffixArrays() {
    for(int i = 0; i < Size; i++) {
        Count[(int)S[i]] ++;
    }
    for(int i = 0, j = 0; i < 256; i++) {
        if(Count[i]) {
            Count[i] = j ++;
        }
    }
    for(int i = 0; i < Size; i++) {
        index(0, i) = Count[(int)S[i]];
    }

    for(int j = 1, L = 1; j < MAX_LOG; j++, L <<= 1) {
        /* construim id1 */
        for(int i = 0; i < Size; i++) {
            Count[i] = 0;
        }
        for(int i = 0; i < Size; i++) {
            Count[index(j - 1, i + L)] ++;
        }
        for(int i = 1; i < Size; i++) {
            Count[i] += Count[i - 1];
        }
        for(int i = Size - 1; i >= 0; i--) {
            id1[--Count[index(j - 1, i + L)]] = i;
        }

        /* construim id2 */
        for(int i = 0; i < Size; i++) {
            Count[i] = 0;
        }
        for(int i = 0; i < Size; i++) {
            Count[index(j - 1, i)] ++;
        }
        for(int i = 1; i < Size; i++) {
            Count[i] += Count[i - 1];
        }
        for(int i = Size - 1; i >= 0; i--) {
            id2[--Count[index(j - 1, id1[i])]] = id1[i];
        }

        index(j, id2[0]) = 0;
        for(int i = 1; i < Size; i++) {
            if(index(j - 1, id2[i]) == index(j - 1, id2[i - 1]) &&
                        index(j - 1, id2[i] + L) == index(j - 1, id2[i - 1] + L)) {
                index(j, id2[i]) = index(j, id2[i - 1]);
            } else {
                index(j, id2[i]) = index(j, id2[i - 1]) + 1;
            }
        }
    }

    for(int i = 0; i < Size; i++) {
        id1[index(MAX_LOG - 1, i)] = i;
        trueID[i] = index(MAX_LOG - 1, i);
    }
}

int getLCP(int a, int b) {
    int Answer = 0;
    for(int j = MAX_LOG - 1, L = (1 << (MAX_LOG - 1)); j >= 0; j--, L >>= 1) {
        if(index(j, a) == index(j, b)) {
            Answer += L;
            a += L;
            b += L;
        }
    }

    Answer = min(Answer, start);
    return Answer;
}

void Update(int pos) {
    pos ++; /* nu vrem sa existe pos = 0 */
    for(int i = pos; i <= Size; i += lsb(i)) {
        aib[i] ++;
    }
}

int Query(int pos) {
    int Answer = 0;
    for(int i = pos; i > 0; i -= lsb(i)) {
        Answer += aib[i];
    }
    return Answer;
}

void buildAIB() {
    for(int i = 0; i < Size; i++) {
        if(S[i] == 'D') {
            Update(i);
        }
    }
}

void writeOutput() {
  //  printf("%s\n", S);
    for(int i = 1; i <= M; i++) {
        int lcp = getLCP(id1[trueID[0]], id1[trueID[where[i]]]);
       // printf("%d\n", lcp);
        printf("%d\n", Query(lcp) + 1);
    }
}

int main() {
    readInput();
    transformIntoString();
    buildSuffixArrays();
    buildAIB();
    writeOutput();
    return 0;
}
