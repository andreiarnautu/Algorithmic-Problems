/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <unordered_map>

using namespace std;
FILE *fin = freopen("kino.in", "r", stdin);
FILE *fout = freopen("kino.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 20000;
const int MAX_L = 1 + 50;

class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;
/*----------------------*/
int N, L;
int K[MAX_L];
int a[MAX_N][MAX_L];
/*----------------------*/
unordered_map<int,int> Map[MAX_L];
int Freq[MAX_L][MAX_N];
/*----------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(L);
    for(int i = 1; i <= L; ++i) {
        cin.getInt(K[i]);
    }
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= L; ++j) {
            cin.getInt(a[i][j]);
        }
    }
}

int Solve(int index) {

    int answer = 0;
    int count = 0;
    for(int i = 1; i <= N; ++i)
        if(a[i][index] != 0) {
            answer += count - Map[index][a[i][index]];
            Map[index][a[i][index]]++;
            count++;
        }

    int rest = N - count;
    if(K[index] >= (int)Map[index].size() + rest) {
        answer += count * rest + rest * (rest - 1) / 2;

    } else {
        for(int i = 1; i <= K[index]; ++i) {
            Freq[index][Map[index][i]]++;
        }

        int current = 0;
        for(int i = 1; i <= rest; ++i) {
            while(!Freq[index][current]) {
                current++;
            }
            answer += count - current;
            count++;
            Freq[index][current]--;
            Freq[index][current + 1]++;
        }
    }

    return answer;

}

int main() {
    clock_t startTime = clock();

    readData();
    long long SOL = 0;
    for(int i = 1; i <= L; ++i) {
        SOL += 1LL * Solve(i);
        //printf("%lld\n", SOL);
    }
    printf("%lld\n", SOL);

    clock_t finishTime = clock();
    //printf("%.3f", (float)(finishTime - startTime) / CLOCKS_PER_SEC);
}
