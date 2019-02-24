/**
  *  Worg
  */
#include <iostream>

using namespace std;

int Oglindit(int x) {
    int sol = 0;
    do {
        sol = sol * 10 + x % 10;
        x /= 10;
    }while(x != 0);
    return sol;
}

int main() {
    int n, x;
    cin >> n >> x;
    x = Oglindit(x);
    for(int i = 2; i <= n; i++) {
        int y; cin >> y;
        if(y == x) {
            cout << "DA"; return 0;
        }
    }
    cout << "NU"; return 0;
}
