/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("main.in");
ofstream cout("main.out");

int N;

int main() {
    cin >> N;
    for(int i = 2; i <= N; i++) {
        bool ok = true;
        for(int j = 2; j * j <= i; j++) {
            if(i % j == 0) {
                ok = false;
                break;
            }
        }

        if(ok == true) {
            cout << i << " ";
        }
    }

    return 0;
}
