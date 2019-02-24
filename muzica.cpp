/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("muzica.in", "r", stdin);
FILE *fout = freopen("muzica.out", "w", stdout);

const int mask = (1 << 14) - 1;

int n, m;
int a, b, c, d, e;

vector <int> h[mask + 1];

void readData() {
    scanf("%d%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d, &e);
    for(int i = 1; i <= n; ++i) {
        int x; scanf("%d", &x);
        h[x & mask].push_back(x);
    }
}

int answer;

bool search(int key) {
    int level = key & mask;
    for(vector <int>::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(*it == key) {
            h[level].erase(it);
            return true;
        }
    return false;
}

void solveProblem() {

    answer += search(a);
    answer += search(b);

    int k;
    for(int i = 3; i <= m; ++i) {
        k = (1LL * c * b + 1LL * d * a) % e;
        answer += search(k);
        a = b;
        b = k;
    }
    printf("%d", answer);
}

int main() {

    readData();
    solveProblem();
    return 0;
}
