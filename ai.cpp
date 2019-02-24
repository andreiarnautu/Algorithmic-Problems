/**
  *  Worg
  */
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair
#define pb          push_back
#define INF         1000000000
#define MAX_N       1 + 1000 + 10
#define buffDim     10000

using namespace std;
FILE *fin=freopen("ai.in","r",stdin);
FILE *fout=freopen("ai.out","w",stdout);

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0,-1, 1};
queue < pair<int,int> > Q;

bool wall[MAX_N][MAX_N], viz[MAX_N][MAX_N];
char buffer[MAX_N];
int dp[2][MAX_N][MAX_N];
int lin[MAX_N][MAX_N], col[MAX_N][MAX_N], best[2][2];
int n, k, t1, t2, s1, s2, s3, s4, r1, r2, r3, r4, pos, maxWall;

void read(int &nr) {

    while(buffer[pos] < '0' || '9' < buffer[pos])
        if(++pos == buffDim)
            fread(buffer, 1, buffDim, stdin), pos = 0;
    nr = 0;
    while('0' <= buffer[pos] && buffer[pos] <= '9') {

        nr = nr * 10 + buffer[pos] - '0';
        if(++pos == buffDim)
            fread(buffer, 1, buffDim, stdin), pos = 0;
    }
}

void readData() {

    /*fread(buffer, 1, buffDim, stdin);
    read(n);
    read(t1); read(t2); read(s1); read(s2); read(s3); read(s4); read(r1); read(r2); read(r3); read(r4);
    read(k);*/
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d ", &n, &t1, &t2, &s1, &s2, &s3, &s4, &r1, &r2, &r3, &r4, &k);

    wall[t1][t2] = 1;
    int x, y;
    for(int i = 1; i <= k; ++i) {

        scanf("%d %d ", &x, &y);
        wall[x][y] = 1;
    }
    best[0][0] = best[1][1] = best[0][1] = best[1][0] = INF;
}

void getMaxWall() {

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {

            lin[i][j] = lin[i][j - 1] * wall[i][j] + wall[i][j];
            col[i][j] = col[i - 1][j] * wall[i][j] + wall[i][j];
            maxWall = max(maxWall, max(lin[i][j], col[i][j]));
        }
}

void bfs(int bit, int a, int b) {

    memset(viz, 0, sizeof(viz));

    int x, y, X, Y;
    Q.push(mp(a, b));
    viz[a][b] = 1;
    while(!Q.empty()) {

        x = Q.front().fi, y = Q.front().se;
        Q.pop();

        for(int i = 0; i < 4; ++i) {

            X = x + dx[i], Y = y + dy[i];
            if(X && Y && X <= n && Y <= n && !viz[X][Y] && !wall[X][Y]) {

                viz[X][Y] = 1;
                dp[bit][X][Y] = dp[bit][x][y] + 1;
                Q.push(mp(X, Y));
            }
        }
    }
}

void savePositions_1() {

    int A = abs(s1 - t1), B = abs(s2 - t2), a, b, r;

    while(B)
        r = A % B, A = B, B = r;
    a = (t1 - s1) / A, b = (t2 - s2) / A;

    for(int x = s1, y = s2; !(x == t1 && y == t2); x += a, y += b) {

        best[0][0] = min(best[0][0], (wall[x][y] == 1 || !dp[0][x][y] ? INF : dp[0][x][y]));
        best[1][0] = min(best[1][0], (wall[x][y] == 1 || !dp[1][x][y] ? INF : dp[1][x][y]));
    }
}

void savePositions_2() {

    int A = abs(s3 - t1), B = abs(s4 - t2), a, b, r;

    while(B)
        r = A % B, A = B, B = r;
    a = (t1 - s3) / A, b = (t2 - s4) / A;

    for(int x = s3, y = s4; !(x == t1 && y == t2); x += a, y += b) {

        best[0][1] = min(best[0][1], (wall[x][y] == 1 || !dp[0][x][y] ? INF : dp[0][x][y]));
        best[1][1] = min(best[1][1], (wall[x][y] == 1 || !dp[1][x][y] ? INF : dp[1][x][y]));
    }
}

void writeData() {

    printf("%d\n", maxWall);
    printf("%d", min(max(best[0][0], best[1][1]), max(best[1][0], best[0][1])));
}

int main() {

    readData();
    getMaxWall();
    bfs(0, r1, r2);
    bfs(1, r3, r4);
    savePositions_1();
    savePositions_2();
    writeData();
    return 0;
}
