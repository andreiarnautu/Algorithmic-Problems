/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <utility>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int MAX_N = 1 + 10000;

/*-------- Input data --------*/
int N;
int capital[MAX_N];
/*-------- Set --------*/
set< pair< int,int > > Set;
/*-------- --------*/

void readInput() {
    for(int i = 1; i <= N; i++) {
        scanf("%d", &capital[i]);
        Set.insert(make_pair(capital[i], i));
    }
}

void anotherStep() {
    pair< int,int > Pair = *Set.begin();
    Set.erase(Set.begin());

    int left = Pair.second - 1;
    int right = Pair.second + 1;

    if(left == 0) {
        left = N;
    }
    if(right == N + 1) {
        right = 1;
    }

    Set.erase(Set.find(make_pair(capital[left], left)));
    Set.erase(Set.find(make_pair(capital[right], right)));

    capital[left] += Pair.first;
    capital[right] += Pair.first;
    capital[Pair.second] -= 2 * Pair.first;

    Set.insert(make_pair(capital[Pair.second], Pair.second));
    Set.insert(make_pair(capital[left], left));
    Set.insert(make_pair(capital[right], right));
}

int main() {

    /* while( scanf("%d", &N) ) {} */

    while( 69 ) {
        scanf("%d", &N);
        if(N == 0) {
            return 0;
        }
        readInput();
        int stepCount = 0;
        while(Set.begin()->first < 0) {
            anotherStep();
            stepCount ++;
        }
        N = 0;
        printf("%d\n", stepCount);
    }

    return 0;
}
