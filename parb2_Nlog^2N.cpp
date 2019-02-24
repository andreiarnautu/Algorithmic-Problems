/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("parb2.in", "r", stdin);
FILE *fout = freopen("parb2.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MAX_Q = 1 + 100000;
const int MAX_LOG = 1 + 17;

/*-------- Input data --------*/
int N, Q;
vector< pair< int,char > > graph[MAX_N];
vector< pair< int,int > > queries;
/*-------- DFS stuff --------*/
int depth[MAX_N];
int ancestor[MAX_LOG][MAX_N];
/*-------- Suffix Array data --------*/
int where[MAX_N], vec[MAX_N];
int Index[MAX_LOG][MAX_N];
pair< pair< int,int >,int > L[MAX_N];
/*-------- --------*/

void readInput() {
    scanf("%d%d", &N, &Q);
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d %d ", &u, &v);
        char c; scanf("%c", &c);
        graph[u].push_back(make_pair(v, c));
        graph[v].push_back(make_pair(u, c));
    }

    for(int i = 1; i <= Q; i++) {
        int u, v; scanf("%d%d", &u, &v);
        queries.push_back(make_pair(u, v));
    }
}

void DFS(int node = 1, int father = 0) {
    depth[node] = depth[father] + 1;
    for(pair< int,char > p : graph[node]) {
        if(p.first != father) {
            ancestor[0][p.first] = node;
            Index[0][p.first] = p.second;
            DFS(p.first, node);
        }
    }
}

void getAncestors() {
    for(int i = 1; i < MAX_LOG; i++) {
        for(int j = 1; j <= N; j++) {
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
        }
    }
}

void getSuffixArrays() {
    for(int i = 1; i < MAX_LOG; i++) {
        for(int j = 1; j <= N; j++) {
            L[j].first.first = Index[i - 1][j];
            L[j].first.second = Index[i - 1][ancestor[i - 1][j]];
            L[j].second = j;
        }
        sort(L + 1, L + N + 1);
        for(int j = 1; j <= N; j++) {
            Index[i][L[j].second] = Index[i][L[j - 1].second] + (L[j].first != L[j - 1].first);
        }
    }

    for(int i = 1; i <= N; i++) {
        where[L[i].second] = i;
        vec[i] = L[i].second;
    }
}

int getLCP(int u, int v) {
    int Answer = 0;
    int maxValue = min(depth[u], depth[v]) - 1;

    if(u == v) {
        return maxValue;
    }

    for(int i = MAX_LOG - 1; i >= 0; i--) {
        if(Index[i][u] == Index[i][v]) {
            Answer += (1 << i);
            u = ancestor[i][u];
            v = ancestor[i][v];
        }
    }

    Answer = min(Answer, maxValue);
    return Answer;
}

int upperBound(const int pos, const int wantedLength) {
    int left = pos, right = N, Answer = left;

    while(left <= right) {
        int mid = (left + right) >> 1;
        int crtLCP = getLCP(vec[pos], vec[mid]);

        if(crtLCP >= wantedLength) {
            Answer = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return Answer;
}

int lowerBound(const int pos, const int wantedLength) {
    int left = 1, right = pos, Answer = right;

    while(left <= right) {
        int mid = (left + right) >> 1;
        int crtLCP = getLCP(vec[pos], vec[mid]);

        if(crtLCP >= wantedLength) {
            Answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return Answer;
}

void answerQueries() {
    for(pair< int,int > Query : queries) {
        if(depth[Query.second] < depth[Query.first]) {
            swap(Query.first, Query.second);
        }

        int wantedLength = depth[Query.second] - depth[Query.first];
        int Left = lowerBound(where[Query.second], wantedLength);
        int Right = upperBound(where[Query.second], wantedLength);
        printf("%d\n", Right - Left + 1);
    }
}

int main() {
    readInput();
    DFS();
    getAncestors();
    getSuffixArrays();
    answerQueries();
    return 0;
}
