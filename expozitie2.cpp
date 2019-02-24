/**
  *  Worg
  */
#include <cstdio>
#include <utility>

using namespace std;
FILE *fin = freopen("expozitie2.in", "r", stdin);
FILE *fout = freopen("expozitie2.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_Q = 1 + 1000000;
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
/*-------- Input data --------*/
int N, Q, y;
int x[MAX_N];
pair< int,int > query[MAX_Q];
/*-------- Greater --------*/
int firstRotation[MAX_N], firstApp[MAX_N];
/*-------- Lower --------*/
int mat[MAX_N][MAX_N];
int when[MAX_N];
/*----------------*/

void readInput() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(Q); cin.getInt(y);
    for(int i = 1; i <= N; i++) {
        cin.getInt(x[i]);
    }
    for(int i = 1; i <= Q; i++) {
        cin.getInt(query[i].first); cin.getInt(query[i].second);
    }
}

int getXSum() {
    int Answer = 0;
    for(int i = 1; i <= N; i++) {
        Answer += x[i];
    }
    return Answer;
}

void solveGreater() {
    firstRotation[1] = y; firstApp[0] = N + 1; firstApp[1] = 1;
    for(int i = 2; i <= N; i++) {
        firstRotation[i] = firstRotation[i - 1] - x[i - 1];
        firstApp[i] = i;
    }
    int rest = firstRotation[N] - x[N];
    firstRotation[0] = rest;

    for(int i = 1; i <= Q; i++) {
        int Time = query[i].first;
        int Room = query[i].second;
        if(Time < firstApp[Room]) {
            printf("0\n");
        } else {
            long long Answer = 1LL * firstRotation[Room] + 1LL * ((Time - firstApp[Room]) / (N + 1)) * rest;
            printf("%lld\n", Answer);
        }
    }
}

void solveLower(int xSum) {
    for(int i = 1; i <= N; i++) {
        firstApp[i] = i;
    }
    firstApp[0] = 0;

    mat[1][0] = 0; mat[1][1] = y;
    when[0] = 1;

    for(int i = 2; i <= N; i++) {
        if(mat[1][i - 1] >= x[i - 1]) {
            mat[1][i] = mat[1][i - 1] - x[i - 1];
        } else {
            mat[1][i] = mat[1][i - 1];
        }
    }

    /*for(int i = 0; i <= N; i++) {
        printf("%d ", mat[1][i]);
    }
    printf("\n");*/

    bool isCycle = false;
    int start, finish;
    for(int i = 2; i <= 200; i++) {
        if(mat[i - 1][N] >= x[N]) {
            mat[i][0] = mat[i - 1][N] - x[N];
        } else {
            mat[i][0] = mat[i - 1][N];
        }

        if(when[mat[i][0]]) {
            isCycle = true;
            start = when[mat[i][0]];
            finish = i - 1;
            break;
        } else {
            when[mat[i][0]] = i;
            mat[i][1] = mat[i][0] + y;
            if(mat[i][1] >= xSum) {
                finish = i - 1; break;
            }
            for(int j = 2; j <= N; j++) {
                if(mat[i][j - 1] >= x[j - 1]) {
                    mat[i][j] = mat[i][j - 1] - x[j - 1];
                } else {
                    mat[i][j] = mat[i][j - 1];
                }
            }

            /*for(int j = 0; j <= N; j++) {
                printf("%d ", mat[i][j]);
            }
            printf("\n");*/
        }
    }

    if(isCycle) {
        //printf("%d %d", start, finish);
        //return;
       // while(1);
        for(int i = 1; i <= Q; i++) {
            int Time = query[i].first;
            int Room = query[i].second;

            if(Time < firstApp[Room]) {
                printf("0\n");
            } else {
                /** calculam timpul petrecut inainte de intrarea in ciclu */
                int beforeCycle = 0;
                if(start > 1) {
                    beforeCycle = N + (start - 2) * (N + 1);
                } else {
                    beforeCycle= -1;
                }
                /** cazul 1: Time este inainte de intrarea in ciclu */
                if(Time < beforeCycle + firstApp[Room] + 1) {
                  //  printf("Inainte: ");
                    int level = 1 + (Time - firstApp[Room]) / (N + 1);
                    printf("%d\n", mat[level][Room]);
                } else {
                    /** cazul 2: Time este dupa intrarea in ciclu si vrem sa vedem in care perioada trebuie pus */
                  //  printf("Dupa: ");
                    Time -= (beforeCycle);
                    int cycleTime = (N + 1) * (finish - start + 1); /* calculam timpul necesar parcurgerii ciclului */
                   // printf("CICLU %d; ", cycleTime);
                    if(Time % cycleTime == 0) {
                        Time = cycleTime;
                    } else {
                        Time %= cycleTime;
                    }

                    Time--; /* mai scadem 1 fiindca noi indexam initial aparitiile de la 0 */
                    if(Time < firstApp[Room]) {
                        printf("%d\n", mat[finish][Room]);
                    } else {
                        int level = (Time - firstApp[Room]) / (N + 1);
                        printf("%d\n", mat[start + level][Room]);
                    }
                }
            }
        }
    }
}

int main() {
    readInput();
    int xSum = getXSum();
    if(y >= xSum) {
        solveGreater();
    } else {
        solveLower(xSum);
    }
    return 0;
}
