#include <cstdio>
using namespace std;
FILE *fin=freopen("jocprim.in","r",stdin);
FILE *fout=freopen("jocprim.out","w",stdout);
int N, V[30003];
int Ciur[300003], Prime[1000], Nr, Last;

void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
}

void ciur()
{
    int i, j;
    Prime[1] = 2;
    Nr = 1;
    for(i = 3 ; i * i <= 300000 ; i += 2 )
        if( !Ciur[i] )
        {
            Prime[++Nr] = i;
            if( Nr >= 300 )
                return;
            for(j = i * i ; j <= 300000 ; j += 2 * i )
                Ciur[j] = 1;
        }
}

void Solve()
{
    int Turn = 0, Start, End, Pos = 0, Sum = 0;
    Prime[0] = 1;
    int ok = 1;
    do
    {
        ++Pos;
        Turn = (Turn + 1) % 2;
        Start = Last + Prime[Pos] - Prime[Pos - 1] + 1;
        End = Start + Prime[Pos] - 1;
        if( End >= N )
        {
            ok = 0;
            for(int i = Start ; i <= N ; ++i )
                Sum += V[i];
            if( Turn == 0 )
                printf("2 ");
            else
                printf("1 ");
            printf("%d", Sum);
        }
        else if( End + Prime[Pos + 1] - Prime[Pos] + 1 > N )
        {
            ok = 0;
            for(int i = Start ; i <= End ; ++i )
                Sum += V[i];
            if( Turn == 0 )
                printf("2 ");
            else
                printf("1 ");
            printf("%d", Sum);
            return;
        }
    //    printf("%d %d\n", Start, End);
        Last = End;
    }while(ok);
}

int main()
{
    Read();
    ciur();
   // for(int i = 1 ; i <= Nr ; ++i )
    //    printf("%d ",Prime[i]);
    Solve();
    return 0;
}
