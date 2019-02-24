/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("cuburi3.in", "r", stdin);
FILE *fout = freopen("cuburi3.out", "w", stdout);

const int MAX_N = 1 + 4000;

struct Cube{
    int length;
    int weight;
    int index;
    Cube() {
        this->length = this->weight = this->index = 0;
    }
    Cube(const int &length, const int &weight, const int &index) {
        this->length = length; this->weight = weight; this->index = index;
    }
    bool operator <(const Cube &other) const {
        if(this->length != other.length) {
            return this->length < other.length;
        } else {
            return this->weight < other.weight;
        }
    }
};

/*------------------*/
Cube cubes[MAX_N];
int N;
/*------------------*/
int dp[MAX_N], before[MAX_N];
vector< int > vec;
/*------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        int length, weight; scanf("%d%d", &length, &weight);
        cubes[i] = Cube(length, weight, i);
    }
    sort(cubes + 1, cubes + N + 1);
}

int findBest() {
    int answer = 0, value = -1;
    for(int i = 1; i <= N; ++i) {
        if(dp[i] > value) {
            value = dp[i]; answer = i;
        }
    }
    return answer;
}

void writeSol(int index) {
    int cubeCount = 0;
    for(int i = index; i > 0; i = before[i]) {
        cubeCount++;
        vec.push_back(i);
    }
    printf("%d %d\n", cubeCount, dp[index]);
    for(vector< int >::iterator it = vec.begin(); it != vec.end(); it++) {
        printf("%d\n", cubes[*it].index);
    }
}

void runDP() {
    for(int i = 1; i <= N; i++) {
        int best = 0, index = 0;
        for(int j = 1; j < i; j++) {
            if(cubes[i].weight >= cubes[j].weight) {
                if(dp[j] > best) {
                    best = dp[j]; index = j;
                }
            }
        }
        dp[i] = best + cubes[i].length;
        before[i] = index;
    }

    writeSol(findBest());
}

int main() {
    readData();
    runDP();
    return 0;
}
