/**
  *  Worg
  */
#include <cstdio>

//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kSize = 9;

bool A[kSize][kSize], B[kSize][kSize], C[kSize][kSize];
int config[2 * kSize];

int Value(const char c) {
    if('0' <= c && c <= '9') {
        return c - '0';
    } else if('A' <= c && c <= 'F') {
        return 10 + c - 'A';
    } else {
        return -1;  ///  Implementation detail: we have this so we don't take spaces into consideration when we get the hex config.
    }
}

void GetMatrix(bool M[kSize][kSize]) {
    int cursor = 0;
    char c;

    while(cursor <= 15) {
        scanf("%c", &c);
        int value = Value(c);
        if(value != -1) {  //  If it is not a space
            config[cursor ++] = value;
        }
    }

    int row = 1, column = 1;
    cursor = 0;
    while(row <= 8) {
        int power = (1 << 3);
        for(int i = column; i <= column + 3; i++, power >>= 1) {
            if(power & config[cursor]) {
                M[row][i] = true;
            } else {
                M[row][i] = false;
            }
        }

        cursor ++;
        if(column == 1) {
            column = 5;
        } else {
            row ++; column = 1;
        }
    }
}

void WriteMatrix(bool M[kSize][kSize]) {
    for(int i = 1; i < kSize; i++) {
        for(int j = 1; j < kSize; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

void WriteCenter(const bool A[kSize][kSize], const bool B[kSize][kSize], bool changed[kSize][kSize]) {
    for(int i = 1; i < kSize; i++) {
        for(int j = 1; j < kSize; j++) {
            if(A[i][j] != B[i][j]) {
                changed[i][j] = true;
            } else {
                changed[i][j] = false;
            }
        }
    }

    int line_max = 0, column_max = 0;
    int line_index = 0, column_index = 0;

    int count;
    for(int i = 1; i < kSize; i++) {
        count = 0;
        for(int j = 1; j < kSize; j++) {
            if(changed[i][j] == true) {
                count ++;
            } else {
                count = 0;
            }

            if(count > line_max) {
                line_index = i;
                line_max = count;
            }
        }
    }

    for(int j = 1; j < kSize; j++) {
        count = 0;
        for(int i = 1; i < kSize; i++) {
            if(changed[i][j] == true) {
                count ++;
            } else {
                count = 0;
            }

            if(count > column_max) {
                column_index = j;
                column_max = count;
            }
        }
    }

    printf("%d%d\n", line_index, column_index);
}

void CopyMatrix(bool from[kSize][kSize], bool to[kSize][kSize]) {
    for(int i = 1; i < kSize; i++) {
        for(int j = 1; j < kSize; j++) {
            to[i][j] = from[i][j];
        }
    }
}

int main() {
    const int kChangeCount = 5;
    GetMatrix(A);
    for(int i = 1; i <= kChangeCount; i++) {
        GetMatrix(B);
        WriteCenter(A, B, C);
        CopyMatrix(B, A);
    }
    return 0;
}
