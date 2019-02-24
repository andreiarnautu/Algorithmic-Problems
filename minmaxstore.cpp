/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("minmaxstore.in", "r", stdin);
FILE *fout = freopen("minmaxstore.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 100000;

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

int N, M;
int type[MAX_N];

vector <int> vec[MAX_N];

void adauga(vector <int> &x, vector <int> &y) {
    for(vector <int>::iterator it = y.begin(); it != y.end(); ++it) {
        x.push_back(*it);
    }
}

void update() {
    int x, y;
    cin.getInt(x); cin.getInt(y);

    if(x == y) {
        if(type[x] == 0) {
            return;
        }
        else {
            vec[x].clear(); type[x] = 3;
        }
        return;
    }


    /* type == 0 (initial)
       type == 1 (minim)
       type == 2 (maxim)
       type == 3 (distrus)
                            */

    if(type[x] == 1 && type[y] == 1) {
        adauga(vec[x], vec[y]);
        vec[y].clear();
        type[y] = 3;
    }
    else if(type[x] == 2 && type[y] == 2) {
        adauga(vec[y], vec[x]);
        vec[x].clear();
        type[x] = 3;
    }
    else if(type[x] == 1 && type[y] == 2) {
        return;
    }
    else if(type[x] == 2 && type[y] == 1) {
        vec[x].clear();
        vec[y].clear();
        type[x] = type[y] = 3;
    }
    else if(type[x] == 3 && type[y] == 1) {
        adauga(vec[x], vec[y]);
        type[x] = 1;
        vec[y].clear(); type[y] = 3;
    }
    else if(type[x] == 1 && type[y] == 3) {
        return;
    }
    else if(type[x] == 3 && type[y] == 2) {
        return;
    }
    else if(type[x] == 2 && type[y] == 3) {
        adauga(vec[y], vec[x]);
        type[y] = 2;
        vec[x].clear(); type[x] = 3;
    }
    else if(type[x] == 0 && type[y] == 1) {
        adauga(vec[x], vec[y]);
        type[x] = 1;
        vec[y].clear(); type[y] = 3;
    }
    else if(type[x] == 1 && type[y] == 0) {
        adauga(vec[x], vec[y]);
        type[y] = 2;
    }
    else if(type[x] == 0 && type[y] == 2) {
        adauga(vec[y], vec[x]);
        type[x] = 1;
    }
    else if(type[x] == 2 && type[y] == 0) {
        adauga(vec[y], vec[x]);
        vec[x].clear(); type[x] = 3;
    }
    else if(type[x] == 0 && type[y] == 3) {
        type[x] = 1;
    }
    else if(type[x] == 3 && type[y] == 0) {
        type[y] = 2;
    }
    else if(type[x] == 3 && type[y] == 3) {
        return;
    }
    else if(type[x] == 0 && type[y] == 0) {
        vec[x].push_back(vec[y][0]);
        vec[y].push_back(vec[x][0]);
        type[x] = 1; type[y] = 2;
    }
}

bool checked[MAX_N];

bool verifica(int x, int givenType) {
    if(type[x] != givenType) {
        return false;
    }
    else {
        for(int i = 1; i <= N; ++i) {
            checked[i] = false;
        }
        for(vector <int>::iterator it = vec[x].begin(); it != vec[x].end(); ++it) {
            checked[*it] = true;
        }
        bool ok = true;
        for(int i = 1; i <= N; ++i) {
            if(!checked[i]) {
                ok = false;
            }
        }
        return ok;
    }
}

int main() {
    cin.getBuffer();
    int T;

    for(cin.getInt(T); T; T--) {
        cin.getInt(N); cin.getInt(M);
        for(int i = 1; i <= N; ++i) {
            type[i] = 0;
            vec[i].clear();
            vec[i].push_back(i);
        }
        for(int i = 1; i <= M; ++i) {
            update();
        }
        int x, y; cin.getInt(x); cin.getInt(y);
        if(N == 1) {
            if(x == 1 && y == 1) {
                printf("Popeala");
            }
            else if(x == 1) {
                printf("Popel");
            }
            else if(y == 1) {
                printf("Popita");
            }
            else {
                printf("Comisarul");
            }
            printf("\n");
        }
        else {
            bool answer1 = verifica(x, 1);
            bool answer2 = verifica(y, 2);
            if(answer1 && answer2) {
                printf("Popeala\n");
            }
            else if(answer1) {
                printf("Popel\n");
            }
            else if(answer2) {
                printf("Popita\n");
            }
            else {
                printf("Comisarul\n");
            }
        }
    }
    return 0;
}
