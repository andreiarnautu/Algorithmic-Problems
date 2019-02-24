/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using std::sort;
using std::vector;
FILE *fin = freopen("matrice2.in", "r", stdin);
FILE *fout = freopen("matrice2.out", "w", stdout);

const int MAX_N = 1 + 300;
const int MAX_Q = 1 + 20000;
const int Dx[] = {-1, 1, 0,  0};
const int Dy[] = { 0, 0, 1, -1};
const int dSize = 4;

struct Cell {
    int x, y, val;

    Cell(const int &x, const int &y, const int &val) {
        this->x = x; this->y = y; this->val = val;
    }

    bool operator <(const Cell &other) const {
        return this->val > other.val;
    }
};

struct Query {
    int x1, y1, x2, y2;
    int answer, index;

    Query(const int &x1, const int &y1, const int &x2, const int &y2, const int &index) {
        this->x1 = x1; this->y1 = y1; this->x2 = x2; this->y2 = y2; this->index = index;
        this->answer = 0; /* initial */
    }

    bool operator <(const Query &other) const {
        return this->answer > other.answer;
    }
};

class disjointHeaps {
private:
        int father[MAX_N * MAX_N];
        int N;
public:
        void Construct(const int &N) {
            this->N = N;

            for(int i = 1; i <= N; i++) {
                for(int j = 1; j <= N; j++) {
                    const int crtIndex = (i - 1) * N + j;
                    father[crtIndex] = crtIndex;
                }
            }
        }

        int Group(int index) {
            if(index != father[index]) {
                father[index] = Group(father[index]);
            }
            return father[index];
        }

        void Unite(const int &x1, const int &y1, const int &x2, const int &y2) {
            int indexA = Group( (x1 - 1) * N + y1 );
            int indexB = Group( (x2 - 1) * N + y2 );
            father[indexA] = indexB;
        }

        bool sameGroup(const int &x1, const int &y1, const int &x2, const int &y2) {
            int g1 = Group( (x1 - 1) * N + y1 );
            int g2 = Group( (x2 - 1) * N + y2 );
            return (g1 == g2);
        }

        void Reset() {
            for(int i = 1; i <= N; i++) {
                for(int j = 1; j <= N; j++) {
                    const int crtIndex = (i - 1) * N + j;
                    father[crtIndex] = crtIndex;
                }
            }
        }
} disjointSolver;

/*------------------------*/
int N, Q;
int mat[MAX_N][MAX_N];
/*------------------------*/
vector< Query > Queries;
vector< Cell > Cells;
/*------------------------*/
int queryAnswer[MAX_Q];
/*------------------------*/

void readInput() {
    scanf("%d%d", &N, &Q);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            scanf("%d", &mat[i][j]);
            Cells.push_back(Cell(i, j, mat[i][j]));
        }
    }
    for(int i = 1; i <= Q; i++) {
        int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        Queries.push_back(Query(x1, y1, x2, y2, i));
    }
}

void solveQueries() {
    disjointSolver.Construct(N);
    sort(Cells.begin(), Cells.end());

    for(int crtPow = (1 << 20); crtPow > 0; crtPow >>= 1) {
        sort(Queries.begin(), Queries.end());
        disjointSolver.Reset();

        /* we try to add (+= crtPow) to every query answer */
        int Cursor = 0; /* for cells */

        for(int i = 0; i < (int)Queries.size(); i++) {
            const int Limit = Queries[i].answer + crtPow;

            while(Cursor < (int)Cells.size() && Cells[Cursor].val >= Limit) {
                int x = Cells[Cursor].x;
                int y = Cells[Cursor].y;
                for(int i = 0; i < dSize; i++) {
                    int newX = x + Dx[i];
                    int newY = y + Dy[i];
                    if(mat[newX][newY] >= mat[x][y]) {
                        disjointSolver.Unite(x, y, newX, newY);
                    }
                }
                Cursor++;
            }

            if(disjointSolver.sameGroup(Queries[i].x1, Queries[i].y1, Queries[i].x2, Queries[i].y2)) {
                Queries[i].answer += crtPow;
            }
        }
    }

    for(vector< Query >::iterator it = Queries.begin(); it != Queries.end(); it++) {
        queryAnswer[it->index] = it->answer;
    }
}

void writeOutput() {
    for(int i = 1; i <= Q; i++) {
        printf("%d\n", queryAnswer[i]);
    }
}

int main() {
    readInput();
    solveQueries();
    writeOutput();
    return 0;
}
