/**
  *  Worg
  */
#include <cstdio>
#include <bitset>
#include <vector>

using namespace std;
FILE *fin = freopen("hideandseek.in", "r", stdin);
FILE *fout = freopen("hideandseek.out", "w", stdout);

const int MAX_N = 1 + 1000000;
const int bufferDim = 100000;

/*-------- Input reader --------*/
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

        void operator >>(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++ pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++ pos == bufferDim)
                    getBuffer();
            }
        }

        void operator >>(long long &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++ pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10LL + 1LL * buffer[pos] - 1LL * '0';
                if(++ pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

/*-------- Input data --------*/
int N;
long long x, y;
int A[MAX_N], B[MAX_N];
/*-------- Euclid --------*/
long long a, b;
/*-------- Permutation cycles --------*/
bitset< MAX_N > checked;
vector< vector< int > > Cycles;
vector< int > cycle;
/*-------- Final permutations --------*/
int Final[2][MAX_N];
/*-------- --------*/

void readInput() {
    cin.getBuffer();
    cin >> N; cin >> x; cin >> y;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for(int i = 1; i <= N; i++) {
        cin >> B[i];
    }
}

long long Euclid(long long x, long long y, long long &a, long long &b) {
    if(!y) {
        a = 1; b = 0;
        return a;
    } else {
        long long a0, b0;
        long long div = Euclid(y, x % y, a0, b0);
        a = b0;
        b = a0 - (x / y) * b0;

        return div;
    }
}

void getPermutationCycles(int *perm) {
    Cycles.clear();
    for(int i = 1; i <= N; i++) {
        checked[i] = false;
    }

    for(int i = 1; i <= N; i++) {
        if(!checked[i]) {
            cycle.push_back(i);
            checked[i] = true;

            int j = i;
            while(!checked[perm[j]]) {
                cycle.push_back(perm[j]);
                checked[perm[j]] = true;
                j = perm[j];
            }

            Cycles.push_back(cycle);
            cycle.clear();
        }
    }
}

void shiftCycles(int index, long long k) {
    for(vector< int > vec : Cycles) {
        for(int i = 0; i < (int)vec.size(); i++) {
            long long where = ((long long) (k % vec.size())) % vec.size();
            where = (where + i) % vec.size();

            if(where < 0) {
                where += vec.size();
            }
            Final[index][vec[i]] = vec[where];
        }
    }

    /*printf("%lld\n", k);
    for(int i = 1; i <= N; i++) {
        printf("%d ", Final[index][i]);
    }*/
}

void getSolution() {
    for(int i = 1; i <= N; i++) {
        printf("%d ", Final[1][Final[0][i]]);
    }
}

int main() {
    readInput();
    Euclid(x, y, a, b);
    getPermutationCycles(A);
    shiftCycles(0, a);
    getPermutationCycles(B);
    shiftCycles(1, b);
    getSolution();
    return 0;
}
