/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair
#define pb          push_back

using namespace std;
FILE *fin = freopen("ct.in", "r", stdin);
FILE *fout = freopen("ct.out", "w", stdout);

const int MAX_N = 1 + 300000,
          MAX_K = 1 + 300000,
          MAX_LOG = 20,
          bufferSize = 10000;

int n, k, q;

class inputReader {

private:
        char buffer[bufferSize];
        int pos;
public:
        void getBuffer() {

            fread(buffer, 1, bufferSize, stdin);
            pos = 0;
        }

        bool digit(char c) {

            return ('0' <= c && c <= '9');
        }

        void getInt(int &nr) {

            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferSize)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferSize)
                    getBuffer();
            }
        }
} cin;

class graph {

private:
        struct myStruct {

            int a, b, ancestor, depth;

            myStruct(const int &a, const int &b, const int &ancestor, const int &depth) {

                this->a = a, this->b = b, this->ancestor = ancestor, this->depth = depth;
            }

            bool operator <(const myStruct &other) const {

                return this->depth < other.depth;
            }
        };

        vector < int > V[MAX_N];
        vector < myStruct > LCA;
        int rmq[MAX_LOG][MAX_N << 1];
        int pos[MAX_N], depth[MAX_N << 1], list[MAX_N << 1], log[MAX_N << 1], father[MAX_N];
        int sol;
        bool viz[MAX_N], solved[MAX_N];

public:

        void clear() {

            for(int i = 1; i <= n; ++i) {

                V[i].clear();
                viz[i] = solved[i] = false;
            }
            LCA.clear();
        }

        void addEdge(const int &x, const int &y) {

            V[x].pb(y);
            V[y].pb(x);
        }

        void dfs(int node, int level) {

            viz[node] = true;
            list[++k] = node;
            depth[k] = level;
            pos[node] = k;

            for(vector < int >::iterator it = V[node].begin(); it != V[node].end(); ++it)
                if(!viz[*it]) {

                    father[*it] = node;
                    dfs(*it, level + 1);
                    list[++k] = node;
                    depth[k] = level;
                }
        }

        void getRMQ() {

            for(int i = 2; i <= k; ++i)
                log[i] = log[i >> 1] + 1;
            for(int i = 1; i <= k; ++i)
                rmq[0][i] = i;

            for(int i = 1; (1 << i) < k; ++i) {

                int lastPos = k - (1 << i);
                for(int j = 1; j <= lastPos; ++j)
                    rmq[i][j] = (depth[rmq[i - 1][j]] < depth[rmq[i - 1][j + (1 << (i - 1))]]) ? rmq[i - 1][j] : rmq[i - 1][j + (1 << (i - 1))];
            }
        }

        void getLCA(const int &x, const int &y) {

            int a = pos[x], b = pos[y];
            if(a > b)
                swap(a, b);

            int level = log[b - a + 1];
            int node = (depth[rmq[level][a]] < depth[rmq[level][b - (1 << level) + 1]]) ? list[rmq[level][a]] : list[rmq[level][b - (1 << level) + 1]];
            LCA.pb(myStruct(x, y, node, min(depth[rmq[level][a]], depth[rmq[level][b - (1 << level) + 1]])));
        }

        void dfsMark(int node) {

            solved[node] = true;
            for(vector < int >::iterator it = V[node].begin(); it != V[node].end(); ++it)
                if(!solved[*it] && *it != father[node])
                    dfsMark(*it);
        }

        void solve() {

            sort(LCA.begin(), LCA.end());
            sol = 0;

            for(vector < myStruct >::iterator it = LCA.end() - 1; it >= LCA.begin(); --it)
                if(!solved[it->a] && !solved[it->b]) {

                    ++sol;
                    dfsMark(it->ancestor);
                }
            printf("%d\n", sol);
        }
} G;

int main() {

    int t;
    cin.getBuffer();
    for(cin.getInt(t); t; --t) {

        cin.getInt(n); cin.getInt(q);
        G.clear();                      /* clear data */
        for(int j = 1; j < n; ++j) {    /* add edges */

            int x, y;
            cin.getInt(x); cin.getInt(y);
            G.addEdge(x, y);
        }
        G.dfs(1, 0);
        G.getRMQ();     /* get RMQ */
        for(int j = 1; j <= q; ++j) {

            int x, y;
            cin.getInt(x); cin.getInt(y);
            G.getLCA(x, y);
        }
        G.solve();
    }

}
