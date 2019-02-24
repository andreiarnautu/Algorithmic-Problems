/**
  *   Worg
  */
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

#define fi first
#define se second
#define rep(i,a,n) for (int i=a;i<n;i++)

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1010;
const int M = 1001;

/*-------- Input data --------*/
char a[kMaxN];
int m;

int n;
int len[kMaxN];
char b[kMaxN][kMaxN];

int cost[10];
/*-------- Algo data --------*/
long long dp[kMaxN][kMaxN];
pair<int, int > vec[kMaxN];

int val[kMaxN], max_len[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%s", a);
    m = strlen(a);
    reverse(a, a + m);
    rep(i, m, M + 1) a[i] = '0';

    scanf("%d", &n);
    rep(i, 0, n) {
        scanf("%s", b[i]);
        int l = strlen(b[i]);
        reverse(b[i], b[i] + l);

        rep(j, l, M + 1) b[i][j] = '0';
        len[i] = l;
    }

    rep(i, 0, 10) {
        scanf("%d", &cost[i]);
    }
}

void RunAlgo() {
    rep(i, 0, n) vec[i] = make_pair(0, i);
    memset(dp,0xee,sizeof(dp));
    dp[0][0] = 0;
    rep(i, 0, M + 1) {
        int left = 0, right = 9;
        if(i == m - 1) left = 1;  //  Prima cifra nu poate fi 0
        if(a[i] != '?') right = left = a[i] - '0';  //  Cifra e fixata
        rep(j, 0, n) {
            val[j] = b[vec[j].se][i] - '0';
            max_len[j] = max(m, len[vec[j].se]);
        }
        rep(k, left, right + 1) {
            int c = 0;  //  Carry count
            int d = 0;  //  Cost count

            rep(j, 0, n) {
                c += (val[j] + k >= 10);
                d += (val[j] + k == 0 && i >= max_len[j]) ? 0 : cost[(val[j] + k) % 10];
            }
            rep(j, 0, n + 1) {
                dp[i + 1][c] = max(dp[i + 1][c], dp[i][j] + d);
                if(j < n) {
                    c -= (val[j] + k >= 10);
                    c += (val[j] + k + 1 >= 10);

                    d -= (val[j] + k == 0 && i >= max_len[j]) ? 0 : cost[(val[j] + k) % 10];
                    d += cost[(val[j] + k + 1) % 10];
                }
            }
        }

        rep(j, 0, n) {
            vec[j] = make_pair(val[j] * (n + 1) + n - j, vec[j].se);
        }
        sort(vec, vec + n); reverse(vec, vec + n);
    }
}

int main() {
    ReadInput();
    RunAlgo();
    printf("%lld\n", dp[M + 1][0]);
    return 0;
}
