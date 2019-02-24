/**
  *  Worg
  */
#include <bitset>
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("albinuta1.in", "r", stdin);
FILE *fout = freopen("albinuta1.out", "w", stdout);

const int MAX_N = 1 + 50;
const int MAX_Q = 1 + 50;
const int MAX_CMMMC = 200000;

/*---------------------*/
int N, Q;
pair< int,int > T[MAX_Q];
int graph[MAX_N][MAX_N];

int cmmmc;
/*---------------------*/ /** Cycle detection */
bitset< MAX_CMMMC > marked[MAX_N];
pair< int,int > Final;
int loopStop, X, Y;

int queryAns[MAX_Q];
/*---------------------*/

void readData() {
    scanf("%d%d", &N, &Q);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &graph[i][0]);
        for(int j = 1; j <= graph[i][0]; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    for(int i = 1; i <= Q; i++) {
        scanf("%d", &T[i].first);
        T[i].second = i;
    }
}

int getCmmdc(int a, int b) {
    int r;
    while(b) {
        r = a % b; a = b;b = r;
    }
    return a;
}

int getCmmmc(int a, int b) {
    return (a * b) / getCmmdc(a, b);
}

void getGlobalCmmmc() {
    if(N == 1) {
        cmmmc = graph[1][0];
    } else {
        cmmmc = getCmmmc(graph[1][0], graph[2][0]);
        for(int i = 3; i <= N; i++) {
            cmmmc = getCmmmc(cmmmc, graph[i][0]);
        }
    }
}

int getLoopStop() {
    int realTime = 1;
    int time = 1;
    int node = 1;

    while(!marked[node][time]) {
        marked[node][time] = true;
        node = graph[node][1 + (time - 1) % graph[node][0]];

        realTime++;
        time++;
        if(time > cmmmc) {
            time -= cmmmc;
        }
    }
    Final.first = node; Final.second = time;

    return (realTime - 1);
}

void findXY() {
    int realTime = 1;
    int time = 1;
    int node = 1;

    while(node != Final.first || time != Final.second) {
        node = graph[node][1 + (time - 1) % graph[node][0]];

        realTime++;
        time++;
        if(time > cmmmc) {
            time -= cmmmc;
        }
    }
    X = realTime - 1;
    Y = loopStop - X;
}

void answerQueries() {
    for(int i = 1; i <= Q; i++) {
        if(T[i].first > X + Y) {
            T[i].first = X + 1 + (T[i].first - X - 1) % Y;
        }
    }
    sort(T + 1, T + Q + 1);

    int node = 1, time = 1;
    int crtQuery = 1;

    for(int i = 1; i <= X + Y; i++) {
        while(crtQuery <= Q && T[crtQuery].first == i) {
            queryAns[T[crtQuery].second] = node;
            crtQuery++;
        }
        node = graph[node][1 + (time - 1) % graph[node][0]];
        time++;
        if(time > cmmmc) {
            time -= cmmmc;
        }
    }

    for(int i = 1; i <= Q; i++) {
        printf("%d\n", queryAns[i]);
    }
}

int main() {
    readData();
    getGlobalCmmmc();
    loopStop = getLoopStop();
    findXY();
    answerQueries();
}
