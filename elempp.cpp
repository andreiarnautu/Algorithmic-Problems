/**
  *  Worg
  */
#include <cmath>
#include <fstream>

using namespace std;
ifstream cin("elempp.in");
ofstream cout("elempp.out");

int digits[15];

int FirstTwo(int x) {
    int pos = 0;
    do {
        pos ++;
        digits[pos] = x % 10;
        x /= 10;
    }while(x);

    return digits[pos] * 10 + digits[pos - 1];
}

int main() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        int nr = FirstTwo(x);

        bool ok = false;
        for(int j = 1; j <= 10; j++) {
            if(j * j == nr) {
                ok = true;
            }
        }
        if(ok) {
            cout << x << " ";
        }
    }
    return 0;
}
