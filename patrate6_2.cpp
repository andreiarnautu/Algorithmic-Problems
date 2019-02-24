#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("patrate6.in");
ofstream out("patrate6.out");

int N;
int V[100013], Stack;


int main()
{
    in >> N;
    for(int i = 0 ; i < N ; ++i )
        in >> V[i];
    sort(V , V + N);
    int cnt , p = 0, valmax, Diff, ok = 1, aux, Pow, nr;
    valmax = V[N - 1];

    while( V[p] < valmax )
    {
        cnt = 1 + Stack;
        while( V[p] == V[p + 1] )
        {
            ++p;
            ++cnt;
        }

       // out << cnt << "\n";

        Diff = V[p + 1] - V[p];

        aux = cnt;
        Pow = 1;
        while( aux && Diff )
        {
            Pow *= 4;
            aux /= 4;
            --Diff;
        }

        if( cnt % Pow != 0 )
            ok = 0;
        Stack = cnt / Pow;
        ++p;
    }


    nr = 0;
    cnt = N - p + Stack;
    aux = cnt;
    Pow = 1;

    //printf("%d", cnt);
    while( aux > 1 )
    {
        Pow *= 4;
        aux /= 4;
        if( aux >= 1 )
           ++nr;
    }

    if( cnt % Pow != 0 )
    {
        ok = 0;
    }

    if( !ok )
        out << V[N - 1] + nr + 1;
    else
        out << V[N - 1] + nr ;

    return 0;
}
