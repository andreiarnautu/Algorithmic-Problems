/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("partii.in", "r", stdin);
FILE *fout = freopen("partii.out", "w", stdout);

const int MAX_N = 1 + 1000 + 1;
const int buffer_dim = 1 + 100000;

/*-------- Input Reader --------*/
class inputReader {
private:
        char buffer[buffer_dim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void GetBuffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;
/*-------- Input data --------*/
int N, M;
int height[MAX_N][MAX_N];
/*-------- Dynamic Programming --------*/
int left[MAX_N][MAX_N], right[MAX_N][MAX_N], up[MAX_N][MAX_N], down[MAX_N][MAX_N];
/*-------- --------*/

void ReadInput() {
    cin.GetBuffer();
    cin >> N; cin >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> height[i][j];
        }
    }
}

void RunDP() {
    //  Up
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(i == 1 || height[i][j] <= height[i - 1][j]) {
                up[i][j] = 1;
            } else {
                up[i][j] = up[i - 1][j] + 1;
            }
        }
    }

    // Down
    for(int i = N; i >= 1; i--) {
        for(int j = 1; j <= M; j++) {
            if(i == N || height[i][j] <= height[i + 1][j]) {
                down[i][j] = 1;
            } else {
                down[i][j] = down[i + 1][j] + 1;
            }
        }
    }

    //  Left
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(j == 1 || height[i][j] <= height[i][j - 1]) {
                left[i][j] = 1;
            } else {
                left[i][j] = left[i][j - 1] + 1;
            }
        }
    }

    //  Right
    for(int i = 1; i <= N; i++) {
        for(int j = M; j >= 1; j--) {
            if(j == M || height[i][j] <= height[i][j + 1]) {
                right[i][j] = 1;
            } else {
                right[i][j] = right[i][j + 1] + 1;
            }
        }
    }
}

void WriteOutput() {
    int answer = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            answer = max(answer, left[i][j] + right[i][j] + up[i][j] + down[i][j] - 3);
        }
    }
    printf("%d\n", answer);
}

void Test() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            printf("%d ", right[i][j]);
        }
        printf("\n");
    }
}

int main() {
    ReadInput();
    RunDP();
    //Test();
    WriteOutput();
    return 0;
}
