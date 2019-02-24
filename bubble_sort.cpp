#include <fstream>
#include <algorithm>

using namespace std;
ifstream fin("main.in");
ofstream fout("main.out");

const int MAX_N = 1 + 100000;

int v[MAX_N];
int n;

int main() {
    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> v[i];
    }

    bool ok;
    do {
        ok = false;
        for(int i = 1; i <= n - 1; i++) {
            if(v[i] > v[i + 1]) {
                swap(v[i], v[i + 1]);
                ok = true; /* am dat peste o interschimbare */
            }
        }
    }while(ok == true);

    for(int i = 1; i <= n; i++) {
        fout << v[i] << " ";
    }
    return 0;
}
