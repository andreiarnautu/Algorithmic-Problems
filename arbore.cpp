/**
  *  Worg
  */
#include <bitset>
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb          push_back
#define buffDim     50000

using namespace std;
FILE *fin=freopen("arbore.in","r",stdin);
FILE *fout=freopen("arbore.out","w",stdout);

const int MAX_N     = 1 + 100000,
          MAX_S     = 1 + 1000000,
          blockDim  = 1 + 300,
          maxBlocks = MAX_N / blockDim + 2;

bitset < MAX_N > viz;
bitset < MAX_S > ok[maxBlocks];
vector < int > G[MAX_N];

int first[MAX_N], last[MAX_N], nodeNumber[MAX_N], add[maxBlocks], elemValue[MAX_N + 100];
int n, m, k;

class inputReader {

private:
    char buffer[buffDim];
    int pos = 0;

public:

    void getBuffer() {

        fread(buffer, 1, buffDim, stdin);
        pos = 0;
    }
    int readInteger() {

        int ret = 0;
        while(buffer[pos] < '0' || '9' < buffer[pos])
            if(++pos == buffDim)
                getBuffer();
        while('0' <= buffer[pos] && buffer[pos] <= '9') {

            ret = ret * 10 + buffer[pos] - '0';
            if(++pos == buffDim)
                getBuffer();
        }
        return ret;
    }
} cin;

void readData() {

    cin.getBuffer();
    n = cin.readInteger(); m = cin.readInteger();

    for(int i = 1; i < n; ++i) {

        int x = cin.readInteger(), y = cin.readInteger();
        G[x].pb(y); G[y].pb(x);
    }
}

void dfs(int node) {

    first[node] = ++k;
    nodeNumber[k] = node;
    viz[node] = 1;
    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!viz[*it])
            dfs(*it);
    last[node] = k;
}

void updateBlock(int x, int pos, int val, bool starting) {

    int a = x * blockDim + 1;
    int b = min(n, (x + 1) * blockDim);

    for(int i = a; i <= b; ++i)
        ok[x][elemValue[i]] = 0;
    if(starting)
        for(int i = a; i <= pos; ++i)
            elemValue[i] += val;
    else
        for(int i = pos; i <= b; ++i)
            elemValue[i] += val;
    for(int i = a; i <= b; ++i)
        ok[x][elemValue[i]] = 1;
}

void update() {

    int p = cin.readInteger(), s = cin.readInteger();
    int firstBlock = (first[p] - 1) / blockDim, lastBlock = (last[p] - 1) / blockDim;

    for(int i = firstBlock + 1; i < lastBlock; ++i)
        add[i] += s;

    if(firstBlock != lastBlock) {

        updateBlock(firstBlock, first[p], s, 0);
        updateBlock(lastBlock, last[p], s, 1);
    }
    else {

        updateBlock(firstBlock, last[p], s, 1);
        updateBlock(firstBlock, first[p] - 1, -s, 1);
    }
}

void query() {

    int s = cin.readInteger();

    for(int i = 0; i * blockDim < n; ++i)
        if(s >= add[i] && ok[i][s - add[i]]) {
            int a;
            for(a = i * blockDim + 1; elemValue[a] != s - add[i]; ++a);
            printf("%d\n", nodeNumber[a]);
            return;
        }
    printf("-1\n");
}

int main() {

    readData();
    dfs(1);
    for(int i = 0; i * blockDim < n; ++i)
        ok[i][0] = 1;
    for(int i = 1; i <= m; ++i) {

        int op = cin.readInteger();
        if(op == 1)
            update();
        else
            query();
    }
    return 0;
}
