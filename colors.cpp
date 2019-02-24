/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("colors.in", "r", stdin);
FILE *fout = freopen("colors.out", "w", stdout);

const int kMaxN = 1 + 1000000 + 10;
const int mod = 666013;

/*-------- Input data --------*/
int N;
char colors[kMaxN];
/*-------- Algorithm data --------*/
int fact[kMaxN * 2], inv_mod[mod];
int last_even, even, odd, catalan;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    scanf("%s", colors + 1);
}

int Power(int base, int exp) {
    int answer = 1, aux = base;
    for(int i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = (1LL * answer * aux) % mod;
        }
        aux = (1LL * aux * aux) % mod;
    }
    return answer;
}

void PrecalcFact() {
    fact[0] = 1;
    for(int i = 1; i < 2 * kMaxN; i++) {
        if(i % mod == 0) {
            fact[i] = fact[i - 1] * (i / mod);
        } else {
            fact[i] = 1LL * fact[i - 1] * i % mod;
        }
    }
    for(int i = 1; i < mod; i++) {
        inv_mod[i] = Power(i, mod - 2);
    }
}

int GetCatalan(int n) {
    ///  Catalan(n) = (2n)! / n! * (n+1)!
    int answer;
    int k1 = (2 * n) / mod;
    int k2 = n / mod + (n + 1) / mod;
    if(k1 > k2) {
        answer = 0;
    } else {
        answer = (1LL * fact[2 * n] * inv_mod[fact[n]] % mod * inv_mod[fact[n + 1]] % mod);
    }
    return answer;
}

void CountEvenAndOdd() {
    ///  La pasul n : odd = numarul de arbori cu n noduri, ultimul nod aflandu-se pe un nivel impar
    ///               even = numarul de arbori cu n noduri, ultimul nod aflandu-se pe un nivel par (last_even = even(n-1))
    ///               catalan = Catalan(n)

    //  La pasul 0:
    even = 1; odd = 0; catalan = 1;
    int inv_mod_2 = Power(2, mod - 2);

    for(int i = 1; i < N; i++) {
        catalan = GetCatalan(i);
        even = 1LL * (catalan - even + mod) % mod;
        if(even % 2 == 0) {
            even >>= 1;
        } else {
            even = (1LL * even * inv_mod_2 % mod);
        }
    }

    odd = (catalan - even + mod) % mod;
}

void WriteOutput() {
    //colors[N] = 'V';

    if('V' == colors[N]) {
        printf("%d\n", even);
    } else {
        printf("%d\n", odd);
    }
}

int main() {
    ReadInput();
    //N = 666016;
    PrecalcFact();
    CountEvenAndOdd();
    WriteOutput();
    return 0;
}
