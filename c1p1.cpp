// Arnautu Andrei 2014
#include <cstdio>
#define Dim 50003
using namespace std;
FILE *fin=freopen("progresie.in","r",stdin);
FILE *fout=freopen("progresie.out","w",stdout);
int N, V[Dim], Min = 2000000003, Max, Second = 2000000003, R, Frequency[Dim], Difmax;

void Read()
{

    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &V[i]);
        if( V[i] > Max )
            Max = V[i];
        if( V[i] < Min )
            Min = V[i];
        if( i > 1 && V[i] - V[i - 1] > Difmax )
            Difmax = V[i] - V[i - 1];
        if( i > 1 && V[i - 1] - V[i] > Difmax )
            Difmax = V[i - 1] - V[i];
    }
}

void Solve()
{
    for(int i = 1 ; i <= N ; ++i )
    {
        if( V[i] < Second && V[i] != Min )
            Second = V[i];
        V[i] -= Min;
    }
    if( Second == 2000000003 )
    {
        printf("0 %d", Difmax);
        return ;
    }
    R = Second - Min;
    for(int i = 1 ; i <= N ; ++i )
    {
        if( V[i] % R != 0 )
        {
            printf("0 %d", Difmax);
            return;
        }
        else if( V[i] / R >= N )
        {
            printf("0 %d", Difmax);
            return;
        }
        else
            ++Frequency[ V[i] / R ];
    }
    for(int i = 0 ; i < N ; ++i )
        if( Frequency[i] != 1 )
        {
            printf("0 %d", Difmax);
            return;
        }
    printf("%d %d", Min , R);
}

int main()
{
    Read();
    Solve();
    return 0;
}
