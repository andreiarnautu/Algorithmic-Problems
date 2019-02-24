/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("cumpanit.in", "r", stdin);
FILE *fout = freopen("cumpanit.out", "w", stdout);

const int MAX_PRIMES = 16;

int primes[MAX_PRIMES] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
long long A, B;

vector <long long> vec, sol;
long long cnt, prod = 1;

void readData() {
    scanf("%lld%lld", &A, &B);
}

bool smaller(long long base, long long exp, long long val) {
    long long current = 1;
    for(long long i = 1; i <= exp; ++i) {
        if(val / base < current) {
            return false;
        }
        current *= base;
    }
    return true;
}

int unused;
long long current;

void Get(int index) {
    if(index == vec.size() - 1) {
        if(smaller(vec[index], unused, B / current)) {
            long long toAdd = current;
            for(int i = 1; i <= unused; ++i) {
                toAdd *= vec[index];
            }
            sol.push_back(toAdd);
        }
        return;
    }
    else {
        if(smaller(vec[index], unused, B / current)) {
            long long toAdd = 1;
            for(int i = 1; i + vec.size() - index - 1 <= unused; ++i) {
                toAdd *= vec[index];
                current *= toAdd;
                unused -= i;
                Get(index + 1);
                unused += i;
                current /= toAdd;
            }
        }
    }
}

void getNumbers() {
    /* Suma bazelor este cnt */
    /*for(vector <long long>::iterator it = vec.begin(); it != vec.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");*/
    unused = cnt;
    current = 1;
    Get(0);
}

void back(int index) {
    for(int i = 0; i < MAX_PRIMES; ++i) {
        if(index == 1 || (index > 1 && primes[i] > vec[vec.size() - 1])) {
            vec.push_back(primes[i]);
            cnt += primes[i];
            if(index > 1) {
                prod *= primes[i];
            }


            if(smaller(vec[0], cnt - vec.size() + 1, B / prod)) {
                getNumbers();
                back(index + 1);
                if(index > 1) {
                    prod /= primes[i];
                }
                cnt -= primes[i];
                vec.pop_back();
            }
            else {
                if(index > 1) {
                    prod /= primes[i];
                }
                cnt -= primes[i];
                vec.pop_back();
                return;
            }
        }
    }
}

int main() {
    readData();
    back(1);
    sort(sol.begin(), sol.end());
    for(vector <long long>::iterator it = sol.begin(); it != sol.end(); ++it) {
        if(*it >= A) {
            printf("%lld\n", *it);
        }
    }
}
