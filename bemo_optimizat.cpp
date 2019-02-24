/**
  *  Worg
  */
#include <bitset>
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("bemo.in", "r", stdin);
FILE *fout = freopen("bemo.out", "w", stdout);

const int buffer_dim = 1 + 10000;
const int MAX_N = 1 + 1500;


/*-------- Input Reader --------*/
class inputReader {
private:
        char buffer[buffer_dim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void get_buffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    get_buffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    get_buffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;

/*-------- Input data --------*/
struct position {
    short int row, column;

    position() {}

    position(short int _row, short int _column) {
        this->row = _row;
        this->column = _column;
    }
};
int R, C;
position where[MAX_N * MAX_N];
/*-------- Algorithm Data --------*/
bitset< MAX_N > marked[MAX_N];

int solution[MAX_N << 1];
int solution_size;
/*-------- --------*/

void read_input() {
    cin.get_buffer();
    cin >> R; cin >> C;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            int x; cin >> x;
            where[x] = position(i, j);
        }
    }
}

bool in_matrix(int row, int column) {
    return (1 <= row && row <= R && 1 <= column && column <= C);
}

void mark_rectangle(int row, int column, int row_add, int column_add) {
    while(in_matrix(row, column) && !marked[row][column]) {
        for(int j = column; in_matrix(row, j) && !marked[row][j]; j += column_add) {
            marked[row][j] = true;
        }
        row += row_add;
    }
}

void solve_problem() {
    const int max_value = R * C;
    for(int i = 1; i <= max_value; i++) {
        if(!marked[where[i].row][where[i].column]) {
            solution[++solution_size] = i;
            mark_rectangle(where[i].row + 1, where[i].column - 1, +1, -1);
            mark_rectangle(where[i].row - 1, where[i].column + 1, -1, +1);
        }
    }
}

bool comp(const int &a, const int &b) {
    if(where[a].row != where[b].row) {
        return where[a].row < where[b].row;
    } else {
        return where[a].column < where[b].column;
    }
}

void write_output() {
    sort(solution + 1, solution + solution_size + 1, comp);
    for(int i = 1; i <= solution_size; i++) {
        printf("%d ", solution[i]);
    }
}

int main() {
    read_input();
    solve_problem();
    write_output();
    return 0;
}
