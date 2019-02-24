/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("memcpy.in", "r", stdin);
FILE *fout = freopen("memcpy.out", "w", stdout);

const int MAX_N = 1 + 1000;

struct Casuta {
    short int x, y;
    Casuta(const int &x, const int &y) {
        this->x = x; this->y = y;
    }
    bool operator <(const Casuta &other) const {
        if(this->x != other.x) {
            return this->x < other.x;
        }
        else {
            return this->y < other.y;
        }
    }
};

int N, M, X, Y, newX, newY;

set <Casuta> Set;
bool checked[MAX_N][MAX_N];

void readData() {
    scanf("%d%d%d%d%d%d", &N, &M, &X, &Y, &newX, &newY);
}

bool inside(short int x, short int y) {
    return (X <= x && x < X + N && Y <= y && y < Y + M);
}

void solveProblem() {
    int delayX = newX - X;
    int delayY = newY - Y;
    for(int i = X; i < X + N; ++i) {
        for(int j = Y; j < Y + M; ++j) {
            if(!inside(i + delayX, j + delayY) || (delayX == 0 && delayY == 0)) {
                Set.insert(Casuta(i, j));
            }
        }
    }

    long long hashVal = 0, MOD = 1e9 + 7, index = 1;
    while(!Set.empty()) {
        Casuta current = *Set.begin(); Set.erase(Set.begin());
        hashVal = (hashVal + 1LL * index * current.x * current.y) % MOD;
        index++;

        int newI = current.x - delayX;
        int newJ = current.y - delayY;
        if(inside(newI, newJ) && !(delayX == 0 && delayY == 0)) {
            Set.insert(Casuta(newI, newJ));
        }
    }
    printf("%lld", hashVal);
}

int main() {
    readData();
    solveProblem();
}
