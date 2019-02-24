/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("gfact.in", "r", stdin);
FILE *fout = freopen("gfact.out", "w", stdout);

const long long MAX_P = 2000000000;
const long long MAX_Q = 30000;
const int MAX_DIV = 30;

/*------------------*/
long long P, Q;
/*------------------*/
long long primes[MAX_DIV];
long long freq[MAX_DIV];
int currentPos = 0;
/*------------------*/

void readData() {
    scanf("%lld%lld", &P, &Q);
}

void getPrimes() {
    for(long long i = 2; i * i <= P; i++) {
        if(P % i == 0) {
            primes[++currentPos] = i;
            while(P % i == 0) {
                freq[currentPos]++;
                P /= i;
            }
            freq[currentPos] *= Q;
        }
    }
    if(P > 1) {
        primes[++currentPos] = P;
        freq[currentPos] = Q;
    }
}

bool Try(long long X) {
    for(int i = 1; i <= currentPos; i++) {
        long long query = 0;
        long long current = primes[i];

        while(current <= X) {
            query += (X / current);
            current *= primes[i];
        }

        if(query < freq[i]) {
            return false;
        }
    }

    return true;
}

long long binarySearch() {
    long long left = 1, right = MAX_P * MAX_Q, answer = right;

    while(left <= right) {
        long long mid = (left + right) / 2;
        if(Try(mid)) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return answer;
}

int main() {
    readData();
    getPrimes();
    printf("%lld", binarySearch());

    return 0;
}
