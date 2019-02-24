/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("indep.in", "r", stdin); FILE *fout = freopen("indep.out", "w", stdout);

const int kMaxDigits = 600;
const int kMaxValue = 1000 + 1;
const int kMaxN = 500 + 1;

class Huge {
public:
    int v[kMaxDigits];

    Huge() {
        memset(v, 0, sizeof(v));
        v[0] = 1;
    }

    void operator *=(const int &value) {
        int i, t;
        for(i = 1, t = 0; i <= v[0] || t != 0; i++, t /= 10) {
            v[i] = (t += value * v[i]) % 10;
        }
        v[0] = i - 1;
    }

    void operator +=(const int value) {
        int i, t;
        for(i = 1, t = value; i <= v[0] || t != 0; i++, t /= 10) {
            v[i] = (t += v[i]) % 10;
        }
        v[0] = i - 1;
    }

    void operator +=(const Huge &other) {
        int i, t;
        for(i = 1, t = 0; i <= this->v[0] || i <= other.v[0] || t != 0; i++, t /= 10) {
            v[i] = (t += this->v[i] + other.v[i]) % 10;
        }
        v[0] = i - 1;
    }

    void operator -=(const Huge &other) {
        int i, t;
        for(i = 1, t = 0; i <= this->v[0]; i++) {
            v[i] -= (i <= other.v[0] ? other.v[i] : 0) + t;
            v[i] += (t = (v[i] < 0)) * 10;
        }

        while((int)v[0] > 1 && v[(int)v[0]] == 0) {
            v[0] --;
        }
    }

    void Print() {
        for(int i = v[0]; i > 0; i--) {
            printf("%d", v[i]);
        }
        printf("\n");
    }
};

/*-------- Data --------*/
int N;
int v[kMaxN];
int pinex[kMaxValue];
Huge power[kMaxN];
/*-------- --------*/

void ComputePinex() {
    for(int i = 2; i < kMaxValue; i++) {
        if(pinex[i] == 0) {
            for(int j = i; j < kMaxValue; j += i) {
                pinex[j] ++;
            }
        }
    }

    //!  Numbers with primes at powers > 1 don't matter
    for(int i = 2; i * i < kMaxValue; i++) {
        for(int j = 1; i * i * j < kMaxValue; j++) {
            pinex[i * i * j] = 0;
        }
    }
}

void ReadInput() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }
}

void ComputePowers() {
    power[1].v[0] = power[1].v[1] = 1;
    for(int i = 2; i <= N; i++) {
        power[i] = power[i - 1];
        power[i] *= 2;
        power[i] += 1;
    }
}

void ComputeAnswer() {
    Huge ans = power[N];

    for(int i = 2; i < kMaxValue; i++) {
        if(pinex[i] != 0) {
            int freq = 0;
            for(int j = 0; j < N; j++) {
                freq += (v[j] % i == 0);
            }

            if(freq != 0) {
                if(pinex[i] % 2 == 1) {
                    ans -= power[freq];
                } else {
                    ans += power[freq];
                }
            }
        }
    }

    ans.Print();
}

int main() {
    ComputePinex();

    ReadInput();

    ComputePowers();

    ComputeAnswer();
	return 0;
}
