/**
  *  Worg
  */
#include <iostream>

using namespace std;

unsigned long long int valMax = 18446744073709551615;

int main() {

    int n, m;
    bool ok;

    cin >> n;
    for(int i = 1; i <= n; ++i) {

        cin >> m;
        unsigned long long int x = 0, rest;
        ok = true;

        for(int j = 1; j <= m; ++j) {

            unsigned long long int a, b, rezultat = 1;
            cin >> a >> b;

            rest = valMax - x;
            for(int k = 1; k <= b && ok == true; ++k) {

                if(a != 0 && rest / a >= rezultat)
                    rezultat *= a;
                else if(a != 0)
                    ok = false;
                else
                    rezultat = 0;
            }
            x += rezultat;
        }
        if(ok == false)
            cout << "Overflow!\n";
        else
            cout << x << '\n';
    }
    return 0;
}
