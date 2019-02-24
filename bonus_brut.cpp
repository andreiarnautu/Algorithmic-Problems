/**
  *  Worg
  */
#include <cmath>
#include <climits>
#include <fstream>
#include <algorithm>

using namespace std;
ifstream fin("bonus.in");
ofstream fout("bonus.out");

unsigned long long SOLS[70];

bool Possible(unsigned long long value, int exp) {
    unsigned long long aux = 2; /* 2 < value, garantat in enunt */
    for(int i = 2; i <= exp; i++) {
        if(2 > value / aux) {
            return false;
        } else {
            aux <<= 1;
        }
    }
    return true;
}

bool checkSmaller(unsigned long long value, unsigned long long base, int exp) {
    unsigned long long aux = base;
    if(aux > value) {return false;}

    for(int i = 2; i <= exp; i++) {
        if(base > value / aux) {
            return false;
        } else {
            aux *= base;
        }
    }

    return true;
}

unsigned long long lastBase;

unsigned long long getMaxBase(unsigned long long A, int exp) {
    unsigned long long left = 2;
    unsigned long long right = lastBase;
    unsigned long long Answer = 2;

    while(left <= right) {
        unsigned long long mid = (left + right) >> 1;
        bool ok = checkSmaller(A, mid, exp);

        if(ok) {
            Answer = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return Answer;
}

unsigned long long Pow(unsigned long long base, int exp) {

    /** Apelam functia doar pentru valori la care suntem siguri ca base^exp nu da overflow */

    unsigned long long Ans = 1, aux = base;
    for(int i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            Ans = Ans * aux;
        }
        if((i << 1) <= exp) {
            aux = aux * aux;
        }
    }

    return Ans;
}

bool checkSolo(unsigned long long A, unsigned long long value) {
    if(value * value > A) {
        return false;
    }

    unsigned long long aux = value;
    int exp1 = 1;
    for(;;exp1++) {
        if(value > A / aux) {
            break;
        } else {
            aux = aux * value;
        }
    }

    A -= aux;

    int exp2 = 0;
    while(A > 0 && A % value == 0) {
        exp2 ++; A /= value;
    }

    if(A == 1 && exp2 < exp1) {
        return true;
    } else {
        return false;
    }
}

void solveTestCase() {
    unsigned long long A; fin >> A;
    unsigned long long Solution = A - 1;
    lastBase = 1LL << 32;

    SOLS[1] = A;

    for(int i = 2; i <= 5; i++) {
        if(checkSolo(A, i)) {
            Solution = min(Solution, (unsigned long long)i);
        }
    }

    for(int exp = 2; exp <= 25; exp++) {
        if(!Possible(A, exp)) {
            break;
        } else {
            unsigned long long base;
            if(exp % 2 == 0) {
                base = (long long) sqrt((long double)SOLS[exp / 2]);
            } else {
                base = getMaxBase(A, exp);
            }

            if(base <= 5) {
                break;
            }
            SOLS[exp] = base;

            unsigned long long rest = A - Pow(base, exp);

            lastBase = base;
            int Count = 0;
            while(rest % base == 0 && rest > 0) {
                rest /= base; Count ++;
            }
            if(rest == 1 && Count < exp) {
                Solution = min(Solution, base);
            }
        }
    }

   // fout << (long long) sqrt((long double)A) << '\n';
    fout << Solution << '\n';
}

int main() {
    int N; fin >> N;
    for(; N; N--) {
        solveTestCase();
    }
    return 0;
}
