/**
  *  Worg
  */
#include <iostream>

using namespace std;

int cifra[6];

int main() {

    /* P.S. : problema asta este de backtracking in mod normal */

    for(int i = 10000; i <= 56789; ++i) {

        int copie = i;
        for(int j = 5; j > 0; --j) {

            cifra[j] = copie % 10;
            copie /= 10;
        }
        bool ok = true;
        for(int j = 5; j > 1; --j)
            if(cifra[j] <= cifra[j - 1])
                ok = false;
        if(ok) {

            for(int j = 1; j <= 5; ++j)
                cout << cifra[j];
            for(int j = 4; j >= 1; --j)
                cout << cifra[j];
            cout << '\n';
        }
    }
    return 0;
}
