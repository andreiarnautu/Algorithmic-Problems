/**
  *  Worg
  */
#include <cstdio>
#include <vector>

#define pb          push_back
#define leftSon     (node << 1)
#define rightSon    (node << 1) + 1

using namespace std;
FILE *fin = freopen("delay.in", "r", stdin);
FILE *fout = freopen("delay.out", "w", stdout);

const int MAX_N = 1 + 16000,
          MAX_LOG = 17,
          bufferSize = 10000;

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
};

inputReader cin;
vector < int > G[MAX_N];

bool checked[MAX_N];
int rmq[MAX_LOG][MAX_N << 1];
int time[MAX_N], firstPos[MAX_N], lastPos[MAX_N], arb[MAX_N << 3], list[MAX_N << 1], pos[MAX_N], depth[MAX_N << 1], lg[MAX_N << 1];
int n, m, seqLen, listLen, queryResult;

void readData() {

    cin.getInt(n);
    for(int i = 1; i <= n; ++i)
        cin.getInt(time[i]);
    for(int i = 1; i < n; ++i) {

        int x, y;
        cin.getInt(x); cin.getInt(y);
        G[x].pb(y); G[y].pb(x);
    }
}

void update(int node, int left, int right, int pos, int value) {

    if(left == right) {

        arb[node] += value;
        return;
    }

    int mid = (left + right) >> 1;
    if(pos <= mid)
        update(leftSon, left, mid, pos, value);
    else
        update(rightSon, mid + 1, right, pos, value);
    arb[node] = arb[leftSon] + arb[rightSon];
}

void query(int node, int left, int right, int first, int last) {

    if(first <= left && right <= last) {

        queryResult += arb[node];
        return;
    }

    int mid = (left + right) >> 1;
    if(first <= mid)
        query(leftSon, left, mid, first, last);
    if(mid < last)
        query(rightSon, mid + 1, right, first, last);
}

void dfs(int node) {

    checked[node] = true;
    ++seqLen;
    firstPos[node] = seqLen;
    update(1, 1, n << 1, seqLen, time[node]);

    for(vector < int >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!checked[*it])
            dfs(*it);

    ++seqLen;
    lastPos[node] = seqLen;
    update(1, 1, n << 1, seqLen, -time[node]);
}

void eulerianDfs(int node, int level) {

    checked[node] = true;
    list[++listLen] = node;
    depth[listLen] = level;
    pos[node] = listLen;

    for(vector < int >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!checked[*it]) {

            eulerianDfs(*it, level + 1);
            list[++listLen] = node;
            depth[listLen] = level;
        }
}

void getRMQ() {

    for(int i = 2; i <= listLen; ++i)
        lg[i] = lg[i >> 1] + 1;
    for(int i = 1; i <= listLen; ++i)
        rmq[0][i] = i;

    for(int i = 1; (1 << i) < listLen; ++i) {

        int maxPos = listLen - (1 << i) + 1;
        for(int j = 1; j <= maxPos; ++j)
            rmq[i][j] = (depth[rmq[i - 1][j]] < depth[rmq[i - 1][j + (1 << (i - 1))]]) ? rmq[i - 1][j] : rmq[i - 1][j + (1 << (i - 1))];
    }
}

int LCA(int x, int y) {

    int a = pos[x], b = pos[y];
    if(a > b)
        swap(a, b);

    int level = lg[b - a + 1];
    return (depth[rmq[level][a]] < depth[rmq[level][b - (1 << level) + 1]]) ? list[rmq[level][a]] : list[rmq[level][b - (1 << level) + 1]];
}

void solveQuery() {

    int a, b, c, diff;
    cin.getInt(a); cin.getInt(b); cin.getInt(c);

    if(a == 1) {

        diff = c - time[b];
        update(1, 1, n << 1, firstPos[b], diff);
        update(1, 1, n << 1, lastPos[b], -diff);
        time[b] = c;
    }

    else {

        int ancestor = LCA(b, c), sol = 0;
        queryResult = 0;
        query(1, 1, n << 1, firstPos[ancestor], firstPos[b]);
        sol += queryResult;

        queryResult = 0;
        query(1, 1, n << 1, firstPos[ancestor], firstPos[c]);
        sol += queryResult;

        sol -= time[ancestor];
        printf("%d\n", sol);
    }
}

int main() {

    readData();
    dfs(1);
    for(int i = 1; i <= n; ++i)
        checked[i] = false;
    eulerianDfs(1, 0);
    getRMQ();
    cin.getInt(m);
    for(int i = 1; i <= m; ++i)
        solveQuery();
    return 0;
}
