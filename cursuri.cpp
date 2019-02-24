#include <fstream>
#include <algorithm>

using namespace std;
ifstream cin("cursuri.in");
ofstream cout("cursuri.out");

struct Interval {
    int a, b;
};

/*-------- Date de intrare --------*/
int C, N, K;
Interval intervale[1000 + 1];
/*-------- Datele algoritmului --------*/
Interval sala[1000 + 1];
/*-------- --------*/


bool comp(Interval x, Interval y) {
    return x.b < y.b;
}

bool comp2(Interval x, Interval y) {
    return x.a < y.a;
}

int main() {
    cin >> C >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> intervale[i].a >> intervale[i].b;
    }
    sort(intervale + 1, intervale + N + 1, comp);

    if(C == 1) {
        for(int i = 1; i <= K; i++) {
            sala[i].a = sala[i].b = 0;
        }

        int numar_intervale_alese = 0;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= K; j++) {
                if(sala[j].b <= intervale[i].a) {
                    numar_intervale_alese ++;
                    sala[j] = intervale[i];
                    //  cout << "Am pus intervalul " << intervale[i].a << " " << intervale[i].b << " in sala " << j << "\n";
                    break;
                }
            }
        }
        cout << numar_intervale_alese << '\n';
    } else if(C == 2) {
        sort(intervale + 1, intervale + N + 1, comp2);
        int t_max = 0;
        for(int i = 1; i <= N; i++) {
            t_max = max(t_max, intervale[i].b - intervale[i].a);
        }

        for(int t = t_max; t >= 1; t--) {
            for(int i = 1; i <= N; i++) {
                intervale[i].b = intervale[i].a + t;
            }
            for(int i = 1; i <= K; i++) {
                sala[i].a = sala[i].b = 0;
            }

            int numar_intervale_alese = 0;
            for(int i = 1; i <= N; i++) {
                for(int j = 1; j <= K; j++) {
                    if(sala[j].b <= intervale[i].a) {
                        numar_intervale_alese ++;
                        sala[j] = intervale[i];
                        //  cout << "Am pus intervalul " << intervale[i].a << " " << intervale[i].b << " in sala " << j << "\n";
                        break;
                    }
                }
            }

            if(numar_intervale_alese == N) {
                cout << t << '\n';
                break;
            }
        }
    }


    return 0;
}
