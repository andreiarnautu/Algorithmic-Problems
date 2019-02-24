/**
  *  Worg
  */
#include <bitset>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("ferma3.in", "r", stdin);
FILE *fout = freopen("ferma3.out", "w", stdout);

const int MAX_N = 500;
const int dx[] = {-1, 1,  0, 0};
const int dy[] = { 0, 0, -1, 1};

int task, n, m;
char matrix[1 + MAX_N][1 + MAX_N];

int zone[1 + MAX_N][1 + MAX_N], color[1 + MAX_N][1 + MAX_N];
int elemCount[200000];
int currentZone, currentColor;

bitset <1 + (MAX_N + 1) * (MAX_N + 1)> used;
vector < pair<int,int> > N;
vector <int> usedZones;

void readData() {

    scanf("%d%d%d", &task, &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%s", matrix[i] + 1);
}

bool inTheMatrix(int i, int j) {

    return(1 <= i && i <= n && 1 <= j && j <= m);
}

void fill(int x, int y) {

    elemCount[currentZone]++;
    zone[x][y] = currentZone;
    color[x][y] = matrix[x][y] - 'a' + 1;

    for(int i = 0 ; i < 4; ++i) {

        int newX = x + dx[i], newY = y + dy[i];
        if(color[newX][newY] == 0 && inTheMatrix(newX, newY) && matrix[x][y] == matrix[newX][newY]) {
            fill(newX, newY);
        }
    }
}

void addSomeColors() {

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            if(!color[i][j]) {

                currentZone++;
                currentColor = matrix[i][j] - 'a' + 1;
                fill(i, j);
            }
        }
}

void getBiggestSurface() {

    int sol = 0;
    for(int i = 1; i <= currentZone; ++i)
        sol = max(sol, elemCount[i]);
    printf("%d", sol);
}

void getNeighbours(int x, int y) {

    for(int i = 0; i < 4; ++i) {

        int newX = x + dx[i], newY = y + dy[i];
        if(inTheMatrix(newX, newY) && !used[zone[newX][newY]] && zone[x][y] != zone[newX][newY]) {

            N.push_back(make_pair(elemCount[zone[newX][newY]], color[newX][newY]));
            used[zone[newX][newY]] = true;
            usedZones.push_back(zone[newX][newY]);
        }
    }
    sort(N.begin(), N.end());
}

pair<int,char> getSurface() {

    int ret = 0;
    char c = 'a';

    if(N.size()) {

        ret = N[(int)N.size() - 1].first + 1;
        c = N[(int)N.size() - 1].second - 1 + 'a';
    }

    for(int i = 0; i < (int)N.size() - 1; ++i)
        for(int j = i + 1; j < (int)N.size(); ++j)
            if(N[i].second == N[j].second) {
                if(ret < 1 + N[i].first + N[j].first) {

                    c = N[i].second - 1 + 'a';
                    ret = 1 + N[i].first + N[j].first;
                }
            }

    for(int i : usedZones)
        used[i] = false;

    usedZones.clear();
    N.clear();
    return make_pair(ret, c);
}

void getCoordinates() {

    int maxSurface = -1, x = 0, y = 0;
    char usedColor = 'a';

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {

            getNeighbours(i, j);
            pair<int,char> currentSurface = getSurface();

            if(maxSurface <= currentSurface.first) {

                maxSurface = currentSurface.first;
                x = i; y = j;
                usedColor = currentSurface.second;
            }
        }

    printf("%d %d\n", x, y);
    printf("%c", usedColor);
}

int main() {

    readData();
    addSomeColors();
    if(task == 1) {
        getBiggestSurface();
    }
    else {
        getCoordinates();
    }
    return 0;
}
