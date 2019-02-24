/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair

using namespace std;
FILE *fin=freopen("coach.in","r",stdin);
FILE *fout=freopen("coach.out","w",stdout);

const int buffDim = 50000, MAX_N = 1 + 100, INF = 1000000000;

class inputReader {

private:
        int pos;
        char buffer[buffDim];

public:

        void getBuffer() {

            pos = 0;
            fread(buffer, 1, buffDim, stdin);
        }

        bool isDigit(char c) {

            return ('0' <= c && c <= '9');
        }

        int getInteger() {

            int ret = 0;
            while(!isDigit(buffer[pos]))
                if(++pos == buffDim)
                    getBuffer();
            while(isDigit(buffer[pos])) {

                ret = ret * 10 + buffer[pos] - '0';
                if(++pos == buffDim)
                    getBuffer();
            }
            return ret;
        }
} cin;

class graph {

private:
        int dim;

public:
        int pos[MAX_N];
        pair<int,int> v[MAX_N];

        void readData(int n) {

            dim = n;
            for(int i = 1; i <= n; ++i) {

                v[i].fi = cin.getInteger();
                v[i].se = i;
            }
            sort(v + 1, v + n + 1);
            for(int i = 1; i <= n; ++i)
                pos[v[i].se] = i;
        }

} g;

class matrix {

private:
        int init[MAX_N][MAX_N], a[MAX_N][MAX_N];
        int n, t;

public:
        void set(int m, int n, int t) {

            int x, y, cost;
            this->n = n;
            this->t = t;

            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= n; ++j)
                    init[i][j] = INF;

            for(int i = 1; i <= m; ++i) {

                x = cin.getInteger(); y = cin.getInteger(); cost = cin.getInteger();
                init[g.pos[x]][g.pos[y]] = init[g.pos[y]][g.pos[x]] = cost;
            }
        }

        bool check(int first) {


            for(int i = 1; i < first; ++i)
                for(int j = 1; j < first; ++j)
                    a[i][j] = INF;
            for(int i = first; i <= n; ++i)
                for(int j = first; j <= n; ++j)
                    a[i][j] = init[i][j];

            for(int k = first; k <= n; ++k) {

                for(int i = first; i <= n; ++i)
                    for(int j = first; j <= n; ++j)
                        a[i][j] = min(a[i][j], a[i][k] + a[k][j]);

                for(int i = first; i <= k; ++i)
                    for(int j = first; j <= k; ++j)
                        if(a[i][j] == t) {

                            printf("%d %d %d %d ", g.v[i].se, g.v[j].se, g.v[first].fi, g.v[k].fi);
                            return 1;
                        }

            }
            return 0;
        }

        void run() {

            for(int i = 1; i <= n && !check(i); ++i);
        }

} rf;

int main() {

    cin.getBuffer();
    int n = cin.getInteger(), m = cin.getInteger(), t = cin.getInteger();

    g.readData(n);
    rf.set(m, n, t);
    rf.run();
    return 0;
}
