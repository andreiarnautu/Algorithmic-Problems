/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("danger.in", "r", stdin);
FILE *fout = freopen("danger.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int bufferDim = 100000;

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
                if(++ pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++ pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

struct Line {
    int index;
    int best;
    Line(const int index, const int best) {
        this->index = index; this->best = best;
    }
    bool operator <(const Line other) const {
        if(this->best != other.best) {
            return this->best > other.best;
        } else {
            return this->index < other.index;
        }
    }
};

struct Line2 {
    int index;
    int best;
    Line2(const int index, const int best) {
        this->index = index; this->best = best;
    }
    bool operator <(const Line2 other) const {
        if(this->best != other.best) {
            return this->best < other.best;
        } else {
            return this->index < other.index;
        }
    }
};

/*-----------------------*/
int N, M;
int MAX = 0;
vector< int > mat[MAX_N];
/*-----------------------*/
vector< int > Solution[MAX_N];
int maxValue[MAX_N];
set< Line > Set;
set< Line2 > Set2;
/*-----------------------*/

void readInput() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            int x; cin.getInt(x);
            MAX = max(MAX, x << 1);
            mat[i].push_back(x);
        }
        sort(mat[i].begin(), mat[i].end());
        reverse(mat[i].begin(), mat[i].end());
    }
    for(int i = 1; i <= M; i++) {
        Solution[i].resize(N + 1);
    }
}

bool Check(unsigned int maxSum, bool Build = false) {
    for(int i = 1; i <= M; i++) {
        maxValue[i] = 0;
    }
    Set.clear();

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            Set.insert(Line(j, maxValue[j]));
        }

        for(int j = 0; j < M; j++) {
            set< Line >::iterator it = Set.lower_bound(Line(0, maxSum - mat[i][j]));

            if(it == Set.end()) {
                return false;
            } else {
                maxValue[it->index] = max(it->best, mat[i][j]);
                if(Build) {Solution[it->index][i] = mat[i][j];}
                Set.erase(it);
            }
        }
    }
    return true;
}

int solveProblem() {
    unsigned int left = 2, right = (unsigned int) MAX, Answer = right;

    while(left <= right) {
        unsigned int mid = (left + right) >> 1;
        if(Check(mid)) {
            Answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return Answer;
}

void writeOutput(unsigned int maxSum) {
    bool useless = Check(maxSum, true);
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            printf("%d ", Solution[i][j]);
        }
        printf("\n");
    }
}

void solveProblem2() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            Set2.insert(Line2(j, maxValue[j]));
        }
        for(int j = 0; j < M; j++) {
            Line2 line = *Set2.begin(); Set2.erase(Set2.begin());

            maxValue[line.index] = max(line.best, mat[i][j]);
            Solution[line.index][i] = mat[i][j];
        }
    }
}

void writeOutput2() {
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            printf("%d ", Solution[i][j]);
        }
        printf("\n");
    }
}

int main() {
    readInput();
    if(N * M <= 90000) {
        writeOutput(solveProblem());
    } else {
        solveProblem2();
        writeOutput2();
    }
    return 0;
}
