/**
  *  Worg
  */
#include <iostream>

using namespace std;

/*-------- Data --------*/
int N, B;
/*-------- --------*/

int main() {
    cin >> N >> B;

    int solutie = 0;
    while(N != 0) {
        int cifra = N % B;
        N /= B;

        if(cifra > solutie) {
            solutie = cifra;
        }
    }

    cout << solutie << '\n';
    return 0;
}
