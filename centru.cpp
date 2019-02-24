/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::queue;
using std::vector;
using std::pair;
using std::make_pair;

FILE *fin = freopen("centru.in", "r", stdin);
FILE *fout = freopen("centru.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_DIST = (MAX_N << 1);
const int dx[] = {0,  0, 1, -1};
const int dy[] = {1, -1, 0,  0};


/*-------- Input data --------*/
int N, K;
vector<pair<int, int > > centres;
/*-------- Lee --------*/
queue<pair<int, int > > my_queue;
int min_dist[MAX_N][MAX_N];
/*-------- Distances --------*/
vector<pair<int, int > > cells[MAX_DIST];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= K; i++) {
        int u, v; scanf("%d%d", &u, &v);
        centres.push_back(make_pair(u, v));
    }
}

bool in_matrix(const int x, const int y) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

void RunLeeAlgorithm() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            min_dist[i][j] = MAX_DIST;
        }
    }

    for(pair<int, int > p : centres) {  //  Lee cu plecari multiple, introducem toate centrele initiale in coada
        min_dist[p.first][p.second] = 0;
        my_queue.push(make_pair(p.first, p.second));
    }

    while(!my_queue.empty()) {
        pair<int, int > cell = my_queue.front(); my_queue.pop();

        for(int i = 0; i < 4; i++) {
            int x = cell.first + dx[i];
            int y = cell.second + dy[i];

            if(in_matrix(x, y) && min_dist[x][y] == MAX_DIST) {
                min_dist[x][y] = min_dist[cell.first][cell.second] + 1;
                my_queue.push(make_pair(x, y));
            }
        }
    }
}

void ProcessCells() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cells[min_dist[i][j]].push_back(make_pair(i, j));
        }
    }
}

int GetAnswer() {
    int dist = MAX_DIST - 1;
    while(cells[dist].empty()) {
        dist --;
    }

    pair<int, int > corner_1 = make_pair(MAX_DIST, MAX_DIST);
    pair<int, int > corner_2 = make_pair(-MAX_DIST, -MAX_DIST);

    bool ok = true;
    do {
        for(pair<int, int > cell : cells[dist]) {
            corner_1.first = std::min(corner_1.first, cell.first + cell.second);
            corner_1.second = std::min(corner_1.second, cell.first - cell.second);
            corner_2.first = std::max(corner_2.first, cell.first + cell.second);
            corner_2.second = std::max(corner_2.second, cell.first - cell.second);
        }

        int length = 1 + std::max(corner_2.first - corner_1.first, corner_2.second - corner_1.second);
        if(length % 2 == 0) {
            length /= 2;
        } else {
            length /= 2; length ++;
        }

        if(length >= dist) {
            ok = false;
        } else {
            dist --;
        }
    }while(ok && dist >= 0);

    return dist;
}

int main() {
    ReadInput();
    RunLeeAlgorithm();
    ProcessCells();
    printf("%d\n", std::max(0, GetAnswer()));
    return 0;
}
