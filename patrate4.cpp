/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using std::vector;

FILE *fin = freopen("patrate4.in", "r", stdin);
FILE *fout = freopen("patrate4.out", "w", stdout);

const int kMaxN = 1 + 1024;

/*-------- Structures --------*/
struct Square {
    int x, y, l;
    Square() {}
    Square(const int _x, const int _y, const int _l) {
        x = _x; y = _y; l = _l;
    }
};
/*-------- Input data --------*/
int N, K;
bool is_black[kMaxN][kMaxN];
/*-------- Algo data --------*/
int black_count[kMaxN][kMaxN];
vector<Square > squares;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; i++) {
        int x, y; scanf("%d%d", &x, &y);
        is_black[x][y] = true;
    }
}
void BuildMatrix() {
    for(int i = 1; i < kMaxN; i++) {
        for(int j = 1; j < kMaxN; j++) {
            black_count[i][j] = black_count[i - 1][j] + black_count[i][j - 1] - black_count[i - 1][j - 1] + is_black[i][j];
        }
    }
}

void GetSquares(int x, int y, int l) {
    int x1 = x + l - 1;
    int y1 = y + l - 1;

    int inside_count = black_count[x1][y1] - black_count[x1][y - 1] - black_count[x - 1][y1] + black_count[x - 1][y - 1];
    if(K * inside_count >= l * l && K * inside_count < 4 * l * l) {  //  Am gasit un patrat valid
        squares.push_back(Square(x, y, l));
    } else if(inside_count != 0) {  //  Daca mai are sens sa continuam
        GetSquares(x, y, l / 2);
        GetSquares(x + l / 2, y, l / 2);
        GetSquares(x, y + l / 2, l / 2);
        GetSquares(x + l / 2, y + l / 2, l / 2);
    }
}

void WriteOutput() {
    printf("%d\n", (int)squares.size());
    for(auto square : squares) {
        printf("%d %d %d\n", square.x, square.y, square.l);
    }
}

int main() {
    ReadInput();
    BuildMatrix();
    GetSquares(1, 1, kMaxN - 1);
    WriteOutput();
    return 0;
}
