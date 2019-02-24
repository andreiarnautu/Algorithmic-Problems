/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("lru.in", "r", stdin);
FILE *fout = freopen("lru.out", "w", stdout);

const int MAX_N = 1 + 1000000 + 1;
const int SIGMA = 4;

/*-------- Input data --------*/
int test_count;
int N;
char first_config[MAX_N], last_config[MAX_N];
/*-------- Algorithm --------*/
int first_array[MAX_N], second_array[MAX_N];
int letter_cursor[SIGMA];
int letter_delay[SIGMA];

/*-------- --------*/

void ReadTestData() {
    scanf("%d", &N);
    scanf("%s", first_config + 1);
    scanf("%s", last_config + 1);
}

int GetValue(char c) {
    if(c == 'L') {
        return 0;
    } else if(c == 'R') {
        return 1;
    } else if(c == 'U'){
        return 2;
    }
}

long long SolveTest() {
    long long test_result = 0;
    int first_index = 0;

    // Convertim stringurile la vectori de intregi
    for(int i = 1; i <= N; i++) {
        first_array[i] = GetValue(first_config[i]);
        second_array[i] = GetValue(last_config[i]);
    }

    for(int i = 0; i < 3; i++) {
        int j = N;
        while(j > 0 && first_array[j] != i) {
            j --;
        }
        letter_cursor[i] = j;
    }

    // Rezolvam sirul de la dreapta la stanga
    for(int i = N; i >= 1; i--) {
        if(letter_cursor[second_array[i]] <= first_index) {  // Suntem in cazul in care trebuie sa creem litera
            test_result += i;

            for(int j = 0; j < 3; j++) {
                if(j != second_array[i]) {
                    letter_delay[j] ++;
                }
            }

            while(first_array[first_index + 1] == 3) {
                first_index ++;
            }
            first_index ++;
        } else {  // Trebuie sa facem swapuri ca sa aducem litera care ne trebuie pe pozitia curenta
            test_result += i - letter_cursor[second_array[i]] + letter_delay[second_array[i]];

            first_array[letter_cursor[second_array[i]]] = 3; // Marcam pozitia de pe care swapuim ca fiind folosita

            for(int j = 0; j < 3; j++) {
                if(j != second_array[i] && letter_cursor[j] > letter_cursor[second_array[i]]) {
                    letter_delay[j] ++;
                }
            }

            letter_cursor[second_array[i]] --;
            while(letter_cursor[second_array[i]] > first_index && first_array[letter_cursor[second_array[i]]] != second_array[i]) {
                if(letter_cursor[first_array[letter_cursor[second_array[i]]]] < letter_cursor[second_array[i]]) {
                    letter_delay[second_array[i]] --;
                }
                letter_cursor[second_array[i]] --;
            }
        }
    }

    return test_result;

}

void ClearTestData() {
    for(int i = 0; i < 3; i++) {
        letter_delay[i] = 0;
    }
}

int main() {
    for(scanf("%d", &test_count); test_count > 0; test_count --) {
        ReadTestData();
        printf("%lld\n", SolveTest());
        ClearTestData();
    }

    return 0;
}
