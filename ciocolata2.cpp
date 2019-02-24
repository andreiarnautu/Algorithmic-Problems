/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <fstream>
#include <cstring>

using std::pair;
using std::vector;

FILE *fin = freopen("ciocolata2.in", "r", stdin);

const int kMaxN = 1 + 70 + 1;
const int dx[] = {-1, 1,  0, 0};
const int dy[] = { 0, 0, -1, 1};

class Writer {
  public:
    Writer(const char *name):
        m_stream(name) {
        memset(m_buffer, 0, sizeof(m_buffer));
        m_pos = 0;
    }

    Writer& operator<<(int a) {
        int many = 0;
        do {
            digit_buffer[many++] = a % 10 + '0';
            a /= 10;
        } while (a > 0);
        for (int i = many - 1; i >= 0; --i)
            putchar(digit_buffer[i]);
        return *this;
    }

    Writer& operator<<(const char *s) {
        for (; *s; ++s)
            putchar(*s);
        return *this;
    }

    ~Writer() {
        m_stream.write(m_buffer, m_pos);
    }

  private:
    void putchar(char c) {
        m_buffer[m_pos++] = c;
        if (m_pos == kBufferSize) {
            m_stream.write(m_buffer, m_pos);
            m_pos = 0;
        }
    }

    static const int kBufferSize = 32768;
    std::ofstream m_stream;
    char m_buffer[kBufferSize];
    char digit_buffer[30];
    int m_pos;
} fout("ciocolata2.out");

/*-------- Input data --------*/
int N, M, K;
char matrix[kMaxN][kMaxN];  //  Codificam in forma L-R-U-D
/*-------- Matrix & Question Marks --------*/
char old_matrix[kMaxN][kMaxN];
vector<pair<int, int > > question_marks;

/*-------- DFS --------*/
pair<int, int > start;
vector<pair<int, int > > stack, path;
bool checked[kMaxN][kMaxN];
bool dfs_finished;
/*-------- Changed pieces --------*/
vector<pair<pair<int, int >, pair<int, int > > > deleted_pieces, added_pieces;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d%d", &N, &M, &K);
    fout << N * M / 2 << "\n";
    if(N % 2 == 0) {  //  Numar par de linii
        for(int j = 1; j <= M; j++) {
            for(int i = 1; i < N; i += 2) {
                fout << i << " " << j << " " << i + 1 << " " << j << "\n";
                matrix[i][j] = 'U'; matrix[i + 1][j] = 'D';
            }
        }
    } else {  //  Numar par de coloane
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j < M; j += 2) {
                fout << i << " " << j << " " << i << " " << j + 1 << "\n";
                matrix[i][j] = 'L'; matrix[i][j + 1] = 'R';
            }
        }
    }
}

void CopyMatrix(char to[kMaxN][kMaxN], char from[kMaxN][kMaxN]) {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            to[i][j] = from[i][j];
        }
    }
}

void OutputMatrix(char m[kMaxN][kMaxN]) {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
}

void ReadAndMarkCuts() {
    int marked_number; scanf("%d", &marked_number);
    for(int i = 1; i <= marked_number; i++) {
        int x, y; scanf("%d%d", &x, &y);
        if(matrix[x][y] == 'L') {
            matrix[x][y + 1] = '?';
        } else if(matrix[x][y] == 'R') {
            matrix[x][y - 1] = '?';
        } else if(matrix[x][y] == 'U') {
            matrix[x + 1][y] = '?';
        } else if(matrix[x][y] == 'D') {
            matrix[x - 1][y] = '?';
        }

        matrix[x][y] = '*';
    }

    question_marks.clear();
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(matrix[i][j] == '?') {
                question_marks.push_back(std::make_pair(i, j));
            }
        }
    }
}

bool ValidPosition(int x, int y) {
    return (1 <= x && x <= N && 1 <= y && y <= M && matrix[x][y] != '*');
}

void DFS(int x, int y) {
    checked[x][y] = true;
    stack.push_back(std::make_pair(x, y));
    if(dfs_finished) {
        stack.pop_back();
        return;
    }

    for(int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(ValidPosition(new_x, new_y) && !checked[new_x][new_y]) {
            stack.push_back(std::make_pair(new_x, new_y));
            checked[new_x][new_y] = true;
            if(matrix[new_x][new_y] == 'L') {
                DFS(new_x, new_y + 1);
            } else if(matrix[new_x][new_y] == 'R') {
                DFS(new_x, new_y - 1);
            } else if(matrix[new_x][new_y] == 'U') {
                DFS(new_x + 1, new_y);
            } else if(matrix[new_x][new_y] == 'D') {
                DFS(new_x - 1, new_y);
            } else if(matrix[new_x][new_y] == '?') {
                path = stack; dfs_finished = true; return;
            }
            stack.pop_back();
        }
    }
    stack.pop_back();
}

bool SolveQuestionMarks() {
    for(auto question_mark : question_marks) {
        if(matrix[question_mark.first][question_mark.second] == '?') {  //  Daca nu am cuplat deja semnul curent, incercam sa il cuplam
            for(int i = 1 ; i <= N; i++) {
                for(int j = 1; j <= M; j++) {
                    checked[i][j] = false;
                }
            }
            stack.clear();
            dfs_finished = false; start = question_mark;
            DFS(question_mark.first, question_mark.second);

            if(!dfs_finished) {
                return false;
            } else {
                for(int i = 0; i + 1 < (int)path.size(); i += 2) {
                    pair<int, int > now = path[i], next = path[i + 1];
                    if(next.first - now.first == 1) {
                        matrix[now.first][now.second] = 'U'; matrix[next.first][next.second] = 'D';
                    } else if(next.first - now.first == -1) {
                        matrix[now.first][now.second] = 'D'; matrix[next.first][next.second] = 'U';
                    } else if(next.second - now.second == 1) {
                        matrix[now.first][now.second] = 'L'; matrix[next.first][next.second] = 'R';
                    } else {
                        matrix[now.first][now.second] = 'R'; matrix[next.first][next.second] = 'L';
                    }
                }
            }
        }
    }
    return true;
}

void SpotAndOutputDifferences() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(old_matrix[i][j] != matrix[i][j] && (old_matrix[i][j] == 'L' || old_matrix[i][j] == 'U')) {
                if(old_matrix[i][j] == 'L') {
                        deleted_pieces.push_back(std::make_pair(std::make_pair(i, j), std::make_pair(i, j + 1)));
                }
                else {
                        deleted_pieces.push_back(std::make_pair(std::make_pair(i, j), std::make_pair(i + 1, j)));
                }
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(old_matrix[i][j] != matrix[i][j] && (matrix[i][j] == 'L' || matrix[i][j] == 'U')) {
                if(matrix[i][j] == 'L') {
                    added_pieces.push_back(std::make_pair(std::make_pair(i, j), std::make_pair(i, j + 1)));
                }
                else {
                    added_pieces.push_back(std::make_pair(std::make_pair(i, j), std::make_pair(i + 1, j)));
                }

            }
        }
    }

    fout << (int)deleted_pieces.size() << "\n";
    for(auto piece : deleted_pieces) {
       fout << piece.first.first << " " << piece.first.second << " " << piece.second.first << " " << piece.second.second << "\n";
    }

    fout << (int)added_pieces.size() << "\n";
    for(auto piece : added_pieces) {
        fout << piece.first.first << " " << piece.first.second << " " << piece.second.first << " " << piece.second.second << "\n";
    }
    added_pieces.clear();
    deleted_pieces.clear();
}

int main() {
    ReadInput();
    for(int i = 1; i <= K; i++) {
        CopyMatrix(old_matrix, matrix);
        ReadAndMarkCuts();
        bool ok = SolveQuestionMarks();
        if(!ok) {
            fout << "-1\n"; return 0;
        } else {
            SpotAndOutputDifferences();
        }
    }
    return 0;
}
