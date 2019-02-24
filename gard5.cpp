/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>

using namespace std;
FILE *fin = freopen("gard5.in", "r", stdin);
FILE *fout = freopen("gard5.out", "w", stdout);

const int MAX_N = 1 + 100 + 1;

/*-------- Input data --------*/
int N;
int height[MAX_N];
/*-------- Algorithm --------*/
bool fixed[MAX_N];
vector<pair<int, int > > areas;

int total_sum;
long long number_of_ways = 1;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &height[i]);
    }
}

void GetFixedOnes() {
    height[0] = 0;
    height[N + 1] = N + 1;
    for(int i = 1; i <= N; i++) {
        fixed[i] = true;
        for(int j = i - 1; j >= 0; j--) {
            if(height[i] < height[j]) {
                fixed[i] = false; break;
            }
        }
    }
}

void GetAreas() {
    for(int i = 1; i < N; i++) {
        if(fixed[i]) {
            int j = i + 1;
            while(!fixed[j] && j <= N) {
                j ++;
            }
            if(i + 1 <= j - 1) {
                areas.push_back(make_pair(i + 1, j - 1));
            }
        }
    }
}

void ProcessAreas() {
    for(pair<int, int > p : areas) {
        vector< int > vec;
        for(int i = p.first; i <= p.second; i++) {
            vec.push_back(height[i]);
        }
        sort(vec.begin(), vec.end());

        for(int i = 0; i < (int)vec.size() - 1; i++) {
            total_sum += (vec[i + 1] - vec[i]) * 2;
        }

        total_sum += (height[p.first - 1] + height[p.second + 1]) - (vec[0] + vec.back());
        if(vec.size() > 1) {
            number_of_ways <<= 1;
        }
    }
}

void WriteOutput() {
    printf("%d %lld\n", total_sum, number_of_ways);
}

int main() {
    ReadInput();
    GetFixedOnes();
    GetAreas();
    ProcessAreas();
    WriteOutput();
    return 0;
}
