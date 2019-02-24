/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("demolish.in", "r", stdin);
FILE *fout = freopen("demolish.out", "w", stdout);

const int MAX_N = 1 + 500000;
const int bufferDim = 50000;
const int MAX_INF = 2000000000;

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

struct Event {
    int left, right, cost, pos;

    Event(const int &left, const int &right, const int &cost, const int &pos) {
        this->left = left;
        this->right = right;
        this->cost = cost;
        this->pos = pos;
    }
};

vector <Event> add[MAX_N], elim[MAX_N];

int arbInt[4 * MAX_N], lazy[4 * MAX_N], pos[4 * MAX_N];
int m, n, dx, dy;

int sol = MAX_INF, X, Y;

void readData() {

    cin.getBuffer();

    int f;
    cin.getInt(m); cin.getInt(n); cin.getInt(f); cin.getInt(dx); cin.getInt(dy);

    for(int i = 1; i <= f; ++i) {

        int x1, y1, x2, y2, c;
        cin.getInt(x1); cin.getInt(y1); cin.getInt(x2); cin.getInt(y2); cin.getInt(c);

        add[x1].push_back(Event(y1, y2, c, 0));
        elim[x2].push_back(Event(y1, y2, c, 0));
    }
}

void update(int node, int left, int right, int first, int last, int cost) {

    int leftSon = node * 2, rightSon = node * 2 + 1;


    if(!pos[node]) {
        pos[node] = left;
    }

    if(lazy[node] != 0) {
        /* verificam daca nodul trebuie actualizat */

        arbInt[node] += lazy[node];
        if(left != right) {
            lazy[leftSon] += lazy[node];
            lazy[rightSon] += lazy[node];
        }

        lazy[node] = 0;
    }
    if(left > right || right < first || last < left) {
        return;
    }

    if(first <= left && right <= last) {
        /* daca intervalul curent este continut complet */

        arbInt[node] += cost;
        if(left != right) {
            lazy[leftSon] += cost;
            lazy[rightSon] += cost;
        }
        return;
    }

    int mid = (left + right) / 2;

    if(first <= mid) {
        update(leftSon, left, mid, first, last, cost);
    }
    if(mid < last) {
        update(rightSon, mid + 1, right, first, last, cost);
    }

    /* updatam intervalul curent pe baza fiilor */
    if(!pos[leftSon]) {
        pos[leftSon] = left;
    }
    if(!pos[rightSon]) {
        pos[rightSon] = mid + 1;
    }
    if(arbInt[leftSon] + lazy[leftSon] <= arbInt[rightSon] + lazy[rightSon]) {
        arbInt[node] = arbInt[leftSon] + lazy[leftSon];
        pos[node] = pos[leftSon];
    }
    else {
        arbInt[node] = arbInt[rightSon] + lazy[rightSon];
        pos[node] = pos[rightSon];
    }
}

void initialize() {
    /* initializam arborele de intervale */

    /* arborele de intervale se face pe un vector "S", unde S[i] = suma pe intervalul de coloane [i + dy - 1] */

    for(int i = 0; i < dx; ++i)
        for(Event event : add[i]) {
            update(1, 0, n - dy, max(0, event.left - dy + 1), min(n - dy, event.right - 1), event.cost);
        }
}

void continueSweeping() {

    sol = arbInt[1];
    X = 0;
    Y = pos[1];

    /* continuam baleierea */
    for(int line = dx + 1; line <= m; line++) {
        /* unde ajunge linia maxima a parcelei */
        if(!add[line - 1].size() && !elim[line - dx].size())
            continue;


        for(Event event : add[line - 1]) {
            update(1, 0, n - dy, max(0, event.left - dy + 1), min(n - dy, event.right - 1), event.cost);
        }

        /* linia minima a parcelei este line - dx */
        for(Event event : elim[line - dx]) {
            update(1, 0, n - dy, max(0, event.left - dy + 1), min(n - dy, event.right - 1), -event.cost);
        }

        if(arbInt[1] < sol) {
            sol = arbInt[1];
            X = line - dx;
            Y = pos[1];
        }
    }

    printf("%d\n", sol);
    printf("%d %d %d %d", X, Y, X + dx, Y + dy);
}

int main() {

    readData();
    initialize();
    continueSweeping();
    return 0;
}
