/**
  *  Worg
  */
#include <queue>
#include <cstdio>

#define fi          first
#define se          second
#define mp          make_pair
#define INF         260000
#define MAX_N       1 + 500
#define inFile      "panda.in"
#define outFile     "panda.out"

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0,-1, 1};
queue < pair<int,int> > Q;

bool ok[MAX_N][MAX_N];
int code[MAX_N][MAX_N], dmin[MAX_N][MAX_N];
int p, n, m, t, l, c, k, s, mask;

void readData() {

    freopen(inFile,"r",stdin);
    int x, y;
    scanf("%d %d %d %d %d %d %d %d ", &p, &n, &m, &t, &l, &c, &k, &s);

    for(int i = 1; i <= t; ++i) {

        scanf("%d %d ", &x, &y);
        ok[x][y] = 1;
    }

    mask = (1 << s) - 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {

            scanf("%d ", &code[i][j]);
            code[i][j] &= mask;
        }
    k &= mask;
}

void task_1() {

    freopen(outFile,"w",stdout);
    int sol = 0, rest = mask - k;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            sol += (code[i][j] == rest && (i != l || j != c));
    printf("%d", sol);
}

void lee() {

    int x, y, X, Y, rest = mask - k;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            dmin[i][j] = INF;
    dmin[l][c] = 0;
    Q.push(mp(l, c));

    while(!Q.empty()) {

        x = Q.front().fi, y = Q.front().se; Q.pop();

        for(int i = 0; i < 4; ++i) {

            X = x + dx[i];
            Y = y + dy[i];
            if(X && Y && X <= n && Y <= m && dmin[X][Y] == INF && code[X][Y] == rest) {

                dmin[X][Y] = dmin[x][y] + 1;
                Q.push(mp(X, Y));
            }
        }
    }
}

void task_2() {

    freopen(outFile,"w",stdout);
    lee();

    int sol = INF, cnt;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {

            if(sol > dmin[i][j] && ok[i][j])
                sol = dmin[i][j], cnt = 1;
            else if (sol == dmin[i][j] && ok[i][j])
                ++cnt;
        }
    printf("%d %d ", sol, cnt);
}

int main() {

    readData();
    if(p == 1)
        task_1();
    else
        task_2();
    return 0;
}
