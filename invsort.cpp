/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair
#define MAX_N       1 + 32000

using namespace std;
FILE *fin=freopen("invsort.in","r",stdin);
FILE *fout=freopen("invsort.out","w",stdout);

bool unu_zero, v[MAX_N], aux[MAX_N];
int n, pos, last;
int W[MAX_N], V[MAX_N], aux_2[MAX_N], cnt[MAX_N];
long long int TOTAL;

void readData() {

    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d ", &W[i]);
        ++cnt[W[i] + 1];
        v[i] = W[i];
        if(W[i] != 0 && W[i] != 1)
            unu_zero = 1;
    }
    for(int i = 1; i <= 32000; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = 1; i <= n; ++i)
        V[i] = (cnt[W[i]]++) + 1;
}

void reverse(int low, int high) {

    for(int i = high, j = 1; i >= low; --i, ++j)
        aux[j] = v[i], aux_2[j] = V[i];
    for(int i = low, j = 1; i <= high; ++i, ++j)
        v[i] = aux[j], V[i] = aux_2[j];
}

pair <int,int> sort(int low, int high) {

    if(low == high) {

        if(v[low] == 1)
            return mp(0, 1);
        return mp(1, 0);
    }
    pair <int,int> a, b;
    int mid = (low + high) >> 1;
    a = sort(low, mid);
    b = sort(mid + 1, high);
    if(a.se && b.fi) {

        printf("%d %d\n", mid - a.se + 1, mid + b.fi);
        reverse(mid - a.se + 1, mid + b.fi);
    }
    return mp(a.fi + b.fi, a.se + b.se);
}

void partition(int low, int high) {

    int pivot = V[(low + high) >> 1];
    for(int i = low; i <= high; ++i) {

        if(V[i] >= pivot)
            v[i] = 1;
        else
            v[i] = 0;
    }
    pair <int,int> a = sort(low, high);
    bool ok = (high - low + 1) == a.se;

    int mid;
    if(ok) {

        if(high - low > 1) {
            reverse(low, (low + high) >> 1);
            printf("%d %d\n", low, (low + high) >> 1);
        }
        mid = low;
    }
    else
        mid = low + a.fi - 1;
    if(low < mid)
        partition(low, mid);
    if(mid + 1 < high)
        partition(mid + 1, high);
}

int main() {

    readData();
   /* if(!unu_zero)
        sort(1, n);
    else*/
    partition(1, n);
    return 0;
}
