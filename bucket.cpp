/**
  *  Worg
  */
#include <bitset>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("bucket.in", "r", stdin);
FILE *fout = freopen("bucket.out", "w", stdout);

const int MAX_N = 1 + 5000000;
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

struct Quad {
    int a, b, c, d;

    Quad(const int a, const int b, const int c, const int d) {
        this->a = a; this->b = b; this->c = c; this->d = d;
    }
};

/*---------------*/
int N, M;
bool trigger;
vector< pair< int,int > > vec;
/*---------------*/
int Mars[MAX_N];
vector< pair< int,int > > ListA, ListB;
bitset< MAX_N > ResultA(0), ResultB(0), CheckedB(0);

vector< int > Solution;
/*---------------*/

void readInput() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    for(int i = 1; i <= M; i++) {
        int a, b; cin.getInt(a); cin.getInt(b);
        vec.push_back(make_pair(a, b));
    }
}

bool cmp1(const pair< int,int > &a, const pair< int,int > &b) {
    return (a.second - a.first) > (b.second - b.first);
}

bool cmp2(const pair< int,int > &a, const pair< int,int > &b) {
    return (a.second - a.first) < (b.second - b.first);
}

void makeList() {
    int capatMin = N + 1;
    for(int i = 0; i < M - 1; i++) {
        if(vec[i].first > vec[i + 1].first && vec[i].second > vec[i + 1].second) {
            trigger = true; return;
        } else if(vec[i].first > vec[i + 1].first) {
            ListA.push_back(make_pair(vec[i].first, vec[i + 1].first));
        } else if(vec[i].first < vec[i + 1].first && vec[i].second > vec[i + 1].second) {
            ListB.push_back(make_pair(vec[i].first, vec[i + 1].first));
            capatMin = min(capatMin, vec[i + 1].first);
        }
    }

    sort(ListA.begin(), ListA.end(), cmp1);
    sort(ListB.begin(), ListB.end(), cmp2);

    for(pair< int,int > P : ListA) {
        Mars[P.first] ++;
        Mars[P.second] --;
    }

    for(int i = 1; i <= N; i++) {
        Mars[i] = Mars[i - 1] + Mars[i];
        if(Mars[i]) {
            ResultA[i] = false;
        } else {
            ResultA[i] = true;
        }
    }

    for(int i = 1; i <= N; i++) {
        if(i < capatMin) {
            ResultB[i] = true;
        } else {
            ResultB[i] = false;
        }
    }


}

void solveProblem() {
    if(trigger) {return;}

    for(int i = 1; i <= N; i++) {
        if(ResultA[i] == true) {
            bool ok = true;
            for(int j = 2 * i; j <= N; j += i) {
                if(ResultA[j] == false) {
                    ok = false; break;
                }
            }
            ResultA[i] = ok;
        }
    }

    for(int i = N; i >= 1; i--) {
        if(ResultB[i]) {
            bool ok = false;
            for(int j = 2 * i; j <= N; j += i) {
                if(ResultB[j]) {
                    ok = true; break;
                }
            }

            if(!ok) {
                ok = true;
                for(pair< int,int > P : ListB) {
                    int a = (P.first - 1) / i + 1;
                    int b = (P.second - 1) / i + 1;

                    if(a == b) {
                        ok = false; break;
                    }
                }
            }
            ResultB[i] = ok;
        }
    }

    for(int i = 1; i <= N; i++) {
        if(ResultA[i] && ResultB[i]) {
            Solution.push_back(i);
        }
    }
}


void writeOutput() {
    printf("%d\n", (int)Solution.size());
    for(int i : Solution) {
        printf("%d ", i);
    }
}

int main() {
    readInput();
    makeList();
    solveProblem();
    writeOutput();
    return 0;

    
}
