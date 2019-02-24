/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("impartire.in", "r", stdin);
FILE *fout = freopen("impartire.out", "w", stdout);

const int MAX_N = 1 + 100000 + 10;

int N, M;

unsigned char divider_list[MAX_N];
short int occured_at[MAX_N];
int current_pos = 0, repeat_pos = 0, last_rest = -1;

void readData() {
    scanf("%d%d", &N, &M);
}

void divide() {
    while(N) {
        N *= 10;
        int current_divider = N / M;
        int current_rest = N % M;
      // printf("%d %d\n", current_rest, current_divider);

        if(occured_at[current_rest]) {
            repeat_pos = current_pos;
            last_rest = current_rest;
            divider_list[++current_pos] = current_divider;
            break;
        } else {
            divider_list[++current_pos] = current_divider;
            occured_at[current_rest] = current_pos;
            N -= M * current_divider;
            if(!N) {
                break;
            }
        }

    }
}

void write_non_period(int first, int last) {
    for(; first <= last; first++) {
        printf("%d", divider_list[first]);
    }
}

void write_period(int first, int last) {
    printf("(");
    for(; first <= last; first++) {
        printf("%d", divider_list[first]);
    }
    printf(")");
}

void writeData() {
    printf("0.");
    if(last_rest != -1) {
        if(divider_list[occured_at[last_rest]] == divider_list[current_pos]) {
            write_non_period(1, occured_at[last_rest] - 1);
            write_period(occured_at[last_rest], current_pos - 1);
        } else {
            write_non_period(1, occured_at[last_rest]);
            write_period(occured_at[last_rest] + 1, current_pos);
        }
    } else {
        write_non_period(1, current_pos);
    }
}

int main() {
    readData();
    divide();
    writeData();
    return 0;
}
