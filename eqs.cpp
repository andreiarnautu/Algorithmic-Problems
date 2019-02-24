/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
FILE *fin = freopen("eqs.in", "r", stdin);
FILE *fout = freopen("eqs.out", "w", stdout);

const int P = 60013;

vector < pair<int,int> > h[P + 1];

int a1, a2, a3, a4, a5;

void insert(int value) {
    int level = (value % P + P) % P;
    for(vector < pair<int,int> >::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(it->first == value) {
            it->second++;
            return;
        }
    h[level].push_back(make_pair(value, 1));
}

int search(int value) {
    int level = (value % P + P) % P;
    for(vector < pair<int,int> >::iterator it = h[level].begin(); it != h[level].end(); ++it)
        if(it->first == value) {
            return it->second;
        }
    return 0;
}

void createHashTable() {

    for(int x = -50; x <= 50; ++x)
        for(int y = -50; y <= 50; ++y)
            if(x != 0 && y != 0) {
                insert(a4 * x * x * x + a5 * y * y * y);
            }
}

int main() {

    scanf("%d%d%d%d%d", &a1, &a2, &a3, &a4, &a5);
    createHashTable();

    int answer = 0;
    for(int x1 = -50; x1 <= 50; ++x1)
        for(int x2 = -50; x2 <= 50; ++x2)
            for(int x3 = -50; x3 <= 50; ++x3)
                if(x1 != 0 && x2 != 0 && x3 != 0) {
                    answer += search(0 - a1 * x1 * x1 * x1 - a2 * x2 * x2 * x2 - a3 * x3 * x3 * x3);
                }
    printf("%d", answer);
    return 0;
}
