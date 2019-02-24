/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

FILE *fin = freopen("becuri.in", "r", stdin);
FILE *fout = freopen("becuri.out", "w", stdout);

const int MAX_N = 1 + 500;
const int MAX_INF = 0x3fffffff;

/*-------- Input data --------*/
int N, M;
bool bulb[MAX_N][MAX_N];
/*-------- Algorithm data --------*/
bool switched[MAX_N];
vector<int > switched_lines[2], switched_columns[2];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            scanf("%d", &bulb[i][j]);
        }
    }
}

int CountSwitches(const bool first_line_switch, const bool where) {
    int line_switches = first_line_switch;
    int col_switches = 0;
    bool possible = true;

    if(first_line_switch == true) {
        switched_lines[where].push_back(1);
    }

    for(int j = 1; j <= M; j++) {
        if(bulb[1][j] != first_line_switch) {
            col_switches ++;
            switched[j] = true;
            switched_columns[where].push_back(j);
        } else {
            switched[j] = false;
        }
    }

    for(int i = 2; i <= N; i++) {
        int crt_line_switch = (bulb[i][1] + switched[1]) % 2;

        for(int j = 2; j <= M; j++) {
            if(crt_line_switch != (bulb[i][j] + switched[j]) % 2) {
                possible = false;
            }
        }

        line_switches += crt_line_switch;
        if(crt_line_switch) {
            switched_lines[where].push_back(i);
        }
    }

    if(line_switches % 2 != col_switches % 2) {
        possible = false;
    }

    if(possible == false) {
        return MAX_INF;
    } else {
        return std::max(line_switches, col_switches);
    }
}

void WriteBulbs(const bool from) {
    for(int i = 0; i < (int)std::min(switched_lines[from].size(), switched_columns[from].size()); i++) {
        printf("%d %d\n", switched_lines[from][i], switched_columns[from][i]);
    }

    if(switched_lines[from].size() > switched_columns[from].size()) {
        for(int i = (int)switched_columns[from].size(); i < (int)switched_lines[from].size(); i++) {
            printf("%d %d\n", switched_lines[from][i], 1);
        }
    } else if(switched_lines[from].size() < switched_columns[from].size()) {
        for(int i = (int)switched_lines[from].size(); i < (int)switched_columns[from].size(); i++) {
            printf("%d %d\n", 1, switched_columns[from][i]);
        }
    }
}

int main() {
    ReadInput();
    int count_1 = CountSwitches(false, 0);
    int count_2 = CountSwitches(true, 1);
    if(std::min(count_1, count_2) == MAX_INF) {
        printf("-1\n");
    } else {
        printf("%d\n", std::min(count_1, count_2));
        if(count_1 < count_2) {
            WriteBulbs(0);
        } else {
            WriteBulbs(1);
        }
    }

    return 0;
}
