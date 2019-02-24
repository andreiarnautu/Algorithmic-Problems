/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("main.in");
ofstream cout("main.out");

const int MAX_N = 1 + 1000000;
const int MAX_VAL = 1 + 1000000;

/*-------- --------*/
int N;
/*-------- --------*/
bool checked[MAX_VAL];
int prime_list[MAX_VAL], count_primes;
/*-------- --------*/

void ciur() {
    checked[0] = checked[1] = 1;  /* 0 si 1 nu sunt prime */
    for(int i = 4; i < MAX_VAL; i += 2) {
        checked[i] = 1;
    }

    for(int i = 3; i * i < MAX_VAL; i += 2) {
        if(checked[i] == 0) { /* i este prim */
            for(int j = i * i; j < MAX_VAL; j += 2 * i) {
                checked[j] = 1; /* il marcam pe j ca nefiind prim */
            }
        }
    }
}

int main() {
    cin >> N;
    ciur();
    for(int i = 1; i < MAX_VAL; i++) {
        if(checked[i] == 0) { /* daca numarul e prim, il afisam */
            ++ count_primes;
            prime_list[count_primes] = i;
        }
    }

    for(int i = 1; i <= N; i++) {
        int x; cin >> x;

        for(int j = 1; j <= count_primes; j++) {
            int prim = prime_list[j];
            if(x % prim == 0) {
                int power = 0;
                while(x % prim == 0) {
                    power ++;
                    x /= prim;
                }
                cout << prim << "^" << power << " ";
            }

            if(x == 1) {
                cout << '\n';
                break;
            }
        }
    }

    return 0;
}
