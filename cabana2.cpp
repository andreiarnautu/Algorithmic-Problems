/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair
#define pb          push_back
#define i64         long long int
#define INF         1000000001
#define MAX_N       1 + 50000

using namespace std;
FILE *fin=freopen("cabana.in","r",stdin);
FILE *fout=freopen("cabana.out","w",stdout);

pair <int,int> v[MAX_N];
vector <int> L[MAX_N];
int C[MAX_N];
int n, nr;
i64 sol;

void readData() {

    int x, y;
    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i) {

        scanf("%d %d ", &x, &y);
        v[i] = mp(x, y);
    }
    sort(v + 1, v + n + 1);
    v[0] = mp(-INF, 0);
}

void setLines() {

    for(int i = 1; i <= n; ++i) {

        if(v[i].fi != v[i - 1].fi)
            ++nr;
        C[nr] = v[i].fi;
        L[nr].pb(v[i].se);
    }
}

int bigger_than(int x, int val) {

    int low = 0, high = L[x].size() - 1, mid, ret = high;
    while(low <= high) {

        mid = (low + high) >> 1;
        if(L[x][mid] >= val)
            ret = mid, high = mid - 1;
        else
            low = mid + 1;
    }
    return ret;
}

void checkLine(int x) {

    int y1, y2, k, y3, y4, y5;

    for(int j = L[x].size() - 1; j; --j) {

        y1 = L[x][j];
        y2 = L[x][j - 1];
        k = x + 1;
        while(k <= nr) {

            y3 = L[k][bigger_than(k, y1)];
            y4 = L[k][bigger_than(k, y2)];
            if(y2 > y3 || y1 < y4)
                ++k;
            else if(y1 == y3 && y2 == y4) {

                y5 = L[k][bigger_than(k, y2 + 1)];
                if(y2 + 1 != y1 && y5 < y1)
                    break;
                sol = max(sol, 1LL * (y1 - y2) * (C[k] - C[x]));
                break;
            }
            else
                break;
        }
    }
}

int main() {

    readData();
    setLines();
    for(int i = 1; i < nr; ++i)
        if(L[i].size() > 1)
            checkLine(i);
    printf("%lld", sol);
    return 0;
}
