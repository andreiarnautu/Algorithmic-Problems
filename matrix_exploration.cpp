/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <utility>

//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1 + 1000;
const int kMaxInf = 0x3fffffff;

/*-------- Input data --------*/
int N, M, K;
char matrix[kMaxN][kMaxN];
/*-------- Lee --------*/
std::queue<std::pair<int, int > > queue;
int minDist[kMaxN][kMaxN];

std::vector<std::pair<int, int > > directions;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d%d", &N, &M, &K);
    for(int i = 1; i <= N; i++) {
        scanf("%s", matrix[i] + 1);
    }
}

void Initialize() {
    directions.push_back({-1, 0}); directions.push_back({1, 0}); directions.push_back({0, 1}); directions.push_back({0, -1});
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            minDist[i][j] = kMaxInf;
        }
    }
    for(int i = 1; i <= K; i++) {
        int x, y; scanf("%d%d", &x, &y);
        minDist[x][y] = 0; queue.push({x, y});
    }
}

bool Valid(std::pair<int, int > cell) {
    return 0 < cell.first && cell.first <= N && 0 < cell.second && cell.second <= M && matrix[cell.first][cell.second] != '#';
}

long long Lee() {
    Initialize();
    while(!queue.empty()) {
        auto cell = queue.front(); queue.pop();
        for(auto direction : directions) {
            auto newCell = cell;
            newCell.first += direction.first; newCell.second += direction.second;

            if(Valid(newCell) && minDist[newCell.first][newCell.second] == kMaxInf) {
                minDist[newCell.first][newCell.second] = minDist[cell.first][cell.second] + 1;
                queue.push(newCell);
            }
        }
    }

    long long answer = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(minDist[i][j] != kMaxInf) {
                answer += minDist[i][j];
            }
        }
    }
    return answer;
}

int main() {
    ReadInput();
    printf("%lld\n", Lee());
    return 0;
}
