/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("curent.in", "r", stdin);
FILE *fout = freopen("curent.out", "w", stdout);

const int MAX_N = 100100;

struct Event {
    bool isQuery;
    bool repair;
    int time, node, queryIndex;

    Event() {}

    Event(const bool isQuery, const int time, const int queryIndex) { /* queries */
        this->isQuery = isQuery; this->time = time; this->queryIndex = queryIndex;
    }

    Event(const bool isQuery, const bool repair, const int time, const int node) { /* updates */
        this->isQuery = isQuery; this->repair = repair; this->time = time; this->node = node;
    }

    bool operator <(const Event &other) const {
        return this->time < other.time;
    }
};

/*-----------------------------*/
int N, M, T, crtEvent;
vector< Event > events;
vector< int > graph[MAX_N];
/*-----------------------------*/ /** DFS */
int crtIndex;
pair< int,int > secv[MAX_N];
/*-----------------------------*/ /** Segment Tree */
int destroyCount[4 * MAX_N];
int sTree[4 * MAX_N];
/*-----------------------------*/
int queryAnswer[MAX_N];

void readInput() {
    scanf("%d", &N);
    for(int i = 2; i <= N; i++) {
        int father; scanf("%d", &father);
        graph[father].push_back(i);
    }
    scanf("%d", &M);
    for(int i = 1; i <= M; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        events.push_back(Event(false, (bool)c, a, b));
    }
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) {
        int time; scanf("%d", &time);
        events.push_back(Event(true, time, i));
    }

    sort(events.begin(), events.end());
}

void DFS(int node = 1) {
    int pos = (++crtIndex);
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        DFS(*it);
    }
    secv[node] = make_pair(pos, crtIndex);

}

void buildTree(int node, int left, int right) {
    int mid = (left + right) >> 1;
    int leftSon = node << 1;
    int rightSon = leftSon + 1;

    destroyCount[node] = 0;

    if(left == right) {
        sTree[node] = 1;
    } else {
        buildTree(leftSon, left, mid);
        buildTree(rightSon, mid + 1, right);

        sTree[node] = sTree[leftSon] + sTree[rightSon];
    }
}

void Update(int node, int left, int right, int first, int last, bool repair) {
    int mid = (left + right) >> 1;
    int leftSon = node << 1;
    int rightSon = leftSon + 1;

    if(first <= left && right <= last) {
        if(repair) {
            destroyCount[node]--;
        } else {
            destroyCount[node]++;
        }
    } else {
        if(first <= mid) {
            Update(leftSon, left, mid, first, last, repair);
        }
        if(mid < last) {
            Update(rightSon, mid + 1, right, first, last, repair);
        }
    }

    if(left == right) {
        if(!destroyCount[node]) {
            sTree[node] = 1;
        } else {
            sTree[node] = 0;
        }
    } else {
        if(!destroyCount[node]) {
            sTree[node] = sTree[leftSon] + sTree[rightSon];
        } else {
            sTree[node] = 0;
        }
    }
}

void solveEvents() {
    buildTree(1, 1, N);

    for(vector< Event >::iterator it = events.begin(); it != events.end(); it++) {
        Event event = *it;

        if(event.isQuery) {
            queryAnswer[event.queryIndex] = sTree[1];
        } else {
            Update(1, 1, N, secv[event.node].first, secv[event.node].second, event.repair);
        }
    }
}

void writeOutput() {
    for(int i = 1; i <= T; i++) {
        printf("%d\n", queryAnswer[i]);
    }
}

int main() {
    readInput();
    DFS();
    solveEvents();
    writeOutput();
    return 0;
}
