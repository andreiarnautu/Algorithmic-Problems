/**
  *  Worg
  *
  *  Bun...hai sa vedem cum gandim problema.
  *  Primul lucru pe care il faci e sa te uiti la restrictii. Numerele sunt in intervalul [0, 1.000.000.000].
  *  Ceea ce inseamna ca numarul cu cea mai mare suma a cifrelor este 999.999.999 -> suma cifrelor 81
  *
  *  O sa tinem un vector de frecventa de la 0 la 81, unde f[i] = numarul de elemente din vector cu suma cifrelor i.
  *  Evident, vom parcurge vectorul, si vom calcula valorile din vectorul de frecventa.
  *
  *  Apoi, ce facem?
  *  Pentru fiecare suma a cifrelor de la 0 la 81, avem f[i] numere si vrem sa vedem cate perechi putem forma.
  *  Pentru asta e o formula foarte usoara, care ne spune ca sunt f[i] * (f[i] - 1) / 2 perechi care se pot forma cu suma cifrelor i.
  *
  *  Adaugam la solutie pentru fiecare i numarul de perechi, iar la final afisam solutia.
  */
#include <iostream>

using namespace std;

const int MAX_N = 1 + 200; /* dimensiunea vectorului din datele de intrare */
const int MAX_SUM = 1 + 81; /* suma maxima a cifrelor pe care o poate avea un numar */

/*-------- Input data --------*/
int N;
int vec[MAX_N];
/*-------- Algorithm data --------*/
int f[MAX_SUM];
int Solution;
/*-------- --------*/

void read_input() {
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> vec[i];
    }
}

int sum(int value) {
    int answer = 0;
    /* o functie care ne returneaza suma cifrelor unui numar dat ca si paramentru, ceva de baza */

    while(value != 0) {
        answer += value % 10;
        value /= 10;
    }

    return answer; /* returnam suma */
}

void build_f_vector() {
    /* construim vectorul de frecventa */
    /* pentru asta am facut functia ajutatoare sum() */

    for(int i = 1; i <= N; i++) {
        int x = sum(vec[i]); /* vec[i] are suma cifrelor x */
        f[x] ++; /* incrementam numarul de numere care au suma cifrelor x */
    }
}

void get_solution() {
    for(int i = 0; i <= 81; i++) {
        /* folosim formula pe care am gasit-o */
        Solution += f[i] * (f[i] - 1) / 2;
    }
    cout << Solution; /* afisam */
}

int main() {
    read_input();
    build_f_vector();
    get_solution();
    return 0;
}
