/**
  *  Worg
  */
#include <iostream>

using namespace std;

unsigned long long int valMax = 18446744073709551615;

int main() {

    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {

        unsigned long long int x, y;
        cin >> x >> y;
        if(x == 0)
            cout << "0\n";
        else if(valMax / x >= y)
            cout << x * y << '\n';
        else
            cout << "Overflow!\n";
    }
    return 0;
}
