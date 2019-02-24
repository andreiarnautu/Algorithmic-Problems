/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("banana.in", "r", stdin);
FILE *fout = freopen("banana.out", "w", stdout);

const int MAX_N = 1 + 16000;

int n, k;
int father[MAX_N];

struct Punct {
    int index;
    int x, y;
};

Punct p[MAX_N];

bool dupaX(const Punct &p1, const Punct &p2) {
    if(p1.x != p2.x) {
        return p1.x < p2.x;
    }
    else {
        return p1.y < p2.y;
    }
}

bool dupaY(const Punct &p1, const Punct &p2) {
    if(p1.y != p2.y) {
        return p1.y < p2.y;
    }
    else {
        return p1.x < p2.x;
    }
}

int group(int x) {
    if(x != father[x]) {
        father[x] = group(father[x]);
    }
    return father[x];
}

void unite(int x, int y) {
    x = group(x);
    y = group(y);
    father[x] = y;
}

void readData() {

    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
        p[i].index = i;
    }
}

void getGroups() {

    for(int i = 1; i <= n; ++i)
        father[i] = i;

    sort(p + 1, p + n + 1, dupaX);
    for(int i = 2; i <= n; ++i)
        if(p[i].x == p[i - 1].x && p[i].y == p[i - 1].y + 1) {
            unite(p[i].index, p[i - 1].index);
        }

    sort(p + 1, p + n + 1, dupaY);
    for(int i = 2; i <= n; ++i)
        if(p[i].y == p[i - 1].y && p[i].x == p[i - 1].x + 1) {
            unite(p[i].index, p[i - 1].index);
        }
}

int cnt[MAX_N];

void chooseGroups() {

    for(int i = 1; i <= n; ++i) {
        int g = group(i);
        cnt[g]++;
    }
    sort(cnt + 1, cnt + n + 1);

    int answer = 0;
    for(int i = n; i > n - k; --i) {
        answer += cnt[i];
    }
    printf("%d", answer);
}

int main() {

    readData();
    getGroups();
    chooseGroups();
    return 0;
}
