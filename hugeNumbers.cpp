/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int kSize = 1000;

class Huge {
public:
  int a[kSize];
  //  In vectorul a[] avem pe pozitia 0 numarul de cifre ale numarului
  //  a[1] = cifra unitatilor; a[2] = cifra zecilor; etc

  void Reset() {
    memset(a, 0, sizeof(a));  //  Toate cifrele devin 0
    a[0] = 1;  //  Valoarea numarului este 0, deci numarul cifrelor este 1
  }

  Huge() {
    Reset();
  }
}

class Huge {
public:
  int a[kSize];
  //  In vectorul a[] avem pe pozitia 0 numarul de cifre ale numarului
  //  a[1] = cifra unitatilor; a[2] = cifra zecilor; etc

  void Reset() {
    memset(a, 0, sizeof(a));  //  Toate cifrele devin 0
    a[0] = 1;  //  Valoarea numarului este 0, deci numarul cifrelor este 1
  }

  Huge() {
    Reset();
  }

  void SetValue(int x) {
    Reset();

    a[0] = 0;
    do {
      a[0]++;  //  Incrementam numarul de cifre
      a[a[0]] = x % 10;  //  Punem pe pozitia curenta ultima cifra a numarului

      x /= 10;
    }while(x != 0);
  }

  //  Adunarea a doua numere mari
  void operator +=(const Huge &other) {
    int i, t = 0;  //  t <-> transport
    for(int i = 1; i <= a[0] || i <= other.a[0] || t != 0; i++, t /= 10) {
      a[i] = (t += a[i] + other.a[i]) % 10;
    }
    a[0] = i - 1;  //  Actualizam numarul de cifre
  }

  //  Scaderea a doua numere mari
  void operator -=(const Huge &other) {
    int i, t = 0;
    for(i = 1; i <= a[0]; i++) {
      if(i <= other.a[0]) {
        a[i] -= t;
      } else {
        a[i] -= (other.a[i] + t);
      }

      if(a[i] < 0) {
        t = 1;
      } else {
        t = 0;
      }
      a[i] += t * 10;
    }

    //  Actualizam numarul de cifre
    while(a[0] > 1 && a[a[0]] == 0) {
      a[0]--;
    }
  }

  //  Inmultirea cu un numar mic
  void operator *=(const int x) {
    int i, t = 0;
    for(int i = 1; i <= a[0] || t; i++, t /= 10) {
      a[i] = (t += a[i] * x) % 10;
    }
    a[0] = i - 1;
  }

  //  Inmultirea cu un numar mare
  void operator *=(const Huge other) {
    int i, j, t;
    Huge aux;  //  Ne va trebui un numar mare auxiliar in care sa stocam raspunsul

    for(i = 1; i <= a[0]; i++) {
      for(j = 1, t = 0; j <= other.a[0] || t; j++, t /= 10) {
        aux.a[i + j - 1] = (t += aux.a[i + j - 1] + a[i] * other.a[j]) % 10;
      }

      if(i + j - 2 > aux.a[0]) {  //  Verificam daca numarul de cifre creste
        aux.a[0] = i + j - 2;
      }
    }

    Reset();
    for(int i = 0; i <= aux.a[0]; i++) {
      a[i] = aux.a[i];
    }
  }

  //  Impartim cu un numar mic
  void operator /=(const int x) {
    int i, t = 0;
    for(i = a[0]; i > 0; i--, t %= x) {
      a[i] = (t = t * 10 + a[i]) / x;
    }

    //  Numarul cifrelor e posibil sa fi scazut
    while(a[0] > 1 && a[a[0]] == 0) {
      //  Cat timp numarul are mai mult de o cifra si prima cifra e nula
      a[0]--;
    }
  }

  //  Restul unui numar mare la un numar mic
  int operator %(const int x) {
    int i, t = 0;
    for(i = a[0]; i > 0; i--) {
      t = (t * 10 + a[i]) % x;
    }
    return t;
  }

  void Write() {
    for(int i = a[0]; i > 0; i--) {
      printf("%d", a[i]);
    }
    printf("\n");
  }
};

int main() {
  Huge a; a.SetValue(1024);
  Huge b; b.SetValue(1024);
  a *= b; a.Write();
  a /= 1024; a.Write();
  int x = a % 1000; printf("%d\n", x);
	return 0;
}
