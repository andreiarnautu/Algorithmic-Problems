/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("nrapprime.in");
ofstream cout("nrapprime.out");

int main() {
    int n; cin >> n;
    int sol = 0;

    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        bool ok = true;

        if(x <= 1) {
            ok = false;
        }
        for(int j = 2; j * j <= x; j++) {
            if(x % j == 0) {
                ok = false; break;
            }
        }

        if(ok == true) {
            sol ++;
        }
    }
    cout << sol;
    return 0;
}
