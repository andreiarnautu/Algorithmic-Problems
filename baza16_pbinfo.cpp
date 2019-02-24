/**
  *  Worg
  */
#include <iostream>

using namespace std;

const int MAX_CIFRE = 1 + 10;

/*-------- Date --------*/
int N;
int nr_cifre;
int cifre[MAX_CIFRE];
/*-------- --------*/

int main() {
    cin >> N;

    /* aplicam din nou metoda resturilor */
    while(N != 0) {
        int cifra = N % 16;
        N /= 16;

        nr_cifre ++;
        cifre[nr_cifre] = cifra;
    }

    /* vom afisa din nou de la coada la cap */
    for(int i = nr_cifre; i >= 1; i--) {
        if(cifre[i] >= 10) {
            /* daca valoarea cifrei curente este mai mare sau egala decat 10, inseamna ca trebuie sa o codificam cu o litera */
            char c = 'A' + cifre[i] - 10;
            cout << c;
        } else {
            cout << cifre[i];
        }
    }

    cout << '\n';
    return 0;
}
