#include <fstream>

using namespace std;
ifstream cin("minmax.in");
ofstream cout("minmax.out");

int main() {
    int minim = 2000000000, maxim = -2000000000;
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        if(x < minim) {
            minim = x;
        }
        if(x > maxim) {
            maxim = x;
        }
    }
    cout << minim << " " << maxim;
    return 0;
}
