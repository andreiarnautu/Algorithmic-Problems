/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;
FILE *fin = freopen("gravity.in", "r", stdin);
FILE *fout = freopen("gravity.out", "w", stdout);

const int MAX_N = 1760;
const int dx[] = { 0, 0, 1, -1};
const int dy[] = {-1, 1, 0,  0};

/*------------------------*/
int N, M;
char line[MAX_N];
bitset< MAX_N > mat[MAX_N];
/*------------------------*/
int index[MAX_N][MAX_N];
int crtIndex;
/*------------------------*/
vector< pair< int,int > > graph[MAX_N * MAX_N / 2];

int Time[MAX_N * MAX_N / 2], goingTo[MAX_N * MAX_N / 2], degree[MAX_N * MAX_N / 2];
/*------------------------*/

struct Duo {
    int timeSpan;
    int index;

    Duo(const int timeSpan, const int index) {
        this->timeSpan = timeSpan; this->index = index;
    }

    bool operator <(const Duo &other) const {
        if(this->timeSpan != other.timeSpan) {
            return this->timeSpan < other.timeSpan;
        } else {
            return this->index < other.index;
        }
    }
};

set< Duo > Set;
char Solution[MAX_N][MAX_N];
/*------------------------*/

void readInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%s", line + 1);
        for(int j = 1; j <= M; j++) {
            if(line[j] == '#') {
                mat[i][j] = 1;
            }
        }
    }
    for(int j = 1; j <= M; j++) {
        mat[N + 2][j] = 1;
    }
}

bool inTheMatrix(const int x, const int y) {
    return(1 <= x && x <= N + 2 && 1 <= y && y <= M);
}

void addCell(int x, int y) {
    index[x][y] = crtIndex;
    for(int i = 0; i < 4; i++) {
        int X = x + dx[i];
        int Y = y + dy[i];
        if(inTheMatrix(X, Y) && mat[X][Y] == 1 && !index[X][Y]) {
            addCell(X, Y);
        }
    }
}

void getObjects() {
    for(int i = 1; i <= N + 2; i++) {
        for(int j = 1; j <= M; j++) {
            if(mat[i][j] && !index[i][j]) {
                crtIndex ++;
                addCell(i, j);
            }
        }
    }
}

void buildVector() {
    for(int j = 1; j <= M; j++) {
        int crtObject = 0, where = N + 2;
        for(int i = N + 2; i > 0; i--) {
            if(index[i][j]) {
                if(crtObject != 0 && crtObject != index[i][j]) {
                    graph[crtObject].push_back(make_pair(index[i][j], where - i - 1));
                    degree[index[i][j]] ++;
                }
                crtObject = index[i][j];
                where = i;
            }
        }
    }
}

void addSpecials(int node) {
        for(vector< pair< int,int > >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(Time[it->first] == -3 && Time[node] + it->second < goingTo[it->first]) {
                if(degree[it->first] > 1) {
                    Set.insert(Duo(Time[node] + it->second, it->first));
                    goingTo[it->first] = Time[node] + it->second;
                } else {
                    Time[it->first] = Time[node] + it->second;
                    addSpecials(it->first);
                }
            }
        }
}

void getSolution() {
    Set.insert(Duo(-1, index[N + 2][1]));

    for(int i = 1; i <= crtIndex; i++) {
        Time[i] = -3; goingTo[i] = 10000;
    }

    assert(crtIndex <= 1500000);

    while(!Set.empty()) {
        Duo now = *Set.begin(); Set.erase(Set.begin());

        if(Time[now.index] == -3) { /* daca nu am calculat deja timpul pentru obiectul curent */
            Time[now.index] = now.timeSpan;
            for(vector< pair< int,int > >::iterator it = graph[now.index].begin(); it != graph[now.index].end(); it++) {
                if(Time[it->first] == -3 && now.timeSpan + it->second < goingTo[it->first]) {
                    if(degree[it->first] > 1) {
                        Set.insert(Duo(now.timeSpan + it->second, it->first));
                        goingTo[it->first] = now.timeSpan + it->second;
                    } else {
                        Time[it->first] = now.timeSpan + it->second;
                        addSpecials(it->first);
                    }
                }
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            Solution[i][j] = '.';
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(index[i][j]) {
                Solution[i + Time[index[i][j]]][j] = '#';
            }
        }
    }
}

void writeOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%s\n", Solution[i] + 1);
    }
}

int main() {
    readInput();
    getObjects();
    buildVector();
    getSolution();
    writeOutput();

    return 0;
}
