#include <fstream>

using namespace std;
ifstream cin("main.in");
ofstream cout("main.out");

const int MAX_M = 1 + 350000;

int N, M;
int v[MAX_M];
int pos;

int main() {
    cin >> N >> M;

    for(int i = 1; i <= M; i++) {
        int op, x;
        cin >> op >> x;

        if(op == 1) {  //  Daca trebuie sa inseram un numar in lista
            pos ++;
            v[pos] = x;
        } else {  //  Trebuie sa raspundem la o intrebare
            bool ok = false;
            for(int j = 1; j <= pos; j++) {
                if(x % v[j] == 0) {
                    ok = true; break;
                }
            }
            if(ok) {
                cout << "BOLTZ\n";
            } else {
                cout << x << '\n';
            }
        }
    }
}
