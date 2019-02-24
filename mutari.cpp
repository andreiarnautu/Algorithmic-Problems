#include <cstdio>
#define Dim 100003

using namespace std;

FILE *fin=freopen("mutari.in","r",stdin);
FILE *fout=freopen("mutari.out","w",stdout);

int Mutari[10 * Dim] , nr;
int V[Dim], N;


void Solve()
{
    int Last = N, c;

    while( Last > 1 )
    {
        for(int i = Last - 1 ; i > 0 ; --i )
        {
            if( V[i + 1] % V[i] == 0 )
            {
                c = V[i + 1] / V[i];
                if( Last == i + 1 )
                {
                    --Last;
                    for(int j = 1 ; j <= c ; ++j )
                        Mutari[++nr] = i;
                }

                else
                {
                    V[i + 1] = V[i];
                    for(int j = 1 ; j < c ; ++j )
                        Mutari[++nr] = i;
                }
            }

            else
            {
                c = V[i + 1] / V[i];
                for(int j = 1 ; j <= c ; ++j )
                    Mutari[++nr] = i;
                V[i + 1] -= c * V[i];
            }
        }
    }

    printf("%d\n" , nr);
    for(int i = 1 ; i <= nr ; ++i )
        printf("%d\n", Mutari[i]);
}

int main()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);

    for(int i = 2 ; i <= N ; ++i )
        if( V[i] % V[1] != 0 )
        {
            printf("-1");
            return 0;
        }

    Solve();
}
