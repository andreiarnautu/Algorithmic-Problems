/**
  *  Worg
  */
#include <queue>
#include <cstdio>

using namespace std;
FILE *fin = freopen("memory006.in", "r", stdin);
FILE *fout = freopen("memory006.out", "w", stdout);

const int MAX_K = 1 + 10000;

/*-------- Input data --------*/
int N, K;

queue< char > my_queue;
/*-------- --------*/

void read_data() {
    scanf("%d%d", &N, &K);
}

void run_algorithm() {
    int solution = 0;
    int exponents_sum = 0;

    for(int i = 1; i <= N; i++) {
        long long x; scanf("%lld", &x);

        int exponent = 0;
        while((x & 1) == 0) {
            x >>= 1;
            exponent ++;
        }

        if(x != 1) {
            while(!my_queue.empty()) {
                my_queue.pop();
            }
            exponents_sum = 0;
        } else {
            exponents_sum += exponent;
            my_queue.push(exponent);
            while(exponents_sum > K && !my_queue.empty()) {
                char to_substract = my_queue.front();
                my_queue.pop();

                exponents_sum -= to_substract;
            }
            if(exponents_sum == K) {
                solution ++;
            }
        }
    }

    printf("%d\n", solution);
}

int main() {
    read_data();
    run_algorithm();

    return 0;
}
