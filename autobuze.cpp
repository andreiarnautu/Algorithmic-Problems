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
#define MAX_N       1 + 50000
#define buffDIM     50000

using namespace std;
FILE *fin=freopen("autobuze.in","r",stdin);
FILE *fout=freopen("autobuze.out","w",stdout);

const int mod = (1 << 16) - 1;
vector < pair<int,int> > h[mod + 5];
vector < pair<int,int> >::iterator it;
vector < int > G[MAX_N];

char buffer[MAX_N];
bool viz[MAX_N];
int a[MAX_N];
int n, biggestValue, pos;

void hashInsert(int index) {

    int level = a[index] & mod;
    h[level].pb(mp(a[index], index));
}

void read(int &nr) {

    while(buffer[pos] < '0' || '9' < buffer[pos])
        if(++pos == buffDIM)
            fread(buffer, 1, buffDIM, stdin), pos = 0;
    nr = 0;
    while('0' <= buffer[pos] && buffer[pos] <= '9') {

        nr = nr * 10 + buffer[pos] - '0';
        if(++pos == buffDIM)
            fread(buffer, 1, buffDIM, stdin), pos = 0;
    }
}

void readData() {

    read(n);
    for(int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; ++i)
        hashInsert(i);
    biggestValue = a[n];
}

void searchHash(int index) {

    for(int i = 2 * a[index]; i <= biggestValue; i += a[index]) {

        int level = i & mod;
        for(it = h[level].begin(); it != h[level].end(); ++it)
            if(it->fi == i) {

                G[index].pb(it->se);
                G[it->se].pb(index);
                break;
            }
    }
}

void normalSearch(int index) {

    for(int i = index + 1; i <= n; ++i)
        if(a[i] % a[index] == 0) {

            G[i].pb(index);
            G[index].pb(i);
        }
}

void dfs(int node) {

    for(vector <int>::iterator i = G[node].begin(); i != G[node].end(); ++i)
        if(!viz[*i]) {

            viz[*i] = 1;
            dfs(*i);
        }
}

int main() {

    readData();
    for(int i = 1; i <= n; ++i) {

        int raport = biggestValue / a[i];
        if(raport < n * 10)
            searchHash(i);
        else
            normalSearch(i);
    }

    int sol = 0;
    for(int i = 1; i <= n; ++i)
        if(!viz[i]) {

            ++sol;
            dfs(i);
        }
    printf("%d", sol);
    return 0;
}
