/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

using namespace std;
FILE *fin = freopen("ghicit.in", "r", stdin);
FILE *fout = freopen("ghicit.out", "w", stdout);

const int MAX_N = 1 + 51211;
const int MAX_LOG = 1 + 16;
int ZERO = 0;

/*-------- Input data --------*/
char text[MAX_N];
int length;
/*-------- Suffix Arrays --------*/
int Index[MAX_LOG][MAX_N];
int count[MAX_N], id_1[MAX_N], id_2[MAX_N];
/*-------- --------*/

void read_input() {
    fread(text, 1, MAX_N, stdin); length = strlen(text);
    for(int i = 0; i < length; i++) {
        if(text[i] == '\n') {
            length = i; break;
        }
    }
}

int &index(const int &i, const int &j) {
    if(j < MAX_N) {
        return Index[i][j];
    } else {
        return ZERO;
    }
}

void compute_suffix_arrays() {
    text[length ++] = 1;

    for(int i = 0; i < length; i++) {
        count[text[i]] ++;
    }
    for(int i = 1, j = 0; i < 256; i++) {
        if(count[i]) {
            count[i] = j ++;
        }
    }
    for(int i = 0; i < length; i++) {
        index(0, i) = count[(int)text[i]];
    }

    for(int j = 1, L = 1; j < MAX_LOG; j++, L <<= 1) {
        /* construim id_1 */
        for(int i = 0; i < length; i++) {
            count[i] = 0;
        }
        for(int i = 0 ; i < length; i++) {
            count[index(j - 1, i + L)] ++;
        }
        for(int i = 1; i < length; i++) {
            count[i] += count[i - 1];
        }
        for(int i = length - 1; i >= 0; i--) {
            id_1[-- count[index(j - 1, i + L)]] = i;
        }

        /** construim id_2 */
        for(int i = 0; i < length; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < length; i++) {
            count[index(j - 1, i)] ++;
        }
        for(int i = 1; i < length; i++) {
            count[i] += count[i - 1];
        }
        for(int i = length - 1; i >= 0; i--) {
            id_2[-- count[index(j - 1, id_1[i])]] = id_1[i];
        }

        /** construim etajul curent din matricea Index[][] */
        index(j, id_2[0]) = 0;
        for(int i = 1; i < length; i++) {
            if(index(j - 1, id_2[i]) == index(j - 1, id_2[i - 1]) &&
                    index(j - 1, id_2[i] + L) == index(j - 1, id_2[i - 1] + L)) {
                index(j, id_2[i]) = index(j, id_2[i - 1]);
            } else {
                index(j, id_2[i]) = index(j, id_2[i - 1]) + 1;
            }
        }
    }

    for(int i = 0; i < length; i++) {
        id_1[index(MAX_LOG - 1, i)] = i;
    }
}

int LCP(int a, int b) {
    int answer = 0;
    for(int i = MAX_LOG - 1, L = (1 << (MAX_LOG - 1)); i >= 0; i--, L >>= 1) {
        if(index(i, a) == index(i, b)) {
            answer += L;
            a += L;
            b += L;
        }
    }
    return answer;
}

long long get_answer() {
    long long answer = 1LL * (length) * (length - 1) / 2;

    for(int i = 1; i < length; i++) {
        int current_LCP = LCP(id_1[i], id_1[i - 1]);
        answer -= current_LCP;
    }

    return answer;
}

int main() {
    read_input();
    compute_suffix_arrays();                                    /** O(N * log(N)) */
    printf("%lld\n", get_answer());                             /** O(N * log(N)) */
    return 0;
}
