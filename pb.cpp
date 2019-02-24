/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("pb.in", "r", stdin);
FILE *fout = freopen("pb.out", "w", stdout);

const int MAX_N = 1 + 10000;

/*-------------------------*/
pair< double, double > Points[MAX_N];
int N, K;
/*-------------------------*/
vector< pair< double, int > > Distances;

void readData() {
    scanf("%d%d", &N, &K);
    for(int i = 0; i < N; ++i) {
        scanf("%lf%lf", &Points[i].first, &Points[i].second);
    }
}

double getDist(int a, int b) {
    return sqrt((Points[a].first - Points[b].first) * (Points[a].first - Points[b].first) +
                (Points[a].second - Points[b].second) * (Points[a].second - Points[b].second));
}

void Solve(int index) {
    Distances.clear();

    for(int i = 0; i < N; ++i) {
        if(i != index) {
            double dist = getDist(i, index);
            Distances.push_back(make_pair(dist, i));
        }
    }

    sort(Distances.begin(), Distances.end());
    for(int i = 0; i < K; ++i) {
        printf("%d ", Distances[i].second);
    }
    printf("\n");
}

int main() {
    readData();
    for(int i = 0; i < N; ++i) {
        Solve(i);
    }

    return 0;
}
