/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("arbore7.in", "r", stdin);
FILE *fout = freopen("arbore7.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int bufferDim = 100000;
const int MOD = 1000000007;

/*------------------------*/
vector<int> G[MAX_N];
int N;
/*------------------------*/
long long dp[MAX_N][2], cnt[MAX_N][2];
/*------------------------*/

class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;
        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

void readData() {
    cin.getBuffer(); cin.getInt(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin.getInt(u); cin.getInt(v);
        G[u].push_back(v); G[v].push_back(u);
    }
}

void DFS(int node = 1, int father = 0) {
    dp[node][1] = 1;
    cnt[node][0] = cnt[node][1] = 1;
    for(vector<int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(*it != father) {
            DFS(*it, node);

            dp[node][0] += max(dp[*it][0], dp[*it][1]);
            dp[node][1] += max(dp[*it][0], dp[*it][1] - 1);
            if(dp[*it][0] == dp[*it][1]) {
                cnt[node][0] *= (cnt[*it][0] + cnt[*it][1]);
            } else if(dp[*it][0] > dp[*it][1]) {
                cnt[node][0] *= cnt[*it][0];
            } else if(dp[*it][0] < dp[*it][1]) {
                cnt[node][0] *= cnt[*it][1];
            }

            if(dp[*it][0] == dp[*it][1] - 1) {
                cnt[node][1] *= (cnt[*it][0] + cnt[*it][1]);
            } else if(dp[*it][0] > dp[*it][1] - 1) {
                cnt[node][1] *= cnt[*it][0];
            } else if(dp[*it][0] < dp[*it][1] - 1) {
                cnt[node][1] *= cnt[*it][1];
            }

            dp[node][0] %= MOD;
            dp[node][1] %= MOD;
            cnt[node][0] %= MOD;
            cnt[node][1] %= MOD;
        }
    }
}

void writeData() {
    int node = 1;

    if(dp[node][0] == dp[node][1]) {
        printf("%lld %lld\n", dp[node][0], (cnt[node][0] + cnt[node][1]) % MOD);
    } else if(dp[node][0] > dp[node][1]) {
        printf("%lld %lld\n", dp[node][0], cnt[node][0]);
    } else {
        printf("%lld %lld\n", dp[node][1], cnt[node][1]);
    }
}

int main() {
    readData();
    DFS();
    writeData();
    return 0;
}
