/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("arhitectura2.in");
ofstream cout("arhitectura2.out");

const int hmax = 100000;

int n;
int f[hmax + 1];
int v[2000010];

int main() {
    //  Vom sorta valorile folosind un vector de frecventa
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        f[x] ++;
    }

    int pos = 0;

    v[0] = 0;
    for(int i = hmax; i >= 0; i--) {
        while(f[i]) {
            pos ++;
            v[pos] = i;
            f[i] --;
        }
    }
    pos ++;
    v[pos] = 0;

    for(int i = 1; i < pos; i++) {
        cout << v[i] << " ";
    }
    cout << '\n';
    for(int i = 1; i < pos; i++) {
        if(2 * v[i] == v[i - 1] + v[i + 1]) {
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }
    return 0;
}
