/**
  *  Worg
  */
#include <cstdio>

#define Dim 1000010 * 3
#define buffDim 100100
#define isDigit(c) '0' <= c && c <= '9'
#define notDigit(c) c < '0' || c > '9'

using namespace std;
FILE *fin=freopen("eliminare.in","r",stdin);
FILE *fout=freopen("eliminare.out","w",stdout);

int arb[Dim], cnt[Dim];
int v[Dim / 3];
int n, m, pos, ans;
char buff[buffDim];

void read(int &nr) {

    while(notDigit(buff[pos]))
        if(++pos == buffDim)
            fread(buff, 1, buffDim, stdin), pos = 0;
    nr = 0;
    while(isDigit(buff[pos])) {

        nr = nr * 10 + buff[pos] - '0';
        if(++pos == buffDim)
            fread(buff, 1, buffDim, stdin), pos = 0;
    }
}

void update(int node, int left, int right, int pos) {

    if(left == right) {
        arb[node] = pos;
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    if(pos <= mid)
        update(lSon, left, mid, pos);
    else
        update(rSon, mid + 1, right, pos);

    if(v[arb[lSon]] >= v[arb[rSon]])
        arb[node] = arb[lSon];
    else
        arb[node] = arb[rSon];
}

void query(int node, int left, int right, int first, int last) {

    if(left > last || right < first)
        return;
    if(first <= left && right <= last) {

        if(v[arb[node]] > v[ans])
            ans = arb[node];
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;

    if(first <= mid)
        query(lSon, left, mid, first, last);
    if(mid < last)
        query(rSon, mid + 1, right, first, last);
}

void change(int node, int left, int right, int pos, int val) {

    if(left == right) {
        cnt[node] = val;
        return;
    }

    int mid = (left + right) >> 1, lSon = node << 1, rSon = (node << 1) + 1;
    if(pos <= mid)
        change(lSon, left, mid, pos, val);
    else
        change(rSon, mid + 1, right, pos, val);

    cnt[node] = cnt[lSon] + cnt[rSon];
}

int getPos(int node, int left, int right, int pos) {

    if(left == right)
        return left;

    if(cnt[node << 1] >= pos)
        return getPos(node << 1, left, (left + right) >> 1, pos);
    else
        return getPos((node << 1) + 1, ((left + right) >> 1) + 1, right, pos - cnt[node << 1]);
}

int main() {

    int x, y;
    read(n); read(m); v[0] = -2;
    for(int i = 1; i <= n; ++i) {

        read(v[i]);
        update(1, 1, n, i);
        change(1, 1, n, i, 1);
    }

    for(int i = 1; i <= m; ++i) {

        read(x); x = getPos(1, 1, n, x);
        read(y); y = getPos(1, 1, n, y);
        ans = 0; query(1, 1, n, x, y);
        v[ans] = -1; update(1, 1, n, ans); change(1, 1, n, ans, 0);
    }

    for(int i = 1; i <= n; ++i)
        if(v[i] != -1)
            printf("%d\n", v[i]);
    return 0;
}
