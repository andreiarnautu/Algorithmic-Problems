/**
  *  Worg
  */
#include <bitset>
#include <cstdio>

using namespace std;
FILE *fin = freopen("crescator3.in", "r", stdin);
FILE *fout = freopen("crescator3.out", "w", stdout);

const int buffer_dim = 1 + 100000;
const int MAX_DIF = 1 + 300000;
const int MAX_N = 1 + 100000;

/*-------- Input reader --------*/
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
int N;
int vec[MAX_N];
/*-------- Algo data --------*/
bitset< MAX_DIF > checked;
/*-------- --------*/

void ReadInput() {
    cin.GetBuffer();
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> vec[i];
    }
}

int DigitSum(int k) {
    int answer = 0;

    while(k != 0) {
        answer += k % 10;
        k /= 10;
    }

    return answer;
}

void JustSimulate() {
    int value = vec[1];

    while(value <= vec[N]) {
        checked[value - vec[1]] = true;
        value += DigitSum(value);
    }
}

void WriteOutput() {
    int answer = 0;

    for(int i = 1; i <= N; i++) {
        if(checked[vec[i] - vec[1]]) {
            answer ++;
        }
    }

    printf("%d\n", answer);
}

int main() {
    ReadInput();
    JustSimulate();
    WriteOutput();
    return 0;
}
