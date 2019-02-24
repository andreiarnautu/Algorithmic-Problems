/**
  *  Worg
  *
  *  Asta chiar e usoara
  *  Citesti tot vectorul, dupa il parcurgi si pentru fiecare element vec[i], daca vec[i] % vec[N] == 0, atunci afisezi vec[i].
  */
#include <iostream>

using namespace std;

const int MAX_N = 1 + 1000; /* dimensiunea vectorului din datele de intrare */

/*-------- Input data --------*/
int N;
int vec[MAX_N];
/*-------- --------*/

void read_input() {
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> vec[i];
    }
}

void write_output() {
    for(int i = 1; i <= N; i++) {
        if(vec[i] % vec[N] == 0) {
            cout << vec[i] << " ";
        }
    }
}

int main() {
    read_input();
    write_output();
    return 0;
}
