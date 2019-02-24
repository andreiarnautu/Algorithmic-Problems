/**
  *  Worg
  */
#include <queue>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
ifstream in("hack.in");
ofstream out("hack.out");

#define PII pair<int, int>
#define VI vector<int>

const int INFINIT = 1000000;
const int dx[5] = {0, 0, 1, -1};
const int dy[5] = {1, -1, 0, 0};

int getDistance(vector<string> &A, PII start) {
    int n = A.size(), m = A[0].size();
    int COUNTER = 0;

    start.first--, start.second--; // reindexam de la 0.

    queue<PII> Q;
    vector<VI> d(n, vector<int> (m, INFINIT));
    d[start.first][start.second] = 0;
    Q.push(start);

    while(!Q.empty()) {
        PII node = Q.front();
        Q.pop();

        COUNTER++;

        for(int dir = 0; dir < 4; ++dir) {
            int newX = node.first + dx[dir];
            int newY = node.second + dy[dir];
            if(newX < 0 || newX >= n || newY < 0 || newY >= m)
                continue;
            int cost = 0;
            if(A[node.first][node.second] != A[newX][newY])
                cost = 1;

            if(d[node.first][node.second] + cost < d[newX][newY]) {
                d[newX][newY] = d[node.first][node.second] + cost;
                Q.push({newX, newY});
            }
        }
    }

    return COUNTER;
}

int main() {

    int n, m, startx, starty;
    in >> n >> m >> startx >> starty;
    vector < string > A;
    string text;
    for(int i = 1; i <= n; ++i) {

        in >> text;
        A.push_back(text);
    }
    out << getDistance(A, make_pair(startx, starty));
    return 0;
}
