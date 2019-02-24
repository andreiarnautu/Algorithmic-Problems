/**
  *  Worg
  */
#include <iostream>

using namespace std;

int obtineDivizoriPari(int nr) {

    if(nr % 2 == 1) {
        return 0;
    }

    else {

        int ret = 0;
        nr /= 2;
        for(int i = 1; i * i <= nr; ++i)
            if(nr % i == 0) {

                ret++;
                if(i * i < nr) {
                    ret++;
                }
            }
        return ret;
    }
}

int main() {

    int a, b;
    cin >> a >> b;

    int nrDiv = -1, nrMin, nrMax = 0;
    for(int i = a; i <= b; ++i) {

        int currentDiv = obtineDivizoriPari(i);
        if(currentDiv > nrDiv) {
            nrDiv = currentDiv;
            nrMin = nrMax = i;
        }
        else if(currentDiv == nrDiv) {
            nrMax = i;
        }
    }

    cout << nrDiv << " " << nrMin << " " << nrMax;
}
