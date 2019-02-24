/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair
#define MAX_N       1 + 200000
#define inFile      "invsc.in"
#define outFile     "invsc.out"

using namespace std;

int v[MAX_N], cnt[MAX_N];
int n;

void readData() {

    freopen(inFile, "r", stdin);
    scanf("%d ", &n);
    int x;
    for(int i = 1; i <= n; ++i) {

        scanf("%d ", &v[i]);
        ++cnt[v[i]];
    }
    for(int i = 2; i <= n; ++i)
        cnt[i] += cnt[i - 1];
}

int main() {

    readData();
    freopen(outFile, "w", stdout);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", cnt[v[i]]--);
    return 0;
}
