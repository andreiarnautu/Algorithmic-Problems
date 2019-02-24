/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define i64         long long int
#define INF         1000000
#define MAX_N       1 + 1000
#define buffDIM     50000

using namespace std;
FILE *fin=freopen("fence.in","r",stdin);
FILE *fout=freopen("fence.out","w",stdout);

char buff[buffDIM];
bool ok[MAX_N][MAX_N];
int a[MAX_N][MAX_N], best[MAX_N][MAX_N], dp[MAX_N][MAX_N];
int pos, t, m, n, v, x_nord, x_sud, y_vest, y_est;
i64 sol;

void read(int &nr) {

    while(buff[pos] < '0' || buff[pos] > '9')
        if(++pos == buffDIM)
            fread(buff, 1, buffDIM, stdin), pos = 0;
    nr = 0;
    while('0' <= buff[pos] && buff[pos] <= '9') {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDIM)
            fread(buff, 1, buffDIM, stdin), pos = 0;
    }
}

void readData() {

    fread(buff, 1, buffDIM, stdin);
    read(t); read(m); read(n); read(v); read(x_nord); read(x_sud); read(y_vest); read(y_est);
    for(int i = 1; i <= m; ++i)
        for(int j = 1; j <= n; ++j)
            read(a[i][j]);
}

void solveFirst() {

    for(int i = 1; i < y_vest; ++i)
        for(int j = 1; j < x_nord; ++j)
            ok[i][j] = 1;
    for(int i = y_vest + 1; i <= m; ++i)
        for(int j = 1; j < x_sud; ++j)
            ok[i][j] = 1;
    for(int i = 1; i < y_est; ++i)
        for(int j = x_nord + 1; j <= n; ++j)
            ok[i][j] = 1;
    for(int i = y_est + 1; i <= m; ++i)
        for(int j = x_sud + 1; j <= n; ++j)
            ok[i][j] = 1;

    for(int i = 1; i <= m; ++i)
        for(int j = 1; j <= n; ++j)
            if(!ok[i][j])
                sol += 1LL * (a[i][j] - v);
}

void solveNorthWest() {

    int x_up, x_down, y_left, y_right, add = 0, sum;
    x_up = 1, x_down = y_vest - 1, y_left = 1, y_right = x_nord - 1;


    for(int i = x_down; i >= x_up; --i)
        dp[i][y_right] = dp[i + 1][y_right] + a[i][y_right] - v,
        add = max(add, dp[i][y_right]);

    best[x_up][y_right] = dp[x_up][y_right];
    for(int i = x_up + 1; i <= x_down; ++i)
        best[i][y_right] = max(best[i - 1][y_right], dp[i][y_right]);

    for(int j = y_right - 1; j >= y_left; --j) {

        sum = 0;
        for(int i = x_down; i >= x_up; --i) {

            sum += a[i][j] - v;
            dp[i][j] = sum + best[i][j + 1];
            add = max(add, dp[i][j]);
        }
        best[x_up][j] = dp[x_up][j];
        for(int i = x_up + 1; i <= x_down; ++i)
            best[i][j] = max(dp[i][j], best[i - 1][j]);
    }
    sol += add;
}

void solveSouthWest() {

    int x_up, x_down, y_left, y_right, sum, add = 0;
    x_up = y_vest + 1, x_down = m, y_left = 1, y_right = x_sud - 1;

    for(int i = x_up; i <= x_down; ++i)
        dp[i][y_right] = dp[i - 1][y_right] + a[i][y_right] - v,
        add = max(add, dp[i][y_right]);

    best[x_down][y_right] = dp[x_down][y_right];
    for(int i = x_down - 1; i >= x_up; --i)
        best[i][y_right] = max(dp[i][y_right], best[i + 1][y_right]);

    for(int j = y_right - 1; j >= y_left; --j) {

        sum = 0;
        for(int i = x_up; i <= x_down; ++i) {

            sum += a[i][j] - v;
            dp[i][j] = sum + best[i][j + 1];
            add = max(add, dp[i][j]);
        }
        best[x_down][j] = dp[x_down][j];
        for(int i = x_down - 1; i >= x_up; --i)
            best[i][j] = max(dp[i][j], best[i + 1][j]);
    }
    sol += add;
}

void solveNorthEast() {

    int x_up, x_down, y_left, y_right, add = 0, sum;
    x_up = 1, x_down = y_est - 1, y_left = x_nord + 1, y_right = n;

    for(int i = x_down; i >= x_up; --i)
        dp[i][y_left] = dp[i + 1][y_left] + a[i][y_left] - v,
        add = max(add, dp[i][y_left]);

    best[x_up][y_left] = dp[x_up][y_left];
    for(int i = x_up + 1; i <= x_down; ++i)
        best[i][y_left] = max(dp[i][y_left], best[i - 1][y_left]);

    for(int j = y_left + 1; j <= y_right; ++j) {

        sum = 0;
        for(int i = x_down; i >= x_up; --i) {

            sum += a[i][j] - v;
            dp[i][j] = sum + best[i][j - 1];
            add = max(add, dp[i][j]);
        }
        best[x_up][j] = dp[x_up][j];
        for(int i = x_up + 1; i <= x_down; ++i)
            best[i][j] = max(dp[i][j], best[i - 1][j]);
    }
    sol += add;
}

void solveSouthEast() {

    int x_up, x_down, y_left, y_right, add = 0, sum;
    x_up = y_est + 1, x_down = m, y_left = x_sud + 1, y_right = n;

    for(int i = x_up; i <= x_down; ++i)
        dp[i][y_left] = dp[i - 1][y_left] + a[i][y_left] - v,
        add = max(add, dp[i][y_left]);

    best[x_down][y_left] = dp[x_down][y_left];
    for(int i = x_down - 1; i >= x_up; --i)
        best[i][y_left] = max(dp[i][y_left], best[i + 1][y_left]);

    for(int j = y_left + 1; j <= y_right; ++j) {

        sum = 0;
        for(int i = x_up; i <= x_down; ++i) {

            sum += a[i][j] - v;
            dp[i][j] = sum + best[i][j - 1];
            add = max(add, dp[i][j]);
        }
        best[x_down][j] = dp[x_down][j];
        for(int i = x_down - 1; i >= x_up; --i)
            best[i][j] = max(dp[i][j], best[i + 1][j]);
    }
    sol += add;
}

int main() {

    readData();
    solveFirst();
    if(t == 2) {

        solveNorthEast();
        solveNorthWest();
        solveSouthEast();
        solveSouthWest();
    }
    printf("%lld", sol);
    return 0;
}
