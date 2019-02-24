/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("loto.in", "r", stdin);
FILE *fout = freopen("loto.out", "w", stdout);

const int MAX_N = 1 + 100;
const int P = 100003;

struct Hash {
    int r;
    int x, y, z;

    bool operator ==(const Hash &other) const {
        return (this->r == other.r &&
                this->x == other.x &&
                this->y == other.y &&
                this->z == other.z);
    }
};

int n, s;
int a[MAX_N];

vector <Hash> h[P];

void readData() {

    scanf("%d%d", &n, &s);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);
}

void insert(int value, int x, int y, int z) {
    int level = value % P;
    Hash current = {value, x, y, z};
    for(vector <Hash>::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(current == *it) {
            return;
        }
    h[level].push_back(current);
}

Hash search(int value) {
    int level = value % P;
    Hash answer = {0, 0, 0, 0};
    for(vector <Hash>::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(value == it->r) {
            return *it;
        }
    return answer;
}

void createHashTable() {
    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j)
            for(int k = j; k <= n && a[i] + a[j] + a[k] <= s; ++k) {
                insert(a[i] + a[j] + a[k], a[i], a[j], a[k]);
            }
}

int main() {

    readData();
    createHashTable();

    Hash empty = {0, 0, 0, 0};
    for(int x = 1; x <= n; ++x)
        for(int y = x; y <= n; ++y)
            for(int z = y; z <= n && a[x] + a[y] + a[z] <= s; ++z) {
                Hash current = search(s - a[x] - a[y] - a[z]);
                if(current == empty) {
                    continue;
                }
                else {
                    printf("%d %d %d %d %d %d", a[x], a[y], a[z], current.x, current.y, current.z);
                    return 0;
                }
            }
    printf("-1");

    return 0;
}
