/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

#define pb          push_back
#define MAX_N       1 + 300000
#define inFile      "arbvalmax.in"
#define outFile     "arbvalmax.out"
#define buffDim     50000

using namespace std;
FILE *fin=freopen(inFile,"r",stdin);
FILE *fout=freopen(outFile,"w",stdout);

vector <int> G[MAX_N];

int val[MAX_N], max_subarb[MAX_N], max_subarb2[MAX_N], max_son[MAX_N], dp_1[MAX_N], dp_2[MAX_N];
int pos, n, m;
char buff[buffDim];

void read(int &nr) {

    while(buff[pos] < '0' || buff[pos] > '9')
        if(++pos == buffDim)
            pos = 0, fread(buff, 1, buffDim, stdin);
    nr = 0;
    while(buff[pos] >= '0' && '9' >= buff[pos]) {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDim)
            pos = 0, fread(buff, 1, buffDim, stdin);
    }
}

void readData() {

    int x;
    fread(buff, 1, buffDim, stdin);
    read(n); read(m);

    for(int i = 2; i <= n; ++i) {

        read(x);
        G[x].pb(i);
    }

    for(int i = 1; i <= n; ++i)
        read(val[i]);
}

void dfs_1(int node) {

    int k;
    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {

        dfs_1(*it);
        k = max(val[*it], max_subarb[*it]);
        if(k > max_subarb[node]) {

            max_subarb2[node] = max_subarb[node];
            max_subarb[node] = k;
            max_son[node] = *it;
        }
        else if(k > max_subarb2[node])
            max_subarb2[node] = k;
    }
}

void dfs_2(int node) {

    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {

        if(max_son[node] == *it) {

            dp_1[*it] = max(dp_1[node], max_subarb2[node]);
            dp_2[*it] = max(dp_2[node], max(val[node], max_subarb2[node]));
        }
        else {

            dp_1[*it] = max(dp_1[node], max_subarb[node]);
            dp_2[*it] = max(dp_2[node], max(val[node], max_subarb[node]));
        }
        dfs_2(*it);
    }
}

void writeData(int x, int y) {

    printf("%d\n", max(max_subarb[y], max(dp_1[y], dp_2[x])));
}

int main() {

    readData();
    dfs_1(1);
    dfs_2(1);
    int x, y;
    for(int i = 1; i <= m; ++i) {

        read(x); read(y);
        writeData(x, y);
    }
    return 0;
}
