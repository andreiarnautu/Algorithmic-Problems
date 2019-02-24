/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
FILE *fin = freopen("padure.in", "r", stdin);
FILE *fout = freopen("padure.out", "w", stdout);

const int bufferDim = 1 + 100000;
const int MAX_N = 1 + 1000;
const int dx[] = {-1, 1,  0, 0};
const int dy[] = { 0, 0, -1, 1};


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

/*-----------------------*/
int N, M, x0, y0, x1, y1;
int mat[MAX_N][MAX_N];
/*-----------------------*/
int dist[MAX_N][MAX_N];
vector< pair< int,int > > Queue[2];
/*-----------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    cin.getInt(x0); cin.getInt(y0); cin.getInt(x1); cin.getInt(y1);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin.getInt(mat[i][j]);
            dist[i][j] = -1; /* initializare */
        }
    }
}

bool inTheMatrix(int x, int y) {
    return (1 <= x && x <= N && 1 <= y && y <= M);
}

void Expand(vector< pair< int,int > > &vec) {
    int pos = 0;
    while(pos < (int)vec.size()) {
        int x = vec[pos].first;
        int y = vec[pos].second;

        for(int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if(inTheMatrix(newX, newY) && dist[newX][newY] == -1 && mat[newX][newY] == mat[x][y]) {
                vec.push_back(make_pair(newX, newY));
                dist[newX][newY] = dist[x][y];
            }
        }

        pos++;
    }
}

void getNext(vector< pair< int,int > > &A, vector< pair< int,int > > &B) {
    for(vector< pair< int,int > >::iterator it = A.begin(); it != A.end(); it++) {
        int x = it->first;
        int y = it->second;
        for(int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if(inTheMatrix(newX, newY) && dist[newX][newY] == -1 && mat[newX][newY] != mat[x][y]) {
                B.push_back(make_pair(newX, newY));
                dist[newX][newY] = dist[x][y] + 1;
            }
        }
    }
    A = B;
    B.clear();
}

void solveTask() {
    dist[x0][y0] = 0;
    Queue[0].push_back(make_pair(x0, y0));
    Expand(Queue[0]);

    while(dist[x1][y1] == -1) {
        getNext(Queue[0], Queue[1]);
        Expand(Queue[0]);
    }
}

void writeData() {
    printf("%d", dist[x1][y1]);
}

int main() {
    readData();
    solveTask();
    writeData();
    return 0;
}
