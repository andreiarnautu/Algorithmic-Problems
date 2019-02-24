/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
FILE *fin = freopen("parcele.in", "r", stdin);
FILE *fout = freopen("parcele.out", "w", stdout);

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
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

struct SegmentTree {
    int val, lazy;
};

struct Point {
    int x, y;
};

Point p[MAX_N];
SegmentTree sTree[4 * MAX_N];
int n, dx, dy;

vector <int> event[2 * MAX_N];
int dp[2 * MAX_N], dpAux[2 * MAX_N];
int sol;

void readData() {

    cin.getBuffer();
    cin.getInt(dx); cin.getInt(dy); cin.getInt(n);

    for(int i = 1; i <= n; ++i) {
        cin.getInt(p[i].x);
        cin.getInt(p[i].y);
    }
}

void update(int node, int left, int right, int first, int last, int cost) {

    int leftSon = node << 1, rightSon = leftSon + 1;

    if(sTree[node].lazy) {

        sTree[node].val += sTree[node].lazy;
        if(left != right) {
            sTree[leftSon].lazy += sTree[node].lazy;
            sTree[rightSon].lazy += sTree[node].lazy;
        }

        sTree[node].lazy = 0;
    }

    if(first <= left && right <= last) {

        sTree[node].val += cost;
        if(left != right) {
            sTree[leftSon].lazy += cost;
            sTree[rightSon].lazy += cost;
        }
    }

    else {

        int mid = (left + right) >> 1;
        if(first <= mid) {
            update(leftSon, left, mid, first, last, cost);
        }
        if(mid < last) {
            update(rightSon, mid + 1, right, first, last, cost);
        }

        sTree[node].val = max(sTree[leftSon].val + sTree[leftSon].lazy, sTree[rightSon].val + sTree[rightSon].lazy);
    }

}

void continueSweeping(int start, int d) {

    dp[start] = dpAux[start] = sTree[1].val;

    for(int i = start + 1; i <= 200000; ++i) {

        for(int j : event[i]) {
            update(1, 0, 100000 - d, max(0, j - d), min(100000 - d, j) , 1);
        }
        for(int j : event[i - start - 1]) {
            update(1, 0, 100000 - d, max(0, j - d), min(100000 - d, j), -1);
        }

        dp[i] = sTree[1].val;
        dpAux[i] = max(dpAux[i - 1], dp[i]);

        sol = max(sol, dp[i] + dpAux[i - start - 1]);
    }
}

void lineSweep() {

    for(int i = 1; i <= n; ++i) {
        event[p[i].x].push_back(p[i].y);
    }
    for(int i = 0; i <= dx; ++i) {
        for(int j : event[i]) {
            update(1, 0, 100000 - dy, max(0, j - dy), min(100000 - dy, j), 1);
        }
        if(i == 0) {
            dpAux[i] = sTree[1].val;
        }
        else {
            dpAux[i] = max(dpAux[i - 1], sTree[1].val);
        }
    }
    continueSweeping(dx, dy);
}

void columnSweep() {

    for(int i = 0; i <= 100000; ++i) {
        event[i].clear();
    }
    for(int i = 0; i <= 200000; ++i) {
        dp[i] = dpAux[i] = 0;
    }
    for(int i = 1; i < 4 * MAX_N; ++i) {
        sTree[i].val = sTree[i].lazy = 0;
    }
    /*-------------------------------------------*/

    for(int i = 1; i <= n; ++i) {
        event[p[i].y].push_back(p[i].x);
    }
    for(int i = 0; i <= dy; ++i) {
        for(int j : event[i]) {
            update(1, 0, 100000 - dx, max(0, j - dx), min(100000 - dx, j), 1);
        }
        if(i > 0) {
            dpAux[i] = max(dpAux[i - 1], sTree[1].val);
        }
        else {
            dpAux[0] = sTree[1].val;
        }
    }
    continueSweeping(dy, dx);
}

int main() {

    readData();
    lineSweep();
    columnSweep();
    printf("%d", sol);
    return 0;
}
