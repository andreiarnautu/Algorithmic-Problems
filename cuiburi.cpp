/**
  *  Worg
  */
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("cuiburi.in", "r", stdin);
FILE *fout = freopen("cuiburi.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int MAX_INF = 0x3fffffff;

struct Object {
    int type;
    int x1, y1, x2, y2;
    int x, y, r;
    Object() {
        this->type = this->x1 = this->y1 = this->x2 = this->y2 = this->x = this->y = this->r = 0;
    }
    Object(const int &type, const int &x1, const int &y1, const int &x2, const int &y2) {
        this->type = type; this->x1 = x1; this->y1 = y1; this->x2 = x2; this->y2 = y2;
    }
    Object(const int &type, const int &x, const int &y, const int &r) {
        this->type = type; this->x = x;; this->y = y; this->r = r;
    }
};
/*------------------*/
Object nest[MAX_N];
int N;
/*------------------*/
int dp[MAX_N], degree[MAX_N];
vector<int> G[MAX_N];
queue<int> q;
bool ok[MAX_N][MAX_N];
/*------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        int type; scanf("%d", &type);
        if(type == 0) {
            int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            nest[i] = Object(type, x1, y1, x2, y2);
        } else {
            int x, y, r; scanf("%d%d%d", &x, &y, &r);
            nest[i] = Object(type, x, y, r);
        }
    }
}

double dist(int x1, int y1, int x2, int y2) {
    return sqrt((double)(x1 - x2) * (x1 - x2) +
                (double)(y1 - y2) * (y1 - y2));
}

bool inRectangle(int x, int y, int x1, int y1, int x2, int y2) {
    return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}

bool Try(const Object &A, const Object &B) {
    /* incercam sa il incadram pe A in B */
    if(A.type == 0) {
        /* daca A este dreptunghi */
        if(B.type == 0) {
            /* daca si B este dreptunghi */
            if(B.x1 <= A.x1 && A.x2 <= B.x2 && B.y1 <= A.y1 && A.y2 <= B.y2) {
                return true;
            } else {
                return false;
            }
        } else {
            /* daca B este cerc */
            double dist1 = dist(B.x, B.y, A.x1, A.y1);
            double dist2 = dist(B.x, B.y, A.x1, A.y2);
            double dist3 = dist(B.x, B.y, A.x2, A.y1);
            double dist4 = dist(B.x, B.y, A.x2, A.y2);
            if(dist1 > (double)B.r || dist2 > (double)B.r || dist3 > (double)B.r || dist4 > (double)B.r) {
                return false;
            } else {
                return true;
            }
        }
    } else {
        /* daca A este cerc */
        if(B.type == 0) {
            /* daca B este dreptunghi */
            if(!inRectangle(A.x, A.y, B.x1, B.y1, B.x2, B.y2)) {
                return false;
            } else {
                int dmin = MAX_INF;
                dmin = min(dmin, A.x - B.x1);
                dmin = min(dmin, B.x2 - A.x);
                dmin = min(dmin, A.y - B.y1);
                dmin = min(dmin, B.y2 - A.y);
                if(A.r > dmin) {
                    return false;
                } else {
                    return true;
                }
            }
        } else {
            /* daca B este cerc */
            double Dist = dist(A.x, A.y, B.x, B.y);
            if(Dist + (double)A.r > (double)B.r) {
                return false;
            } else {
                return true;
            }
        }
    }
}

void constructGraph() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            if(i != j) {
                ok[i][j] = Try(nest[i], nest[j]);
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            if(i != j) {
                if(ok[i][j] && ok[j][i]) {
                    G[i].push_back(j); degree[j]++;
                    ok[j][i] = false;
                } else if(ok[i][j]) {
                    G[i].push_back(j); degree[j]++;
                }
            }
        }
    }
}

void getAnswer() {
    for(int i = 1; i <= N; ++i) {
        if(!degree[i]) {
            q.push(i); dp[i] = 1;
        }
    }
    while(!q.empty()) {
        int node = q.front(); q.pop();
        for(vector<int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
            dp[*it] = max(dp[*it], 1 + dp[node]);
            degree[*it]--;
            if(!degree[*it]) {
                q.push(*it);
            }
        }
    }
    int answer = 0;
    for(int i = 1; i <= N; ++i) {
        answer = max(answer, dp[i]);
    }
    printf("%d\n", answer);
}

int main() {
    readData();
    constructGraph();
    getAnswer();
    return 0;
}
