/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("car.in", "r", stdin); FILE *fout = freopen("car.out", "w", stdout);

const int kMaxN = 500 + 1;
const int kStates = 8;
const int kMaxInf = 1e9;

const std::vector<std::pair<int,int > > dir = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

/*-------- Structures --------*/
struct Trio {
    int a, b, state;
    Trio() {}

    Trio(int _a, int _b, int _state) {
        a = _a; b = _b; state = _state;
    }
};
/*-------- Data --------*/
int N, M;
int xs, ys, xf, yf;
int a[kMaxN][kMaxN];

std::deque<Trio > deque;
int dp[kMaxN][kMaxN][kStates];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d%d%d%d%d", &N, &M, &xs, &ys, &xf, &yf);
    xs--; ys--; xf--; yf--;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}

bool Valid(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M && a[x][y] == 0;
}

void RunDP() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < kStates; k++) {
                dp[i][j][k] = kMaxInf;
            }
        }
    }
    for(int i = 0; i < kStates; i++) {
        deque.emplace_back(xs, ys, i);
        dp[xs][ys][i] = 0;
    }

    while(!deque.empty()) {
        int x = deque.front().a, y = deque.front().b, k = deque.front().state;
        deque.pop_front();

        if(x == xf && y == yf) {
            printf("%d\n", dp[x][y][k]); return;
        }

        //!  Add the next cell in this direction
        int newX = x + dir[k].first, newY = y + dir[k].second;
        if(Valid(newX, newY) && dp[newX][newY][k] > dp[x][y][k]) {
            dp[newX][newY][k] = dp[x][y][k];
            deque.emplace_front(newX, newY, k);
        }

        //!  Don't move but change direction
        int newK = (k + 1) & (kStates - 1);
        if(dp[x][y][newK] > dp[x][y][k] + 1) {
            dp[x][y][newK] = dp[x][y][k] + 1;
            deque.emplace_back(x, y, newK);
        }

        newK = (k + 7) & (kStates - 1);
        if(dp[x][y][newK] > dp[x][y][k] + 1) {
            dp[x][y][newK] = dp[x][y][k] + 1;
            deque.emplace_back(x, y, newK);
        }
    }

    printf("-1\n");
}

int main() {
    ReadInput();

    RunDP();
    return 0;
}
